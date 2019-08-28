#include "sum.h"

CSum::CSum(int maxSize)
{
	this->maxSize = maxSize;
	clear();
}

CSum::~CSum()
{
}

void CSum::add(double value)
{
	dataList.push_back(value);
	sumValue += value;
	if (dataList.size() > maxSize)
	{
		auto iter = dataList.begin();
		if (iter != dataList.end())
		{
			sumValue -= *iter;
			dataList.pop_front();
		}
	}
}

void CSum::clear()
{
	dataList.clear();
	sumValue = 0;
}

double CSum::getAverage()
{
	int size = getSize();
	if (0 != size)
	{
		return getSum() / getSize();
	}
	else
	{
		return 0;
	}
}