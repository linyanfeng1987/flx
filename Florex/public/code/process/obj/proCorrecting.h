#pragma once
#include "PubFun.h"
#include "ConstDef.h"
// 连续的校正数据，返回连续的值，在step中

class CProCorrecting
{
public:
	CProCorrecting();
	~CProCorrecting();

	void setStep(int step) { this->step = step; }
	bool calc(double curTime, double curValue, map<double, double>& valueMap);

protected:
	// 步长， 单位 秒
	int step;
	// 两点的值和对应时间
	double lastValue;
	double lastTime;
	double curValue;
	double curTime;
};
