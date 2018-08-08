#include "curRateAverageStruct.h"
#include "PubFun.h"
#include "ConstDef.h"


CCurRateAverageStruct::CCurRateAverageStruct(string rateName,string timeName):CCurRateStruct(rateName)
{
	setTimeName(timeName);	
}

CCurRateAverageStruct::~CCurRateAverageStruct()
{
	
}

void CCurRateAverageStruct::setTimeName(string timeName)
{
	tableName = curRateTableName; 
	tableName.append(".").append("_").append(timeName);

	this->setName(tableName);
}
