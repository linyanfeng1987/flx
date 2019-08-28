#pragma once
#include <string>
#include "db/dataStruct/processTaskInfoStruct.h"
#include "db/dataStruct/calcRateStruct.h"
#include "db/dataStruct/curRateStruct.h"
#include "obj/rateValue.h"
#include "rate/rateInfo.h"
#include "table/Row.h"
#include "table/Table.h"

using namespace std;
class CCalcProData
{
public:
	CCalcProData(PRateInfo rateInfo);
	~CCalcProData();

	PRateValue calcRateValue(PRow rateRow);
	void init(PRateInfo rateInfo);
	PTableStruct calcRateStruct;
	PTable resTable;

protected:
	void saveToDb(PRateValue rateValue);
};
typedef shared_ptr<CCalcProData> PCalcProData;
#define newCalcProData(T) make_shared<CCalcProData>(T)
