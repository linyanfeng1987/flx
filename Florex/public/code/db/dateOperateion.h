#pragma once
#include "DbObj.h"
#include "ConstDef.h"

class CDataOperation
{
public:
	~CDataOperation();
	static CDataOperation& getDataOperation();

	time_t GetLastTimeFromeRate(string rateName, int nType = timeStepStep_def);

protected:
	
private:
	CDataOperation();
	CLogObj& log;
};
