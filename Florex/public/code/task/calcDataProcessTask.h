#pragma once
#include "table/Row.h"
#include "baseTask.h"
#include "process/baseProcess.h"
#include "processTask.h"
#include "db/dataStruct/calcRateStruct.h"

// taskµÄÔËÐÐÈÝÆ÷
class CCalcProcessTask : public CProcessTask
{
public:
	//using CProcessTask;
	CCalcProcessTask( PRow porcessStatus, PBaseProcess pProcess, string name);
	~CCalcProcessTask();

protected:
	void saveToDb( PRateValue rateValue );
	void runInThread(const char* argv);

	PTableStruct calcRateStruct;
	PTable resTable;
};
typedef shared_ptr<CCalcProcessTask> PCalcDataProcessTask;
#define newCalcDataProcessTask(T1,T2,T3) make_shared<CCalcProcessTask>(T1,T2,T3)
