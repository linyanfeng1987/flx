#pragma once
#include "continueKeeper.h"
#include "rate/rateInfo.h"
using namespace std;

// 连续分析器，拥有多个finder
class CContinueAnalysis
{
public:
	CContinueAnalysis(PRateInfo _rateInfo);

	void add(PRateValue value);

protected:
	// 初始化finder
	void init();
	map<long, PContinueKeeper> continueKeepers;
	long keeperIndex;
	PRateInfo rateInfo;
// 	unsigned int maxMemberSize;
// 	double minContinueStep;
// 	double persentStep;
};
typedef shared_ptr<CContinueAnalysis> PContinueAnalysis;
#define newContinueAnalysis(T) make_shared<CContinueAnalysis>(T)