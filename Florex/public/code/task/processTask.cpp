#include "processTask.h"
#include "db/dataStruct/processTaskInfoStruct.h"
#include "db/dataStruct/processStatusStruct.h"
#include "db/dataStruct/curRateStruct.h"
#include "table/Table.h"
#include "db/DbObj.h"

CProcessTask::CProcessTask( PRow taskInfo, PRow status, PBaseProcess process ):porcessTaskInfo(taskInfo),porcessStatus(status)
{
	this->process = process;
}

CProcessTask::~CProcessTask()
{
}

int CProcessTask::completeTask()
{
	try
	{
		porcessTaskInfo->setStringValue(CProcessTaskInfoStruct::key_status, "3");
		porcessTaskInfo->save();

		string completeTime = porcessStatus->getStringValue(CProcessStatusStruct::key_buildTaskLastTime);
		porcessStatus->setStringValue(CProcessStatusStruct::key_completeTaskLastTime, completeTime);
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
		string rateName = porcessTaskInfo->getStringValue(CProcessTaskInfoStruct::key_rate);
		string startTime = porcessTaskInfo->getStringValue(CProcessTaskInfoStruct::key_startTime);
		string endTime = porcessTaskInfo->getStringValue(CProcessTaskInfoStruct::key_endTime);
		PCurRateStruct rateStruct = newCurRateStruct(rateName);
		PTable rateTable = newTable(rateStruct);

		string condition = "";
		condition.append(CProcessTaskInfoStruct::key_startTime).append(">=").append(startTime);
		condition.append(" and ");
		condition.append(CProcessTaskInfoStruct::key_endTime).append("<=").append(endTime);
		string sql = rateStruct->getSelectSql(condition);
		CDbObj::instance().selectData(sql.c_str(), rateTable);
		process->calc(rateTable);
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
