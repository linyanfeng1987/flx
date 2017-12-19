#pragma once
#include "db/DbObj.h"
#include "data/globalData.h"
#include "db/dataObj/processTask.h"
#include "PubFun.h"
#include "ConstDef.h"

class CTaskBuilder
{
public:
	CTaskBuilder();
	~CTaskBuilder();

	void reLoadTask();

	void run();
protected:
	void runOneRate(string rateName);
	void runOneProcess(CProcessConfig& porcessConfig);


	time_t getRateLastTime(string rateName);
	time_t getProcessLastTime(string processName);
	map<string, CProcessTask> tasks;

	static CDbObj& db; 
	static CGlobalData& gData; 
};

