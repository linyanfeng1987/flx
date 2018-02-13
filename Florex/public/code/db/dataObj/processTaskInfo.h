#pragma once
#include "baseObj.h"
#include "process/processInfo.h"

/*
CProcessTask = config + srcdata + timestep
*/
// 任务相关信息，具体任务的操作信息
class CProcessTaskInfo : public CBaseObj
{
public:
	CProcessTaskInfo();
	~CProcessTaskInfo();

	static string fields[];

	string getTaskId();
	string getRate();
	int getRateType();
	time_t getStartTime();
	time_t getEndTime();
	string getProcessTypeName();
	string getParamter();
	int getStatus();


	void setTaskId(string taskId);
	void setRate(string rate);
	void setRateType(int rateType);
	void setStartTime(time_t startTime);
	void setEndTime(time_t endTime);
	void setProcessTypeName(string processTypeName);
	void setParamter(string paramter);
	void setStatus(int status);

	void setprocessInfo(CProcessInfo config);
	CProcessInfo getprocessInfo(){return this->config;}

protected:
	CProcessInfo config;
	string taskId;
	// 指明元数据的类型 
	string rate;

	string dataSrc;
	time_t startTime;
	time_t endTime;

	// 指明处理方式
	string processTypeName;
	// process的参数，以逗号分隔
	string paramter;
	// 状态 0.初始化， 1.处理中，2. 处理结束
	int status;  
};