#pragma once
#include <list>
#include <map>
#include <memory>

#include "ConstDef.h"
#include "process/obj/rateValue.h"
#include "rate/rateInfo.h"
#include "process/obj/sumByTime.h"

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

	PSumByTime averCalcObj;
};

typedef shared_ptr<CAverageObj> PAverageObj;
#define newAverageObj(T,T2,T3) make_shared<CAverageObj>(T,T2,T3)