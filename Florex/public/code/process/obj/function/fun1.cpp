#include "fun1.h"
#include <math.h>

// º¯Êý f(x) = 0.618*(1-0.4^x)
double CFun1::calc( double xValue )
{
	double yValue = param1 * (1 - pow(param2, xValue));
	return yValue;
}
