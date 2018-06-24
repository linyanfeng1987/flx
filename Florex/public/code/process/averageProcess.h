#pragma once
#include <string>
#include "baseProcess.h"

using namespace std;
class CAverageProcess : public CBaseProcess
{
public:
	CAverageProcess();
	~CAverageProcess();

	void calc(const char* argv);
private:

};

