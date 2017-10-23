#include "threshold.h"
#include "rate/HisRate.h"
#include "rate/CurRate.h"
#include "PubFun.h"

class CBaseCap
{
public:
	CBaseCap();
	~CBaseCap();

	void setThreshold(list<CThreshold> thresholds);
	CThreshold* pour(double value, double second);
	CThreshold* pour(HisRate rate);
	CThreshold* pour(CurRate rate);

	void clear();
protected:
	CThreshold* check(double checkValue);
	double calculate(double beginValue, double endValue, double second);


	map<string, CurRate> lastCurRateMap;
	map<string, HisRate> lastHisRateMap;
	double total;
};
