#pragma once
#include <string>
#include "baseProcess.h"
#include "process/calculation/averageCalc.h"
#include "db/dataStruct/curRateStruct.h"

using namespace std;
class CAverageProcess : public CBaseProcess
{
public:
	CAverageProcess();
	~CAverageProcess();

	void calc(CTable& table);
	void init(CRow* pTaskInfo);
protected:
	int cycle;

	
};

