#pragma once
#include <mutex>

#include "PubFun.h"
#include "ConstDef.h"
#include "process/processType.h"
#include "db/dataStruct/processTaskInfoStruct.h"
#include "table/Table.h"

class CGlobalData
{
public:
	static CGlobalData& instance();
	
	~CGlobalData();

	void init();

	void loadConfig();
	// 暂时代替loadConfig，做代码中的数据初始化
	void initDataInCode();

	void initDataInXml();

	CProcessType* getProcessType(string processId);

	// process类型的信息
	map<string, CProcessType> porcessTypes;

	// process类型，对应的rate类型
	map<string, list<string> > processRates;

	void addProcessTaskInfo(PRow cfg);
	PRow popProcessTaskInfo();

	map<string, PRow> porcessInfos;
protected:
	//map<string, PTableStruct> 
	
	PTable tasks;
	recursive_mutex taskMutex; 
	CGlobalData();
};

