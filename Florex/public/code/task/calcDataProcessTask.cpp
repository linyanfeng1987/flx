#include "calcDataProcessTask.h"
#include "db/dataStruct/processTaskInfoStruct.h"
#include "db/dataStruct/processStatusStruct.h"
#include "db/dataStruct/curRateStruct.h"
#include "table/Table.h"
#include "db/DbObj.h"
#include "PubFun.h"
#include "tools/FunctionLog.h"

const int timeStep = 3600;

CCalcProcessTask::CCalcProcessTask( PRow status, PBaseProcess process, string name ):CProcessTask(status, process, name)
{

}

CCalcProcessTask::~CCalcProcessTask()
{

}

void CCalcProcessTask::runInThread( const char* argv )
{
	try
	{
		CFunctionLog funLog(logInfo, __FUNCTION__, __LINE__);
		string rateName = porcessTaskInfo->getStringValue(CProcessTaskInfoStruct::key_rate);
		string startTime = porcessTaskInfo->getStringValue(CProcessTaskInfoStruct::key_startTime);
		string endTime = porcessTaskInfo->getStringValue(CProcessTaskInfoStruct::key_endTime);
		string rateType = porcessTaskInfo->getStringValue(CProcessTaskInfoStruct::key_rateType);
		string processTypeName = porcessTaskInfo->getStringValue(CProcessTaskInfoStruct::key_processTypeName);
		PCurRateStruct rateStruct = newCurRateStruct(rateName);
		PTable rateTable = newTable(rateStruct);
		calcRateStruct = newCalcRateStruct(rateName);
		resTable = newTable(calcRateStruct);

		map<long, long> resValueMap;
		PubFun::buildValueList(PubFun::stringToInt(startTime), PubFun::stringToInt(endTime), timeStep, resValueMap);

		for (auto iter : resValueMap)
		{
			string condition = "";
			condition.append(CCurRateStruct::curTime).append(">=").append(PubFun::intToString(iter.first));
			condition.append(" and ");
			condition.append(CCurRateStruct::curTime).append("<=").append(PubFun::intToString(iter.second));
			string sql = rateStruct->getSelectSql(condition);
			CDbObj::instance().selectData(sql.c_str(), rateTable);

			for (auto rowPair : *rateTable)
			{
				PRow row = rowPair.second;

				long curTime = row->getIntValue(CCurRateStruct::curTime);
				long curMsec = row->getIntValue(CCurRateStruct::curMsec);
				double curDTime = PubFun::timeConvert(curTime, curMsec);
				double priceBuy = row->getDoubleValue(CCurRateStruct::priceBuy);
				string timeDesc = row->getStringValue(CCurRateStruct::timeFormat);

				PRateValue rateValue = newRateValueP3(curDTime, priceBuy, timeDesc);
				saveToDb(rateValue);
			}
		}
		resTable->save();
		completeTask();
	}
	catch (CStrException& e)
	{
		log.error(logInfo, string("runInThread Ê§°Ü£¡msg:").append(e.what()));
	}
}

void CCalcProcessTask::saveToDb( PRateValue rateValue )
{
	PRow row = newRow(calcRateStruct);
	row->setDoubleValue(CCalcRateStruct::curValue, rateValue->value);
	row->setDoubleValue(CCalcRateStruct::curTime, rateValue->time);
	row->setStringValue(CCalcRateStruct::timeFormat, rateValue->timeDesc);

	resTable->addRow(row);

	if (resTable->size() >= 10000)
	{
		resTable->save();
		resTable->clear();
	}
}
