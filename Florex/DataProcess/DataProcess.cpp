// DataProcess.cpp : 定义控制台应用程序的入口点。
//

#include <stdio.h>
#include <tchar.h>
#include <thread>

#include "process/processType.h"
#include "data/globalData.h"
#include "task/taskBuilder.h"
#include "task/taskRunner.h"

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
	string strSqlFormat = "insert into core.newTable ( name, value ) value ( 'testName', 'testValue');";

	CDbObj &db = CDbObj::instance();
	db.ExecuteSql(strSqlFormat.c_str());

	gData.init();

	threadRun();

	return 0;
}



