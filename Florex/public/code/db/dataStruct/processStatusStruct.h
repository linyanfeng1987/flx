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

	static string key_processName; 
	static string key_processStatus; 
	//static string key_step; 
	static string key_buildTaskLastTime; 
	static string key_completeTaskLastTime; 

};

