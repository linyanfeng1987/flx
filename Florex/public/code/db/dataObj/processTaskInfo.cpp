#include "processTaskInfo.h"
#include "PubFun.h"
#include "db/dataStruct/processTaskInfoStruct.h"

string CProcessTaskInfo::fields[] = {"taskId", "rate", "rateType", "startTime", "endTime", "processTypeName", "paramter", "status"};


CProcessTaskInfo::CProcessTaskInfo()
{
	pTableStruct = new CProcessTaskInfoStruct();
	pRow = nullptr;
}

CProcessTaskInfo::~CProcessTaskInfo()
{
	
}

std::string CProcessTaskInfo::getTaskId()
{
	
	return pRow->getValue(CProcessTaskInfoStruct::key_taskId);
}
void CProcessTaskInfo::setTaskId( string taskId )
{
	pRow->setValue(CProcessTaskInfoStruct::key_taskId, taskId);
}

std::string CProcessTaskInfo::getRate()
{
	return pRow->getValue(CProcessTaskInfoStruct::key_rate);
}

void CProcessTaskInfo::setRate( string rateName )
{
	pRow->setValue(CProcessTaskInfoStruct::key_rate, rateName);
}

int CProcessTaskInfo::getRateType()
{
	return PubFun::stringToInt(pRow->getValue(CProcessTaskInfoStruct::key_rateType));
}

void CProcessTaskInfo::setRateType( int rateType )
{
	pRow->setValue(CProcessTaskInfoStruct::key_rateType, PubFun::intToString(rateType));
}

time_t CProcessTaskInfo::getStartTime()
{
	return PubFun::stringToInt(pRow->getValue(CProcessTaskInfoStruct::key_startTime));
}

void CProcessTaskInfo::setStartTime( time_t startTime )
{
	pRow->setValue(CProcessTaskInfoStruct::key_startTime, PubFun::intToString((int)startTime));
}

time_t CProcessTaskInfo::getEndTime()
{
	return PubFun::stringToInt(pRow->getValue(CProcessTaskInfoStruct::key_endTime));
}

void CProcessTaskInfo::setEndTime( time_t endTime )
{
	pRow->setValue(CProcessTaskInfoStruct::key_endTime, PubFun::intToString((int)endTime));
}

std::string CProcessTaskInfo::getProcessTypeName()
{
	return pRow->getValue(CProcessTaskInfoStruct::key_processTypeName);
}

void CProcessTaskInfo::setProcessTypeName( string processTypeName )
{
	pRow->setValue(CProcessTaskInfoStruct::key_processTypeName, processTypeName);
}

std::string CProcessTaskInfo::getParamter()
{
	return pRow->getValue(CProcessTaskInfoStruct::key_paramter);
}

void CProcessTaskInfo::setParamter( string paramter )
{
	pRow->setValue(CProcessTaskInfoStruct::key_paramter, paramter);
}

int CProcessTaskInfo::getStatus()
{
	return PubFun::stringToInt(pRow->find(CProcessTaskInfoStruct::key_status)->second);
}

void CProcessTaskInfo::setStatus( int status )
{
	pRow->setValue(CProcessTaskInfoStruct::key_status, PubFun::intToString(status));
}

void CProcessTaskInfo::setprocessInfo( CProcessInfo config )
{
	this->config = config;

	this->setProcessTypeName(config.pProcessType->getType());
	this->setRate(config.rate);

}















