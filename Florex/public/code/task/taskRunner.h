#pragma once
#include "db/DbObj.h"
#include "data/globalData.h"
#include "PubFun.h"
#include "ConstDef.h"
#include "process/baseProcess.h"
#include "task/processTask.h"

class CtaskRunner
{
public:
	CtaskRunner();
	~CtaskRunner();

	void run();

protected:

	bool reloadTaskList();
	void rangTaskList();

	void buildTestDbTask();

	PProcessTask getProcessTask(PRow taskInfo);
	PBaseProcess getProcess( PRow taskInfo );

	int maxProcessCount;
	CLogObj& log;
	map<string, PProcessTask> runingTasks;
	CGlobalData& gData; 

	static const string logTag;
	PLogInfo logInfo;
};

