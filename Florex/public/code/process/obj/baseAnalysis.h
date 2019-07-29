#pragma once
#include "rateValue.h"
#include "rate/rateInfo.h"
#include "config/analysisInfo.h"
using namespace std;

// »ù´¡·ÖÎöÆ÷
class CBaseAnalysis
{
public:
	CBaseAnalysis(PAnalysisInfo _analysisInfo, PRateInfo _rateInfo);
	virtual void add(PRateValue value) = 0;

protected:
	virtual void init();
	PRateInfo rateInfo;
	PAnalysisInfo analysisInfo;
};
typedef shared_ptr<CBaseAnalysis> PBaseAnalysis;
