#pragma once
#include "LogObj.h"

using namespace std;
class CFunctionLog
{
public:
	CFunctionLog(PLogInfo _logInfo, string funName, long line);
	~CFunctionLog(void);

protected:
	PLogInfo logInfo;
	CLogObj& log;
};
