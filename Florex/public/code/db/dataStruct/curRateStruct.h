#pragma once
#include "table/TableStruct.h"


class CCurRateStruct : public CTableStruct
{
public:
	CCurRateStruct();
	~CCurRateStruct();

	static string curTime; 
	static string curMsec; 
	static string priceBuy; 
	static string priceCell; 
	static string volume; 

	static string timeFormat; 
	static string percentSpead_s; 

};