#pragma once
#include "db/dataObj/processTaskConfig.h"

class CProcessTask
{
public:
	CProcessTask();
	~CProcessTask();

	void setProcessTaskConfig(CProcessTaskConfig* pConfig){this->pConfig = pConfig;}
	int run();
protected:
	CProcessTaskConfig* pConfig;

};
