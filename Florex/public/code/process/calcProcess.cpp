#include "calcProcess.h"
#include "db/dataStruct/calcRateStruct.h"
#include "rate/rateInfo.h"
#include "PubFun.h"

CCalcProcess::CCalcProcess(PRateInfo _rateInfo):CBaseProcess(_rateInfo)
{
	init();
}

CCalcProcess::~CCalcProcess()
{

}

void CCalcProcess::calc( PTable rateTable )
{
	list<PRateValue> values;
	for (auto rowPair : *rateTable)
	{
		PRateValue rateValue = calcProData->calcRateValue(rowPair.second);
		values.push_back(rateValue);
	}
	calc(values);
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

void CCalcProcess::init()
{
	calcProData = newCalcProData(rateInfo);
// 	PRateInfo rateInfo = newRateInfo();
// 	rateInfo->rateName = pTaskInfo->getStringValue(CProcessTaskInfoStruct::key_rateType);
}

void CCalcProcess::addAnalysis( string name, PBaseAnalysis analysis )
{
	analysiss.insert(make_pair(name, analysis));
}

bool CCalcProcess::isBaseCalc()
{
	return analysiss.size() == 0;
}
