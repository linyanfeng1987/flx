#include "optValueStruct.h"
#include "PubFun.h"
#include "ConstDef.h"

string COptValueStruct::optTagId = "optTagId";
string COptValueStruct::srcTagId = "srcTagId";
string COptValueStruct::tagName = "tagName";
string COptValueStruct::rateName = "rateName";
string COptValueStruct::startTime = "startTime";
string COptValueStruct::startTimeDesc = "startTimeDesc";
string COptValueStruct::startValue = "startValue";
string COptValueStruct::endTime = "endTime";
string COptValueStruct::endTimeDesc = "endTimeDesc";
string COptValueStruct::endValue = "endValue";
string COptValueStruct::stepTime = "stepTime";
string COptValueStruct::resValue = "resValue";
string COptValueStruct::direct = "direct";
string COptValueStruct::optDesc = "optDesc";
mutex COptValueStruct::initMutex;

COptValueStruct::COptValueStruct()
{
	string tableName = PubFun::strFormat("%s.optRecord", calcDbName.c_str());
	setName(tableName);
	init();
}


COptValueStruct::~COptValueStruct()
{
	
}

void COptValueStruct::init()
{
	CField field;

	field.load(optTagId, typeIndex, false, true);
	this->insert(make_pair(field.strName, field));

	field.load(tagName, typeString, true);
	this->insert(make_pair(field.strName, field));
	
	field.load(rateName, typeString, true);
	this->insert(make_pair(field.strName, field));

	field.load(startTime, typeDouble, true);
	this->insert(make_pair(field.strName, field));

	field.load(srcTagId, typeString);
	this->insert(make_pair(field.strName, field));

	field.load(startTimeDesc, typeString);
	this->insert(make_pair(field.strName, field));

	field.load(startValue, typeDouble);
	this->insert(make_pair(field.strName, field));

	field.load(endTime, typeDouble);
	this->insert(make_pair(field.strName, field));

	field.load(endTimeDesc, typeString);
	this->insert(make_pair(field.strName, field));

	field.load(endValue, typeDouble);
	this->insert(make_pair(field.strName, field));

	field.load(stepTime, typeDouble);
	this->insert(make_pair(field.strName, field));

	field.load(resValue, typeDouble);
	this->insert(make_pair(field.strName, field));

	field.load(direct, typeInt);
	this->insert(make_pair(field.strName, field));

	field.load(optDesc, typeBigString);
	this->insert(make_pair(field.strName, field));

	ensureExist();
}

POptValueStruct COptValueStruct::instence()
{
	initMutex.lock();
	static POptValueStruct gp = newOptValueStruct();
	initMutex.unlock();
	return gp;
}

