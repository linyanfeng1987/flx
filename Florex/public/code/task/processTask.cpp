#include "processTask.h"
#include "db/dataStruct/processTaskInfoStruct.h"
#include "db/dataStruct/processStatusStruct.h"
#include "db/dataStruct/curRateStruct.h"
#include "db/dataStruct/calcRateStruct.h"
#include "table/Table.h"
#include "db/DbObj.h"
#include "PubFun.h"
#include "tools/FunctionLog.h"

const int timeStep = 3600;
const string CProcessTask::logTag = "processTask";

CProcessTask::CProcessTask( PTaskInfo _porcessTaskInfo, PRow _porcessStatus, PCalcProcess _process ):porcessTaskInfo(_porcessTaskInfo),porcessStatus(_porcessStatus),CBaseTask(_porcessTaskInfo)
{
	logInfo = newLogInfo(logTag);
	log.debug(logInfo, PubFun::strFormat("CProcessTask build, %d\n", this));
	process = _process;
	isBaseCale = _process->isBaseCalc();
}

CProcessTask::~CProcessTask()
{
	log.debug(logInfo, PubFun::strFormat("CProcessTask end, %d\n", this));
}

int CProcessTask::completeTask()
{
	try
	{
		porcessTaskInfo->getRowData()->setStringValue(CProcessTaskInfoStruct::key_status, string("3"));
		porcessTaskInfo->getRowData()->save();

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
		string rateName = porcessTaskInfo->getRowData()->getStringValue(CProcessTaskInfoStruct::key_rate);
		string startTime = porcessTaskInfo->getRowData()->getStringValue(CProcessTaskInfoStruct::key_startTime);
		string endTime = porcessTaskInfo->getRowData()->getStringValue(CProcessTaskInfoStruct::key_endTime);
		string rateType = porcessTaskInfo->getRowData()->getStringValue(CProcessTaskInfoStruct::key_rateType);
		string processTypeName = porcessTaskInfo->getRowData()->getStringValue(CProcessTaskInfoStruct::key_processTypeName);
		
		string logName = rateName + "_" + processTypeName;

		map<long, long> resValueMap;
		PubFun::buildValueList(PubFun::stringToInt(startTime), PubFun::stringToInt(endTime), timeStep, resValueMap);

		if (process->isBaseCalc())
		{
			baseCalc(resValueMap, rateName);
		}
		else
		{
			calcProcess(resValueMap, rateName);
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
	return porcessTaskInfo->getRowData()->getStringValue(CProcessTaskInfoStruct::key_taskId);
}

void CProcessTask::baseCalc( map<long, long>& resValueMap, string& rateName )
{
	PCurRateStruct rateStruct = newCurRateStruct(rateName);
	PTable rateTable = newTable(rateStruct);
	for (auto iter : resValueMap)
	{
		string condition = "";
		condition.append(CCurRateStruct::curTime).append(">=").append(PubFun::intToString(iter.first));
		condition.append(" and ");
		condition.append(CCurRateStruct::curTime).append("<=").append(PubFun::intToString(iter.second));
		string sql = rateStruct->getSelectSql(condition);

		CDbObj::instance().selectData(sql.c_str(), rateTable);
		process->calc(rateTable);
	}
}

void CProcessTask::calcProcess( map<long, long>& resValueMap, string& rateName )
{
	PCalcRateStruct rateStruct = newCalcRateStruct(rateName);
	PTable rateTable = newTable(rateStruct);
	for (auto iter : resValueMap)
	{
		string condition = "";
		condition.append(CCalcRateStruct::curTime).append(">=").append(PubFun::intToString(iter.first));
		condition.append(" and ");
		condition.append(CCalcRateStruct::curTime).append("<=").append(PubFun::intToString(iter.second));
		string sql = rateStruct->getSelectSql(condition);

		CDbObj::instance().selectData(sql.c_str(), rateTable);

		list<PRateValue> values;
		for (auto rowPair : *rateTable)
		{
			PRow row = rowPair.second;;
			double curDTime = row->getDoubleValue(CCalcRateStruct::curTime);
			double curValue = row->getDoubleValue(CCalcRateStruct::curValue);
			string timeDesc = row->getStringValue(CCalcRateStruct::timeFormat);

			PRateValue rateValue = newRateValueP3(curDTime, curValue, timeDesc);
			values.push_back(rateValue);
		}
		
		process->calc(rateTable);
	}
}
