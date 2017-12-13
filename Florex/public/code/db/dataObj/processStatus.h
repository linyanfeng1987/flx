#pragma once
#include "baseObj.h"

class CProcessStatus : public CBaseObj
{
public:
	CProcessStatus();
	~CProcessStatus();

	static string fields[];

	void load(CRow *pRow);

	string getProcessName();
	int getProcessStatus();
	int getStep();
	time_t getLastTime();

protected:
	CRow* pRow;
};