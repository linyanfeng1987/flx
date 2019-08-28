// DataProcess.cpp : 定义控制台应用程序的入口点。
//

#include <stdio.h>
#include <tchar.h>
#include <thread>
#include <memory>

#include "process/processType.h"
#include "data/globalData.h"
#include "task/taskBuilder.h"
#include "task/taskRunner.h"
#include "db/dataStruct/curRateStruct.h"

CGlobalData* gData;
shared_ptr<CTaskBuilder> taskBuilder = nullptr;
shared_ptr<CtaskRunner> taskRunner = nullptr;

void buildTask(int value)
{
	//CTaskBuilder taskBuilder;

	try
	{
		taskBuilder->run();
	}
	catch (CStrException& e)
	{
		printf("error:%s\n", e.what());
		int a = 0;
		a++;
	}
}

void runTask(int value)
{
	//CtaskRunner taskRunner;
	try
	{
		taskRunner->run();
	}
	catch (CStrException& e)
	{
		printf("error:%s\n", e.what());
		int a = 0;
		a++;
	}
}

void threadRun()
{
	thread buildTaskThread(buildTask, 0);
	thread runTaskThread(runTask, 0);

	buildTaskThread.join();
	runTaskThread.join();
}

int _tmain(int argc, _TCHAR* argv[])
{
	gData = &CGlobalData::instance();

	taskBuilder = make_shared<CTaskBuilder>();
	taskRunner = make_shared<CtaskRunner>();

	CDbObj& db = CDbObj::instance();
	db.initMySQL();
	string strSqlFormat = "insert into core.newTable ( name, value ) value ( '%s', '%s');";

	try
	{
		string sql = PubFun::strFormat(strSqlFormat.c_str(), PubFun::get14CurTimeString().c_str(), "linyanfeng");
		db.executeSql(sql.c_str());
	}
	catch (CStrException& e)
	{
		// 必然出错
		printf("db start! \n%s", e.what());
	}

	/*
	string strSqlTest = "select * from florex.currency_pair_XAUUSD order by curTime desc, curMsec desc limit 1;";
	CCurRateStruct rateStruct;
	CTable table(&rateStruct);
	db.SelectData(strSqlTest.c_str(), table);
	*/

	gData->init();

	threadRun();

	return 0;
}