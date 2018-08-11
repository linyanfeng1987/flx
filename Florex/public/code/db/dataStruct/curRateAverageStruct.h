#pragma once
#include "curRateStruct.h"
#include "table/TableStruct.h"


class CCurRateAverageStruct : public CCurRateStruct
{
public:
	CCurRateAverageStruct(string rateName,string timeName);
	~CCurRateAverageStruct();

	void setTimeName(string timeName);

	string timeName;
}; 
typedef shared_ptr<CCurRateAverageStruct> PCurRateAverageStruct;
#define newCurRateAverageStruct(T1,T2) make_shared<CCurRateAverageStruct>(T1,T2);