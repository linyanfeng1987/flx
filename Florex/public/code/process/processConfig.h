#pragma once
#include <string>
#include <map>

using namespace std;

class CProcessConfig
{
public:
	CProcessConfig();
	~CProcessConfig();

	string processTypeName;
	// process的标志位
	int porcessFlag;
	// 最小时间步长， 单位秒
	int minTimeStep;

	map<string, string> rates;
private:
	
};


