#pragma once
#include <string>
#include "baseProcess.h"
#include "db/dataStruct/curRateStruct.h"

#include "process/obj/baseAnalysis.h"

using namespace std;
class CCalcProcess : public CBaseProcess
{
public:
	CCalcProcess();
	~CCalcProcess();
	void addAnalysis(string name, PBaseAnalysis analysis);

	void calc(list<PRateValue> &values);
	void calc(list<PRateValue> &values);
	void init();
protected:
	map<string, PBaseAnalysis> analysiss;
	//PAverageAnalysis averageAnalysis;
	//PContinueAnalysis continueAnalysis;
};
typedef shared_ptr<CCalcProcess> PContinueProcess;
#define newCalcProcess(T) make_shared<CCalcProcess>(T)

