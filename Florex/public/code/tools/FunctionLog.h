#pragma once
#include "LogObj.h"

using namespace std;
class CFunctionLog
{
public:
	CFunctionLog(string funName, long line);
	~CFunctionLog(void);

protected:
	CLogObj& log;
};
