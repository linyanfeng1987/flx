#pragma once
#include "baseCurRateStruct.h" 
#include "table/TableStruct.h"


class CContinueValueStruct : public CTableStruct
{
public:
	CContinueValueStruct(string rateName);
	~CContinueValueStruct();

	static string groupId;
	static string startTime;
	static string stepTime;

	static string startTimeDesc;

	static string direct;

	static string startValue;
	static string endValue;
	static string stopValue;
	static string stepValue;

	static string startLevel;
	static string maxLevel;
	static string stopLevel;

	static string curRetrcementValue;
	static string retrcementValue;
	static string judgeRetrcementValue;

	static string levels;
	
protected:
	void init();
}; 
typedef shared_ptr<CContinueValueStruct> PContinueValueStruct;
#define newContinueValueStruct(T1) make_shared<CContinueValueStruct>(T1)