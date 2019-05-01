#pragma once
#include "table/Row.h"
#include "baseTask.h"
#include "process/calcProcess.h"

// taskµÄÔËÐÐÈÝÆ÷
class CProcessTask : public CBaseTask
{
public:
	CProcessTask( PTaskInfo _porcessTaskInfo, PRow _porcessStatus, PCalcProcess _process );
	~CProcessTask();

	string getTaskId();

protected:
	void runInThread(const char* argv);
	int completeTask();
	
	PTaskInfo porcessTaskInfo;
	PRow porcessStatus;
	PCalcProcess process;

	static const string logTag;
	PLogInfo logInfo;
};
typedef shared_ptr<CProcessTask> PProcessTask;
#define newProcessTask(T1,T2,T3) make_shared<CProcessTask>(T1,T2,T3)