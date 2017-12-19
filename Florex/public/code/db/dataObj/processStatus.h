#pragma once
#include "baseObj.h"

class CProcessStatus : public CBaseObj
{
public:
	CProcessStatus();
	~CProcessStatus();

	static string fields[];

	string getProcessName();
	void setProcessName(string processName);
	int getProcessStatus();
	void setProcessStatus(int processStatus);
	int getStep();
	void setStep(int step);
	time_t getLastTime();
	void setLastTime(time_t lastTime);
};