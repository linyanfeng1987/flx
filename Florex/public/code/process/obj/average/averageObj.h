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

#include "process/decision/averageDecision.h"

using namespace std;

class CAverageObj
{
public:
	CAverageObj(list<PAverageDecisionTemplate> &_dTemplates, PRateInfo _rateInfo, double _stepTime);

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
	list<PAverageDecision> decisions;
};

typedef shared_ptr<CAverageObj> PAverageObj;
#define newAverageObj(T1,T2,T3) make_shared<CAverageObj>(T1,T2,T3)