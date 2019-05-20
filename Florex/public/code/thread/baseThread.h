#pragma once
#include <memory>
#include "LogObj.h"
#include "db/DbObj.h"
#include "db/dataStruct/processTaskInfoStruct.h"

using namespace std;

enum CalcThreadType
{
	// 映射计算，可开多线程
	thread_calc_map,
	// 形态计算，不可开多线程，保持顺序
	thread_calc_stauts,
};

class CThreadInfo
{
public:
	CThreadInfo(PRow _threadInfoRow, CalcThreadType _threadType);
	//CThreadInfo(string _taskName, ThreadType _ThreadType);
	~CThreadInfo(){};
	void setThreadType(CalcThreadType _threadType);
	bool threadAble(){return threadsAble;}
	PRow getRowData(){return threadInfoRow;}
private:
	bool threadsAble;
	CalcThreadType threadType; 
	PRow threadInfoRow;
};

typedef shared_ptr<CThreadInfo> PThreadInfo;
#define newThreadInfo(T1,T2) make_shared<CThreadInfo>(T1,T2)
//#define newThreadInfo(T1) make_shared<CThreadInfo>(T1)

//任务基础类 可能被多线程调用
class CBaseThread
{
public:
	CBaseThread(PThreadInfo _threadInfo);
	~CBaseThread();
	PThreadInfo getThreadInfo(){return threadInfo;}
	int getStatus(){return status;}

	int run(const char* argv);
protected:
	void baseRunInThread(const char* argv);
	virtual void runInThread(const char* argv) = 0;

	int status;
	CLogObj& log;
	PThreadInfo threadInfo;
private:
	
};
