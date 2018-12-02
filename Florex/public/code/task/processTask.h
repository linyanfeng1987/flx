#pragma once
#include "table/Row.h"
#include "baseTask.h"
#include "process/baseProcess.h"

// taskµÄÔËÐÐÈÝÆ÷
class CProcessTask : public CBaseTask
{
public:
	CProcessTask( PRow porcessStatus, PBaseProcess pProcess, string name);
	~CProcessTask();

	string getTaskId();

protected:
	void runInThread(const char* argv);
	int completeTask();
	
	PRow porcessTaskInfo;
	PRow porcessStatus;
	PBaseProcess process;
};
typedef shared_ptr<CProcessTask> PProcessTask;
#define newProcessTask(T1,T2,T3) make_shared<CProcessTask>(T1,T2,T3);