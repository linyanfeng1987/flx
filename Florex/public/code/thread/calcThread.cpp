#include "calcThread.h"
#include "db/dataStruct/processTaskInfoStruct.h"
#include "db/dataStruct/threadStatusStruct.h"
#include "db/dataStruct/curRateStruct.h"
#include "db/dataStruct/calcRateStruct.h"

#include "table/Table.h"
#include "db/DbObj.h"
#include "PubFun.h"
#include "tools/FunctionLog.h"

#include "process/obj/average/averageAnalysis.h"
#include "process/obj/continue/continueAnalysis.h"

const int timeStep = 3600;
const string CCalcThread::logTag = "threadRun";

CCalcThread::CCalcThread( PThreadInfo _threadInfo ):CBaseThread(_threadInfo)
{
	logInfo = newLogInfo(logTag);	
}

CCalcThread::~CCalcThread()
{
	log.debug(logInfo, PubFun::strFormat("CCalcThread end, %d\n", this));
}

void CCalcThread::runInThread( const char* argv )
{
	init();
	while (true)
	{
		rangTaskList();
	}
}

void CCalcThread::init()
{
	// 从数据库中加载未执行的任务
	int processId = threadInfo->getRowData()->getIntValue(CThreadStatusStruct::key_processId);
	getTaskSql = CProcessTaskInfoStruct::instence()->getSelectSql(PubFun::strFormat("%s=%d and %s=%d", 
		CProcessTaskInfoStruct::key_processId.c_str(), processId,
		CProcessTaskInfoStruct::key_status.c_str(), 0));
	process = getProcess(threadInfo->getRowData());
}

PCalcProcess CCalcThread::getProcess( PRow taskInfo )
{
	PRateInfo rateInfo = newRateInfo();
	rateInfo->rateName = taskInfo->getStringValue(CThreadStatusStruct::key_rateName);
	PCalcProcess process = newCalcProcess(rateInfo);
	string processTypeName = taskInfo->getStringValue(CThreadStatusStruct::key_processTypeName);
	if (-1 == processTypeName.find(processType_baseCalc))
	{
		if (-1 != processTypeName.find(processType_average))
		{
			PAverageAnalysis averageAnalysis = newAverageAnalysis(rateInfo);
			process->addAnalysis(processType_average, averageAnalysis);
		}
		else if (-1 != processTypeName.find(processType_continue))
		{
			PContinueAnalysis continueAnalysis = newContinueAnalysis(rateInfo);
			process->addAnalysis(processType_continue, continueAnalysis);
		}
	}

	return process;
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

void CCalcThread::runTask( PRow taskInfoRow )
{
	try
	{
		CFunctionLog funLog(logInfo, __FUNCTION__, __LINE__);
		string rateName = taskInfoRow->getStringValue(CProcessTaskInfoStruct::key_rate);
		string startTime = taskInfoRow->getStringValue(CProcessTaskInfoStruct::key_startTime);
		string endTime = taskInfoRow->getStringValue(CProcessTaskInfoStruct::key_endTime);
		string rateType = taskInfoRow->getStringValue(CProcessTaskInfoStruct::key_rateType);
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

		completeTask(taskInfoRow);
	}
	catch (CStrException& e)
	{
		log.error(logInfo, string("runInThread 失败！msg:").append(e.what()));
	}
}

int CCalcThread::completeTask(PRow taskInfoRow)
{
	try
	{
		taskInfoRow->setStringValue(CProcessTaskInfoStruct::key_status, string("3"));
		taskInfoRow->save();

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




