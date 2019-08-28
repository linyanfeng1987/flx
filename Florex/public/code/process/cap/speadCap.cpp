#include "speadCap.h"

CSpeadCap::CSpeadCap()
{
	declinePercent = 0.01;
}

CSpeadCap::~CSpeadCap()
{
}

double CSpeadCap::calculate(double beginValue, double endValue, double second)
{
	total += PubFun::calcPercentSpeadProS(beginValue, endValue, second);

	return total;
}