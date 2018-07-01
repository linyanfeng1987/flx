#pragma once
#include "table/TableStruct.h"

class CProcessStatusStruct : public CTableStruct
{
public:
	CProcessStatusStruct();
	~CProcessStatusStruct();

	static string key_processName; 
	static string key_processStatus; 
	static string key_step; 
	static string key_lastTime; 

};