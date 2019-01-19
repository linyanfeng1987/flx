#include "continueAnalysis.h"

CContinueAnalysis::CContinueAnalysis()
{
	finderIndex = 0;
	init();
}

void CContinueAnalysis::add(CRateValue& value )
{
	for (auto conPair : continueFinders)
	{
		conPair.second->add(value);
	}

	// 连续查找的意义在哪里，如果没有预测和几率就没有意义
}

void CContinueAnalysis::init( )
{
	PContinueJudgeGroup pGroup = newContinueJudgeGroup(100, 0.618);
	pGroup->init(0.1/1000, 0, 0.618, 0, 0);
	PContinueFinder pFinder = newContinueFinder(pGroup);
	pFinder->setId(finderIndex++);
	continueFinders.insert(make_pair(pFinder->getId(), pFinder));
}
