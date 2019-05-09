#pragma once
#include "table/TableStruct.h"

class CProcessStatusStruct;
typedef shared_ptr<CProcessStatusStruct> PProcessStatusStruct;

class CProcessStatusStruct : public CTableStruct
{
protected:
	CProcessStatusStruct();
public:
	static PProcessStatusStruct instence();
	
	~CProcessStatusStruct();

	static string key_processId; 
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

