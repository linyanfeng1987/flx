#pragma once
#include "table/Row.h"
#include "baseThread.h"
#include "process/calcProcess.h"

// taskµÄÔËÐÐÈÝÆ÷
class CCalcThread : public CBaseThread
{
public:
	CCalcThread( PThreadInfo _threadInfo, PRow _porcessStatus, PCalcProcess _process );
	~CCalcThread();

	string getTaskId();
	void setBaseCale(bool _isBaseCale){isBaseCale = _isBaseCale;}

protected:
	void runInThread(const char* argv);
	int completeTask();

	void baseCalc(map<long, long>& resValueMap, string& rateName);
	void calcProcess(map<long, long>& resValueMap, string& rateName);
	
	//PThreadInfo threadInfo;
	PRow curTaskStatus;
	PCalcProcess process;

	static const string logTag;
	PLogInfo logInfo;
	bool isBaseCale;
};
typedef shared_ptr<CCalcThread> PCalcThread;
#define newCalcThread(T1,T2,T3) make_shared<CCalcThread>(T1,T2,T3)