#include "averageCalcNode.h"
#include "PubFun.h"

indexType CAverageCalcNode::tagIdCount = 0;
CAverageCalcNode::CAverageCalcNode(PRateInfo _rateInfo, double _stepTime) :tagId(++tagIdCount), stepTime(_stepTime)
{
	rateInfo = _rateInfo;
	averCalcObj = newSumByTime(_stepTime);
	averageStruct = newCalcRateAverageStruct(rateInfo->rateName, PubFun::intToString((long)stepTime));
	resTable = newTable(averageStruct);
}

PRateValue CAverageCalcNode::add(PRateValue curValue)
{
	PRateValue averValue = newRateValueCopy(*curValue);
	averValue->value = averCalcObj->add(curValue);

	saveToDb(averValue);
	return averValue;
}

void CAverageCalcNode::saveToDb(PRateValue averageValue)
{
	PRow row = newRow(averageStruct);
	row->setDoubleValue(CCalcRateStruct::curValue, averageValue->value);
	row->setDoubleValue(CCalcRateStruct::curTime, averageValue->time);
	row->setStringValue(CCalcRateStruct::timeFormat, averageValue->timeDesc);

	resTable->addRow(row);

	if (resTable->size() >= 10000)
	{
		resTable->save();
		resTable->clear();
	}
}

CAverageCalcNode::~CAverageCalcNode()
{
	if (resTable->size() > 0)
	{
		resTable->save();
	}
}