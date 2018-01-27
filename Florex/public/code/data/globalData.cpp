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

void CGlobalData::addProcessConfig( CProcessTaskInfo cfg )
{
	taskMutex.lock();
	tasks.push_back(cfg);
	taskMutex.unlock();
}

CProcessTaskInfo* CGlobalData::popProcessConfig()
{
	CProcessTaskInfo* pCfg = nullptr;
	taskMutex.lock();
	auto it = tasks.begin();
	if(it != tasks.end())
	{
		pCfg = &*it;
		tasks.erase(it);
	}
	taskMutex.unlock();
	return pCfg;
}


