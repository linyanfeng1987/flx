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

CProcessType* CGlobalData::getProcessType( string processId )
{
	CProcessType *pCfg = nullptr;
	map<string, CProcessType>::iterator iter = porcessTypes.find(processId);
	if (iter != porcessTypes.end())
	{
		pCfg = &(iter->second);
	}
	return pCfg;
}

void CGlobalData::addprocessInfo( CProcessTaskInfo cfg )
{
	taskMutex.lock();
	tasks.push_back(cfg);
	taskMutex.unlock();
}

CProcessTaskInfo* CGlobalData::popprocessInfo()
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


