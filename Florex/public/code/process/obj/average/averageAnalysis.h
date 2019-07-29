#pragma once
#include "rate/rateInfo.h"
#include "../baseAnalysis.h"
#include "process/obj/calcPipeline.h"
#include "averageCalcNode.h"
#include "averageDecisionNode.h"

using namespace std;

// 连续分析器，拥有多个finder
class CAverageAnalysis : public CBaseAnalysis
{
public:
	using CBaseAnalysis::CBaseAnalysis;
	CAverageAnalysis(PAnalysisInfo _analysisInfo, PRateInfo _rateInfo):CBaseAnalysis(_analysisInfo, _rateInfo){}

	virtual void add(PRateValue value);

protected:
	// 初始化finder
	virtual void init();
	void init_s();
	//map<long, PAverageObj> averageObjs;

	list<PCalcPipeline> pipelines;
// 	unsigned int maxMemberSize;
// 	double minContinueStep;
// 	double persentStep;
};
typedef shared_ptr<CAverageAnalysis> PAverageAnalysis;
#define newAverageAnalysis(T1,T2) make_shared<CAverageAnalysis>(T1,T2)