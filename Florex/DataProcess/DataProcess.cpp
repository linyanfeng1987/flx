// DataProcess.cpp : 定义控制台应用程序的入口点。
//

#include <stdio.h>
#include <tchar.h>
#include <thread>

#include "process/processType.h"
#include "data/globalData.h"
#include "task/taskBuilder.h"
#include "task/taskRunner.h"
#include "db/dataStruct/curRateStruct.h"

CGlobalData& gData = CGlobalData::instance();

void buildTask(int value)
{
	CTaskBuilder taskBuilder;
	taskBuilder.run();
}

void runTask(int value)
{
	CtaskRunner taskRunner;
	taskRunner.run();
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
	CDbObj &db = CDbObj::instance();
	db.tryConnect();
	string strSqlFormat = "insert into core.newTable ( name, value ) value ( '%s', '%s');";

	string sql = PubFun::strFormat(strSqlFormat.c_str(), PubFun::get14CurTimeString().c_str(), "linyanfeng");
	db.executeSql(sql.c_str());
	/*
	string strSqlTest = "select * from florex.currency_pair_XAUUSD order by curTime desc, curMsec desc limit 1;";
	CCurRateStruct rateStruct;
	CTable table(&rateStruct);
	db.SelectData(strSqlTest.c_str(), table);
	*/

	gData.init();

	threadRun();

	return 0;
}



