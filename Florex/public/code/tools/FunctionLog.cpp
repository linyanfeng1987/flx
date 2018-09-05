#include "FunctionLog.h"
#include "PubFun.h"

CFunctionLog::CFunctionLog( string funName, long line):log(CLogObj::instance())
{
	log.debug(PubFun::strFormat("function in, thisId:%d, name:%s, line:%d.", this, funName.c_str(), line));
}

CFunctionLog::~CFunctionLog( void )
{
	log.debug(PubFun::strFormat("function out, thisId:%d.", this));
}
