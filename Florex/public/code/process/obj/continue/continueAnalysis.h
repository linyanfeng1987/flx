#pragma once
#include "continueFinder.h"

using namespace std;

// 连续分析器，拥有多个finder
class CContinueAnalysis
{
public:
	CContinueAnalysis();

	void add(PRateValue value);

protected:
	// 初始化finder
	void init();
	map<long, PContinueFinder> continueFinders;
	long finderIndex;
// 	unsigned int maxMemberSize;
// 	double minContinueStep;
// 	double persentStep;
};
typedef shared_ptr<CContinueAnalysis> PContinueAnalysis;
#define newContinueAnalysis() make_shared<CContinueAnalysis>()