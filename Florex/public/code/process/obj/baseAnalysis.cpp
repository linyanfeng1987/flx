#include "baseAnalysis.h"
#include "ConstDef.h"
#include "PubFun.h"


CBaseAnalysis::CBaseAnalysis( PAnalysisInfo _analysisInfo, PRateInfo _rateInfo )
{
	rateInfo = _rateInfo;
	analysisInfo = _analysisInfo;
	init();
}

void CBaseAnalysis::init()
{

}
