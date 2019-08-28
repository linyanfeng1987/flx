#include "taskBuilder.h"
#include "db/DbFunc.h"

//CGlobalData& CTaskBuilder::gData = CGlobalData::instance();

// 思路整理
// 获取一个配置的process信息，获取这个process对应的rate或rates
// 获取一个rate的最新报价
// 根据porcess的基础信息，在porcessStatus表中获取历史的最新处理时间，根据这个时间，以及step判断是否需要新建task
// 若要建立新的task则讲任务放入porcessTask表中
// 布置任务后重写processStatus表的时间，防止重新布置任务

const string CTaskBuilder::logTag = "taskBuilder";

CTaskBuilder::CTaskBuilder() :log(CLogObj::instance()), gData(CGlobalData::instance())
{
	logInfo = newLogInfo(logTag);
}

CTaskBuilder::~CTaskBuilder()
{
	int a = 0;
	a++;
	CDbObj::release();
}

void CTaskBuilder::run()
{
	for (auto& rateIter : gData.processRates)
	{
		buildThreadByRate(rateIter.first, rateIter.second);
	}

	bool hasTask = false;
	while (true)
	{
		hasTask = buildByThread();
		if (!hasTask)
		{
			::Sleep(longSleepTime);
			//::Sleep(shortSleepTime);
		}
	}
}

void CTaskBuilder::buildThreadByRate(string rateName, list<string>& processTypeNames)
{
	for (string& processTypeName : processTypeNames)
	{
		CProcessType* pPorcessType = gData.getProcessType(processTypeName);
		if (pPorcessType != nullptr)
		{
			buildThreadByType(rateName, *pPorcessType);
		}
	}
}

void CTaskBuilder::buildThreadByType(string rateName, CProcessType& processType)
{
	//string tableName = PubFun::strFormat("%s.currency_pair_%s", florexDbName.c_str(), rateName.c_str());
	string porcessTypeName = processType.getProcessName();
	PRow threadStatusInfo = CDbFunc::getThreadStatusLine(rateName, porcessTypeName);
	int lastThreadId = CDbFunc::getThreadLastId();
	//获取第一行的值
	time_t processBuildLastTime = 0;
	time_t taskBuildEndTime = 0;
	if (nullptr == threadStatusInfo)
	{
		// 获取rate的起始时间代替
		processBuildLastTime = getRateStartTime(rateName);
		log.debug(logInfo, PubFun::strFormat("get buildLastTime from rateStartTime %ld", processBuildLastTime));

		auto tableSt = CThreadStatusStruct::instence();
		threadStatusInfo = newRow(tableSt);
		threadStatusInfo->setIntValue(CThreadStatusStruct::key_threadId, ++(lastThreadId));
		threadStatusInfo->setStringValue(CThreadStatusStruct::key_rateName, rateName);
		threadStatusInfo->setStringValue(CThreadStatusStruct::key_threadTypeName, porcessTypeName);
		threadStatusInfo->setIntValue(CThreadStatusStruct::key_threadStatus, 0);
		threadStatusInfo->setTimeValue(CThreadStatusStruct::key_stepTime, processType.timeStep);
		threadStatusInfo->setTimeValue(CThreadStatusStruct::key_buildTaskLastTime, processBuildLastTime);
		threadStatusInfo->setTimeValue(CThreadStatusStruct::key_completeTaskLastTime, 0);

		threadStatusInfo->save();
	}
}

bool CTaskBuilder::buildByThread()
{
	bool hasTask = false;
	list<PThreadInfo> threadInfos;
	CDbFunc::getThreadInfos(threadInfos);

	for (PThreadInfo threadInfo : threadInfos)
	{
		//获取第一行的值
		time_t processBuildLastTime = 0;
		time_t taskBuildEndTime = 0;
		PRow threadInfoRow = threadInfo->getRowData();
		string rateName = threadInfoRow->getStringValue(CThreadStatusStruct::key_rateName);
		int threadId = threadInfoRow->getIntValue(CThreadStatusStruct::key_threadId);

		processBuildLastTime = threadInfoRow->getTimeValue(CThreadStatusStruct::key_buildTaskLastTime);
		log.debug(logInfo, PubFun::strFormat("get buildLastTime from threadStatusInfo %ld", processBuildLastTime));
		// 获取终止时间
		string formartEndTime = threadInfoRow->getStringValue(CThreadStatusStruct::key_buildTaskEndTimeDesc);
		log.debug(logInfo, PubFun::strFormat("get buildTaskEndTimeDesc from threadStatusInfo %%s", formartEndTime.c_str()));
		taskBuildEndTime = PubFun::formartTimeToDatetime(formartEndTime.c_str());

		if (0 == processBuildLastTime || -1 == processBuildLastTime)
		{
			// 通过外部配置的起始时间，构造processBuildLastTime
			string formatStartTime = threadInfoRow->getStringValue(CThreadStatusStruct::key_buildTaskStartTimeDesc);
			processBuildLastTime = PubFun::formartTimeToDatetime(formatStartTime.c_str());
			if (0 == processBuildLastTime || -1 == processBuildLastTime)
			{
				//  通过rate起始时间构造
				processBuildLastTime = getRateStartTime(rateName);
			}
			threadInfoRow->setTimeValue(CThreadStatusStruct::key_buildTaskLastTime, processBuildLastTime);
			threadInfoRow->setStringValue(CThreadStatusStruct::key_buildTaskLastTimeDesc, PubFun::getTimeFormat(processBuildLastTime));
			threadInfoRow->save();
		}

		if (0 == taskBuildEndTime || -1 == taskBuildEndTime)
		{
			// 使用rate的时间替换
			taskBuildEndTime = getRateLastTime(rateName);
			log.debug(logInfo, PubFun::strFormat("get rateLastTime by rate:%s value:%ld", rateName.c_str(), taskBuildEndTime));
		}

		PProcessTaskInfoStruct taskInfoStruct = CProcessTaskInfoStruct::instence();
		time_t timeStep = taskBuildEndTime - processBuildLastTime;
		while (processBuildLastTime + gHisCalcStepTime < taskBuildEndTime)
		{
			hasTask = true;
			PRow taskInfo = newRow(taskInfoStruct);
			taskInfo->setStringValue(CProcessTaskInfoStruct::key_rate, rateName);
			taskInfo->setStringValue(CProcessTaskInfoStruct::key_rateType, rateName);
			taskInfo->setStringValue(CProcessTaskInfoStruct::key_taskId, PubFun::get14CurTimeString() + "_" + PubFun::intToString(rand()));
			taskInfo->setTimeValue(CProcessTaskInfoStruct::key_startTime, processBuildLastTime);
			taskInfo->setStringValue(CProcessTaskInfoStruct::key_startTimeDesc, PubFun::getTimeFormat(processBuildLastTime));
			processBuildLastTime += gHisCalcStepTime;
			taskInfo->setTimeValue(CProcessTaskInfoStruct::key_endTime, processBuildLastTime);
			taskInfo->setStringValue(CProcessTaskInfoStruct::key_endTimeDesc, PubFun::getTimeFormat(processBuildLastTime));
			taskInfo->setIntValue(CProcessTaskInfoStruct::key_threadId, threadId);
			//string strParam = PubFun::strFormat("timeStep=%d", processType.timeStep);
			taskInfo->setStringValue(CProcessTaskInfoStruct::key_paramter, string(""));
			taskInfo->setIntValue(CProcessTaskInfoStruct::key_status, taskStatus_def);
			taskInfo->save();

			threadInfoRow->setTimeValue(CThreadStatusStruct::key_buildTaskLastTime, processBuildLastTime);
			threadInfoRow->setStringValue(CThreadStatusStruct::key_buildTaskLastTimeDesc, PubFun::getTimeFormat(processBuildLastTime));
			//threadStatusInfo->setStringValue(CThreadStatusStruct::key_buildTaskLastTimeDesc, PubFun::getTimeFormat(endTime));
			threadInfoRow->save();
		}
	}
	return hasTask;
}

/*
bool CTaskBuilder::reloadTaskList_delete()
{
	taskConfigs.clear();
	bool hasData = false;
	// 从数据库中加载未执行的任务
	CProcessTaskInfoStruct* pTaskInfo = CProcessTaskInfoStruct::instence();
	string sql = pTaskInfo->getSelectSql("status = 0");
	PTable table(pTaskInfo);
	db.SelectData(sql.c_str(), table)111;

	for(auto it : table)
	{
		it.second->setStringValue(CProcessTaskInfoStruct::key_status, taskStatus_run);
		db.ExecuteSql(it.second->getUpdateSql().c_str());
		gData.addProcessTaskInfo(*(it.second));
		taskConfigs.insert(make_pair(it.second->getStringValue(CProcessTaskInfoStruct::key_taskId), *(it.second)));

		hasData = true;
	}
	return hasData;
}*/

time_t CTaskBuilder::getRateLastTime(string strTableName)
{
	return getRateTime(strTableName, "order by curTime desc, curMsec desc limit 1");
}

time_t CTaskBuilder::getRateStartTime(string strTableName)
{
	return getRateTime(strTableName, "order by curTime, curMsec limit 1");
}

time_t CTaskBuilder::getRateTime(string strTableName, string orderSql)
{
	string strSqlFormat = "select * from %s %s;";
	time_t lastTime = -1;

	char chSql[2048] = { 0 };
	memset(chSql, 0, sizeof(chSql));
	PCurRateStruct rateStruct = newCurRateStruct(strTableName);
	sprintf_s(chSql, strSqlFormat.c_str(), rateStruct->tableName.c_str(), orderSql.c_str());
	PTable resTable = newTable(rateStruct);

	CDbObj::instance().selectData(chSql, resTable);
	auto iter = resTable->begin();
	if (iter != resTable->end())
	{
		//获取第一行的值
		lastTime = PubFun::stringToInt(iter->second->getValue(string("curTime")));
	}

	return lastTime;
}