#pragma once
#include "db/DbObj.h"
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
	void runOneProcess(string processName);


	map<string, CProcessTask> tasks;

	static CDbObj& db; 
};

