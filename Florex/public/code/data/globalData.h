#pragma once
#include <mutex>

#include "PubFun.h"
#include "ConstDef.h"
#include "process/processConfig.h"
#include "db/dataObj/processTaskInfo.h"


class CGlobalData
{
public:
	static CGlobalData& instance();
	
	~CGlobalData();

	void loadConfig();

	CProcessConfig* getProcessConfig(string processId);

	map<string, CProcessConfig> porcessConfigs;

	map<string, list<string> > processRates;

	void addProcessConfig(CProcessTaskInfo cfg);
	CProcessTaskInfo* popProcessConfig();
protected:
	
	list<CProcessTaskInfo> tasks;
	recursive_mutex taskMutex; 
	CGlobalData();
};

