#include "processInfo.h"
#include "PubFun.h"

CProcessInfo::CProcessInfo()
{
	
}

CProcessInfo::~CProcessInfo()
{
}

void CProcessInfo::init( CProcessType* pProcessType, string rate )
{
	this->pProcessType = pProcessType;
	this->rate = rate;

	dependOnList.clear();
	for(string dependType : pProcessType->dependOnTypeList)
	{
		dependOnList.push_back(dependType.append("_").append(rate));
	}
}

