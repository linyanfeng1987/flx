#include "baseCap.h"

CBaseCap::CBaseCap()
{
}

CBaseCap::~CBaseCap()
{
}

void CBaseCap::setThreshold(list<CThreshold> thresholds)
{
}

CThreshold* CBaseCap::pour(double value, double second)
{
	CThreshold* pDestThreshold = check(total);
	return pDestThreshold;
}

CThreshold* CBaseCap::pour(HisRate rate)
{
	map<string, HisRate>::iterator iter = lastHisRateMap.find(rate.rateName);
	if (iter != lastHisRateMap.end())
	{
		this->calculate(iter->second.open, rate.open, 60);
	}

	lastHisRateMap.insert(make_pair(rate.rateName, rate));
	return nullptr;
}

CThreshold* CBaseCap::pour(CurRate rate)
{
	map<string, CurRate>::iterator iter = lastCurRateMap.find(rate.rateName);
	if (iter != lastCurRateMap.end())
	{
		CurRate& lastRate = iter->second;
		double second = (rate.time - lastRate.time) + (rate.mscd - lastRate.mscd) / 1000.0;
		this->calculate(lastRate.priceBuy, rate.priceBuy, second);
	}

	lastCurRateMap.insert(make_pair(rate.rateName, rate));
	return nullptr;
}

CThreshold* CBaseCap::check(double checkValue)
{
	CThreshold* pDestThreshold = nullptr;
	return pDestThreshold;
}

double CBaseCap::calculate(double beginValue, double endValue, double second)
{
	return 0.0;
}

void CBaseCap::clear()
{
	total = 0;
}