#include "baseCap.h"

class CAdditionCap : public CBaseCap
{
public:
	CAdditionCap();
	~CAdditionCap();

protected:
	double calculate(double value, double second);

	double declinePercent;
};
