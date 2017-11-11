#pragma once
#include <string>

using namespace std;
class CBaseProcess
{
public:
	CBaseProcess();
	~CBaseProcess();

private:
	string procssName;
	int processByte;
	int calculateStepSecond;
};

