#include "baseThread.h"
#include <thread>

using namespace std;
CBaseThread::CBaseThread(PThreadInfo _threadInfo):log(CLogObj::instance())
{
	threadInfo = _threadInfo;
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


void CThreadInfo::setThreadType( CalcThreadType _threadType )
{
	threadType = _threadType;
	switch (threadType)
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

CThreadInfo::CThreadInfo( PRow _threadInfoRow, CalcThreadType _threadType ):threadInfoRow(_threadInfoRow)
{
	setThreadType(_threadType);
}
