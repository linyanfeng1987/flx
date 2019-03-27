#pragma once
#include "baseCurRateStruct.h" 
#include "table/TableStruct.h"


class CCurRateAverageStruct : public CTableStruct
{
public:
	CCurRateAverageStruct(string rateName,string timeName);
	~CCurRateAverageStruct();

	void buildTableName(string rateName,string timeName);

	string timeName;
	static string curValue; 
	static string curTime; 
	static string timeFormat;

protected:
	void init();
}; 
typedef shared_ptr<CCurRateAverageStruct> PCurRateAverageStruct;
#define newCurRateAverageStruct(T1,T2) make_shared<CCurRateAverageStruct>(T1,T2)