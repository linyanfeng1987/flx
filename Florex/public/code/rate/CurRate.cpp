
#include "CurRate.h"


CurRate::CurRate(void)
{
	time = 0;
	priceBuy = 0.0;
	priceCell = 0.0;
	volume = 0;
}


CurRate::~CurRate(void)
{
}

std::string CurRate::toString()
{
	char tmp[1024] = {0};
	sprintf_s(tmp, "time:%d, priceBuy:%0.4f, priceCell:%0.4f, volume:%d", time, priceBuy, priceCell, volume);

	return string(tmp);
}
