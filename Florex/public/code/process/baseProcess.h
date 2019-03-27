#pragma once
#include <string>
#include "table/Table.h"
#include "db/dataStruct/processTaskInfoStruct.h"
#include "table/Row.h"
#include "process/obj/rateValue.h"

using namespace std;
class CBaseProcess
{
public:
	CBaseProcess(PRow pTaskInfo);
	~CBaseProcess();

	virtual void calc(list<PRateValue> &values) = 0;
	virtual void init(PRow pTaskInfo);

	PRow getTaskInfo(){return pTaskInfo;}
protected:
	string procssName;
	int processByte;
	int calculateStepSecond;
	PRow pTaskInfo;
};
typedef shared_ptr<CBaseProcess> PBaseProcess;

