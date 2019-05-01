#include "baseProcess.h"
#include <thread>


CBaseProcess::CBaseProcess(PRateInfo _rateInfo):rateInfo(_rateInfo)
{
	//init(pTaskInfo);
}

CBaseProcess::~CBaseProcess()
{
}

// void CBaseProcess::init( PRow pTaskInfo )
// {
// 	this->pTaskInfo = pTaskInfo;
// }
