#include "averageObj.h"
#include "PubFun.h"

indexType CAverageObj::tagIdCount = 0;
CAverageObj::CAverageObj(PRateInfo _rateInfo, double _stepTime):tagId(++tagIdCount),stepTime(_stepTime)
{
	rateInfo = _rateInfo;
	averCalcObj = newSumByTime(_stepTime);
	averageStruct = newCurRateAverageStruct(rateInfo->rateName, PubFun::doubleToString(stepTime));
}

void CAverageObj::add( PRateValue curValue )
{
	PRateValue averValue = newRateValueCopy(*curValue);
	averValue->value = averCalcObj->add(curValue);

	saveToDb(averValue);
}

void CAverageObj::saveToDb( PRateValue averageValue )
{
	PRow row = newRow(averageStruct);
	row->setDoubleValue(CCurRateAverageStruct::curValue, averageValue->value);
	row->setDoubleValue(CCurRateAverageStruct::curTime, averageValue->time);
	row->setStringValue(CCurRateAverageStruct::timeFormat, averageValue->timeDesc);
	row->save();
}
