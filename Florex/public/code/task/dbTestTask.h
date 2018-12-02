#pragma once
#include "table/Row.h"
#include "baseTask.h"
#include "process/baseProcess.h"

// taskµÄÔËĞĞÈİÆ÷
class CDbTestTask : public CBaseTask
{
public:
	CDbTestTask(int step, string name);
	~CDbTestTask();

protected:
	void runInThread(const char* argv);
	int completeTask();
	
	int step;
};
typedef shared_ptr<CDbTestTask> PDbTestTask;
#define newDbTestTask(T1, T2) make_shared<CDbTestTask>(T1, T2);