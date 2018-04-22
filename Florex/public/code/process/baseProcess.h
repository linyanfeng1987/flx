#pragma once
#include <string>

using namespace std;
class CBaseProcess
{
public:
	CBaseProcess();
	~CBaseProcess();

	virtual void calc(char* argv[]) = 0;
private:
	string procssName;
	int processByte;
	int calculateStepSecond;
};

