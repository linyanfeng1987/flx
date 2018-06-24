#pragma once
#include "table/TableStruct.h"


class CProcessTaskInfoStruct : public CTableStruct
{
public:
	CProcessTaskInfoStruct();
	~CProcessTaskInfoStruct();


	static string key_taskId; 
	static string key_rate; 
	static string key_rateType; 
	static string key_startTime; 
	static string key_endTime; 
	static string key_processTypeName; 
	static string key_paramter; 
	static string key_status; 

	static string key_tableName; 
};