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

	void calc(PTable& table);
	void init(PRow pTaskInfo);
protected:
	int cycle;
};
typedef shared_ptr<CAverageProcess> PAverageProcess;
#define newAverageProcess() make_shared<CAverageProcess>();

