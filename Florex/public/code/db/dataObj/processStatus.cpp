#include "processStatus.h"
#include "PubFun.h"

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
	return pRow->find(fields[1])->second;
}

int CProcessStatus::getProcessStatus()
{
	return PubFun::stringToInt(pRow->find(fields[2])->second);
}

int CProcessStatus::getStep()
{
	return PubFun::stringToInt(pRow->find(fields[3])->second);
}

time_t CProcessStatus::getLastTime()
{
	return PubFun::stringToInt(pRow->find(fields[4])->second);
}

void CProcessStatus::load( CRow *pRow )
{
	this->pRow = pRow;
}
