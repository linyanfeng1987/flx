#include "processStatusStruct.h"
#include "PubFun.h"


string CProcessStatusStruct::key_processName = "processName"; 
string CProcessStatusStruct::key_processStatus = "processStatus"; 
string CProcessStatusStruct::key_step = "step"; 
string CProcessStatusStruct::key_buildTaskLastTime = "buildTaskLastTime";
string CProcessStatusStruct::key_completeTaskLastTime = "completeTaskLastTime";


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
	//buildTaskLastTime
	field.load(key_buildTaskLastTime, "int");
	this->insert(make_pair(field.strName, field));
	//completeTaskLastTime
	field.load(key_completeTaskLastTime, "int");
	this->insert(make_pair(field.strName, field));
}

CProcessStatusStruct::~CProcessStatusStruct()
{
	
}

CProcessStatusStruct* CProcessStatusStruct::instence()
{
	static CProcessStatusStruct g;
	return &g;
}
