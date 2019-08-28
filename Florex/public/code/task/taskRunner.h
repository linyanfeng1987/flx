#pragma once
#include "db/DbObj.h"
#include "data/globalData.h"
#include "PubFun.h"
#include "ConstDef.h"
#include "thread/calcThread.h"

class CtaskRunner
{
public:
	CtaskRunner();
	~CtaskRunner();

	void run();

protected:
	bool reloadThreadList();

	int maxProcessCount;
	CLogObj& log;
	map<string, PCalcThread> runingThreads;
	CGlobalData& gData;

	static const string logTag;
	PLogInfo logInfo;
};
