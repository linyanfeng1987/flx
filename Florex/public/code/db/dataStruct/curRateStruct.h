#pragma once
#include "baseCurRateStruct.h"
#include "table/TableStruct.h"


class CCurRateStruct : public CBaseCurRateStruct
{
public:
	CCurRateStruct(string rateName);
	~CCurRateStruct();

	void setRateName(string rateName);
 
	static string priceBuy; 
	static string priceSell; 
	static string volume; 

	static string percentSpead_s; 

	string curRateTableName;
};
typedef shared_ptr<CCurRateStruct> PCurRateStruct;
#define newCurRateStruct(T) make_shared<CCurRateStruct>(T);