#pragma once
#include <string>
#include "baseProcess.h"
#include "process/obj/average/averageAnalysis.h"
#include "db/dataStruct/curRateStruct.h"

using namespace std;
class CAverageProcess : public CBaseProcess
{
public:
	CAverageProcess(PRow pTaskInfo);
	~CAverageProcess();

	void calc(list<PRateValue> &values);
	void init(PRow pTaskInfo);
protected:
	PAverageAnalysis averageAnalysis;
};
typedef shared_ptr<CAverageProcess> PAverageProcess;
#define newAverageProcess(T) make_shared<CAverageProcess>(T)

