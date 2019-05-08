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
	void setBaseCale(bool _isBaseCale){isBaseCale = _isBaseCale;}

protected:
	void runInThread(const char* argv);
	int completeTask();

	void baseCalc(map<long, long>& resValueMap, string& rateName);
	void calcProcess(map<long, long>& resValueMap, string& rateName);
	
	PTaskInfo porcessTaskInfo;
	PRow porcessStatus;
	PCalcProcess process;

	static const string logTag;
	PLogInfo logInfo;
	bool isBaseCale;
};
typedef shared_ptr<CProcessTask> PProcessTask;
#define newProcessTask(T1,T2,T3) make_shared<CProcessTask>(T1,T2,T3)