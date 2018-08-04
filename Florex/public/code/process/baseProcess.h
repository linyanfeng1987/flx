#pragma once
#include <string>
#include "table/Table.h"
#include "db/dataStruct/processTaskInfoStruct.h"
#include "table/Row.h"

using namespace std;
class CBaseProcess
{
public:
	CBaseProcess();
	~CBaseProcess();

	virtual void calc(CTable& table) = 0;
	virtual void init(CRow* pTaskInfo);
protected:
	string procssName;
	int processByte;
	int calculateStepSecond;
	CRow* pTaskInfo;
};

