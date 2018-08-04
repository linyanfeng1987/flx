#include "processTask.h"
#include "db/dataStruct/processTaskInfoStruct.h"
#include "db/dataStruct/processStatusStruct.h"
#include "db/dataStruct/curRateStruct.h"
#include "table/Table.h"
#include "db/DbObj.h"

CProcessTask::CProcessTask( CRow porcessTaskInfo, CRow porcessStatus, CBaseProcess* pProcess ):porcessTaskInfo(porcessTaskInfo),porcessStatus(porcessStatus)
{
	this->pProcess = pProcess;
}

CProcessTask::~CProcessTask()
{
}

int CProcessTask::completeTask()
{
	porcessTaskInfo.setStringValue(CProcessTaskInfoStruct::key_status, "3");
	porcessTaskInfo.save();

	string completeTime = porcessStatus.getStringValue(CProcessStatusStruct::key_buildTaskLastTime);
	porcessStatus.setStringValue(CProcessStatusStruct::key_completeTaskLastTime, completeTime);
	porcessStatus.save();

	return 0;
}

void CProcessTask::runInThread( const char* argv )
{
	string rateName = porcessTaskInfo.getStringValue(CProcessTaskInfoStruct::key_rate);
	string startTime = porcessTaskInfo.getStringValue(CProcessTaskInfoStruct::key_startTime);
	string endTime = porcessTaskInfo.getStringValue(CProcessTaskInfoStruct::key_endTime);
	CCurRateStruct rateStruct(rateName);
	CTable rateTable(&rateStruct);

	string condition = "";
	condition.append(CProcessTaskInfoStruct::key_startTime).append(">=").append(startTime);
	condition.append(" and ");
	condition.append(CProcessTaskInfoStruct::key_endTime).append("<=").append(endTime);
	string sql = rateStruct.getSelectSql(condition);
	CDbObj::instance().SelectData(sql.c_str(), rateTable);

	pProcess->calc(rateTable);

	completeTask();
}

std::string CProcessTask::getTaskId()
{
	return porcessTaskInfo.getStringValue(CProcessTaskInfoStruct::key_taskId);
}
