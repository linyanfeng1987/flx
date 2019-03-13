#include "AutoMutex.h"
#include "PubFun.h"


CAutoMutex::CAutoMutex( recursive_mutex *pMutex )
{
	this->pMutex = pMutex;
	//CLogObj::instance().debug(PubFun::strFormat("mutex while lock, thisId:%d, mutexId:%d", this, pMutex));
	this->pMutex->lock();
	//CLogObj::instance().debug(PubFun::strFormat("mutex locked, thisId:%d, mutexId:%d", this, pMutex));
}

CAutoMutex::~CAutoMutex( void )
{
	//CLogObj::instance().debug(PubFun::strFormat("mutex while unlock, thisId:%d, mutexId:%d", this, pMutex));
	this->pMutex->unlock();
	//CLogObj::instance().debug(PubFun::strFormat("mutex unlocked, thisId:%d, mutexId:%d", this, pMutex));
}
