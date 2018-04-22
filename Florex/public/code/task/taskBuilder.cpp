#include "taskBuilder.h"
#include "ConstDef.h"
#include "db/dataObj/processTaskInfo.h"

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
		for (auto& iter : gData.porcessConfigs)
		{
			runOneProcessType(iter.second);
		}
		::Sleep(1000);
	}
}

void CTaskBuilder::runOneProcessType( CProcessInfo& porcessConfig )
{
	auto iter = gData.processRates.find(porcessConfig.rate);
	if (iter != gData.processRates.end())
	{
		list<string> rates =iter->second;
		for (string rate : rates)
		{
			runOneRate(rate, porcessConfig);
		}
	}
}

void CTaskBuilder::runOneRate( string rateName, CProcessInfo& porcessConfig )
{
	time_t rateLastTime = getRateLastTime(rateName);
	string porcessName = porcessConfig.getProcessName();
	time_t processLastTime = getProcessLastTime(porcessName);
	time_t timeStep = rateLastTime - processLastTime;
	if (timeStep > porcessConfig.timeStep )
	{
		CProcessTaskInfo taskInfo;
		taskInfo.setRate(rateName);
		taskInfo.setTaskId( PubFun::get14CurTimeString() + "_" + PubFun::intToString(rand()));
		taskInfo.setprocessInfo(porcessConfig);
		gData.addprocessInfo(taskInfo);
	}
}


void CTaskBuilder::reLoadTask()
{
	taskConfigs.clear();
	string strSqlFormat = "select * from %s;";
	string strTableName = coreDbName + ".";
	strTableName += "processtask";

	char chSql[2048] = {0};
	memset(chSql, 0, sizeof(chSql));
	sprintf_s(chSql, strSqlFormat.c_str(), strTableName.c_str());
	CTable resTable;
	db.SelectData(chSql, resTable);

	CTable::iterator iter = resTable.begin();
	for (; iter != resTable.end(); iter++)
	{
		CProcessTaskInfo processTask;
		processTask.load(&(iter->second));
		processTask.getTaskId();
		taskConfigs.insert(make_pair(processTask.getTaskId(), processTask));
	}
}

time_t CTaskBuilder::getRateLastTime( string rateName )
{
	string strSqlFormat = "select * from %s order by curTime desc, curMsec desc limit 1;";
	string strTableName = florexDbName + ".";
	strTableName += "currency_pair_";
	strTableName += rateName;
	time_t lastTime = 0;

	char chSql[2048] = {0};
	memset(chSql, 0, sizeof(chSql));
	sprintf_s(chSql, strSqlFormat.c_str(), strTableName.c_str());
	CTable resTable;
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
	string strTableName = florexDbName + ".";
	strTableName += "processstatus";
	time_t lastTime = 0;

	char chSql[2048] = {0};
	memset(chSql, 0, sizeof(chSql));
	sprintf_s(chSql, strSqlFormat.c_str(), strTableName.c_str());
	CTable resTable;
	db.SelectData(chSql, resTable);

	CTable::iterator iter = resTable.begin();
	if (iter != resTable.end())
	{
		//获取第一行的值
		lastTime = PubFun::stringToInt(iter->second.getValue("curTime"));
	}
	return lastTime;
}



