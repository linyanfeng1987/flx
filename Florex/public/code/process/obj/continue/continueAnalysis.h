#pragma once
#include "continueKeeper.h"

using namespace std;

// 连续分析器，拥有多个finder
class CContinueAnalysis
{
public:
	CContinueAnalysis(string _rateName);

	void add(PRateValue value, PContinueValueStruct pTableStruct);

protected:
	// 初始化finder
	void init();
	map<long, PContinueKeeper> continueKeepers;
	long keeperIndex;
	string rateName;
// 	unsigned int maxMemberSize;
// 	double minContinueStep;
// 	double persentStep;
};
typedef shared_ptr<CContinueAnalysis> PContinueAnalysis;
#define newContinueAnalysis(T) make_shared<CContinueAnalysis>(T)