#include "taskBuilder.h"
#include "ConstDef.h"
#include "db/dataStruct/processTaskInfoStruct.h"
#include "db/dataStruct/curRateStruct.h"
#include "db/dataStruct/processStatusStruct.h"

CDbObj& CTaskBuilder::db = CDbObj::instance();
CGlobalData& CTaskBuilder::gData = CGlobalData::instance();

// 思路整理
// 获取一个配置的process信息，获取这个process对应的rate或rates
// 获取一个rate的最新报价
// 根据porcess的基础信息，在porcessStatus表中获取历史的最新处理时间，根据这个时间，以及step判断是否需要新建task
// 若要建立新的task则讲任务放入porcessTask表中
// 布置任务后重写processStatus表的时间，防止重新布置任务
CTaskBuilder::CTaskBuilder()
{
}

CTaskBuilder::~CTaskBuilder()
{
}

void CTaskBuilder::run()
{
	while (true)
	{
		for (auto& rateIter : gData.processRates)
		{
			runOneRate(rateIter.first, rateIter.second);
		}
		::Sleep(1000);
	}
}

void CTaskBuilder::runOneRate( string rateName, list<string>& processTypeNames )
{
	for(string& processTypeName :processTypeNames)
	{
		CProcessType* pPorcessType = gData.getProcessType(processTypeName);
		if(pPorcessType != nullptr)
		{
			runOneProcessType(rateName, *pPorcessType);
		}	
	}
}

void CTaskBuilder::runOneProcessType(string rateName, CProcessType& processType )
{
	time_t rateLastTime = getRateLastTime(rateName);
	string porcessName = processType.getProcessName();
	time_t processLastTime = getProcessLastTime(porcessName);
	if(0 == processLastTime)
	{
		// 说明未存储对应数据, 获取rate的起始时间代替
		processLastTime = getRateStartTime(rateName);
	}
	time_t timeStep = rateLastTime - processLastTime;
	if (timeStep > processType.timeStep )
	{
		// 这里属性缺少
		CRow taskInfo(CProcessTaskInfoStruct::instence());
		taskInfo.setStringValue(CProcessTaskInfoStruct::key_rate, rateName);
		taskInfo.setStringValue(CProcessTaskInfoStruct::key_rateType, rateName);
		taskInfo.setStringValue( CProcessTaskInfoStruct::key_taskId, PubFun::get14CurTimeString() + "_" + PubFun::intToString(rand()));
		taskInfo.setTimeValue(CProcessTaskInfoStruct::key_startTime, processLastTime);
		time_t endTime = processLastTime + timeStep/processType.timeStep * processType.timeStep;
		taskInfo.setTimeValue(CProcessTaskInfoStruct::key_endTime, endTime);
		taskInfo.setStringValue(CProcessTaskInfoStruct::key_processTypeName, processType.getType());
		taskInfo.setStringValue(CProcessTaskInfoStruct::key_paramter, "");
		taskInfo.setStringValue(CProcessTaskInfoStruct::key_status, "0");
		gData.addProcessTaskInfo(taskInfo);
	}
}


bool CTaskBuilder::reloadTaskList()
{
	taskConfigs.clear();
	bool hasData = false;
	// 从数据库中加载未执行的任务
	CProcessTaskInfoStruct* pTaskInfo = CProcessTaskInfoStruct::instence();
	string sql = pTaskInfo->getSelectSql("status = 0");
	CTable table(pTaskInfo);
	db.SelectData(sql.c_str(), table);

	for(auto it : table)
	{
		it.second.setStringValue(CProcessTaskInfoStruct::key_status, "1");
		db.ExecuteSql(it.second.getUpdateSql().c_str());
		gData.addProcessTaskInfo(it.second);
		taskConfigs.insert(make_pair(it.second.getStringValue(CProcessTaskInfoStruct::key_taskId), it.second));

		hasData = true;
	}
	return hasData;
}

time_t CTaskBuilder::getRateLastTime( string rateName )
{
	return getRateTime(rateName, "order by curTime desc, curMsec desc limit 1");
}

time_t CTaskBuilder::getRateStartTime( string rateName )
{
	return getRateTime(rateName, "order by curTime, curMsec limit 1");
}

time_t CTaskBuilder::getRateTime( string rateName, string orderSql )
{
	string strSqlFormat = "select * from %s %s;";
	string strTableName = florexDbName + ".";
	strTableName.append("currency_pair_");
	strTableName.append(rateName);
	time_t lastTime = 0;

	char chSql[2048] = {0};
	memset(chSql, 0, sizeof(chSql));
	sprintf_s(chSql, strSqlFormat.c_str(), strTableName.c_str(), orderSql.c_str());
	CCurRateStruct rateStruct;
	CTable resTable(&rateStruct);
	db.SelectData(chSql, resTable);

	CTable::iterator iter = resTable.begin();
	if (iter != resTable.end())
	{
		//获取第一行的值
		lastTime = PubFun::stringToInt(iter->second.getValue("curTime"));
	}
	return lastTime;
}



time_t CTaskBuilder::getProcessLastTime( string processName )
{
	string strSqlFormat = "select * from %s order by lastTime desc limit 1;";
	string strTableName = coreDbName + ".";
	strTableName += "processstatus";
	time_t lastTime = 0;

	char chSql[2048] = {0};
	memset(chSql, 0, sizeof(chSql));
	sprintf_s(chSql, strSqlFormat.c_str(), strTableName.c_str());
	CProcessStatusStruct processStatusStruct;
	CTable resTable(&processStatusStruct);
	db.SelectData(chSql, resTable);

	CTable::iterator iter = resTable.begin();
	if (iter != resTable.end())
	{
		//获取第一行的值
		lastTime = PubFun::stringToInt(iter->second.getValue("curTime"));
	}
	return lastTime;
}




