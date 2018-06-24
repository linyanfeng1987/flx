#include "processTaskInfoStruct.h"
#include "PubFun.h"

string CProcessTaskInfoStruct::key_taskId = "taskId"; 
string CProcessTaskInfoStruct::key_rate = "rate"; 
string CProcessTaskInfoStruct::key_rateType = "rateType"; 
string CProcessTaskInfoStruct::key_startTime = "startTime"; 
string CProcessTaskInfoStruct::key_endTime = "endTime"; 
string CProcessTaskInfoStruct::key_processTypeName = "processTypeName"; 
string CProcessTaskInfoStruct::key_paramter = "paramter"; 
string CProcessTaskInfoStruct::key_status = "status"; 

string CProcessTaskInfoStruct::key_tableName = "core.processTask" ; 
CProcessTaskInfoStruct::CProcessTaskInfoStruct()
{
	this->setName(key_tableName);
	CField field;
	//taskId
	field.load(key_taskId, "string", true);
	this->insert(make_pair(field.strName, field));
	//rateName
	field.load(key_rate, "string");
	this->insert(make_pair(field.strName, field));
	//rateType
	field.load(key_rateType, "int");
	this->insert(make_pair(field.strName, field));
	//startTime
	field.load(key_startTime, "int");
	this->insert(make_pair(field.strName, field));
	//endTime
	field.load(key_endTime, "int");
	this->insert(make_pair(field.strName, field));
	//processName
	field.load(key_processTypeName, "string");
	this->insert(make_pair(field.strName, field));
	//paramter
	field.load(key_paramter, "string");
	this->insert(make_pair(field.strName, field));
	//status
	field.load(key_status, "int");
	this->insert(make_pair(field.strName, field));
}

CProcessTaskInfoStruct::~CProcessTaskInfoStruct()
{
	
}

