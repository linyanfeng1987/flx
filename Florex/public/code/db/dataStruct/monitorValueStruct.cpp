#include "monitorValueStruct.h"
#include "PubFun.h"
#include "ConstDef.h"

string CMonitorValueStruct::rateName = "rateName";
string CMonitorValueStruct::monitorName = "monitorName";
string CMonitorValueStruct::curTime = "curTime";
string CMonitorValueStruct::sumValue = "sumValue";
string CMonitorValueStruct::dataType = "dataType";
mutex CMonitorValueStruct::initMutex;

CMonitorValueStruct::CMonitorValueStruct()
{
	string tableName = PubFun::strFormat("%s.monitorValue", calcDbName.c_str());
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

	field.load(curTime, typeDouble, true);
	this->insert(make_pair(field.strName, field));

	field.load(dataType, typeInt);
	this->insert(make_pair(field.strName, field));

	field.load(sumValue, typeDouble);
	this->insert(make_pair(field.strName, field));

	ensureExist();
}

PMonitorValueStruct CMonitorValueStruct::instence()
{
	initMutex.lock();
	static PMonitorValueStruct gp = newMonitorValueStruct();
	initMutex.unlock();
	return gp;
}

