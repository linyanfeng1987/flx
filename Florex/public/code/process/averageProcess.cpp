#include "averageProcess.h"
#include "db/dataStruct/curRateAverageStruct.h"

CAverageProcess::CAverageProcess()
{
	cycle = 0;
}

CAverageProcess::~CAverageProcess()
{

}

void CAverageProcess::calc( PTable& table )
{
	string pureRateName = pTaskInfo->getStringValue("");
	string timeName = pTaskInfo->getStringValue("");
	CCurRateAverageStruct curRateAverageStruct(pureRateName, timeName);
	

	CAverageCalc* pCalcBuyObj = new CAverageCalc(cycle);
	CAverageCalc* pCalcSellObj = new CAverageCalc(cycle);;
	for (auto rowIter : table)
	{
		PRow averageRow(&curRateAverageStruct);
		double priceBuy = rowIter.second.getDoubleValue(CCurRateStruct::priceBuy);
		double priceSell = rowIter.second.getDoubleValue(CCurRateStruct::priceSell);

		double averageBuyValue = pCalcBuyObj->addValue(priceBuy);
		double averageSellValue = pCalcSellObj->addValue(priceSell);

		averageRow.setStringValue(CCurRateAverageStruct::curTime,rowIter.second.getStringValue(CCurRateStruct::curTime));
		averageRow.setStringValue(CCurRateAverageStruct::curMsec,rowIter.second.getStringValue(CCurRateStruct::curMsec));
		averageRow.setStringValue(CCurRateAverageStruct::timeFormat,rowIter.second.getStringValue(CCurRateStruct::timeFormat));
		averageRow.setDoubleValue(CCurRateAverageStruct::priceBuy, averageBuyValue);
		averageRow.setDoubleValue(CCurRateAverageStruct::priceSell, averageSellValue);

		averageRow.save();
	}
}

void CAverageProcess::init( PRow pTaskInfo )
{
	CBaseProcess::init(pTaskInfo);
	cycle = pTaskInfo->getIntValue(CProcessTaskInfoStruct::key_paramter);
}
