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
	static string key_processTypeName; 
	static string key_processStatus; 
	
	//static string key_step; 
	static string key_buildTaskLastTime; 
	static string key_buildTaskLastTimeDesc; 
	static string key_completeTaskLastTime; 
	static string key_completeTaskLastTimeDesc; 

	int idCount;
};

