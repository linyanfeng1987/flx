#pragma once
#include <string>
#include <map>
#include <list>

#include "processType.h"

using namespace std;

// CProcessType + rateœ‡πÿ
class CProcessInfo
{
public:
	CProcessInfo();
	~CProcessInfo();

	string getProcessName(){return "";}
	double timeStep;
	
	void init(CProcessType* pProcessType, string rate);
public:
	
	CProcessType* pProcessType;
	string rate;

	list<string> dependOnList;
private:
	
};


