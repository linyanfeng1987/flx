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