#include "processTaskInfoStruct.h"
#include "PubFun.h"

string CProcessTaskInfoStruct::key_taskId = "taskId"; 
string CProcessTaskInfoStruct::key_rate = "rate"; 
string CProcessTaskInfoStruct::key_rateType = "rateType"; 
string CProcessTaskInfoStruct::key_startTime = "startTime"; 
string CProcessTaskInfoStruct::key_startTimeDesc = "startTimeDesc"; 
string CProcessTaskInfoStruct::key_endTime = "endTime"; 
string CProcessTaskInfoStruct::key_endTimeDesc = "endTimeDesc"; 
string CProcessTaskInfoStruct::key_processId = "processId"; 
string CProcessTaskInfoStruct::key_paramter = "paramter"; 
string CProcessTaskInfoStruct::key_status = "status"; 

CProcessTaskInfoStruct::CProcessTaskInfoStruct()
{
	tableName = "core.processTask" ; 
	this->setName(tableName);
	CField field;
	//taskId
	field.load(key_taskId, typeString, true);
	this->insert(make_pair(field.strName, field));
	//processName
	field.load(key_processId, typeInt);
	this->insert(make_pair(field.strName, field));
	//rateName
	field.load(key_rate, typeString);
	this->insert(make_pair(field.strName, field));
	//rateType
	field.load(key_rateType, typeString);
	this->insert(make_pair(field.strName, field));
	//startTime
	field.load(key_startTime, typeInt);
	this->insert(make_pair(field.strName, field));

	field.load(key_startTimeDesc, typeString);
	this->insert(make_pair(field.strName, field));
	//endTime
	field.load(key_endTime, typeInt);
	this->insert(make_pair(field.strName, field));
	//endTime
	field.load(key_endTimeDesc, typeString);
	this->insert(make_pair(field.strName, field));
	//paramter
	field.load(key_paramter, typeString);
	this->insert(make_pair(field.strName, field));
	//status
	field.load(key_status, typeInt);
	this->insert(make_pair(field.strName, field));

	this->ensureExist();
}

CProcessTaskInfoStruct::~CProcessTaskInfoStruct()
{
	
}

PProcessTaskInfoStruct CProcessTaskInfoStruct::instence()
{
	static CProcessTaskInfoStruct *p = new CProcessTaskInfoStruct();
	static PProcessTaskInfoStruct g(p);
	return g;
}

