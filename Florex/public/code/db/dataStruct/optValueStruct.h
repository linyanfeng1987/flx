#pragma once
#include "baseCurRateStruct.h" 
#include "table/TableStruct.h"
#include <mutex>

class COptValueStruct;
typedef shared_ptr<COptValueStruct> POptValueStruct;
#define newOptValueStruct() make_shared<COptValueStruct>()

class COptValueStruct : public CTableStruct
{
public:
	COptValueStruct();
	~COptValueStruct();
	static POptValueStruct instence();

	static string rateName;
	static string startTime;
	static string startTimeDesc;
	static string startValue;

	static string endTime;
	static string endTimeDesc;
	static string endValue;

	static string resValue;
	
	static string direct;

protected:
	void init();
	static mutex initMutex;
}; 
