#pragma once
#include <string>

using namespace std;
class CurRate
{
public:
	~CurRate(void);
	CurRate();

	string rateName;
	long int time;         // 价格时间
	long mscd;
	double priceBuy;
	double priceCell;
	unsigned int volume;
	string timeFormat;

	string toString();
};
