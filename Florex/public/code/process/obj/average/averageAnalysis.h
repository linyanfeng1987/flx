#pragma once
#include "averageObj.h"
#include "rate/rateInfo.h"
using namespace std;

// 连续分析器，拥有多个finder
class CAverageAnalysis
{
public:
	CAverageAnalysis(PRateInfo _rateInfo);

	void add(PRateValue value);

protected:
	// 初始化finder
	void init();
	map<long, PAverageObj> averageObjs;
	PRateInfo rateInfo;
// 	unsigned int maxMemberSize;
// 	double minContinueStep;
// 	double persentStep;
};
typedef shared_ptr<CAverageAnalysis> PAverageAnalysis;
#define newAverageAnalysis(T) make_shared<CAverageAnalysis>(T)