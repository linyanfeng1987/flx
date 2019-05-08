#pragma once
#include "db/DbObj.h"
#include "data/globalData.h"
#include "PubFun.h"
#include "ConstDef.h"
#include "process/calcProcess.h"
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
	void rangTaskList_save();

	void buildTestDbTask();

	void runFixTask();

	PProcessTask getProcessTask(PRow taskInfo);
	PCalcProcess getProcess( PRow taskInfo, bool baseCalc = false);

	int maxProcessCount;
	CLogObj& log;
	map<string, PProcessTask> allTasks;
	map<string, PProcessTask> runingTasks;
	CGlobalData& gData; 

	static const string logTag;
	PLogInfo logInfo;
};

