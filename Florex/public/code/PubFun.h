#pragma once

#include "db/DbObj.h"
#include <time.h>
#include <list>
#include <tuple>
#include <map>
#include <iostream>
#include "ConstDef.h"

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
	static string intToString(int nValue);
	static void log(string str);
	static void logFormat(const char * strFormat, ...);
	static string getValueFromMap(string strKey, map<string, string> mapObj);
	static string strToLower(string str);
	static string strToUpper(string str);
	
	static string getTimeFormat(time_t timep);
	static double calcPercentSpeadProS(long int startTime, long startMscd, double startPrice, long int endTime, long endMscd, double endPrice);
	static double calcPercentSpeadProS(double startPrice, double endPrice, double second);

	static bool readHisFile(ifstream &fin,list<string> &readRes);
	static bool getFileByPath(string path, map<string, string> &files);

	static time_t HisRateStringToDatetime(const char *str);
	static string getStepStr(int nStep);
	static string get14TimeString( SYSTEMTIME& s_time);
	static string get14CurTimeString();

	static double timeConvert(time_t ts, int msec);
	static pair<time_t, int> timeConvert(double dTime);
	

	static void getIntListByStep(list<long long>& destList, double startValue, double endValue, int step);

	//static unsigned long long GetCurrentTimeMsec();
};

