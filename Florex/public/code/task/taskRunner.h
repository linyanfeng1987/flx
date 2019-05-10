#pragma once
#include "db/DbObj.h"
#include "data/globalData.h"
#include "PubFun.h"
#include "ConstDef.h"
#include "process/calcProcess.h"
#include "task/calcThread.h"

class CtaskRunner
{
public:
	CtaskRunner();
	~CtaskRunner();

	void run();

protected:

	bool reloadTaskList();
	bool reloadProcessList();
	void runProcess(PRow processInfoRow);

	void rangTaskList();
	void rangTaskList_save();

	void buildTestDbTask();

	void runFixTask();

	PCalcProcess getProcessTask(PRow taskInfo);
	PCalcProcess getProcess( PRow taskInfo, bool baseCalc = false);

	int maxProcessCount;
	CLogObj& log;
	map<string, PCalcProcess> allTasks;
	map<string, PCalcProcess> runingTasks;
	CGlobalData& gData; 

	static const string logTag;
	PLogInfo logInfo;
};

