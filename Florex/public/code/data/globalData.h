#pragma once
#include <mutex>

#include "PubFun.h"
#include "ConstDef.h"
#include "process/processInfo.h"
#include "db/dataObj/processTaskInfo.h"


class CGlobalData
{
public:
	static CGlobalData& instance();
	
	~CGlobalData();

	void loadConfig();

	CProcessType* getProcessType(string processId);

	// process类型的信息
	map<string, CProcessType> porcessTypes;

	// process类型，对应的rate类型
	map<string, list<string> > processRates;

	void addprocessInfo(CProcessTaskInfo cfg);
	CProcessTaskInfo* popprocessInfo();

	map<string, CProcessInfo> porcessConfigs;
protected:
	
	
	list<CProcessTaskInfo> tasks;
	recursive_mutex taskMutex; 
	CGlobalData();
};

