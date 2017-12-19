#include "globalData.h"

CGlobalData::CGlobalData()
{
}

CGlobalData::~CGlobalData()
{
}

CGlobalData& CGlobalData::instance()
{
	static CGlobalData* pdata = nullptr;

	if (nullptr == pdata)
	{
		pdata = new CGlobalData();
	}

	return *pdata;
}

void CGlobalData::loadConfig()
{

}

CProcessConfig* CGlobalData::getProcessConfig( string processId )
{
	CProcessConfig *pCfg = nullptr;
	map<string, CProcessConfig>::iterator iter = porcessConfigs.find(processId);
	if (iter != porcessConfigs.end())
	{
		pCfg = &(iter->second);
	}
	return pCfg;
}


