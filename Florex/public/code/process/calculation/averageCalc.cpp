#include "averageCalc.h"


CAverageCalc::CAverageCalc( double cycle ): sum(cycle)
{

}

CAverageCalc::~CAverageCalc()
{
}

double CAverageCalc::addValue(double time, double curValue )
{
	return sum.add(time, curValue);
}

