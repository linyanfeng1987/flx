#pragma once
#include "db/DbObj.h"
#include "data/globalData.h"
#include "PubFun.h"
#include "ConstDef.h"
#include "process/baseProcess.h"

class CtaskRunner
{
public:
	CtaskRunner();
	~CtaskRunner();

	void run();

protected:

	bool reloadTaskList();
	void rangTaskList();

	CBaseProcess* getProcess(CProcessTaskInfo& taskInfo);

	int maxProcessCount;

	static CDbObj& db; 
	static CGlobalData& gData; 
};

