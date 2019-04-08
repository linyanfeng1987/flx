#include "curRateAverageStruct.h"
#include "PubFun.h"
#include "ConstDef.h"

string CCurRateAverageStruct::curValue = "curValue"; 
string CCurRateAverageStruct::curTime = "curTime"; 
string CCurRateAverageStruct::timeFormat = "timeFormat"; 

CCurRateAverageStruct::CCurRateAverageStruct(string rateName,string timeName) 
{
	buildTableName(rateName, timeName);	
	init();
}

CCurRateAverageStruct::CCurRateAverageStruct()
{
	addField();
}


CCurRateAverageStruct::~CCurRateAverageStruct()
{
	
}

void CCurRateAverageStruct::init()
{
	addField();
	this->ensureExist();
}

void CCurRateAverageStruct::addField()
{
	CField field;

	field.load(curTime, typeDouble, true);
	this->insert(make_pair(field.strName, field));

	field.load(curValue, typeDouble);
	this->insert(make_pair(field.strName, field));

	field.load(timeFormat, typeString);
	this->insert(make_pair(field.strName, field));
}


void CCurRateAverageStruct::buildTableName( string rateName,string timeName )
{
	string str = PubFun::strFormat("%s.currency_pair_%s_average%s", calcDbName.c_str(), rateName.c_str(), timeName.c_str());
	this->setName(str);
}

PCurRateAverageStruct CCurRateAverageStruct::instence()
{
	static PCurRateAverageStruct p = make_shared<CCurRateAverageStruct>();
	return p;
}


