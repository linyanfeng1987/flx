#pragma once
#include "table/Row.h"
#include "baseTask.h"
#include "process/baseProcess.h"

// taskµÄÔËÐÐÈÝÆ÷
class CProcessTask : public CBaseTask
{
public:
	CProcessTask(CRow porcessTaskInfo, CRow porcessStatus, CBaseProcess* pProcess);
	~CProcessTask();

	string getTaskId();

protected:
	void runInThread(const char* argv);
	int completeTask();
	
	CRow porcessTaskInfo;
	CRow porcessStatus;
	CBaseProcess *pProcess;
};
