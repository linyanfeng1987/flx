#pragma once
#include "baseObj.h"

class CProcessTask : public CBaseObj
{
public:
	CProcessTask();
	~CProcessTask();

	static string fields[];

	string getTaskId();
	string getRateName();
	int getRateType();
	time_t getStartTime();
	time_t getEndTime();
	string getProcessTypeName();
	string getParamter();
	int getStatus();


	void setTaskId(string taskId);
	void setRateName(string rateName);
	void setRateType(int rateType);
	void setStartTime(time_t startTime);
	void setEndTime(time_t endTime);
	void setProcessTypeName(string processTypeName);
	void setParamter(string paramter);
	void setStatus(int status);
protected:
	string taskId;
	// 指明元数据的类型
	string rateName;
	int rateType;
	time_t startTime;
	time_t endTime;

	// 指明处理方式
	string processTypeName;
	// process的参数，以逗号分隔
	string paramter;
	// 状态 0.初始化， 1.处理中，2. 处理结束
	int status;  
};