#include "testDbInfoStruct.h"
#include "PubFun.h"

string CTestDbInfoStruct::key_id = "id"; 
string CTestDbInfoStruct::key_value = "value"; 


CTestDbInfoStruct::CTestDbInfoStruct()
{
	tableName = "core.testDb" ; 
	this->setName(tableName);
	CField field;
	//taskId
	field.load(key_id, "string", true);
	this->insert(make_pair(field.strName, field));
	field.load(key_value, "int");
	this->insert(make_pair(field.strName, field));
}

CTestDbInfoStruct::~CTestDbInfoStruct()
{
	
}

PTestDbInfoStruct CTestDbInfoStruct::instence()
{
	static CTestDbInfoStruct *p = new CTestDbInfoStruct();
	static PTestDbInfoStruct g(p);
	return g;
}

