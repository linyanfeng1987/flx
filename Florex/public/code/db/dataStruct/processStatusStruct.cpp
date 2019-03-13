#include "processStatusStruct.h"
#include "PubFun.h"


string CProcessStatusStruct::key_processName = "processName"; 
string CProcessStatusStruct::key_processStatus = "processStatus"; 
//string CProcessStatusStruct::key_step = "step"; 
string CProcessStatusStruct::key_buildTaskLastTime = "buildTaskLastTime";
string CProcessStatusStruct::key_buildTaskLastTimeDesc = "buildTaskLastTimeDesc";
string CProcessStatusStruct::key_completeTaskLastTime = "completeTaskLastTime";
string CProcessStatusStruct::key_completeTaskLastTimeDesc = "completeTaskLastTimeDesc"; 

CProcessStatusStruct::CProcessStatusStruct()
{
	tableName = "core.processstatus" ;
	this->setName(tableName);
	CField field;
	//processName
	field.load(key_processName, typeString, true);
	this->insert(make_pair(field.strName, field));
	//processStatus
	field.load(key_processStatus, typeInt);
	this->insert(make_pair(field.strName, field));
	//step
// 	field.load(key_step, typeInt);
// 	this->insert(make_pair(field.strName, field));
	//buildTaskLastTime
	field.load(key_buildTaskLastTime, typeInt);
	this->insert(make_pair(field.strName, field));

	field.load(key_buildTaskLastTimeDesc, typeString);
	this->insert(make_pair(field.strName, field));

	//completeTaskLastTime
	field.load(key_completeTaskLastTime, typeInt);
	this->insert(make_pair(field.strName, field));

	field.load(key_completeTaskLastTimeDesc, typeString);
	this->insert(make_pair(field.strName, field));

	this->ensureExist();
}

CProcessStatusStruct::~CProcessStatusStruct()
{
	
}

PProcessStatusStruct CProcessStatusStruct::instence()
{
	static CProcessStatusStruct *p = new CProcessStatusStruct();
	static PProcessStatusStruct g(p);
	return g;
}
