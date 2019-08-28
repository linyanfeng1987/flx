#pragma once
#include <string>
#include "table/Table.h"
#include "db/dataStruct/processTaskInfoStruct.h"
#include "table/Row.h"
#include "process/obj/rateValue.h"
#include "rate/rateInfo.h"
#include "config/processCfgInfo.h"

using namespace std;
class CBaseProcess
{
public:
	CBaseProcess(PProcessCfgInfo _threadInfo, PRateInfo _rateInfo);
	~CBaseProcess();

	virtual void calc(list<PRateValue>& values) = 0;
	//virtual void init(PRow pTaskInfo);

	virtual void init();

	//PRow getTaskInfo(){return pTaskInfo;}
protected:
	string procssName;
	int processByte;
	int calculateStepSecond;
	PRateInfo rateInfo;
	PProcessCfgInfo threadInfo;
};
typedef shared_ptr<CBaseProcess> PBaseProcess;
