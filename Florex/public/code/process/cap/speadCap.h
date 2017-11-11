#pragma once
#include "baseCap.h"

class CSpeadCap : public CBaseCap
{
public:
	CSpeadCap();
	~CSpeadCap();

protected:
	double calculate(double beginValue, double endValue, double second);

	double dStep;
	double declinePercent;
};
