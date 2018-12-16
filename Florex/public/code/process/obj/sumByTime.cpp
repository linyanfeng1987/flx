#include "sumByTime.h"

CSumByTime::CSumByTime( double maxTimeStep )
{
	this->maxTimeStep = maxTimeStep;
	lastTime = 0;
	sumTime = 0;
	sumValue = 0;
	firstTime = 0;
	clear();
}

CSumByTime::~CSumByTime()
{
}

double CSumByTime::add( double time, double value )
{
	if(0 == firstTime){
		firstTime = time;
		lastTime = time;
	}
	double tagTime = time - firstTime;
	CStepValue stepValue;
	stepValue.stepTime = time - lastTime;
	stepValue.stepValue = value;
	auto inserRes = valueMap.insert(make_pair(tagTime, stepValue));
	if (inserRes.second)
	{
		sumTime += stepValue.stepTime;
		sumValue += value;
		tryPop();
		lastTime = time;
	}
	
	return getAverage();
}

void CSumByTime::tryPop()
{
	if(sumTime > maxTimeStep)
	{
		auto firstIter = valueMap.begin();
		sumTime -= firstIter->second.stepTime;
		sumValue -= firstIter->second.stepValue;
		valueMap.erase(firstIter->first);
		tryPop();
	}
}

void CSumByTime::clear()
{
	valueMap.clear();
	sumValue = 0;
	sumTime = 0;
}

double CSumByTime::getAverage()
{
	int size = getSize();
	if(0 != size)
	{
		return sumValue/size;
	}
	else
	{
		return 0;
	}
}
