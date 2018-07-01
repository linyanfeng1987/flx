#include "curRateStruct.h"
#include "PubFun.h"

string CCurRateStruct::curTime = "curTime"; 
string CCurRateStruct::curMsec = "curMsec"; 
string CCurRateStruct::priceBuy = "priceBuy"; 
string CCurRateStruct::priceCell = "priceCell"; 
string CCurRateStruct::volume = "volume"; 
string CCurRateStruct::timeFormat = "timeFormat"; 
string CCurRateStruct::percentSpead_s = "percentSpead_s"; 

CCurRateStruct::CCurRateStruct()
{
	tableName = "ratebase" ; 
	this->setName(tableName);
	CField field;

	field.load(curTime, "int", true);
	this->insert(make_pair(field.strName, field));

	field.load(curMsec, "int");
	this->insert(make_pair(field.strName, field));

	field.load(priceBuy, "double");
	this->insert(make_pair(field.strName, field));

	field.load(priceCell, "double");
	this->insert(make_pair(field.strName, field));

	field.load(volume, "double");
	this->insert(make_pair(field.strName, field));

	field.load(timeFormat, "string");
	this->insert(make_pair(field.strName, field));

	field.load(percentSpead_s, "double");
	this->insert(make_pair(field.strName, field));
}

CCurRateStruct::~CCurRateStruct()
{
	
}

