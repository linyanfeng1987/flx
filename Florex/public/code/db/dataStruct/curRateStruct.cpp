#include "curRateStruct.h"
#include "PubFun.h"
#include "ConstDef.h"

string CCurRateStruct::priceBuy = "priceBuy"; 
string CCurRateStruct::priceSell = "priceCell"; 
string CCurRateStruct::volume = "volume"; 
string CCurRateStruct::percentSpead_s = "percentSpead_s"; 


CCurRateStruct::CCurRateStruct(string rateName):CBaseCurRateStruct(rateName)
{
	init();
}

void CCurRateStruct::init()
{
	CField field;

	field.load(priceBuy, typeDouble);
	this->insert(make_pair(field.strName, field));

	field.load(priceSell, typeDouble);
	this->insert(make_pair(field.strName, field));

	field.load(volume, typeDouble);
	this->insert(make_pair(field.strName, field));

	field.load(percentSpead_s, typeDouble);
	this->insert(make_pair(field.strName, field));
}


CCurRateStruct::~CCurRateStruct()
{
	
}

PRateValue CCurRateStruct::getRateValue( PRow pCurRateRow )
{
	long curTime = pCurRateRow->getIntValue(CCurRateStruct::curTime);
	long curMsec = pCurRateRow->getIntValue(CCurRateStruct::curMsec);
	double curDTime = PubFun::timeConvert(curTime, curMsec);
	double priceBuy = pCurRateRow->getDoubleValue(CCurRateStruct::priceBuy);

	PRateValue pValue = newRateValueP3(curDTime, priceBuy, pCurRateRow->getStringValue(CCurRateStruct::timeFormat));
	return pValue;
}





