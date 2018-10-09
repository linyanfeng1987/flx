#pragma once
#include "LogObj.h"
#include "db/DbObj.h"
//任务基础类 可能被多线程调用

class CBaseTask
{
public:
	CBaseTask();
	~CBaseTask();
	int getStatus(){return status;}

	int run(const char* argv);
protected:
	virtual void runInThread(const char* argv) = 0;
	virtual int completeTask() = 0;

	int status;
	CLogObj& log;
private:
	
};
