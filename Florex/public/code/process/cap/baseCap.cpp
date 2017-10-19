#include "baseCap.h"

CBaseCap::CBaseCap()
{

}

CBaseCap::~CBaseCap()
{

}

void CBaseCap::setThreshold( list<CThreshold> thresholds )
{

}

CThreshold* CBaseCap::pour( double value, double second )
{
	calculate(value, second);
	CThreshold* pDestThreshold = check(total); 
	return pDestThreshold;
}

CThreshold* CBaseCap::check( double checkValue )
{
	CThreshold* pDestThreshold = nullptr; 
	return pDestThreshold;
}

double CBaseCap::calculate( double value, double second )
{
	return 0.0;
}

