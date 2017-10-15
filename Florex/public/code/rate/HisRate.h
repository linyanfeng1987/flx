#pragma once
#include <string>

using namespace std;
class HisRate
{
public:
	HisRate(void);
	~HisRate(void);

	string rateName;
	long int time;         // 周期开始时间
	int timeStepType;
	double   open;         // 开盘价
	double   high;         // 周期最高价
	double   low;          // 周期最低价
	double   close;        // 收盘价
	unsigned int     tick_volume;  // 订单交易量
	int      spread;       // 点差
	unsigned int     real_volume;  // 交易量

	double percentSpead_s;
	string timeFormat;

	string toString();
	void loadByLine(string line);
	string toSqlString();
};

