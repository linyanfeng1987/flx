#include "sumByTime.h"

CSumByTime::CSumByTime( double _maxTimeStep )
{
	maxTimeStep = _maxTimeStep;
	sumValue = 0;
	clear();
}

CSumByTime::~CSumByTime()
{
}

double CSumByTime::add( PRateValue curValue )
{
	values.push_back(curValue);
	sumValue += curValue->value;

	double lastTime = curValue->time - maxTimeStep;
	bool isEnd = false;
	while (!isEnd)
	{
		isEnd = true;
		list<PRateValue>::iterator iter = values.begin();
		if (iter != values.end())
		{
			PRateValue rateValue = *iter;
			if (rateValue->time < lastTime)
			{
				values.pop_front();
				sumValue -= rateValue->value;
				isEnd = false;
			}
		}
	}
	return getAverage();
}

void CSumByTime::clear()
{
	values.clear();
	sumValue = 0;
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
