#pragma once
#include <mutex>

#include "PubFun.h"
#include "ConstDef.h"
#include "process/processType.h"
#include "table/Table.h"
#include "LogObj.h"
#include "Exception.h"


#include "db/dataStruct/processTaskInfoStruct.h"
#include "db/dataStruct/processStatusStruct.h"
#include "db/dataStruct/testDbInfoStruct.h"

#include "task/baseTask.h"

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

	void initDataStruct();

	CProcessType* getProcessType(string processId);

	// process类型的信息
	map<string, CProcessType> porcessTypes;

	// process类型，对应的rate类型
	map<string, list<string> > processRates;

	void addProcessTaskInfo(PRow cfg);
	PTaskInfo popProcessTaskInfo(string &processKey);
	string popProcessKey();

	map<string, PRow> porcessInfos;
protected:
	//map<string, PTableStruct> 
	
	map<string, list<PTaskInfo>> taskInfos;
	list<string> processKeys;
	PTable tasks;
	recursive_mutex taskMutex; 
	CGlobalData();

	CLogObj& log;
};

