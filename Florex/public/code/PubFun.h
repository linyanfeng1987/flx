#pragma once

#include "db/DbObj.h"
#include <time.h>
#include <list>
//#include <tuple>
#include <map>
#include <iostream>

#include "ConstDef.h"
#include "LogObj.h"
#include "Exception.h"

using namespace std;
class PubFun
{
public:
	PubFun(void);
	~PubFun(void);

	static list<string> split(const string &str,const string &pattern);
	static tuple<bool,string, string> parseKeyValue(string strSrc);

	static long stringToInt(string str);
	static double stringToDouble(string str);
	static time_t stringToTimet(string str);

	static string intToString(int nValue);
	static string indexToString(indexType nValue);
	static string timetToString(time_t tValue);
	static string doubleToString(double dValue);
	static void log(string str);
	static void logFormat(const char * strFormat, ...);
	static string strFormat(const char * strFormat, ...);
	static string getValueFromMap(string strKey, map<string, string> mapObj);
	static string strToLower(string str);
	static string strToUpper(string str);
	
	static string getTimeFormat(time_t timep);
	static double calcPercentSpeadProS(time_t startTime, int startMscd, double startPrice, time_t endTime, int endMscd, double endPrice);
	static double calcPercentSpeadProS(double startPrice, double endPrice, double second);

	static bool readHisFile(ifstream &fin,list<string> &readRes);
	static bool getFileByPath(string path, map<string, string> &files);

	static void makeNewFile(string filePath, string fileName);
	static void makePath(string filePath);
	static void removeDir(string dirPath);

	static time_t HisRateStringToDatetime(const char *str);

	static string getStepNameByType(int nStepType);
	static string getStepNameBySecond(time_t second);
	static int getStepType(time_t second);
	
	static string get14TimeString( SYSTEMTIME& s_time);
	static string get14CurTimeString();

	static double timeConvert(time_t ts, double msec);
	static pair<time_t, int> timeConvert(double dTime);
	

	static void getIntListByStep(list<time_t>& destList, double startValue, double endValue, int step);

	static double getFileSize( string filePath );

	static char* wcharToChar(const wchar_t* wp);

	static void buildValueList(time_t startValue, time_t endValue, long step, map<time_t, time_t>& resValueMap);

	static void splitParamStr(string paramters, map<string, string> &resMap); 

	//static unsigned long long GetCurrentTimeMsec();
};

