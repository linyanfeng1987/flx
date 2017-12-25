#pragma once
//任务基础类 可能被多线程调用

class CBaseTask
{
public:
	CBaseTask();
	~CBaseTask();

	virtual int run() = 0;
private:

};
