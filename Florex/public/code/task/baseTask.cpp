#include "baseTask.h"
#include <thread>

using namespace std;
CBaseTask::CBaseTask(PTaskInfo _taskInfo):log(CLogObj::instance())
{
	taskInfo = _taskInfo;
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
	runInThread(argv);
}


void CTaskInfo::setTaskType( TaskType _taskType )
{
	taskType = _taskType;
	switch (taskType)
	{
	case task_calc_map:
		threadsAble = true;
		break;
	case task_calc_stauts:
		threadsAble = false;
		break;
	default:
		break;
	}
}

CTaskInfo::CTaskInfo( PRow _porcessTaskInfo, TaskType _taskType ):porcessTaskInfo(_porcessTaskInfo)
{
	setTaskType(_taskType);
}
