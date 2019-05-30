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
	static string intToString(long nValue);
	static string indexToString(indexType nValue);
	static string doubleToString(double dValue);
	static void log(string str);
	static void logFormat(const char * strFormat, ...);
	static string strFormat(const char * strFormat, ...);
	static string getValueFromMap(string strKey, map<string, string> mapObj);
	static string strToLower(string str);
	static string strToUpper(string str);
	
	static string getTimeFormat(time_t timep);
	static double calcPercentSpeadProS(long int startTime, long startMscd, double startPrice, long int endTime, long endMscd, double endPrice);
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
	

	static void getIntListByStep(list<long long>& destList, double startValue, double endValue, int step);

	static double getFileSize( string filePath );

	static char* wcharToChar(const wchar_t* wp);

	static void buildValueList(time_t startValue, time_t endValue, long step, map<long, long>& resValueMap);

	static void splitParamStr(string paramters, map<string, string> &resMap); 

	//static unsigned long long GetCurrentTimeMsec();
};

