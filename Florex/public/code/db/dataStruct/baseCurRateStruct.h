#pragma once
#include "table/TableStruct.h"


class CBaseCurRateStruct : public CTableStruct
{
public:
	CBaseCurRateStruct(string pureRateName);
	~CBaseCurRateStruct();

	void setPureRateName(string pureRateName);
	void setTableName(string rateName);


	static string curTime; 
	static string curMsec; 

	static string timeFormat; 

	string pureRateName;
};
typedef shared_ptr<CBaseCurRateStruct> PBaseCurRateStruct;
#define newBaseCurRateStruct(T1) make_shared<CBaseCurRateStruct>(T1)