#pragma once
#include <string>
#include "baseProcess.h"
#include "db/dataStruct/curRateStruct.h"
#include "process/obj/baseAnalysis.h"
#include "process/calcProData.h"

using namespace std;
class CCalcProcess : public CBaseProcess
{
public:
	CCalcProcess(PRateInfo _rateInfo);
	~CCalcProcess();
	void addAnalysis(string name, PBaseAnalysis analysis);

	void calc(PTable rateTable);
	void calc(list<PRateValue> &values);
	void init();
	bool isBaseCalc();
protected:
	map<string, PBaseAnalysis> analysiss;
	PCalcProData calcProData;

	//PAverageAnalysis averageAnalysis;
	//PContinueAnalysis continueAnalysis;
};
typedef shared_ptr<CCalcProcess> PCalcProcess;
#define newCalcProcess(T) make_shared<CCalcProcess>(T)

