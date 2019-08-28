#include "monitorValueStruct.h"
#include "PubFun.h"
#include "ConstDef.h"

string CMonitorValueStruct::rateName = "rateName";
string CMonitorValueStruct::monitorName = "monitorName";
string CMonitorValueStruct::curTime = "curTime";
string CMonitorValueStruct::curTimeDesc = "curTimeDesc";
string CMonitorValueStruct::sumValue = "sumValue";
string CMonitorValueStruct::dataType = "dataType";
string CMonitorValueStruct::optCount = "optCount";
mutex CMonitorValueStruct::initMutex;

CMonitorValueStruct::CMonitorValueStruct(bool _isTop) :isTop(_isTop)
{
	string tableName;
	if (isTop)
	{
		tableName = PubFun::strFormat("%s.monitorTopValue", calcDbName.c_str());
	}
	else
	{
		tableName = PubFun::strFormat("%s.monitorValue", calcDbName.c_str());
	}

	setName(tableName);
	init();
}

CMonitorValueStruct::~CMonitorValueStruct()
{
}

void CMonitorValueStruct::init()
{
	CField field;

	field.load(rateName, typeString, true);
	this->insert(make_pair(field.strName, field));

	field.load(monitorName, typeString, true);
	this->insert(make_pair(field.strName, field));

	field.load(curTime, typeDouble, !isTop);
	this->insert(make_pair(field.strName, field));

	field.load(curTimeDesc, typeString);
	this->insert(make_pair(field.strName, field));

	field.load(dataType, typeInt);
	this->insert(make_pair(field.strName, field));

	field.load(sumValue, typeDouble);
	this->insert(make_pair(field.strName, field));

	if (isTop)
	{
		field.load(optCount, typeCount, false, false, true);
		this->insert(make_pair(field.strName, field));
	}

	ensureExist();
}

PMonitorValueStruct CMonitorValueStruct::instence()
{
	initMutex.lock();
	static PMonitorValueStruct gp = newMonitorValueStruct();
	initMutex.unlock();
	return gp;
}

PMonitorValueStruct CMonitorValueStruct::instenceTop()
{
	initMutex.lock();
	static PMonitorValueStruct gp = newMonitorTopValueStruct();
	initMutex.unlock();
	return gp;
}