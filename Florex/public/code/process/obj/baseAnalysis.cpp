#include "baseAnalysis.h"
#include "ConstDef.h"
#include "PubFun.h"

CBaseAnalysis::CBaseAnalysis(PRateInfo _rateInfo):rateInfo(_rateInfo)
{
	init();
}

CBaseAnalysis::CBaseAnalysis( PAnalysisInfo _analysisInfo )
{
	analysisInfo = _analysisInfo;
	initByInfo();
}

void CBaseAnalysis::init()
{

}
