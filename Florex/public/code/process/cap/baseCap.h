#include "threshold.h"
#include "PubFun.h"

class CBaseCap
{
public:
	CBaseCap();
	~CBaseCap();

	void setThreshold(list<CThreshold> thresholds);
	CThreshold* pour(double value, double second);

protected:
	CThreshold* check(double checkValue);
	double calculate(double value, double second);

	double total;
};
