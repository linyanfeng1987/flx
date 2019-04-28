#include "calcProcess.h"
#include "db/dataStruct/calcRateStruct.h"
#include "rate/rateInfo.h"
#include "PubFun.h"

CCalcProcess::CCalcProcess()
{
	init();
}

CCalcProcess::~CCalcProcess()
{

}

void CCalcProcess::calc( list<PRateValue> &values )
{
	for (PRateValue rateValue : values)
	{
		for (auto analyPair:analysiss)
		{
			analyPair.second->add(rateValue);
		}
	}
}

void CCalcProcess::init(  )
{
// 	PRateInfo rateInfo = newRateInfo();
// 	rateInfo->rateName = pTaskInfo->getStringValue(CProcessTaskInfoStruct::key_rateType);
}

void CCalcProcess::addAnalysis( string name, PBaseAnalysis analysis )
{
	analysiss.insert(make_pair(name, analysis));
}
