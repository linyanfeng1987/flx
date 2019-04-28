#pragma once
#include "../baseAnalysis.h"
#include "averageObj.h"
#include "rate/rateInfo.h"
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
	map<long, PAverageObj> averageObjs;
// 	unsigned int maxMemberSize;
// 	double minContinueStep;
// 	double persentStep;
};
typedef shared_ptr<CAverageAnalysis> PAverageAnalysis;
#define newAverageAnalysis(T) make_shared<CAverageAnalysis>(T)