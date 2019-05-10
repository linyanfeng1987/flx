#include "baseThread.h"
#include <thread>

using namespace std;
CBaseThread::CBaseThread(PThreadInfo _taskInfo):log(CLogObj::instance())
{
	taskInfo = _taskInfo;
	status = 0;
}

CBaseThread::~CBaseThread()
{
	CDbObj::release();
}

int CBaseThread::run(const char* argv)
{
	thread runThread(&CBaseThread::baseRunInThread, this, argv);
	runThread.detach();
	return 0;
}

void CBaseThread::baseRunInThread( const char* argv )
{
	runInThread(argv);
}


void CThreadInfo::setThreadType( CalcThreadType _ThreadType )
{
	ThreadType = _ThreadType;
	switch (ThreadType)
	{
	case thread_calc_map:
		threadsAble = true;
		break;
	case thread_calc_stauts:
		threadsAble = false;
		break;
	default:
		break;
	}
}

CThreadInfo::CThreadInfo( PRow _porcessTaskInfo, CalcThreadType _ThreadType ):porcessTaskInfo(_porcessTaskInfo)
{
	setThreadType(_ThreadType);
}
