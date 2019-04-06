#include "averageObj.h"
#include "PubFun.h"

indexType CAverageObj::tagIdCount = 0;
CAverageObj::CAverageObj(list<PAverageDecisionTemplate> &_dTemplates, PRateInfo _rateInfo, double _stepTime):tagId(++tagIdCount),stepTime(_stepTime)
{
	rateInfo = _rateInfo;
	averCalcObj = newSumByTime(_stepTime);
	averageStruct = newCurRateAverageStruct(rateInfo->rateName, PubFun::intToString((long)stepTime));
	resTable = newTable(averageStruct);

	for (PAverageDecisionTemplate dTemplate: _dTemplates)
	{
		string objTag = PubFun::strFormat("average_%s_%d", rateInfo->rateName.c_str(), (int)stepTime);
		PAverageDecision decision = newAverageDecision(dTemplate, stepTime, objTag, rateInfo);
		decisions.push_back(decision);
	}
}

void CAverageObj::add( PRateValue curValue )
{
	PRateValue averValue = newRateValueCopy(*curValue);
	averValue->value = averCalcObj->add(curValue);

	saveToDb(averValue);

	for (PAverageDecision decision : decisions)
	{
		decision->add(curValue, averValue);
	}
}

void CAverageObj::saveToDb( PRateValue averageValue )
{
	PRow row = newRow(averageStruct);
	row->setDoubleValue(CCurRateAverageStruct::curValue, averageValue->value);
	row->setDoubleValue(CCurRateAverageStruct::curTime, averageValue->time);
	row->setStringValue(CCurRateAverageStruct::timeFormat, averageValue->timeDesc);

	resTable->addRow(row);

	if (resTable->size() >= 10000)
	{
		resTable->save();
		resTable->clear();
	}
}

CAverageObj::~CAverageObj()
{
	if (resTable->size() > 0)
	{
		resTable->save();
	}
}
