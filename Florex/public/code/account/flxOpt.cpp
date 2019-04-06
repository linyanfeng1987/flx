#include "flxOpt.h"
#include "table/Row.h"

indexType CFlxOpt::optTagIdCount = 0;

CFlxOpt::CFlxOpt(string _tagName, indexType _srcTagId, string _rateName, PRateValue _beginValue, int _direct ):tagName(_tagName),srcTagId(_srcTagId),rateName(_rateName),beginValue(_beginValue),direct(_direct)
{
	optTagId = ++optTagIdCount;
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
	setEnd(_endValue, string(""));
}

void CFlxOpt::setEnd( PRateValue _endValue, string& _desc )
{
	endValue = _endValue;
	desc = _desc;
	endRes = (beginValue->value-endValue->value)*direct;
	saveToDb();
}

void CFlxOpt::saveToDb()
{
	PRow row = newRow(optStruct);

	row->setIndexValue(COptValueStruct::optTagId, optTagId);
	row->setStringValue(COptValueStruct::tagName, tagName);
	row->setIndexValue(COptValueStruct::srcTagId, srcTagId);
	row->setStringValue(COptValueStruct::rateName, rateName);
	row->setDoubleValue(COptValueStruct::startTime, beginValue->time);
	row->setStringValue(COptValueStruct::startTimeDesc, beginValue->timeDesc);
	row->setDoubleValue(COptValueStruct::startValue, beginValue->value);
	row->setDoubleValue(COptValueStruct::endTime, endValue->time);
	row->setStringValue(COptValueStruct::endTimeDesc, endValue->timeDesc);
	row->setDoubleValue(COptValueStruct::endValue, endValue->value);
	row->setDoubleValue(COptValueStruct::stepTime, endValue->time - beginValue->time);
	row->setDoubleValue(COptValueStruct::resValue, endRes);
	row->setIntValue(COptValueStruct::direct, direct);
	row->setStringValue(COptValueStruct::optDesc, desc);
	row->save();
}
