#pragma once
#include "table/TableStruct.h"

class CProcessStatusStruct : public CTableStruct
{
protected:
	CProcessStatusStruct();
public:
	static CProcessStatusStruct* instence();
	
	~CProcessStatusStruct();

	static string key_processName; 
	static string key_processStatus; 
	static string key_step; 
	static string key_buildTaskLastTime; 
	static string key_completeTaskLastTime; 

};