#pragma once
#include <list>
#include <map>
#include <memory>


#include "ConstDef.h"
#include "rate/rateInfo.h"
#include "process/obj/rateValue.h"
#include "process/obj/sumByTime.h"
#include "db/dataStruct/curRateAverageStruct.h"
#include "table/Row.h"

using namespace std;

class CAverageObj
{
public:
	CAverageObj(PRateInfo _rateInfo, double _stepTime);

	void add(PRateValue curValue);
	indexType getTagId(){return tagId;}
protected:
	void saveToDb(PRateValue averageValue);
	indexType tagId;
	static indexType tagIdCount;
	PRateInfo rateInfo;
	double stepTime;

	PSumByTime averCalcObj;
	PCurRateAverageStruct averageStruct;
};

typedef shared_ptr<CAverageObj> PAverageObj;
#define newAverageObj(T,T2) make_shared<CAverageObj>(T,T2)