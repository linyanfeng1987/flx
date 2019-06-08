#include "averageDecisionNode.h"
#include "PubFun.h"

CAverageDecisionNode::CAverageDecisionNode(list<PAverageDecisionTemplate> &_dTemplates, PRateInfo _rateInfo, double _stepTime):stepTime(_stepTime)
{
	rateInfo = _rateInfo;

	for (PAverageDecisionTemplate dTemplate: _dTemplates)
	{
		string objTag = PubFun::strFormat("average_%s_%d", rateInfo->rateName.c_str(), (int)stepTime);
		PAverageDecision decision = newAverageDecision(dTemplate, stepTime, objTag, rateInfo);
		decisions.push_back(decision);
	}
}

CAverageDecisionNode::~CAverageDecisionNode()
{

}

PRateValue CAverageDecisionNode::add( PRateValue curValue )
{
	for (PAverageDecision decision : decisions)
	{
		decision->add(curValue, curValue);
	}
	return nullptr;
}


