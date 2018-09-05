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
	CProcessType tmpType;
	string tmpName = "average";
	tmpType.processTypeName = tmpName;
	//tmpType.porcessFlag = 1;
	tmpType.timeStep = 3000;
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

void CGlobalData::addProcessTaskInfo( PRow cfg )
{
	taskMutex.lock();
	tasks->addRow(cfg);
	taskMutex.unlock();
}

PRow CGlobalData::popProcessTaskInfo()
{
	PRow pCfg = nullptr;
	taskMutex.lock();
	auto it = tasks->begin();
	if(it != tasks->end())
	{
		pCfg = it->second;
		tasks->erase(it);
	}
	taskMutex.unlock();
	return pCfg;
}

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
	PProcessStatusStruct p3 = CProcessStatusStruct::instence();
}

