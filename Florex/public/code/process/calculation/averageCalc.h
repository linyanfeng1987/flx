#include "baseCalc.h"
#include "process/obj/sum.h"

class CAverageCalc : public CBaseCalc
{
public:
	CAverageCalc(int cycle);
	~CAverageCalc();

	double addValue(double curValue);
protected:
	// 周期
	int cycle;
	// 
	// 求和容器
	CSum sum;
};

