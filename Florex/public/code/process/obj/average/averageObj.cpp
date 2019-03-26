#include "averageObj.h"
#include "PubFun.h"

indexType CAverageObj::tagIdCount = 0;
CAverageObj::CAverageObj(PRateInfo _rateInfo, double _stepTime):tagId(++tagIdCount)
{
	rateInfo = _rateInfo;
	averCalcObj = newSumByTime(_stepTime);
}

void CAverageObj::add( PRateValue curValue )
{
	PRateValue averValue = newRateValueCopy(*curValue);
	averValue->value = averCalcObj->add(curValue);

	saveToDb(averValue);
}

void CAverageObj::saveToDb( PRateValue averageValue )
{

}
