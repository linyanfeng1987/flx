#pragma once
#include "baseCurRateStruct.h" 
#include "table/TableStruct.h"

class CCurRateAverageStruct;
typedef shared_ptr<CCurRateAverageStruct> PCurRateAverageStruct;

class CCurRateAverageStruct : public CTableStruct
{
public:
	CCurRateAverageStruct(string rateName,string timeName);
	~CCurRateAverageStruct();

	static PCurRateAverageStruct instence();

	void buildTableName(string rateName,string timeName);

	string timeName;
	static string curValue; 
	static string curTime; 
	static string timeFormat;

protected:
	CCurRateAverageStruct();
	void init();
	void addField();
}; 

#define newCurRateAverageStruct(T1,T2) make_shared<CCurRateAverageStruct>(T1,T2)