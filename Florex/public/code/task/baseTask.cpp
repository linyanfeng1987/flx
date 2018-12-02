#include "baseTask.h"
#include <thread>

using namespace std;
CBaseTask::CBaseTask(string taskName):log(CLogObj::instance())
{
	if(taskName == "")
	{
		int a = 0;
		a++;
	}
	this->taskName = taskName;
	status = 0;
}

CBaseTask::~CBaseTask()
{
	CDbObj::release();
}

int CBaseTask::run(const char* argv)
{
	thread runThread(&CBaseTask::baseRunInThread, this, argv);
	runThread.detach();
	return 0;
}

void CBaseTask::baseRunInThread( const char* argv )
{
	CLogInfo logInfo(taskName);
	log.addLogInfo(logInfo);
	runInThread(argv);
}

