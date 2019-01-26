#pragma once
#include "baseCurRateStruct.h"
#include "table/TableStruct.h"
#include "process/obj/rateValue.h"

#include "table/Row.h"

class CCurRateStruct : public CBaseCurRateStruct
{
public:
	CCurRateStruct(string rateName);
	//CCurRateStruct(string rateName, string timeSetp);
	~CCurRateStruct();
	static PRateValue getRateValue(PRow pCurRateRow);

	static string priceBuy; 
	static string priceSell; 
	static string volume; 

	static string percentSpead_s; 

protected:
	void init();
};
typedef shared_ptr<CCurRateStruct> PCurRateStruct;
#define newCurRateStruct(T) make_shared<CCurRateStruct>(T)