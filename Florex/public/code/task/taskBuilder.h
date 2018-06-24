#pragma once
#include "db/DbObj.h"
#include "data/globalData.h"
#include "db/dataObj/processTaskInfo.h"
#include "process/processType.h"
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
	void runOneRate(string rateName, list<string>& processTypeNames);
	void runOneProcessInfo(string rateName, CProcessType& processType);


	time_t getRateLastTime(string rateName);
	time_t getProcessLastTime(string processName);
	map<string, CProcessTaskInfo> taskConfigs;

	static CDbObj& db; 
	static CGlobalData& gData; 
};

