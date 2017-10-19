#include "additionCap.h"



CAdditionCap::CAdditionCap()
{
	declinePercent = 0.01;
}

CAdditionCap::~CAdditionCap()
{

}

double CAdditionCap::calculate( double value, double second )
{
	total = value + total *(1 - second*declinePercent/100);

	return total;
}

