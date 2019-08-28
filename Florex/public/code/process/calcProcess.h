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
	using CBaseProcess::CBaseProcess;
	CCalcProcess(PProcessCfgInfo _threadInfo, PRateInfo _rateInfo);
	void addAnalysis(string name, PBaseAnalysis analysis);

	void calc(PTable rateTable);
	void calc(list<PRateValue>& values);
	virtual void init();
protected:
	map<string, PBaseAnalysis> analysiss;
	PCalcProData calcProData;

	//PAverageAnalysis averageAnalysis;
	//PContinueAnalysis continueAnalysis;
	double timeCheck;
};
typedef shared_ptr<CCalcProcess> PCalcProcess;
#define newCalcProcess(T1,T2) make_shared<CCalcProcess>(T1,T2)
