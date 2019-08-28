#include "twiceLog.h"
#include "PubFun.h"

CTwiceLog::CTwiceLog(PLogInfo _logInfo, int _logType, string& _logFirst, string& _logSecond) :log(CLogObj::instance()), logInfo(_logInfo)
{
	logType = _logType;
	logFirst = _logFirst;
	logSecond = _logSecond;
	log.logString(logInfo, logType, logFirst);
	//log.debug(logInfo, PubFun::strFormat("function in, thisId:%d, name:%s, line:%d.", this, funName.c_str(), line));
}

CTwiceLog::~CTwiceLog(void)
{
	log.logString(logInfo, logType, logSecond);
	//log.debug(logInfo, PubFun::strFormat("function out, thisId:%d.", this));
}