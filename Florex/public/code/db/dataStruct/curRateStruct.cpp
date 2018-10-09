#include "curRateStruct.h"
#include "PubFun.h"
#include "ConstDef.h"

string CCurRateStruct::priceBuy = "priceBuy"; 
string CCurRateStruct::priceSell = "priceCell"; 
string CCurRateStruct::volume = "volume"; 
string CCurRateStruct::percentSpead_s = "percentSpead_s"; 


CCurRateStruct::CCurRateStruct(string rateName):CBaseCurRateStruct(rateName)
{
	init(rateName);
}

// CCurRateStruct::CCurRateStruct( string rateName, string timeSetp ):CBaseCurRateStruct(rateName)
// {
// 	init(rateName, timeSetp);
// }

void CCurRateStruct::init( string rateName )
{
	setTableName(rateName);
	CField field;

	field.load(priceBuy, "double");
	this->insert(make_pair(field.strName, field));

	field.load(priceSell, "double");
	this->insert(make_pair(field.strName, field));

	field.load(volume, "double");
	this->insert(make_pair(field.strName, field));

	field.load(percentSpead_s, "double");
	this->insert(make_pair(field.strName, field));
}


CCurRateStruct::~CCurRateStruct()
{
	
}

void CCurRateStruct::setTableName( string rateName)
{
	tableName = florexDbName; 
	tableName.append(".").append("currency_pair_").append(rateName);

	this->setName(tableName);
	curRateTableName = tableName;
}



