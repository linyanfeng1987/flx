#include "baseProcess.h"
#include <thread>

CBaseProcess::CBaseProcess()
{
}

CBaseProcess::~CBaseProcess()
{
}

void CBaseProcess::init( CRow* pTaskInfo )
{
	this->pTaskInfo = pTaskInfo;
}
