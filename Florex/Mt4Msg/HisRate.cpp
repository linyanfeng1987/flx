
#include "HisRate.h"


HisRate::HisRate(void)
{
	time = 0;
	timeStepType = 0;
	open = 0.0;
	high = 0.0;
	low = 0.0;
	close = 0.0;
	tick_volume = 0;
	spread = -1;
	real_volume = 0;
}


HisRate::~HisRate(void)
{
}

std::string HisRate::toString()
{
	char tmp[1024] = {0};
	sprintf_s(tmp, "time:%d, timeStepType:%d, open:%f, high:%f, low:%f, close:%f, tick_volume:%d, spread:%d, real_volume:%d",
		time, timeStepType, open,  high, low, close, tick_volume,  spread, real_volume);

	return string(tmp);
}
