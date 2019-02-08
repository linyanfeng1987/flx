#include "baseCurRateStruct.h"
#include "PubFun.h"
#include "ConstDef.h"

string CBaseCurRateStruct::curTime = "curTime"; 
string CBaseCurRateStruct::curMsec = "curMsec"; 
string CBaseCurRateStruct::timeFormat = "timeFormat"; 


CBaseCurRateStruct::CBaseCurRateStruct(string pureRateName)
{
	setPureRateName(pureRateName);
	CField field;

	field.load(curTime, typeInt, true);
	this->insert(make_pair(field.strName, field));

	field.load(curMsec, typeInt, true);
	this->insert(make_pair(field.strName, field));

	field.load(timeFormat, typeString);
	this->insert(make_pair(field.strName, field));
}

CBaseCurRateStruct::~CBaseCurRateStruct()
{
	
}

void CBaseCurRateStruct::setPureRateName(string pureRateName)
{
	this->pureRateName = pureRateName;
	setTableName(pureRateName);
}


void CBaseCurRateStruct::setTableName( string rateName)
{
	string curTableName = florexDbName; 
	curTableName.append(".").append("currency_pair_").append(rateName);

	this->setName(curTableName);
}