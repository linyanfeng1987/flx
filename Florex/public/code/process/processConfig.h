#pragma once
#include <string>
#include <map>
#include <list>

using namespace std;
/*
processName，标识唯一的一种运算
由三部分组成，由下划线链接

processType 标识算法的核心部分
timeStep 标识作用时间跨度（通常是算法的参数）若出现没有时间的跨度，那么此为0
rate  标识作用的货币对

结果集表名即processName

放弃对运算层次的标识

依赖关系，逐次配置依赖的数据源，如果是原始数据，则直接是rate


dependOnList 存储的依赖关系， 
其中标识的是 processTypeName 和 timeStep， 具体使用的时候拼上rate来唯一标识数据

*/

/*
CProcessConfig 用于标识依赖关系，以及基础信息，
*/


class CProcessConfig
{
public:
	CProcessConfig();
	~CProcessConfig();
	
	string getProcessName();
	string getType();
	bool compare(string strFlag);

public:
	

	//string rate;

	string processTypeName;
	// 步长， 单位秒
	time_t timeStep;

	list<string> dependOnList;

	// process的标志位
	int porcessFlag;
private:
	
};


