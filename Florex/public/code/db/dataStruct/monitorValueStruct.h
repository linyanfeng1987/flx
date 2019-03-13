#pragma once
#include "baseCurRateStruct.h" 
#include "table/TableStruct.h"
#include <mutex>

class CMonitorValueStruct;
typedef shared_ptr<CMonitorValueStruct> PMonitorValueStruct;
#define newMonitorValueStruct() make_shared<CMonitorValueStruct>()

class CMonitorValueStruct : public CTableStruct
{
public:
	CMonitorValueStruct();
	~CMonitorValueStruct();
	static PMonitorValueStruct instence();

	static string rateName;
	static string monitorName;
	static string curTime;

	static string sumValue;
	static string dataType;
	
	static const int monitorDataType_endOpt = 0;
	static const int monitorDataType_recordOpt = 1;
protected:
	void init();
	static mutex initMutex;
}; 
