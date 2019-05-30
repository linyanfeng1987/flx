#pragma once
#include "table/Row.h"
#include "baseThread.h"
#include "process/calcProcess.h"

// task����������
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

	void baseCalc(map<long, long>& resValueMap, string& rateName);
	void calcProcess(map<long, long>& resValueMap, string& rateName);
	
	PCalcProcess process;
	list<PRow> tasks;

	string getTaskSql;
	static const string logTag;
	PLogInfo logInfo;
	//bool isBaseCale;
};
typedef shared_ptr<CCalcThread> PCalcThread;
#define newCalcThread(T1) make_shared<CCalcThread>(T1)