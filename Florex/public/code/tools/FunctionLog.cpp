#include "FunctionLog.h"
#include "PubFun.h"

CFunctionLog::CFunctionLog(PLogInfo _logInfo, string funName, long line) :log(CLogObj::instance()), logInfo(_logInfo)
{
	log.debug(logInfo, PubFun::strFormat("function in, thisId:%d, name:%s, line:%d.", this, funName.c_str(), line));
}

CFunctionLog::~CFunctionLog(void)
{
	log.debug(logInfo, PubFun::strFormat("function out, thisId:%d.", this));
}