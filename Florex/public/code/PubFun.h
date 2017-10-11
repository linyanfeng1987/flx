#pragma once

#include "db/DbObj.h"
#include <time.h>
#include <list>
#include <tuple>
#include <map>

using namespace std;
class PubFun
{
public:
	PubFun(void);
	~PubFun(void);

	static list<string> split(const string &str,const string &pattern);
	static tuple<bool,string, string> parseKeyValue(string strSrc);
	static int stringToInt(string str);
	static double stringToDouble(string str);
	static void log(string str);
	static void logFormat(const char * strFormat, ...);
	static string getValueFromMap(string strKey, map<string, string> mapObj);
	static string getTimeFormat(time_t timep);
};

