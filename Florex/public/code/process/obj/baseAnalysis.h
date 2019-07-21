#pragma once
#include "rateValue.h"
#include "rate/rateInfo.h"
#include "config/analysisInfo.h"
using namespace std;

// »ù´¡·ÖÎöÆ÷
class CBaseAnalysis
{
public:
	CBaseAnalysis(PRateInfo _rateInfo);
	CBaseAnalysis(PAnalysisInfo _analysisInfo);
	virtual void add(PRateValue value) = 0;

protected:
	void init();
	virtual void initByInfo() = 0;
	PRateInfo rateInfo;
	PAnalysisInfo analysisInfo;
};
typedef shared_ptr<CBaseAnalysis> PBaseAnalysis;
