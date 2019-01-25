#include "continueAnalysis.h"
#include "ConstDef.h"

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
	PContinueJudgeGroup pGroup = newContinueJudgeGroup(100, goldenSection);
	pGroup->init(0.1, goldenSection, goldenSection);
	PContinueFinder pFinder = newContinueFinder(pGroup);
	pFinder->setId(finderIndex++);
	continueFinders.insert(make_pair(pFinder->getId(), pFinder));
}
