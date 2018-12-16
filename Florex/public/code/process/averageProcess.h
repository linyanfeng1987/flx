#pragma once
#include <string>
#include "baseProcess.h"
#include "process/calculation/averageCalc.h"
#include "db/dataStruct/curRateStruct.h"

using namespace std;
class CAverageProcess : public CBaseProcess
{
public:
	CAverageProcess(PRow pTaskInfo);
	~CAverageProcess();

	void calc(PTable& table);
	void init(PRow pTaskInfo);
protected:
	int cycle;
	int timeStepType;
	double lastPrice;
	shared_ptr<CAverageCalc> calcBuyObj;
	shared_ptr<CAverageCalc> calcSellObj;
};
typedef shared_ptr<CAverageProcess> PAverageProcess;
#define newAverageProcess(T) make_shared<CAverageProcess>(T);

