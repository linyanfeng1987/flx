#pragma once
#include "baseCurRateStruct.h" 
#include "table/TableStruct.h"
#include <mutex>

class CMonitorValueStruct;
typedef shared_ptr<CMonitorValueStruct> PMonitorValueStruct;


class CMonitorValueStruct : public CTableStruct
{
public:
	CMonitorValueStruct(bool _isTop);
	~CMonitorValueStruct();
	static PMonitorValueStruct instence();
	static PMonitorValueStruct instenceTop();

	static string rateName;
	static string monitorName;
	static string curTime;
	static string curTimeDesc;

	static string sumValue;
	static string dataType;
	
	static const int monitorDataType_endOpt = 0;
	static const int monitorDataType_recordOpt = 1;
protected:
	void init();
	static mutex initMutex;

	bool isTop;
}; 

#define newMonitorValueStruct() make_shared<CMonitorValueStruct>(false)
#define newMonitorTopValueStruct() make_shared<CMonitorValueStruct>(true)