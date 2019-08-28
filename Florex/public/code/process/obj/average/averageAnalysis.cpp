#include "averageAnalysis.h"
#include "ConstDef.h"
#include "process/obj/function/fun1.h"
#include "process/decision/continueDecision.h"
#include "PubFun.h"

void CAverageAnalysis::add(PRateValue value)
{
	for (auto pipeline : pipelines)
	{
		//obj.second->add(value);
		pipeline->add(value);
	}

	// 连续查找的意义在哪里，如果没有预测和几率就没有意义
}

void CAverageAnalysis::init()
{
	list<PAverageDecisionTemplate> dTemplates;
	list<double> decisionPersents = analysisInfo->paramGroup.find("decisionPersents")->second->getNumParams();
	for (double decisionPersent : decisionPersents)
	{
		PAverageDecisionTemplate dTemplate = newAverageDecisionTemplate(decisionPersent, decisionPersent * 0.5);
		dTemplates.push_back(dTemplate);
	}

	list<double> stepTimes = analysisInfo->paramGroup.find("stepTimes")->second->getNumParams();
	for (double stepTime : stepTimes)
	{
		PCalcPipeline pipeline = newCalcPipeline();

		PAverageCalcNode  calcNode = newAverageCalcNode(rateInfo, stepTime);
		pipeline->puchBack(calcNode);
		PAverageDecisionNode decisionNode = newAverageDecisionNode(dTemplates, rateInfo, stepTime);
		pipeline->puchBack(decisionNode);

		pipelines.push_back(pipeline);
	}
}

void CAverageAnalysis::init_s()
{
	double stepTimes[] = { 10, 60, 60 * 15, 60 * 60, 60 * 60 * 4, 60 * 60 * 24 };
	//double stepTimes[] = {60*60*4, 60*60*24};
	//double stepTimes[] = {60*60*4};

	list<PAverageDecisionTemplate> dTemplates;
	double decisionPersents[] = { 0.2, 0.4, 0.6, 0.8, 0.99 };
	//double decisionPersents[] = {0.6};
	for (double decisionPersent : decisionPersents)
	{
		PAverageDecisionTemplate dTemplate = newAverageDecisionTemplate(decisionPersent, decisionPersent * 0.5);
		dTemplates.push_back(dTemplate);
	}

	for (double stepTime : stepTimes)
	{
		PCalcPipeline pipeline = newCalcPipeline();

		PAverageCalcNode  calcNode = newAverageCalcNode(rateInfo, stepTime);
		pipeline->puchBack(calcNode);
		PAverageDecisionNode decisionNode = newAverageDecisionNode(dTemplates, rateInfo, stepTime);
		pipeline->puchBack(decisionNode);

		pipelines.push_back(pipeline);
	}
}