#include "taskRunner.h"
#include "db/dataStruct/processTaskInfoStruct.h"

// 查找数据库，开启对应线程处理数据

CDbObj& CtaskRunner::db = CDbObj::instance();
CGlobalData& CtaskRunner::gData = CGlobalData::instance();

void processRun(int value)
{
	CtaskRunner taskRunner;
	taskRunner.run();
}

CtaskRunner::CtaskRunner()
{
	maxProcessCount = 10;
}

CtaskRunner::~CtaskRunner()
{
}

void CtaskRunner::run()
{
	while (true)
	{
		rangTaskList();	
	}
}

bool CtaskRunner::reloadTaskList()
{
	bool hasData = false;
	// 从数据库中加载未执行的任务
	CProcessTaskInfoStruct processTaskInfoStruct;
	string sql = processTaskInfoStruct.getSelectSql("status = 0");
	CTable table;
	db.SelectData(sql.c_str(), table);

	for(auto it : table)
	{
		CProcessTaskInfo processTaskInfo;	
		processTaskInfo.load(&(it.second));
		processTaskInfo.setStatus(1);
		db.ExecuteSql(processTaskInfo.pRow->getUpdateSql().c_str());
		gData.addProcessTaskInfo(processTaskInfo);

		hasData = true;
	}
	return hasData;
}

void CtaskRunner::rangTaskList()
{
	// 执行任务
	CProcessTaskInfo* processTaskInfo = gData.popProcessTaskInfo();
	if(nullptr != processTaskInfo)
	{
		CBaseProcess* pProcess = getProcess(*processTaskInfo);
		if(nullptr != pProcess)
		{
			string param = processTaskInfo->getParamter();
			pProcess->detach(param.c_str());
		}
	}
	else
	{	if (!reloadTaskList())
		{
			::Sleep(1000);
		}
	}
}

// 通过info生成对应处理的process
CBaseProcess* CtaskRunner::getProcess( CProcessTaskInfo& taskInfo )
{
	if (taskInfo.getProcessTypeName() == "acb")
	{
	}
	return nullptr;
}


