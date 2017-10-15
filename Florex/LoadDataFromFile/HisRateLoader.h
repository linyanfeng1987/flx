#pragma once
#include <string>

using namespace std;
class CHisRateLoader
{
public:
	CHisRateLoader(void);
	~CHisRateLoader(void);

	bool load(string file);
	bool loadLine(string line);
};

