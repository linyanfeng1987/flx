#include "processStatus.h"
#include "PubFun.h"
/*
string CProcessStatus::fields[] = {"processName", "processStatus", "step", "lastTime"};


CProcessStatus::CProcessStatus()
{
	if (0 == tableStruct.size())
	{
		tableStruct.setName("core.processTask");
		CField field;
		//processName
		field.load(fields[0], "string", true);
		tableStruct.insert(make_pair(field.strName, field));
		//processStatus
		field.load(fields[1], "int");
		tableStruct.insert(make_pair(field.strName, field));
		//step
		field.load(fields[2], "int");
		tableStruct.insert(make_pair(field.strName, field));
		//lastTime
		field.load(fields[3], "int");
		tableStruct.insert(make_pair(field.strName, field));
	}

	pRow = nullptr;
}

CProcessStatus::~CProcessStatus()
{
	
}

std::string CProcessStatus::getProcessName()
{
	return pRow->getValue(fields[0]);
}

void CProcessStatus::setProcessName( string processName )
{
	pRow->setValue(fields[0], processName);
}

int CProcessStatus::getProcessStatus()
{
	return PubFun::stringToInt( pRow->getValue(fields[1]));
}

void CProcessStatus::setProcessStatus( int processStatus )
{
	pRow->setValue(fields[1], PubFun::intToString(processStatus));
}

int CProcessStatus::getStep()
{
	return PubFun::stringToInt( pRow->getValue(fields[2]));
}

void CProcessStatus::setStep( int step )
{
	pRow->setValue(fields[2], PubFun::intToString(step));
}

time_t CProcessStatus::getLastTime()
{
	return PubFun::stringToInt( pRow->getValue(fields[3]));
}

void CProcessStatus::setLastTime( time_t lastTime )
{
	pRow->setValue(fields[3], PubFun::intToString((int)lastTime));
}

*/

