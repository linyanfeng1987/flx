#include<tchar.h>
#include "globalData.h"
#include "tinyXml/tinyxml.h"

CGlobalData::CGlobalData():log(CLogObj::instance())
{
 	wchar_t* path = nullptr;
 	_get_wpgmptr(&path);
	string strPath = PubFun::wcharToChar(path);
	string strMsg = PubFun::strFormat("curPath:%s", strPath.c_str());
	log.info(strMsg);
	cout<<strMsg<<endl;
// 	wchar_t path2[256];
// 	GetModuleFileName(NULL, path2, 256);
// 	wprintf(_T("path:%s\n"),path2);
	tasks = newTable(CProcessTaskInfoStruct::instence());
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
	list<string> tmpList;
	CProcessType tmpType;

	tmpType.processTypeName = processType_baseCalc;
	tmpType.timeStep = 900;
	tmpType.dependOnTypeList.push_back("");
	porcessTypes.insert(make_pair(tmpType.processTypeName, tmpType));
	tmpList.push_back(tmpType.processTypeName);

// 	tmpType.processTypeName = PubFun::strFormat("%s_%s_%s", processType_baseCalc.c_str(),processType_continue.c_str(),processType_average.c_str());
// 	tmpType.timeStep = 900;
// 	tmpType.dependOnTypeList.push_back("");
// 	porcessTypes.insert(make_pair(tmpType.processTypeName, tmpType));
// 	tmpList.push_back(tmpType.processTypeName);

// 	tmpType.processTypeName = processType_average;
// 	tmpType.timeStep = 900;
// 	tmpType.dependOnTypeList.push_back("");
// 	porcessTypes.insert(make_pair(tmpType.processTypeName, tmpType));
// 	tmpList.push_back(tmpType.processTypeName);

// 	tmpType.processTypeName = processType_continue;
// 	tmpType.timeStep = 900;
// 	tmpType.dependOnTypeList.push_back("");
// 	porcessTypes.insert(make_pair(tmpType.processTypeName, tmpType));
// 	tmpList.push_back(tmpType.processTypeName);


	processRates.insert(make_pair(rateNames[3], tmpList));
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

/*
void CGlobalData::addProcessTaskInfo( PRow cfg )
{
	taskMutex.lock();
	//tasks->addRow(cfg);
	string processTypeName = cfg->getStringValue(CProcessTaskInfoStruct::key_threadTypeName);
	string rateName = cfg->getStringValue(CProcessTaskInfoStruct::key_rate);
	string strKey = PubFun::strFormat("%s_%s", processTypeName.c_str(), rateName.c_str());
	auto iter = taskInfos.find(strKey);
	if (iter == taskInfos.end())
	{
		list<PThreadInfo> infos;
		infos.push_back(newThreadInfo(cfg, thread_calc_stauts));
		auto pr = taskInfos.insert(make_pair(strKey, infos));
		processKeys.push_back(strKey);
	}
	else
	{
		iter->second.push_back(newThreadInfo(cfg, thread_calc_stauts));
	}
	taskMutex.unlock();
}

PThreadInfo CGlobalData::popProcessTaskInfo( string &processKey )
{
	PThreadInfo taskInfo = nullptr;
	taskMutex.lock();
// 	auto it = tasks->begin();
// 	if(it != tasks->end())
// 	{
// 		pCfg = it->second;
// 		tasks->erase(it);
// 	}
	auto iter = taskInfos.find(processKey);
	if (iter != taskInfos.end())
	{
		if (!iter->second.empty())
		{
			taskInfo = *(iter->second.begin());
			iter->second.pop_front();
		}
	}

	taskMutex.unlock();
	return taskInfo;
}

std::string CGlobalData::popProcessKey()
{
	string processKey = "";
	taskMutex.lock();
	if (!processKeys.empty())
	{
		processKey = *(processKeys.begin());
		processKeys.pop_front();
	}
	taskMutex.unlock();
	return processKey;
}*/

void CGlobalData::init()
{
	initDataInCode();
	loadConfig();
	initDataStruct();
}

void CGlobalData::initDataInXml()
{

}

void CGlobalData::initDataStruct()
{
	PTestDbInfoStruct p1 = CTestDbInfoStruct::instence();
	PProcessTaskInfoStruct p2 = CProcessTaskInfoStruct::instence();
	PThreadStatusStruct p3 = CThreadStatusStruct::instence();
}

