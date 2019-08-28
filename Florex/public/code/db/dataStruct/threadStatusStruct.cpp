#include "threadStatusStruct.h"
#include "PubFun.h"

string CThreadStatusStruct::key_threadId = "threadId";
string CThreadStatusStruct::key_rateName = "rateName";
string CThreadStatusStruct::key_threadTypeName = "processTypeName";
string CThreadStatusStruct::key_threadStatus = "threadStatus";
string CThreadStatusStruct::key_stepTime = "stepTime";

//string CThreadStatusStruct::key_step = "step";
string CThreadStatusStruct::key_buildTaskLastTime = "buildTaskLastTime";
string CThreadStatusStruct::key_buildTaskLastTimeDesc = "buildTaskLastTimeDesc";
string CThreadStatusStruct::key_buildTaskStartTimeDesc = "buildTaskStartTimeDesc";
string CThreadStatusStruct::key_buildTaskEndTimeDesc = "buildTaskEndTimeDesc";
string CThreadStatusStruct::key_completeTaskLastTime = "completeTaskLastTime";
string CThreadStatusStruct::key_completeTaskLastTimeDesc = "completeTaskLastTimeDesc";

CThreadStatusStruct::CThreadStatusStruct()
{
	idCount = 0;
	tableName = "core.threadStatus";
	this->setName(tableName);
	CField field;

	field.load(key_threadId, typeInt, true, true);
	this->insert(make_pair(field.strName, field));

	field.load(key_rateName, typeString);
	this->insert(make_pair(field.strName, field));

	//processName
	field.load(key_threadTypeName, typeString);
	this->insert(make_pair(field.strName, field));
	//processStatus
	field.load(key_threadStatus, typeInt);
	this->insert(make_pair(field.strName, field));

	field.load(key_stepTime, typeInt);
	this->insert(make_pair(field.strName, field));

	//step
// 	field.load(key_step, typeInt);
// 	this->insert(make_pair(field.strName, field));
	//buildTaskLastTime
	field.load(key_buildTaskLastTime, typeInt);
	this->insert(make_pair(field.strName, field));

	field.load(key_buildTaskLastTimeDesc, typeString);
	this->insert(make_pair(field.strName, field));

	field.load(key_buildTaskStartTimeDesc, typeString);
	this->insert(make_pair(field.strName, field));

	field.load(key_buildTaskEndTimeDesc, typeString);
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

PThreadStatusStruct CThreadStatusStruct::instence()
{
	static CThreadStatusStruct* p = new CThreadStatusStruct();
	static PThreadStatusStruct g(p);
	return g;
}