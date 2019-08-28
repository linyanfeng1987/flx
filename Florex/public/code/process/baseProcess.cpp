#include "baseProcess.h"
#include <thread>

CBaseProcess::CBaseProcess(PProcessCfgInfo _threadInfo, PRateInfo _rateInfo) :rateInfo(_rateInfo)
{
	threadInfo = _threadInfo;
	init();
}

CBaseProcess::~CBaseProcess()
{
}

void CBaseProcess::init()
{
}

// void CBaseProcess::init( PRow pTaskInfo )
// {
// 	this->pTaskInfo = pTaskInfo;
// }