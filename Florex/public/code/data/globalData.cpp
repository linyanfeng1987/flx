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

void CGlobalData::initDataInCode()
{
	CProcessType tmpType;
	string tmpName = "Average_3600";
	tmpType.processTypeName = tmpName;
	tmpType.porcessFlag = 1;
	tmpType.timeStep = 3600;
	tmpType.dependOnTypeList.push_back("");
	porcessTypes.insert(make_pair(tmpType.processTypeName, tmpType));

	list<string> tmpList;
	tmpList.push_back(tmpName);

	processRates.insert(make_pair("XAUUSD", tmpList));
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

void CGlobalData::addProcessTaskInfo( CProcessTaskInfo cfg )
{
	taskMutex.lock();
	tasks.push_back(cfg);
	taskMutex.unlock();
}

CProcessTaskInfo* CGlobalData::popProcessTaskInfo()
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

void CGlobalData::init()
{
	initDataInCode();
	loadConfig();
}

