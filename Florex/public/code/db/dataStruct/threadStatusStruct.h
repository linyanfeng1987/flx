#pragma once
#include "table/TableStruct.h"

class CThreadStatusStruct;
typedef shared_ptr<CThreadStatusStruct> PThreadStatusStruct;

class CThreadStatusStruct : public CTableStruct
{
protected:
	CThreadStatusStruct();
public:
	static PThreadStatusStruct instence();
	
	~CThreadStatusStruct();

	static string key_threadId; 
	static string key_rateName; 
	static string key_threadTypeName; 
	static string key_threadStatus; 
	
	//static string key_step; 

	// 构建任务的起始时间，终止时间
	static string key_buildTaskStartTimeDesc;
	static string key_buildTaskEndTimeDesc;

	// 最后一个构建任务的起始时间
	static string key_buildTaskLastTime; 
	static string key_buildTaskLastTimeDesc;
	// 轨后一个完成的任务起始时间
	static string key_completeTaskLastTime; 
	static string key_completeTaskLastTimeDesc; 
	
	int idCount;
};

