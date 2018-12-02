#include "averageProcess.h"
#include "db/dataStruct/curRateAverageStruct.h"
#include "PubFun.h"

CAverageProcess::CAverageProcess( PRow pTaskInfo ):CBaseProcess(pTaskInfo)
{
	init(pTaskInfo);
}

CAverageProcess::~CAverageProcess()
{

}

void CAverageProcess::calc( PTable& table )
{
	string pureRateName = pTaskInfo->getStringValue(CProcessTaskInfoStruct::key_rateType);
	string timeName = PubFun::getStepNameByType(timeStepType);
	PCurRateAverageStruct curRateAverageStruct = newCurRateAverageStruct(pureRateName, timeName);
	curRateAverageStruct->ensureExist();
	
	CAverageCalc* pCalcBuyObj = new CAverageCalc(cycle);
	CAverageCalc* pCalcSellObj = new CAverageCalc(cycle);;
	// @@@@@这里应该是历史记录的那种表
	for (auto rowIter : *table)
	{
		PRow averageRow = newRow(curRateAverageStruct);
		double priceBuy = rowIter.second->getDoubleValue(CCurRateStruct::priceBuy);
		double priceSell = rowIter.second->getDoubleValue(CCurRateStruct::priceSell);

		double averageBuyValue = pCalcBuyObj->addValue(priceBuy);
		double averageSellValue = pCalcSellObj->addValue(priceSell);

		averageRow->setStringValue(CCurRateAverageStruct::curTime,rowIter.second->getStringValue(CCurRateStruct::curTime));
		averageRow->setStringValue(CCurRateAverageStruct::curMsec,rowIter.second->getStringValue(CCurRateStruct::curMsec));
		averageRow->setStringValue(CCurRateAverageStruct::timeFormat,rowIter.second->getStringValue(CCurRateStruct::timeFormat));
		averageRow->setDoubleValue(CCurRateAverageStruct::priceBuy, averageBuyValue);
		averageRow->setDoubleValue(CCurRateAverageStruct::priceSell, averageSellValue);

		averageRow->save();
	}
}

void CAverageProcess::init( PRow pTaskInfo )
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
}
