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

class CAverageCalcNode : public CBasePipelineNode
{
public:
	CAverageCalcNode(PRateInfo _rateInfo, double _stepTime);
	virtual ~CAverageCalcNode();

	virtual PRateValue add(PRateValue curValue);
	indexType getTagId() { return tagId; }
protected:
	void saveToDb(PRateValue averageValue);
	indexType tagId;
	static indexType tagIdCount;
	PRateInfo rateInfo;
	double stepTime;

	PSumByTime averCalcObj;
	PCalcRateStruct averageStruct;

	PTable resTable;
};

typedef shared_ptr<CAverageCalcNode> PAverageCalcNode;
#define newAverageCalcNode(T1,T2) make_shared<CAverageCalcNode>(T1,T2)