#pragma once
#include <string>

using namespace std;
class CBaseProcess
{
public:
	CBaseProcess();
	~CBaseProcess();

	void detach(const char* argv);
	virtual void calc(const char* argv) = 0;
private:
	string procssName;
	int processByte;
	int calculateStepSecond;
};

