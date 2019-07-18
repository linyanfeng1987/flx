#pragma once
#include "baseCurRateStruct.h" 
#include "table/TableStruct.h"

class CCalcRateStruct;
typedef shared_ptr<CCalcRateStruct> PCalcRateStruct;

class CCalcRateStruct : public CTableStruct
{
public:
	using CTableStruct::CTableStruct;

	CCalcRateStruct(string _rateName,string _timeName, string _typeName);
	~CCalcRateStruct();

	static PCalcRateStruct instence();
	static double getLastRecordTime(PCalcRateStruct calcRateStruct);

	string getLastRecordSql();

	void buildTableName();

	string rateName;
	string timeName;
	string typeName;

	static string curValue; 
	static string curTime; 
	static string timeFormat;
	CCalcRateStruct();
protected:
	
	void init();
	void addField();
}; 

#define newCalcRateAverageStruct(T1,T2) make_shared<CCalcRateStruct>(T1,T2,"average")
#define newCalcRateStruct(T1) make_shared<CCalcRateStruct>(T1,"","")
#define newSPCalcRateStruct(T1) make_shared<CCalcRateStruct>(T1)