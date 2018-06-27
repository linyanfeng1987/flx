#pragma once
#include "table/TableStruct.h"


class CProcessTaskInfoStruct : public CTableStruct
{
public:
	CProcessTaskInfoStruct();
	~CProcessTaskInfoStruct();

	// 唯一id
	static string key_taskId; 
	// 最终使用的rate是带时间的
	static string key_rate; 
	// 普通rate
	static string key_rateType; 
	static string key_startTime; 
	static string key_endTime; 
	// 处理器类型
	static string key_processTypeName; 
	static string key_paramter; 
	static string key_status; 

	static string key_tableName; 
};