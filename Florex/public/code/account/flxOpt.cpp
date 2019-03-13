#include "flxOpt.h"
#include "table/Row.h"

CFlxOpt::CFlxOpt(string _rateName, PRateValue _beginValue, int _direct ):rateName(_rateName),beginValue(_beginValue),direct(_direct)
{
	endValue = nullptr;
	endRes = 0;
	optStruct = COptValueStruct::instence();
}

double CFlxOpt::getCurResValue( PRateValue curValue )
{
	return (beginValue->value-curValue->value)*direct;
}

double CFlxOpt::getEndResValue()
{
	return endRes;
}

void CFlxOpt::setEnd( PRateValue _endValue )
{
	endValue = _endValue;
	endRes = (beginValue->value-endValue->value)*direct;
	saveToDb();
}

void CFlxOpt::saveToDb()
{
	PRow row = newRow(optStruct);

	row->setStringValue(COptValueStruct::rateName, rateName);
	row->setDoubleValue(COptValueStruct::startTime, beginValue->time);
	row->setStringValue(COptValueStruct::startTimeDesc, beginValue->timeDesc);
	row->setDoubleValue(COptValueStruct::startValue, beginValue->value);
	row->setDoubleValue(COptValueStruct::endTime, endValue->time);
	row->setStringValue(COptValueStruct::endTimeDesc, endValue->timeDesc);
	row->setDoubleValue(COptValueStruct::endValue, endValue->value);
	row->setDoubleValue(COptValueStruct::resValue, endRes);
	row->setIntValue(COptValueStruct::direct, direct);
	row->save();
}
