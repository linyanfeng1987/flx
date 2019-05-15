#pragma once
#include "table/TableStruct.h"

class CProcessTaskInfoStruct;
typedef shared_ptr<CProcessTaskInfoStruct> PProcessTaskInfoStruct;

class CProcessTaskInfoStruct : public CTableStruct
{
protected:
	CProcessTaskInfoStruct();
public:
	static PProcessTaskInfoStruct instence();
	~CProcessTaskInfoStruct();

	// 唯一id
	static string key_taskId; 
	// 最终使用的rate是带时间的
	static string key_rate; 
	// 普通rate
	static string key_rateType; 
	static string key_startTime; 
	static string key_startTimeDesc; 
	static string key_endTime; 
	static string key_endTimeDesc; 
	// 处理器类型
	static string key_processId; 
	static string key_paramter; 
	// 任务状态：
	//0：任务被分配
	//1：任务已分配
	//2：任务已运行
	//3：任务已完成
	//-1：任务失败
	static string key_status; 
};

