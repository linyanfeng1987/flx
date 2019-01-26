#pragma once
#include <string>
#include "baseProcess.h"
#include "process/obj/continue/continueAnalysis.h"
#include "db/dataStruct/curRateStruct.h"

using namespace std;
class CContinueProcess : public CBaseProcess
{
public:
	CContinueProcess(PRow pTaskInfo);
	~CContinueProcess();

	void calc(PTable& table);
	void init(PRow pTaskInfo);
protected:
	int cycle;
	int timeStepType;
	double lastPrice;
	PContinueAnalysis pContinueAnalysis;
};
typedef shared_ptr<CContinueProcess> PContinueProcess;
#define newContinueProcess(T) make_shared<CContinueProcess>(T)

