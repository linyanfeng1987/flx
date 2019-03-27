#include "processTask.h"
#include "db/dataStruct/processTaskInfoStruct.h"
#include "db/dataStruct/processStatusStruct.h"
#include "db/dataStruct/curRateStruct.h"
#include "table/Table.h"
#include "db/DbObj.h"
#include "PubFun.h"
#include "tools/FunctionLog.h"

const int timeStep = 3600;
const string CProcessTask::logTag = "processTask";

CProcessTask::CProcessTask( PRow status, PBaseProcess process, string name ):porcessTaskInfo(process->getTaskInfo()),porcessStatus(status),CBaseTask(name)
{
	logInfo = newLogInfo(logTag);
	log.debug(logInfo, PubFun::strFormat("CProcessTask build, %d\n", this));
	this->process = process;
}

CProcessTask::~CProcessTask()
{
	log.debug(logInfo, PubFun::strFormat("CProcessTask end, %d\n", this));
}

int CProcessTask::completeTask()
{
	try
	{
		porcessTaskInfo->setStringValue(CProcessTaskInfoStruct::key_status, string("3"));
		porcessTaskInfo->save();

		time_t completeTime = porcessStatus->getTimeValue(CProcessStatusStruct::key_buildTaskLastTime);
		porcessStatus->setTimeValue(CProcessStatusStruct::key_completeTaskLastTime, completeTime);
		porcessStatus->setStringValue(CProcessStatusStruct::key_completeTaskLastTimeDesc, PubFun::getTimeFormat(completeTime));
		porcessStatus->save();
	}
	catch (CStrException& e)
	{
		log.error(logInfo, string("completeTask Ê§°Ü£¡msg:").append(e.what()));
	}

	return 0;
}

void CProcessTask::runInThread( const char* argv )
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
		string logName = rateName + "_" + processTypeName;

		map<long, long> resValueMap;
		PubFun::buildValueList(PubFun::stringToInt(startTime), PubFun::stringToInt(endTime), timeStep, resValueMap);

		for (auto iter : resValueMap)
		{
			string condition = "";
			condition.append(CCurRateStruct::curTime).append(">=").append(PubFun::intToString(iter.first));
			condition.append(" and ");
			condition.append(CCurRateStruct::curTime).append("<=").append(PubFun::intToString(iter.second));
			string sql = rateStruct->getSelectSql(condition);

			list<PRateValue> values;
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
				values.push_back(rateValue);
			}
			process->calc(values);
		}
		completeTask();
	}
	catch (CStrException& e)
	{
		log.error(logInfo, string("runInThread Ê§°Ü£¡msg:").append(e.what()));
	}
}

std::string CProcessTask::getTaskId()
{
	return porcessTaskInfo->getStringValue(CProcessTaskInfoStruct::key_taskId);
}
