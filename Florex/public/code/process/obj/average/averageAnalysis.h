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
	CAverageAnalysis(PRateInfo _rateInfo);
	virtual void add(PRateValue value);

protected:
	// 初始化finder
	void init();
	//map<long, PAverageObj> averageObjs;

	list<PCalcPipeline> pipelines;
// 	unsigned int maxMemberSize;
// 	double minContinueStep;
// 	double persentStep;
};
typedef shared_ptr<CAverageAnalysis> PAverageAnalysis;
#define newAverageAnalysis(T) make_shared<CAverageAnalysis>(T)