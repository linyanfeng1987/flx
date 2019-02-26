#pragma once
#include "continueKeeper.h"

using namespace std;

// 连续分析器，拥有多个finder
class CContinueAnalysis
{
public:
	CContinueAnalysis();

	void add(PRateValue value, PContinueValueStruct pTableStruct);

protected:
	// 初始化finder
	void init();
	map<long, PContinueKeeper> continueKeepers;
	long keeperIndex;
// 	unsigned int maxMemberSize;
// 	double minContinueStep;
// 	double persentStep;
};
typedef shared_ptr<CContinueAnalysis> PContinueAnalysis;
#define newContinueAnalysis() make_shared<CContinueAnalysis>()