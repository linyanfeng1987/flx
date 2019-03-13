#include "processTask.h"
#include "db/dataStruct/processTaskInfoStruct.h"
#include "db/dataStruct/processStatusStruct.h"
#include "db/dataStruct/curRateStruct.h"
#include "table/Table.h"
#include "db/DbObj.h"
#include "PubFun.h"
#include "tools/FunctionLog.h"

const int timeStep = 3600;

CProcessTask::CProcessTask( PRow status, PBaseProcess process, string name ):porcessTaskInfo(process->getTaskInfo()),porcessStatus(status),CBaseTask(name)
{
	log.debug(PubFun::strFormat("CProcessTask build, %d\n", this));
	this->process = process;
}

CProcessTask::~CProcessTask()
{
	log.debug(PubFun::strFormat("CProcessTask end, %d\n", this));
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
		log.error(string("completeTask Ê§°Ü£¡msg:").append(e.what()));
	}

	return 0;
}

void CProcessTask::runInThread( const char* argv )
{
	try
	{
		CFunctionLog funLog(__FUNCTION__, __LINE__);
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
			CDbObj::instance().selectData(sql.c_str(), rateTable);
			process->calc(rateTable);
		}
		completeTask();
	}
	catch (CStrException& e)
	{
		log.error(string("runInThread Ê§°Ü£¡msg:").append(e.what()));
	}
}

std::string CProcessTask::getTaskId()
{
	return porcessTaskInfo->getStringValue(CProcessTaskInfoStruct::key_taskId);
}
