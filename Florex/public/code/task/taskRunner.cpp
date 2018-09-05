#include "taskRunner.h"
#include "process/averageProcess.h"
#include "db/DbFunc.h"
#include "task/dbTestTask.h"

// 查找数据库，开启对应线程处理数据

CGlobalData& CtaskRunner::gData = CGlobalData::instance();

void processRun(int value)
{
	CtaskRunner taskRunner;
	taskRunner.run();
}

CtaskRunner::CtaskRunner():log(CLogObj::instance())
{
	maxProcessCount = 10;
}

CtaskRunner::~CtaskRunner()
{
	int a = 0;
	a++;
	//CDbObj::release();
}

void CtaskRunner::run()
{
	while (true)
	{
		//rangTaskList();
		buildTestDbTask();
	}
}

void CtaskRunner::buildTestDbTask()
{
	PDbTestTask ptask1 = newDbTestTask(-1);
	PDbTestTask ptask2 = newDbTestTask(2);

	ptask1->run(nullptr);
	ptask2->run(nullptr);

	while (2 != ptask1->getStatus() || 2 != ptask2->getStatus())
	{
		::Sleep(1000);
	}
}

bool CtaskRunner::reloadTaskList()
{
	bool hasData = false;
	try{
		// 从数据库中加载未执行的任务
		PProcessTaskInfoStruct taskInfoStruct = CProcessTaskInfoStruct::instence();
		string sql = taskInfoStruct->getSelectSql("status = 0");
		PTable table = newTable(taskInfoStruct);
		CDbObj::instance().selectData(sql.c_str(), table);

		for(auto it : *table)
		{
			it.second->setStringValue(CProcessTaskInfoStruct::key_status, "1");
			it.second->save();
			gData.addProcessTaskInfo(it.second);

			hasData = true;
		}
	}
	catch (CStrException& e)
	{
		log.error(string("reloadTaskList 失败！msg:").append(e.what()));
	}
	
	return hasData;
}

void CtaskRunner::rangTaskList()
{
	// 执行任务
	PRow processTaskInfo = gData.popProcessTaskInfo();
	if(nullptr != processTaskInfo)
	{
		PProcessTask task = getProcessTask(processTaskInfo);
		if(nullptr != task)
		{
			string param = processTaskInfo->getStringValue(CProcessTaskInfoStruct::key_paramter);
			task->run(param.c_str());
		}
		runingTasks.insert(make_pair(task->getTaskId(), task));
	}
	else
	{	if (!reloadTaskList())
		{
			::Sleep(1000);
		}
	}
}

// 通过info生成对应处理的process
PBaseProcess CtaskRunner::getProcess( PRow taskInfo )
{
	PBaseProcess process = nullptr;
	if (taskInfo->getStringValue(CProcessTaskInfoStruct::key_processTypeName) == "average")
	{
		process = newAverageProcess(); 
	}
	return process;
}

PProcessTask CtaskRunner::getProcessTask( PRow taskInfo )
{
	PBaseProcess pProcess = getProcess(taskInfo);
	PRow processStatus = CDbFunc::getProcessStatusLine(taskInfo->getStringValue(CProcessTaskInfoStruct::key_processTypeName));

	PProcessTask task = newProcessTask(taskInfo, processStatus, pProcess);

	return task;
}


