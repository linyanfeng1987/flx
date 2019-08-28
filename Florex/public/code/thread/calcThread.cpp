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
#include "data/globalData.h"

const int timeStep = 3600;
const string CCalcThread::logTag = "calcThread";

CCalcThread::CCalcThread(PThreadInfo _threadInfo) :CBaseThread(_threadInfo)
{
	logInfo = newLogInfo(logTag);
	needBaseCalc = false;
}

CCalcThread::~CCalcThread()
{
	log.debug(logInfo, PubFun::strFormat("CCalcThread end, %d\n", this));
}

bool CCalcThread::init()
{
	bool bRes = false;
	// 从数据库中加载未执行的任务
	int processId = threadInfo->getRowData()->getIntValue(CThreadStatusStruct::key_threadId);
	auto taskTableStruct = CProcessTaskInfoStruct::instence();
	string updateSql = PubFun::strFormat("update %s set %s=%d where %s=%d and %s=%d;",
		taskTableStruct->tableName.c_str(),
		CProcessTaskInfoStruct::key_status.c_str(), taskStatus_def,
		CProcessTaskInfoStruct::key_threadId.c_str(), processId,
		CProcessTaskInfoStruct::key_status.c_str(), taskStatus_run);
	CDbObj::instance().executeSql(updateSql.c_str());

	// 拼好查询语句
	getTaskSql = taskTableStruct->getSelectSqlLimit1(
		PubFun::strFormat("%s=%d and %s=%d",
			CProcessTaskInfoStruct::key_threadId.c_str(), processId,
			CProcessTaskInfoStruct::key_status.c_str(), taskStatus_def),
		PubFun::strFormat("order by %s",
			CProcessTaskInfoStruct::key_startTime.c_str()));

	string processTypeName = threadInfo->getRowData()->getStringValue(CThreadStatusStruct::key_threadTypeName);
	processCfgInfo = CGlobalData::instance().getProcessInfo(processTypeName);
	if (nullptr != processCfgInfo)
	{
		string rateName = threadInfo->getRowData()->getStringValue(CThreadStatusStruct::key_rateName);
		process = getProcess(processCfgInfo, rateName);
		bRes = true;
	}
	else
	{
		log.error(PubFun::strFormat("错误的process名称%s", processTypeName.c_str()));
	}
	return bRes;
}

// PCalcProcess CCalcThread::getProcess( PRow taskInfo )
// {
// 	PRateInfo rateInfo = newRateInfo();
// 	rateInfo->rateName = taskInfo->getStringValue(CThreadStatusStruct::key_rateName);
// 	PCalcProcess process = newCalcProcess(rateInfo);
// 	string processTypeName = taskInfo->getStringValue(CThreadStatusStruct::key_threadTypeName);
// 	if (-1 != processTypeName.find(processType_baseCalc))
// 	{
// 		needBaseCalc = true;
// 	}
// 	if (-1 != processTypeName.find(processType_average))
// 	{
// 		PAverageAnalysis averageAnalysis = newAverageAnalysis(rateInfo);
// 		process->addAnalysis(processType_average, averageAnalysis);
// 	}
// 	if (-1 != processTypeName.find(processType_continue))
// 	{
// 		PContinueAnalysis continueAnalysis = newContinueAnalysis(rateInfo);
// 		process->addAnalysis(processType_continue, continueAnalysis);
// 	}
//
// 	return process;
// }

PCalcProcess CCalcThread::getProcess(PProcessCfgInfo processInfo, string& rateName)
{
	PRateInfo rateInfo = newRateInfo();
	rateInfo->rateName = rateName;

	PCalcProcess process = newCalcProcess(processInfo, rateInfo);

	PAnalysisInfo analysisInfo = processInfo->analysisInfo;
	if (analysisInfo->analysisType == processType_average)
	{
		PAverageAnalysis averageAnalysis = newAverageAnalysis(analysisInfo, rateInfo);
		process->addAnalysis(processType_average, averageAnalysis);
	}

	if (analysisInfo->analysisType == processType_continue)
	{
		PContinueAnalysis continueAnalysis = newContinueAnalysis(analysisInfo, rateInfo);
		process->addAnalysis(processType_continue, continueAnalysis);
	}

	return process;
}

void CCalcThread::runInThread(const char* argv)
{
	if (init())
	{
		while (true)
		{
			rangTaskList();
		}
	}
}

void CCalcThread::rangTaskList()
{
	// 执行任务
	static bool isFirstRun = true;
	PRow task = getOneTask();
	if (nullptr != task)
	{
		isFirstRun = false;
		//string param = taskInfoRow->getStringValue(CProcessTaskInfoStruct::key_paramter);
		runTask(task);
	}
	else
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

PRow CCalcThread::getOneTask()
{
	PRow row = nullptr;
	try {
		row = CDbObj::instance().selectOneData(getTaskSql.c_str(), CProcessTaskInfoStruct::instence());
		if (nullptr != row)
		{
			row->setIntValue(CProcessTaskInfoStruct::key_status, taskStatus_run);
			row->save();
		}
	}
	catch (CStrException& e)
	{
		log.error(logInfo, string("reloadTaskList 失败！msg:").append(e.what()));
	}

	return row;
}

void CCalcThread::runTask(PRow taskInfoRow)
{
	try
	{
		CFunctionLog funLog(logInfo, __FUNCTION__, __LINE__);
		string rateName = taskInfoRow->getStringValue(CProcessTaskInfoStruct::key_rate);
		time_t startTime = taskInfoRow->getTimeValue(CProcessTaskInfoStruct::key_startTime);
		time_t endTime = taskInfoRow->getTimeValue(CProcessTaskInfoStruct::key_endTime);
		string rateType = taskInfoRow->getStringValue(CProcessTaskInfoStruct::key_rateType);
		string processTypeName = threadInfo->getRowData()->getStringValue(CThreadStatusStruct::key_threadTypeName);
		log.debug(logInfo, PubFun::strFormat("run task rateName:%s, processTypeName:%s, startTime,%s, endTime,%s",
			rateName.c_str(),
			processTypeName.c_str(),
			PubFun::getTimeFormat(startTime).c_str(),
			PubFun::getTimeFormat(endTime).c_str()));

		string logName = rateName + "_" + processTypeName;

		map<time_t, time_t> resValueMap;
		PubFun::buildValueList(startTime, endTime, timeStep, resValueMap);

		if (needBaseCalc)
		{
			withBaseCalc(resValueMap, rateName);
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
		taskInfoRow->setIntValue(CProcessTaskInfoStruct::key_status, taskStatus_complate);
		taskInfoRow->save();

		time_t completeTime = taskInfoRow->getTimeValue(CProcessTaskInfoStruct::key_startTime);
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

void CCalcThread::withBaseCalc(map<time_t, time_t>& resValueMap, string& rateName)
{
	PCurRateStruct rateStruct = newCurRateStruct(rateName);
	PTable rateTable = newTable(rateStruct);
	for (auto iter : resValueMap)
	{
		// 这里sql的时间必须是半开半闭区间，否则会有数据重复
		string condition = "";
		condition.append(CCurRateStruct::curTime).append(">=").append(PubFun::timetToString(iter.first));
		condition.append(" and ");
		condition.append(CCurRateStruct::curTime).append("<").append(PubFun::timetToString(iter.second));
		string sql = rateStruct->getSelectSql(condition, PubFun::strFormat("order by %s,%s", CCurRateStruct::curTime.c_str(), CCurRateStruct::curMsec.c_str()));

		CDbObj::instance().selectData(sql.c_str(), rateTable);
		process->calc(rateTable);
	}
}

void CCalcThread::calcProcess(map<time_t, time_t>& resValueMap, string& rateName)
{
	PCalcRateStruct rateStruct = newCalcRateStruct(rateName);
	PTable rateTable = newTable(rateStruct);
	for (auto iter : resValueMap)
	{
		// 这里sql的时间必须是半开半闭区间，否则会有数据重复
		string condition = "";
		condition.append(CCalcRateStruct::curTime).append(">=").append(PubFun::timetToString(iter.first));
		condition.append(" and ");
		condition.append(CCalcRateStruct::curTime).append("<").append(PubFun::timetToString(iter.second));
		string sql = rateStruct->getSelectSql(condition, PubFun::strFormat("order by %s", CCalcRateStruct::curTime.c_str()));

		CDbObj::instance().selectData(sql.c_str(), rateTable);

		list<PRateValue> values;
		PRow row = nullptr;
		for (auto rowPair : *rateTable)
		{
			row = rowPair.second;
			double curDTime = row->getDoubleValue(CCalcRateStruct::curTime);
			double curValue = row->getDoubleValue(CCalcRateStruct::curValue);
			string timeDesc = row->getStringValue(CCalcRateStruct::timeFormat);

			PRateValue rateValue = newRateValueP3(curDTime, curValue, timeDesc);
			values.push_back(rateValue);
		}

		process->calc(values);
	}
}