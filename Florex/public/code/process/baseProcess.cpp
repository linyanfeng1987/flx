#include "baseProcess.h"
#include <thread>


CBaseProcess::CBaseProcess( PRow pTaskInfo )
{
	init(pTaskInfo);
}

CBaseProcess::~CBaseProcess()
{
}

void CBaseProcess::init( PRow pTaskInfo )
{
	this->pTaskInfo = pTaskInfo;
}
