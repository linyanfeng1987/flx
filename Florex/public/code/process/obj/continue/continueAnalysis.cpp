#include "continueAnalysis.h"
#include "ConstDef.h"
#include "process/obj/function/fun1.h"
#include "process/decision/continueDecision.h"
#include "PubFun.h"

void CContinueAnalysis::add(PRateValue value)
{
	for (auto conPair : continueKeepers)
	{
		conPair.second->add(value);
	}

	// 连续查找的意义在哪里，如果没有预测和几率就没有意义
}

void CContinueAnalysis::init()
{
	keeperIndex = 0;

	PContinueKeeper pKeeper = nullptr;
	PContinueJudgeGroup pGroup = nullptr;
	PBaseFun retrcementCalcFun = nullptr;
	list<PContinueDecision> decisions;

	double testParam2 = 0.8;
	for (int i = 3; i <= 5; i++)
	{
		PContinueDecision decision = newContinueDecision(i);
		decisions.push_back(decision);
	}
	retrcementCalcFun = newCFun1(goldenSection, testParam2);
	pGroup = newContinueJudgeGroup(15, goldenSection, retrcementCalcFun);
	pGroup->init(basePoint, goldenSection);
	pGroup->name = "61.8%";
	pKeeper = newContinueKeeper(rateInfo, pGroup, direct_up, decisions);
	pKeeper->setId(keeperIndex++);
	continueKeepers.insert(make_pair(pKeeper->getId(), pKeeper));
	pKeeper = newContinueKeeper(rateInfo, pGroup, direct_down, decisions);
	pKeeper->setId(keeperIndex++);
	continueKeepers.insert(make_pair(pKeeper->getId(), pKeeper));

	double testPersent = 0.9;
	decisions.clear();
	for (int i = 9; i <= 15; i++)
	{
		//decisions.push_back(newContinueDecision(i, rateInfo, "90persent", PubFun::intToString(i)));
		decisions.push_back(newContinueDecision(i));
	}
	decisions.push_back(newContinueDecision(20));
	decisions.push_back(newContinueDecision(22));
	decisions.push_back(newContinueDecision(30));
	retrcementCalcFun = newCFun1(testPersent, 0.95);
	pGroup = newContinueJudgeGroup(70, testPersent, retrcementCalcFun);
	pGroup->init(basePoint, testPersent);
	pGroup->name = "90%";
	pKeeper = newContinueKeeper(rateInfo, pGroup, direct_up, decisions);
	pKeeper->setId(keeperIndex++);
	continueKeepers.insert(make_pair(pKeeper->getId(), pKeeper));
	pKeeper = newContinueKeeper(rateInfo, pGroup, direct_down, decisions);
	pKeeper->setId(keeperIndex++);
	continueKeepers.insert(make_pair(pKeeper->getId(), pKeeper));
}
