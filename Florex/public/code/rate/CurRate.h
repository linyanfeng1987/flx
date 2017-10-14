#pragma once
#include <string>

using namespace std;
class CurRate
{
public:
	~CurRate(void);
	CurRate();

	long int time;         // 价格时间
	double priceBuy;
	double priceCell;
	unsigned int volume;

	string toString();
};

