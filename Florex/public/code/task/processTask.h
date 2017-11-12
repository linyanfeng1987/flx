#pragma once
#include <string>
#include "table/TableStruct.h"
#include "table/Field.h"
#include "table/Row.h"

using namespace std;
class CProcessTask
{
public:
	CProcessTask();
	~CProcessTask();

	static CTableStruct tableStruct;
	static string fields[];

	void load(CRow *pRow);

	string getTaskId();
	string getRateName();
	int getRateType();
	time_t getStartTime();
	time_t getEndTime();
	string getProcessName();
	string getParamter();
	int getStatus();

protected:
	string taskId;
	// 指明元数据的类型
	string rateName;
	int rateType;
	time_t startTime;
	time_t endTime;

	// 指明处理方式
	string processName;
	// process的参数，以逗号分隔
	string paramter;
	// 状态 0.初始化， 1.处理中，2. 处理结束
	int status;  

	CRow* pRow;
};