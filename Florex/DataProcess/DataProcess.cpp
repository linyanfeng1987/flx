// DataProcess.cpp : 定义控制台应用程序的入口点。
//

#include <stdio.h>
#include <tchar.h>
#include <thread>

#include "process/processConfig.h"
#include "data/globalData.h"
#include "task/taskBuilder.h"
#include "task/taskRunner.h"

CGlobalData& gData = CGlobalData::instance();
void cfgInit()
{
	CProcessConfig processCfg;
	processCfg.processTypeName = "TEST_3600_XAUUSD";
	processCfg.porcessFlag = 1;
	processCfg.timeStep = 3600;
	processCfg.dependOnList.push_back("XAUUSD");
	gData.porcessConfigs.insert(make_pair(processCfg.processTypeName, processCfg));
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



