#pragma once
#include "baseCurRateStruct.h" 
#include "table/TableStruct.h"


class CCurRateAverageStruct : public CBaseCurRateStruct
{
public:
	CCurRateAverageStruct(string rateName,string timeName);
	~CCurRateAverageStruct();

	void setTimeName(string timeName);

	string timeName;
	static string price; 
protected:
	void init();
}; 
typedef shared_ptr<CCurRateAverageStruct> PCurRateAverageStruct;
#define newCurRateAverageStruct(T1,T2) make_shared<CCurRateAverageStruct>(T1,T2);