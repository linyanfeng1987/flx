#pragma once
#include "table/Row.h"
#include "baseThread.h"
#include "process/calcProcess.h"

// taskµÄÔËÐÐÈÝÆ÷
class CCalcThread : public CBaseThread
{
public:
	CCalcThread( PThreadInfo _threadInfo);
	~CCalcThread();

	//void setBaseCale(bool _isBaseCale){isBaseCale = _isBaseCale;}

protected:
	void init();

	void runInThread(const char* argv);
	void runTask(PRow taskInfoRow);
	int completeTask(PRow taskInfoRow);

	PCalcProcess getProcess( PRow taskInfo );

	PRow getOneTask();
	void rangTaskList();
	PCalcProcess getProcessTask( PRow processTaskInfoRow );

	void withBaseCalc(map<time_t, time_t>& resValueMap, string& rateName);
	void calcProcess(map<time_t, time_t>& resValueMap, string& rateName);
	
	PCalcProcess process;
	list<PRow> tasks;

	bool needBaseCalc;

	string getTaskSql;
	static const string logTag;
	PLogInfo logInfo;
	//bool isBaseCale;
};
typedef shared_ptr<CCalcThread> PCalcThread;
#define newCalcThread(T1) make_shared<CCalcThread>(T1)