#include "taskBuilder.h"
#include "ConstDef.h"
#include "db/dataObj/processTask.h"


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
	for (auto& iter : gData.porcessConfigs)
	{
		runOneProcess(iter.second);
	}
}

void CTaskBuilder::runOneProcess( CProcessConfig& porcessConfig )
{
	for (auto rate : porcessConfig.rates)
	{
		time_t rateLastTime = getRateLastTime(rate.second);
		string porcessName = porcessConfig.processTypeName + "_" + rate.first;
		time_t processLastTime = getProcessLastTime(porcessName);
		time_t timeStep = rateLastTime - processLastTime;
		if (timeStep > porcessConfig.minTimeStep )
		{
			//create task
			CProcessTask task;
			task.setTaskId( PubFun::get14CurTimeString() + "_" + PubFun::intToString(rand()));
		}
	}
}


void CTaskBuilder::reLoadTask()
{
	tasks.clear();
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
		CProcessTask processTask;
		processTask.load(&(iter->second));
		processTask.getTaskId();
		tasks.insert(make_pair(processTask.getTaskId(), processTask));
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


