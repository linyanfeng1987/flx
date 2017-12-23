#include "processConfig.h"
#include "PubFun.h"

CProcessConfig::CProcessConfig()
{
	processTypeName = "";
	timeStep = 0;
}

CProcessConfig::~CProcessConfig()
{
}

std::string CProcessConfig::getProcessName()
{
	if(processTypeName.empty())
	{
		return "";
	}
	else
	{
		return processTypeName + "_" + PubFun::intToString((int)timeStep);
	}
}

std::string CProcessConfig::getType()
{
	if(processTypeName.empty())
	{
		return "";
	}
	else
	{
		return processTypeName + "_" + PubFun::intToString((int)timeStep);
	}
}

bool CProcessConfig::compare( string strFlag )
{
	return strFlag == getProcessName();
}
