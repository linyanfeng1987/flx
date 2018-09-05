#include "baseTask.h"
#include <thread>

using namespace std;
CBaseTask::CBaseTask():log(CLogObj::instance())
{
	status = 0;
}

CBaseTask::~CBaseTask()
{

}

int CBaseTask::run(const char* argv)
{
	thread runThread(&CBaseTask::runInThread, this, argv);
	runThread.detach();
	return 0;
}

