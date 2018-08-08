#include "baseProcess.h"
#include <thread>

CBaseProcess::CBaseProcess()
{
}

CBaseProcess::~CBaseProcess()
{
}

void CBaseProcess::init( PRow pTaskInfo )
{
	this->pTaskInfo = pTaskInfo;
}
