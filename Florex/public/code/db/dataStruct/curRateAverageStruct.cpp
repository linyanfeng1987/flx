#include "curRateAverageStruct.h"
#include "PubFun.h"
#include "ConstDef.h"

string CCurRateAverageStruct::price = "price"; 

CCurRateAverageStruct::CCurRateAverageStruct(string rateName,string timeName):CBaseCurRateStruct(rateName)
{
	setTimeName(timeName);	
	init();
}


CCurRateAverageStruct::~CCurRateAverageStruct()
{
	
}

void CCurRateAverageStruct::setTimeName(string timeName)
{
	tableName.append("_average");
	if (!timeName.empty())
	{
		tableName.append(timeName);
	}
}

void CCurRateAverageStruct::init()
{
	CField field;

	field.load(price, typeDouble);
	this->insert(make_pair(field.strName, field));
}

