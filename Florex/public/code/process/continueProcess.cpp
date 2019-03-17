#include "continueProcess.h"
#include "db/dataStruct/curRateAverageStruct.h"
#include "rate/rateInfo.h"
#include "PubFun.h"

CContinueProcess::CContinueProcess( PRow pTaskInfo ):CBaseProcess(pTaskInfo)
{
	init(pTaskInfo);
}

CContinueProcess::~CContinueProcess()
{

}

void CContinueProcess::calc( PTable& table )
{
	string pureRateName = pTaskInfo->getStringValue(CProcessTaskInfoStruct::key_rateType);
	PContinueValueStruct pTableStruct = newContinueValueStruct(pureRateName);
	for (auto rowIter : *table)
	{
		PRateValue pRateValue = CCurRateStruct::getRateValue(rowIter.second);
		pContinueAnalysis->add(pRateValue, pTableStruct);
	}
}

void CContinueProcess::init( PRow pTaskInfo )
{
	//@@@ 这里需要获取时间跨度值
	string paramter = pTaskInfo->getStringValue(CProcessTaskInfoStruct::key_paramter);

	map<string, string> resMap;
	PubFun::splitParamStr(paramter, resMap);
	auto iter = resMap.find("timeStep");
	string strTimeStep = "";
	if (resMap.end() != iter )
	{
		strTimeStep = iter->second;
	}
	cycle =  PubFun::stringToInt(strTimeStep);
	timeStepType = PubFun::getStepType(cycle);
	PRateInfo rateInfo = newRateInfo();
	rateInfo->rateName = pTaskInfo->getStringValue(CProcessTaskInfoStruct::key_rateType);
	pContinueAnalysis = newContinueAnalysis(rateInfo);
	lastPrice = 0;
}
