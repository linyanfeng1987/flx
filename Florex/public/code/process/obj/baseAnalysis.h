#pragma once
#include "rateValue.h"
#include "rate/rateInfo.h"
using namespace std;

// »ù´¡·ÖÎöÆ÷
class CBaseAnalysis
{
public:
	CBaseAnalysis(PRateInfo _rateInfo);
	virtual void add(PRateValue value) = 0;

protected:
	void init();
	PRateInfo rateInfo;
};
typedef shared_ptr<CBaseAnalysis> PBaseAnalysis;
