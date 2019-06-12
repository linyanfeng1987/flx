#include "sumByTime.h"
#include "PubFun.h"

CSumByTime::CSumByTime( double _maxTimeStep ):log(CLogObj::instance())
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
	double res = 0;
	if(0 != size)
	{
		res = sumValue/size;
#ifdef DEBUG_CHECK
		double debugSum = 0;
		for (PRateValue rateValue : values)
		{
			debugSum += rateValue->value;
		}
		double debugRes = debugSum / values.size();
		if (debugRes - res > 0.0001)
		{
			log.error(PubFun::strFormat("error average value res:%lf, debugRes:%lf", res, debugRes));
		}
#endif // DEBUG_CHECK
	}
	else
	{
		res = 0;
	}

	return res;
}
