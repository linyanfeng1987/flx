#include "processType.h"
#include "PubFun.h"

CProcessType::CProcessType()
{
	processTypeName = "";
	timeStep = 0;
}

CProcessType::~CProcessType()
{
}

std::string CProcessType::getProcessName()
{
	if (processTypeName.empty())
	{
		return "";
	}
	else
	{
		return processTypeName + "_" + PubFun::intToString((int)timeStep);
	}
}

std::string CProcessType::getType()
{
	if (processTypeName.empty())
	{
		return "";
	}
	else
	{
		return processTypeName + "_" + PubFun::intToString((int)timeStep);
	}
}

bool CProcessType::compare(string strFlag)
{
	return strFlag == getProcessName();
}