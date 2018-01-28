#pragma once
#include "db/DbObj.h"
#include "data/globalData.h"
#include "PubFun.h"
#include "ConstDef.h"

class CtaskRunner
{
public:
	CtaskRunner();
	~CtaskRunner();

	void run();

protected:

	void reloadTaskList();
	void rangTaskList();

};

