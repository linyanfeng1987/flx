#include "threadStatusStruct.h"
#include "PubFun.h"


string CThreadStatusStruct::key_processId = "processId"; 
string CThreadStatusStruct::key_rateName = "rateName"; 
string CThreadStatusStruct::key_processTypeName = "processTypeName"; 
string CThreadStatusStruct::key_processStatus = "processStatus"; 

//string CThreadStatusStruct::key_step = "step"; 
string CThreadStatusStruct::key_buildTaskLastTime = "buildTaskLastTime";
string CThreadStatusStruct::key_buildTaskLastTimeDesc = "buildTaskLastTimeDesc";
string CThreadStatusStruct::key_completeTaskLastTime = "completeTaskLastTime";
string CThreadStatusStruct::key_completeTaskLastTimeDesc = "completeTaskLastTimeDesc"; 

CThreadStatusStruct::CThreadStatusStruct()
{
	idCount = 0;
	tableName = "core.processstatus" ;
	this->setName(tableName);
	CField field;

	field.load(key_processId, typeInt, true, true);
	this->insert(make_pair(field.strName, field));

	field.load(key_rateName, typeString);
	this->insert(make_pair(field.strName, field));

	//processName
	field.load(key_processTypeName, typeString);
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

CThreadStatusStruct::~CThreadStatusStruct()
{
	
}

PProcessStatusStruct CThreadStatusStruct::instence()
{
	static CThreadStatusStruct *p = new CThreadStatusStruct();
	static PProcessStatusStruct g(p);
	return g;
}
