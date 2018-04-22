#include "proCorrecting.h"

CProCorrecting::CProCorrecting()
{
	step = 1;

	lastValue = 0;
	lastTime = 0;
	curValue = 0;
	curTime = 0;
}

CProCorrecting::~CProCorrecting()
{
}

bool CProCorrecting::clac( double tmpTime, double tmpValue, map<double, double>& valueMap )
{
	valueMap.clear();
	if(0 != this->curTime)
	{
		lastTime = curTime;
		lastValue = curValue;
	}
	curTime = tmpTime;
	curValue = tmpValue;

	int timeDef = curTime - lastTime;
	if(0 != timeDef)
	{
		int valueDef = curValue - lastValue;
		double valueSetp = valueDef / timeDef;
		list<long long> timeList;
		PubFun::getIntListByStep(timeList, lastTime, curTime, step);
		double tempValue = 0;
		for(long long timePoint : timeList)
		{
			tempValue = lastValue+(timePoint - lastTime)*valueSetp;
			valueMap.insert(make_pair(timePoint, tempValue));
		}
	}
	return true;
}
