#pragma once
#include "table/TableStruct.h"


class CBaseCurRateStruct : public CTableStruct
{
public:
	CBaseCurRateStruct(string pureRateName);
	~CBaseCurRateStruct();

	void setPureRateName(string pureRateName);


	static string curTime; 
	static string curMsec; 

	static string timeFormat; 

	string pureRateName;
};