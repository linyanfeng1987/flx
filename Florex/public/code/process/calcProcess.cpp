#include "calcProcess.h"
#include "db/dataStruct/calcRateStruct.h"
#include "rate/rateInfo.h"
#include "PubFun.h"

CCalcProcess::CCalcProcess( PProcessCfgInfo _threadInfo, PRateInfo _rateInfo ):CBaseProcess(_threadInfo, rateInfo)
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
#ifdef DEBUG_CHECK
		//时间正向检查
		if (timeCheck <= rateValue->time)
		{
			timeCheck = rateValue->time;
		}
		else
		{
			CLogObj::instance().error(PubFun::strFormat("time error before time:%s, curent time:%s", 
				PubFun::getTimeFormat((time_t)timeCheck).c_str(),
				PubFun::getTimeFormat((time_t)rateValue->time).c_str()));
		}
#endif // DEBUG_CHECK

		for (auto analyPair:analysiss)
		{
			analyPair.second->add(rateValue);
		}
	}
}

void CCalcProcess::init()
{
	calcProData = newCalcProData(rateInfo);
	timeCheck = 0;
// 	PRateInfo rateInfo = newRateInfo();
// 	rateInfo->rateName = pTaskInfo->getStringValue(CProcessTaskInfoStruct::key_rateType);
}

void CCalcProcess::addAnalysis( string name, PBaseAnalysis analysis )
{
	analysiss.insert(make_pair(name, analysis));
}

