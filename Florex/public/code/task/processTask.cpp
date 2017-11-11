#include "processTask.h"
#include "PubFun.h"

string CProcessTask::fields[] = {"taskId", "rateName", "rateType", "startTime", "endTime", "processName", "paramter", "status"};
CTableStruct CProcessTask::tableStruct("processTask");

CProcessTask::CProcessTask()
{
	if (0 == tableStruct.size())
	{
		CField field;
		//taskId
		field.load(fields[0], "string", true);
		tableStruct.insert(make_pair(field.strName, field));
		//rateName
		field.load(fields[1], "string");
		tableStruct.insert(make_pair(field.strName, field));
		//rateType
		field.load(fields[2], "int");
		tableStruct.insert(make_pair(field.strName, field));
		//startTime
		field.load(fields[3], "int");
		tableStruct.insert(make_pair(field.strName, field));
		//endTime
		field.load(fields[4], "int");
		tableStruct.insert(make_pair(field.strName, field));
		//processName
		field.load(fields[5], "string");
		tableStruct.insert(make_pair(field.strName, field));
		//paramter
		field.load(fields[6], "string");
		tableStruct.insert(make_pair(field.strName, field));
		//status
		field.load(fields[7], "int");
		tableStruct.insert(make_pair(field.strName, field));
	}

	pRow = nullptr;
}

CProcessTask::~CProcessTask()
{
	
}

std::string CProcessTask::getTaskId()
{
	return pRow->find(fields[0])->second;
}

std::string CProcessTask::getRateName()
{
	return pRow->find(fields[1])->second;
}

int CProcessTask::getRateType()
{
	return PubFun::stringToInt(pRow->find(fields[2])->second);
}

time_t CProcessTask::getStartTime()
{
	return PubFun::stringToInt(pRow->find(fields[3])->second);
}

time_t CProcessTask::getEndTime()
{
	return PubFun::stringToInt(pRow->find(fields[4])->second);
}

std::string CProcessTask::getProcessName()
{
	return pRow->find(fields[5])->second;
}

std::string CProcessTask::getParamter()
{
	return pRow->find(fields[6])->second;
}

int CProcessTask::getStatus()
{
	return PubFun::stringToInt(pRow->find(fields[7])->second);
}
