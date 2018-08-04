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

	field.load(curTime, "int", true);
	this->insert(make_pair(field.strName, field));

	field.load(curMsec, "int");
	this->insert(make_pair(field.strName, field));

	field.load(timeFormat, "string");
	this->insert(make_pair(field.strName, field));
}

CBaseCurRateStruct::~CBaseCurRateStruct()
{
	
}

void CBaseCurRateStruct::setPureRateName(string pureRateName)
{
	this->pureRateName = pureRateName;
}


