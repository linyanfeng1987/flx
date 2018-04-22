#include "averageCalc.h"


CAverageCalc::CAverageCalc( int cycle ): sum(cycle)
{

}

CAverageCalc::~CAverageCalc()
{
}

double CAverageCalc::addValue( double curValue )
{
	sum.add(curValue);
	return sum.getAverage();
}

