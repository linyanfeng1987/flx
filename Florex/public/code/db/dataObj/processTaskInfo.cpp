#include "processTaskInfo.h"
#include "PubFun.h"

string CProcessTaskInfo::fields[] = {"taskId", "rate", "rateType", "startTime", "endTime", "processTypeName", "paramter", "status"};


CProcessTaskInfo::CProcessTaskInfo()
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

CProcessTaskInfo::~CProcessTaskInfo()
{
	
}

std::string CProcessTaskInfo::getTaskId()
{
	
	return pRow->getValue(fields[0]);
}
void CProcessTaskInfo::setTaskId( string taskId )
{
	pRow->setValue(fields[0], taskId);
}

std::string CProcessTaskInfo::getRate()
{
	return pRow->getValue(fields[1]);
}

void CProcessTaskInfo::setRate( string rateName )
{
	pRow->setValue(fields[1], rateName);
}

int CProcessTaskInfo::getRateType()
{
	return PubFun::stringToInt(pRow->getValue(fields[2]));
}

void CProcessTaskInfo::setRateType( int rateType )
{
	pRow->setValue(fields[2], PubFun::intToString(rateType));
}

time_t CProcessTaskInfo::getStartTime()
{
	return PubFun::stringToInt(pRow->getValue(fields[3]));
}

void CProcessTaskInfo::setStartTime( time_t startTime )
{
	pRow->setValue(fields[3], PubFun::intToString((int)startTime));
}

time_t CProcessTaskInfo::getEndTime()
{
	return PubFun::stringToInt(pRow->getValue(fields[4]));
}

void CProcessTaskInfo::setEndTime( time_t endTime )
{
	pRow->setValue(fields[4], PubFun::intToString((int)endTime));
}

std::string CProcessTaskInfo::getProcessTypeName()
{
	return pRow->getValue(fields[5]);
}

void CProcessTaskInfo::setProcessTypeName( string processTypeName )
{
	pRow->setValue(fields[5], processTypeName);
}

std::string CProcessTaskInfo::getParamter()
{
	return pRow->getValue(fields[6]);
}

void CProcessTaskInfo::setParamter( string paramter )
{
	pRow->setValue(fields[6], paramter);
}

int CProcessTaskInfo::getStatus()
{
	return PubFun::stringToInt(pRow->find(fields[7])->second);
}

void CProcessTaskInfo::setStatus( int status )
{
	pRow->setValue(fields[5], PubFun::intToString(status));
}

void CProcessTaskInfo::setProcessConfig( CProcessConfig config )
{
	this->config = config;

	this->setProcessTypeName(config.getProcessName());
}















