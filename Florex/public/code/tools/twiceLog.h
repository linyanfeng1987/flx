#pragma once
#include "LogObj.h"

using namespace std;
class CTwiceLog
{
public:
	CTwiceLog(PLogInfo _logInfo, int _logType, string& _logFirst, string& _logSecond);
	~CTwiceLog(void);

protected:
	PLogInfo logInfo;
	CLogObj& log;
	string logFirst;
	string logSecond;
	int logType;
};
