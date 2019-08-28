#pragma once
#include "db/DbObj.h"
#include "data/globalData.h"
#include "process/processType.h"
#include "PubFun.h"
#include "ConstDef.h"

class CTaskBuilder
{
public:
	CTaskBuilder();
	~CTaskBuilder();

	//bool reloadTaskList_delete();
	void run();
protected:
	void buildThreadByRate(string rateName, list<string>& processTypeNames);
	void buildThreadByType(string rateName, CProcessType& processType);

	bool buildByThread();

	time_t getRateLastTime(string rateName);
	time_t getRateStartTime(string rateName);
	time_t getRateTime(string rateName, string orderSql);
	map<string, PRow> taskConfigs;

	CLogObj& log;
	CDbObj* pDb;
	CGlobalData& gData;

	static const string logTag;
	PLogInfo logInfo;
};
