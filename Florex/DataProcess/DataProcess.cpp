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
void cfgInit()
{
	CProcessType tmpType;
	string tmpName = "TEST_3600";
	tmpType.processTypeName = tmpName;
	tmpType.porcessFlag = 1;
	tmpType.timeStep = 3600;
	tmpType.dependOnTypeList.push_back("");
	gData.porcessTypes.insert(make_pair(tmpType.processTypeName, tmpType));
	
	list<string> tmpList;
	tmpList.push_back(tmpName);

	gData.processRates.insert(make_pair("XAUUSD", tmpList));
}

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
	cfgInit();

	threadRun();

	return 0;
}



