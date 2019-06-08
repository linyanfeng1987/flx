#pragma once
#include <list>
#include <map>
#include <memory>

#include "table/Table.h"
#include "ConstDef.h"
#include "rate/rateInfo.h"
#include "process/obj/rateValue.h"
#include "process/obj/sumByTime.h"
#include "process/obj/basePipelineNode.h"
#include "db/dataStruct/calcRateStruct.h"
#include "table/Row.h"


#include "process/decision/averageDecision.h"

using namespace std;

class CAverageDecisionNode : public CBasePipelineNode
{
public:
	CAverageDecisionNode(list<PAverageDecisionTemplate> &_dTemplates, PRateInfo _rateInfo, double _stepTime);
	virtual ~CAverageDecisionNode();

	virtual PRateValue add(PRateValue curValue);
protected:
	PRateInfo rateInfo;
	double stepTime;

	list<PAverageDecision> decisions;
};

typedef shared_ptr<CAverageDecisionNode> PAverageDecisionNode;
#define newAverageDecisionNode(T1,T2,T3) make_shared<CAverageDecisionNode>(T1,T2,T3)