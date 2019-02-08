#pragma once
#include <list>
#include <map>
#include "LinkedHashMap.h"

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
	CSumByTime(double maxTimeStep);
	~CSumByTime();

	double add(double time, double value);
	
	void clear();
	double getSum(){return sumValue;}
	int getSize(){return valueMap.size();}

	double getAverage();
protected:
	void tryPop();

	Linked_map<double, CStepValue> valueMap;
	double maxTimeStep;
	double sumValue;
	double sumTime;
	double lastTime;
	double firstTime;
};

