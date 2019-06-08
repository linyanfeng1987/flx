#pragma once
#include <list>
#include <map>

#include "LogObj.h"
#include "ConstDef.h"
#include "process/obj/rateValue.h"

using namespace std;

class CStepValue
{
public:
	CStepValue(){
		stepTime = 0;
		stepValue = 0;
	}
	double stepTime;
	double stepValue;
};

class CSumByTime
{
public:
	CSumByTime(double _maxTimeStep);
	~CSumByTime();

	double add(PRateValue rateValue);
	
	void clear();
	double getSum(){return sumValue;}
	int getSize(){return values.size();}

	double getAverage();
protected:
	void tryPop();

	list<PRateValue> values;
	double maxTimeStep;
	double sumValue;

	CLogObj& log;
// 	double lastTime;
// 	double firstTime;
};

typedef shared_ptr<CSumByTime> PSumByTime;
#define newSumByTime(T) make_shared<CSumByTime>(T)