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
	
	
	PTable resTable = newTable(curRateAverageStruct);

	// @@@@@这里应该是历史记录的那种表
	for (auto rowIter : *table)
	{
		PRow averageRow = newRow(curRateAverageStruct);
		long curTime = rowIter.second->getIntValue(CCurRateStruct::curTime);
		long curMsec = rowIter.second->getIntValue(CCurRateStruct::curMsec);
		double curDTime = PubFun::timeConvert(curTime, curMsec);
		double priceBuy = rowIter.second->getDoubleValue(CCurRateStruct::priceBuy);
		double priceSell = rowIter.second->getDoubleValue(CCurRateStruct::priceSell);

		double averageBuyValue = calcBuyObj->addValue(curDTime, priceBuy);
		double averageSellValue = calcSellObj->addValue(curDTime, priceSell);
		double averagePrice = (averageBuyValue + averageSellValue)/2;
		double defValue = fabs(averagePrice - lastPrice);
		if (defValue > g_priveSetp1)
		{
			lastPrice = averagePrice;
			averageRow->setStringValue(CCurRateAverageStruct::curTime,rowIter.second->getStringValue(CCurRateStruct::curTime));
			averageRow->setStringValue(CCurRateAverageStruct::curMsec,rowIter.second->getStringValue(CCurRateStruct::curMsec));
			averageRow->setStringValue(CCurRateAverageStruct::timeFormat,rowIter.second->getStringValue(CCurRateStruct::timeFormat));
			averageRow->setDoubleValue(CCurRateAverageStruct::price, averagePrice);

			resTable->addRow(averageRow);
		}

		//averageRow->save();
	}
	resTable->save();
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

	calcBuyObj = make_shared<CAverageCalc>(cycle);
	calcSellObj = make_shared<CAverageCalc>(cycle);
	lastPrice = 0;
}
