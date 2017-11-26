#pragma once
#include "PubFun.h"
#include "ConstDef.h"
#include "process/processConfig.h"


class CGlobalData
{
public:
	static CGlobalData& instance();
	
	~CGlobalData();

	void loadConfig();

	map<string, CProcessConfig> taskConfigs;

protected:
	CGlobalData();
};

