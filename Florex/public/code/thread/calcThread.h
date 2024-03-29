#pragma once
#include "table/Row.h"
#include "baseThread.h"
#include "process/calcProcess.h"
#include "config/processCfgInfo.h"

// task����������
class CCalcThread : public CBaseThread
{
public:
	CCalcThread(PThreadInfo _threadInfo);
	~CCalcThread();

	//void setBaseCale(bool _isBaseCale){isBaseCale = _isBaseCale;}

protected:
	bool init();

	void runInThread(const char* argv);
	void runTask(PRow taskInfoRow);
	int completeTask(PRow taskInfoRow);

	//PCalcProcess getProcess( PRow taskInfo );

	PCalcProcess getProcess(PProcessCfgInfo processInfo, string& rateName);

	PRow getOneTask();
	void rangTaskList();
	PCalcProcess getProcessTask(PRow processTaskInfoRow);

	void withBaseCalc(map<time_t, time_t>& resValueMap, string& rateName);
	void calcProcess(map<time_t, time_t>& resValueMap, string& rateName);

	PCalcProcess process;
	list<PRow> tasks;

	bool needBaseCalc;

	string getTaskSql;
	static const string logTag;
	PLogInfo logInfo;
	PProcessCfgInfo processCfgInfo;
	//bool isBaseCale;
};
typedef shared_ptr<CCalcThread> PCalcThread;
#define newCalcThread(T1) make_shared<CCalcThread>(T1)