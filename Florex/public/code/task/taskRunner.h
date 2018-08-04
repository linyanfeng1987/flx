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

	CProcessTask* getProcessTask(CRow& taskInfo);
	CBaseProcess* getProcess( CRow& taskInfo );

	int maxProcessCount;

	map<string, CProcessTask*> runingTasks;
	static CDbObj& db; 
	static CGlobalData& gData; 
};

