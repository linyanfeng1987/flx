#include "taskRunner.h"
#include "process/obj/average/averageAnalysis.h"
#include "process/obj/continue/continueAnalysis.h"
#include "db/DbFunc.h"
#include "task/dbTestTask.h"
#include "ConstDef.h"

// 查找数据库，开启对应线程处理数据

//CGlobalData& CtaskRunner::gData = CGlobalData::instance();
const string CtaskRunner::logTag = "taskRunner";

void processRun(int value)
{
	CtaskRunner taskRunner;
	taskRunner.run();
}

CtaskRunner::CtaskRunner():log(CLogObj::instance()),gData(CGlobalData::instance())
{
	logInfo = newLogInfo(logTag);
	maxProcessCount = 10;
}

CtaskRunner::~CtaskRunner()
{
	int a = 0;
	a++;
	CDbObj::release();
}

void CtaskRunner::run()
{
	while (true)
	{
		rangTaskList();
		//buildTestDbTask();
	}
}

void CtaskRunner::buildTestDbTask()
{
// 	PDbTestTask ptask1 = newDbTestTask(-1, "DBTask1");
// 	PDbTestTask ptask2 = newDbTestTask(2, "DBTask2");
// 
// 	ptask1->run(nullptr);
// 	ptask2->run(nullptr);
// 
// 	while (2 != ptask1->getStatus() || 2 != ptask2->getStatus())
// 	{
// 		::Sleep(1000);
// 	}
}

bool CtaskRunner::reloadTaskList()
{
	bool hasData = false;
	try{
		// 从数据库中加载未执行的任务
		PProcessTaskInfoStruct taskInfoStruct = CProcessTaskInfoStruct::instence();
		string sql = taskInfoStruct->getSelectSql(string("status = 0"));
		PTable table = newTable(taskInfoStruct);
		CDbObj::instance().selectData(sql.c_str(), table);

		for(auto it : *table)
		{
			it.second->setStringValue(CProcessTaskInfoStruct::key_status, string("1"));
			it.second->save();
			gData.addProcessTaskInfo(it.second);

			hasData = true;
		}
	}
	catch (CStrException& e)
	{
		log.error(logInfo, string("reloadTaskList 失败！msg:").append(e.what()));
	}
	
	return hasData;
}

void CtaskRunner::rangTaskList_save()
{
	// 执行任务
	static bool isFirstRun = false;
	static int paramCount = 0;
	PRow processTaskInfo = gData.popProcessTaskInfo(string(""));
	int count = -1;
	if(nullptr != processTaskInfo)
	{
		string processTypeName = processTaskInfo->getStringValue(CProcessTaskInfoStruct::key_processTypeName);
		if (runingTasks.find(processTypeName) == runingTasks.end())
		{
			PProcessTask task = getProcessTask(processTaskInfo);
			count = task.use_count();
			if(nullptr != task)
			{
				isFirstRun = true;
				string param = processTaskInfo->getStringValue(CProcessTaskInfoStruct::key_paramter);
				string testParam = PubFun::intToString(paramCount++);
				task->run(testParam.c_str());
			}
			allTasks.insert(make_pair(task->getTaskId(), task));
			runingTasks.insert(make_pair(processTypeName, task));
			count = task.use_count();
		}
		else
		{
			log.error(string("drop task!!!!!!!"));
		}
	}
	else
	{	if (!reloadTaskList())
		{
			if (isFirstRun)
			{
				
				::Sleep(longSleepTime);
			}
			else
			{
				::Sleep(shortSleepTime);
			}
		}
	}
}

void CtaskRunner::rangTaskList()
{
	// 执行任务
	static bool isFirstRun = false;
	static int paramCount = 0;
	string processKey = gData.popProcessKey();
	int count = -1;
	if(!processKey.empty())
	{
		if (runingTasks.find(processKey) == runingTasks.end())
		{
			PProcessTask task = getProcessTask(processTaskInfo);
			count = task.use_count();
			if(nullptr != task)
			{
				isFirstRun = true;
				string param = processTaskInfo->getStringValue(CProcessTaskInfoStruct::key_paramter);
				string testParam = PubFun::intToString(paramCount++);
				task->run(testParam.c_str());
			}
			allTasks.insert(make_pair(task->getTaskId(), task));
			runingTasks.insert(make_pair(processTypeName, task));
			count = task.use_count();
		}
		else
		{
			log.error(string("drop task!!!!!!!"));
		}
	}
	else
	{	if (!reloadTaskList())
	{
		if (isFirstRun)
		{

			::Sleep(longSleepTime);
		}
		else
		{
			::Sleep(shortSleepTime);
		}
	}
	}
}

// 通过info生成对应处理的process
PCalcProcess CtaskRunner::getProcess( PRow taskInfo, bool baseCalc /*= false*/ )
{
	PRateInfo rateInfo = newRateInfo();
	rateInfo->rateName = taskInfo->getStringValue(CProcessTaskInfoStruct::key_rateType);
	PCalcProcess process = newCalcProcess(rateInfo);
	if (-1 == taskInfo->getStringValue(CProcessTaskInfoStruct::key_processTypeName).find(processType_baseCalc))
	{
		if (-1 != taskInfo->getStringValue(CProcessTaskInfoStruct::key_processTypeName).find(processType_average))
		{
			PAverageAnalysis averageAnalysis = newAverageAnalysis(rateInfo);
			process->addAnalysis(processType_average, averageAnalysis);
		}
		else if (-1 != taskInfo->getStringValue(CProcessTaskInfoStruct::key_processTypeName).find(processType_continue))
		{
			PContinueAnalysis continueAnalysis = newContinueAnalysis(rateInfo);
			process->addAnalysis(processType_continue, continueAnalysis);
		}
	}
	
	return process;
}

PProcessTask CtaskRunner::getProcessTask( PRow processTaskInfoRow )
{
	PCalcProcess process = getProcess(processTaskInfoRow);
	PRow processStatus = CDbFunc::getProcessStatusLine(processTaskInfoRow->getStringValue(CProcessTaskInfoStruct::key_processTypeName));

// 	string rateName = processTaskInfo->getStringValue(CProcessTaskInfoStruct::key_rate);
// 	string processTypeName = processTaskInfo->getStringValue(CProcessTaskInfoStruct::key_processTypeName);
// 	string taskName = rateName + "_" + processTypeName;

	PTaskInfo processTaskInfo = newTaskInfo(processTaskInfoRow, task_calc_stauts);
	PProcessTask task = newProcessTask(processTaskInfo, processStatus, process);

	return task;
}

void CtaskRunner::runFixTask()
{
	for (string rateName : rateNames)
	{
	}
}


