#include "processTask.h"
#include "PubFun.h"

string CProcessTask::fields[] = {"taskId", "rateName", "rateType", "startTime", "endTime", "processTypeName", "paramter", "status"};


CProcessTask::CProcessTask()
{
	if (0 == tableStruct.size())
	{
		tableStruct.setName("core.processTask");
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
	
	return pRow->getValue(fields[0]);
}
void CProcessTask::setTaskId( string taskId )
{
	pRow->setValue(fields[0], taskId);
}

std::string CProcessTask::getRateName()
{
	return pRow->getValue(fields[1]);
}

void CProcessTask::setRateName( string rateName )
{
	pRow->setValue(fields[1], rateName);
}

int CProcessTask::getRateType()
{
	return PubFun::stringToInt(pRow->getValue(fields[2]));
}

void CProcessTask::setRateType( int rateType )
{
	pRow->setValue(fields[2], PubFun::intToString(rateType));
}

time_t CProcessTask::getStartTime()
{
	return PubFun::stringToInt(pRow->getValue(fields[3]));
}

void CProcessTask::setStartTime( time_t startTime )
{
	pRow->setValue(fields[3], PubFun::intToString((int)startTime));
}

time_t CProcessTask::getEndTime()
{
	return PubFun::stringToInt(pRow->getValue(fields[4]));
}

void CProcessTask::setEndTime( time_t endTime )
{
	pRow->setValue(fields[4], PubFun::intToString((int)endTime));
}

std::string CProcessTask::getProcessTypeName()
{
	return pRow->getValue(fields[5]);
}

void CProcessTask::setProcessTypeName( string processTypeName )
{
	pRow->setValue(fields[5], processTypeName);
}

std::string CProcessTask::getParamter()
{
	return pRow->getValue(fields[6]);
}

void CProcessTask::setParamter( string paramter )
{
	pRow->setValue(fields[6], paramter);
}

int CProcessTask::getStatus()
{
	return PubFun::stringToInt(pRow->find(fields[7])->second);
}

void CProcessTask::setStatus( int status )
{
	pRow->setValue(fields[5], PubFun::intToString(status));
}















