#include "taskRunner.h"

// 查找数据库，开启对应线程处理数据

CtaskRunner::CtaskRunner()
{
}

CtaskRunner::~CtaskRunner()
{
}

void CtaskRunner::run()
{
	while (true)
	{
		reloadTaskList();
		rangTaskList();
		
		::Sleep(1000);
	}
}

void CtaskRunner::reloadTaskList()
{

}

void CtaskRunner::rangTaskList()
{

}
