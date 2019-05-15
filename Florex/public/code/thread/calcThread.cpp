#include "calcThread.h"
#include "db/dataStruct/processTaskInfoStruct.h"
#include "db/dataStruct/threadStatusStruct.h"
#include "db/dataStruct/curRateStruct.h"
#include "db/dataStruct/calcRateStruct.h"

#include "table/Table.h"
#include "db/DbObj.h"
#include "PubFun.h"
#include "tools/FunctionLog.h"

const int timeStep = 3600;
const string CCalcThread::logTag = "processTask";

CCalcThread::CCalcThread( PThreadInfo _threadInfo ):CBaseThread(_threadInfo)
{
	logInfo = newLogInfo(logTag);
	log.debug(logInfo, PubFun::strFormat("CCalcThread build, %d\n", this));
	//isBaseCale = _process->isBaseCalc();

	// 从数据库中加载未执行的任务
	int processId = threadInfo->getRowData()->getIntValue(CThreadStatusStruct::key_processId);
	getTaskSql = CProcessTaskInfoStruct::instence()->getSelectSql(PubFun::strFormat("%s=%d and %s=%d", 
		CProcessTaskInfoStruct::key_processId.c_str(), processId,
		CProcessTaskInfoStruct::key_status.c_str(), 0));
}

CCalcThread::~CCalcThread()
{
	log.debug(logInfo, PubFun::strFormat("CCalcThread end, %d\n", this));
}

int CCalcThread::completeTask()
{
	try
	{
		curTaskStatus->setStringValue(CProcessTaskInfoStruct::key_status, string("3"));
		curTaskStatus->save();

		time_t completeTime = threadInfo->getRowData()->getTimeValue(CThreadStatusStruct::key_buildTaskLastTime);
		threadInfo->getRowData()->setTimeValue(CThreadStatusStruct::key_completeTaskLastTime, completeTime);
		threadInfo->getRowData()->setStringValue(CThreadStatusStruct::key_completeTaskLastTimeDesc, PubFun::getTimeFormat(completeTime));
		threadInfo->getRowData()->save();
	}
	catch (CStrException& e)
	{
		log.error(logInfo, string("completeTask 失败！msg:").append(e.what()));
	}

	return 0;
}

bool CCalcThread::reloadTaskList()
{
	bool hasData = false;
	try{
		PTable table = newTable(CProcessTaskInfoStruct::instence());
		CDbObj::instance().selectData(getTaskSql.c_str(), table);
		for(auto it : *table)
		{
			it.second->setStringValue(CProcessTaskInfoStruct::key_status, string("1"));
			it.second->save();
			tasks.push_back(it.second);
			hasData = true;
		}
	}
	catch (CStrException& e)
	{
		log.error(logInfo, string("reloadTaskList 失败！msg:").append(e.what()));
	}

	return hasData;
}

void CCalcThread::rangTaskList()
{
	// 执行任务
	static bool isFirstRun = true;
	while(!tasks.empty())
	{
		PRow taskInfoRow = *(tasks.begin());
		//PCalcProcess process = getProcessTask(taskInfoRow);
		tasks.pop_front();
		isFirstRun = false;
		//string param = taskInfoRow->getStringValue(CProcessTaskInfoStruct::key_paramter);
		runTask(taskInfoRow);
	}

	if (!reloadTaskList())
	{
		if (!isFirstRun)
		{
			::Sleep(longSleepTime);
		}
		else
		{
			::Sleep(shortSleepTime);
		}
	}
}

PCalcProcess CCalcThread::getProcessTask( PRow processTaskInfoRow )
{
	PCalcProcess process = getProcess(processTaskInfoRow);
	PRow processStatus = CDbFunc::getProcessStatusLine(processTaskInfoRow->getStringValue(CCalcProcessInfoStruct::key_processTypeName));

	// 	string rateName = processTaskInfo->getStringValue(CCalcProcessInfoStruct::key_rate);
	// 	string processTypeName = processTaskInfo->getStringValue(CCalcProcessInfoStruct::key_processTypeName);
	// 	string taskName = rateName + "_" + processTypeName;

	PThreadInfo processTaskInfo = newThreadInfo(processTaskInfoRow, thread_calc_stauts);
	PCalcProcess task = newCalcProcess(processTaskInfo, processStatus, process);

	return task;
}

void CCalcThread::runInThread( const char* argv )
{
	
}

std::string CCalcThread::getTaskId()
{
	return curTaskStatus->getStringValue(CProcessTaskInfoStruct::key_taskId);
}

void CCalcThread::baseCalc( map<long, long>& resValueMap, string& rateName )
{
	PCurRateStruct rateStruct = newCurRateStruct(rateName);
	PTable rateTable = newTable(rateStruct);
	for (auto iter : resValueMap)
	{
		string condition = "";
		condition.append(CCurRateStruct::curTime).append(">=").append(PubFun::intToString(iter.first));
		condition.append(" and ");
		condition.append(CCurRateStruct::curTime).append("<=").append(PubFun::intToString(iter.second));
		string sql = rateStruct->getSelectSql(condition);

		CDbObj::instance().selectData(sql.c_str(), rateTable);
		process->calc(rateTable);
	}
}

void CCalcThread::calcProcess( map<long, long>& resValueMap, string& rateName )
{
	PCalcRateStruct rateStruct = newCalcRateStruct(rateName);
	PTable rateTable = newTable(rateStruct);
	for (auto iter : resValueMap)
	{
		string condition = "";
		condition.append(CCalcRateStruct::curTime).append(">=").append(PubFun::intToString(iter.first));
		condition.append(" and ");
		condition.append(CCalcRateStruct::curTime).append("<=").append(PubFun::intToString(iter.second));
		string sql = rateStruct->getSelectSql(condition);

		CDbObj::instance().selectData(sql.c_str(), rateTable);

		list<PRateValue> values;
		for (auto rowPair : *rateTable)
		{
			PRow row = rowPair.second;;
			double curDTime = row->getDoubleValue(CCalcRateStruct::curTime);
			double curValue = row->getDoubleValue(CCalcRateStruct::curValue);
			string timeDesc = row->getStringValue(CCalcRateStruct::timeFormat);

			PRateValue rateValue = newRateValueP3(curDTime, curValue, timeDesc);
			values.push_back(rateValue);
		}
		
		process->calc(rateTable);
	}
}

void CCalcThread::runTask( PRow taskInfoRow )
{
	try
	{
		CFunctionLog funLog(logInfo, __FUNCTION__, __LINE__);
		string rateName = curTaskStatus->getStringValue(CProcessTaskInfoStruct::key_rate);
		string startTime = curTaskStatus->getStringValue(CProcessTaskInfoStruct::key_startTime);
		string endTime = curTaskStatus->getStringValue(CProcessTaskInfoStruct::key_endTime);
		string rateType = curTaskStatus->getStringValue(CProcessTaskInfoStruct::key_rateType);
		string processTypeName = threadInfo->getRowData()->getStringValue(CThreadStatusStruct::key_processTypeName);

		string logName = rateName + "_" + processTypeName;

		map<long, long> resValueMap;
		PubFun::buildValueList(PubFun::stringToInt(startTime), PubFun::stringToInt(endTime), timeStep, resValueMap);

		if (process->isBaseCalc())
		{
			baseCalc(resValueMap, rateName);
		}
		else
		{
			calcProcess(resValueMap, rateName);
		}

		completeTask();
	}
	catch (CStrException& e)
	{
		log.error(logInfo, string("runInThread 失败！msg:").append(e.what()));
	}
}
