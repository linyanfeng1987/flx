#include "baseProcess.h"
#include <thread>

CBaseProcess::CBaseProcess()
{
}

CBaseProcess::~CBaseProcess()
{
}

void CBaseProcess::detach( const char* argv )
{
	thread calcThread(&CBaseProcess::calc, this, argv);
	calcThread.detach();
}
