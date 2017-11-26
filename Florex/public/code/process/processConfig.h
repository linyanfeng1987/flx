#pragma once
#include <string>

using namespace std;

class CProcessConfig
{
public:
	CProcessConfig();
	~CProcessConfig();

	string processName;
	// process的标志位
	int porcessFlag;
	// 最小时间步长， 单位秒
	int minTimeStep;

private:
	
};


