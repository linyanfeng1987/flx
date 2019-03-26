#pragma once
#include "baseCalc.h"
#include "process/obj/rateValue.h"
#include "process/obj/sumByTime.h"

class CAverageCalc : public CBaseCalc
{
public:
	CAverageCalc(double cycle);
	~CAverageCalc();

	double addValue(double time, double curValue);
protected:
	// 周期
	double cycle;
	// 
	// 求和容器
	CSumByTime sum;
};

typedef shared_ptr<CAverageCalc> PAverageCalc;
#define newAverageCalc(T) make_shared<CAverageCalc>(T)
