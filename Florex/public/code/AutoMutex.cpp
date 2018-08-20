#include "AutoMutex.h"


CAutoMutex::CAutoMutex( mutex *pMutex )
{
	this->pMutex = pMutex;
	this->pMutex->try_lock();
}

CAutoMutex::~CAutoMutex( void )
{
	this->pMutex->unlock();
}
