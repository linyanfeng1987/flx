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

	void init();

	void loadConfig();
	// 暂时代替loadConfig，做代码中的数据初始化
	void initDataInCode();

	CProcessType* getProcessType(string processId);

	// process类型的信息
	map<string, CProcessType> porcessTypes;

	// process类型，对应的rate类型
	map<string, list<string> > processRates;

	void addProcessTaskInfo(CProcessTaskInfo cfg);
	CProcessTaskInfo* popProcessTaskInfo();

	map<string, CProcessInfo> porcessInfos;
protected:
	
	
	list<CProcessTaskInfo> tasks;
	recursive_mutex taskMutex; 
	CGlobalData();
};

