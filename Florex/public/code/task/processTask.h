#pragma once
#include "table/Row.h"

// taskµÄÔËÐÐÈÝÆ÷
class CProcessTask
{
public:
	CProcessTask();
	~CProcessTask();

	void setProcessTaskConfig(CRow* pConfig){this->pConfig = pConfig;}
	int run();
protected:
	CRow* pConfig;

};
