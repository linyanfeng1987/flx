#include "processStatusStruct.h"
#include "PubFun.h"


string CProcessStatusStruct::key_processName = "processName"; 
string CProcessStatusStruct::key_processStatus = "processStatus"; 
string CProcessStatusStruct::key_step = "step"; 
string CProcessStatusStruct::key_lastTime = "lastTime";

CProcessStatusStruct::CProcessStatusStruct()
{
	tableName = "core.processTask" ;
	this->setName(tableName);
	CField field;
	//processName
	field.load(key_processName, "string", true);
	this->insert(make_pair(field.strName, field));
	//processStatus
	field.load(key_processStatus, "int");
	this->insert(make_pair(field.strName, field));
	//step
	field.load(key_step, "int");
	this->insert(make_pair(field.strName, field));
	//lastTime
	field.load(key_lastTime, "int");
	this->insert(make_pair(field.strName, field));
}

CProcessStatusStruct::~CProcessStatusStruct()
{
	
}