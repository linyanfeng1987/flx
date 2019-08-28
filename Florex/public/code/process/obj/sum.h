#pragma once
#include <list>

using namespace std;
class CSum
{
public:
	CSum(int maxSize);
	~CSum();

	void add(double value);
	void clear();
	double getSum() { return sumValue; }
	int getSize() { return dataList.size(); }

	double getAverage();
protected:
	list<double> dataList;
	unsigned int maxSize;
	double sumValue;
};
