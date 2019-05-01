#include "calcProData.h"
#include "PubFun.h"

CCalcProData::CCalcProData( PRateInfo rateInfo )
{
	init(rateInfo);
}

CCalcProData::~CCalcProData()
{
	if (resTable->size() >= 0)
	{
		resTable->save();
		resTable->clear();
	}
}

PRateValue CCalcProData::calcRateValue( PRow rateRow )
{
	long curTime = rateRow->getIntValue(CCurRateStruct::curTime);
	long curMsec = rateRow->getIntValue(CCurRateStruct::curMsec);
	double curDTime = PubFun::timeConvert(curTime, curMsec);
	double priceBuy = rateRow->getDoubleValue(CCurRateStruct::priceBuy);
	string timeDesc = rateRow->getStringValue(CCurRateStruct::timeFormat);

	PRateValue rateValue = newRateValueP3(curDTime, priceBuy, timeDesc);
	saveToDb(rateValue);
	return rateValue;
}

void CCalcProData::saveToDb( PRateValue rateValue )
{
	PRow row = newRow(calcRateStruct);
	row->setDoubleValue(CCalcRateStruct::curValue, rateValue->value);
	row->setDoubleValue(CCalcRateStruct::curTime, rateValue->time);
	row->setStringValue(CCalcRateStruct::timeFormat, rateValue->timeDesc);

	resTable->addRow(row);

	if (resTable->size() >= 10000)
	{
		resTable->save();
		resTable->clear();
	}
}

void CCalcProData::init( PRateInfo rateInfo )
{
// 	PRateInfo rateInfo = newRateInfo();
// 	string rateName = pTaskInfo->getStringValue(CProcessTaskInfoStruct::key_rateType);
	calcRateStruct = newCalcRateStruct(rateInfo->rateName);
	resTable = newTable(calcRateStruct);
}

