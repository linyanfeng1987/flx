#pragma once
#include "db/DbObj.h"
#include "PubFun.h"
#include "ConstDef.h"

class CTaskBuilder
{
public:
	CTaskBuilder();
	~CTaskBuilder();


	void run();
protected:
	void runOneRate(string rateName);

};

