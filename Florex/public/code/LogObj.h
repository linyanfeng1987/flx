#pragma once
#include <exception>
#include <string>
#include <time.h>
#include <ctime>
#include <fstream>
#include <io.h>
#include <mutex>
#include <thread>
#include <map>

#include "AutoMutex.h"
#include <windows.h>

using namespace std;

class CLogInfo
{
public:
	CLogInfo(string name);
	CLogInfo(size_t id, string name){this->id = id; this->name = name;}
	
	
	// id(线程id)
	size_t id;
	// 名称（线程名称）
	string name;
	// key: tag（info，debug等）, value :path
	map<string, string> logPathMap;
};


class CLogObj
{
public:
	static CLogObj& instance();

	void addLogInfo(size_t id, CLogInfo &info);
	void addLogInfo(CLogInfo &info);
	void error(string& msg);
	void info(string& msg);
	void warn(string& msg);
	void debug(string& msg);
	void test(string& msg, string id);
	void ext( string& msg, string extTag );

	static string errorTag;
	static string infoTag;
	static string warnTag;
	static string debugTag;
	static string extTag;

protected:
	CLogInfo* getLogInfo();
	string makeFileName(string logFileFormat, string id="");
	string makeFileName( string tag, CLogInfo &logInfo, string id="");
	string makeLogStr(string levelTag, string& userMsg);
	void writeLog(string fileName, string& str);
	CLogObj();

	string logBasePathFormat;
	string logBaseTastPathFormat;

	string baseErrorlogFile;
	string baseInfologFile;
	string baseWarnlogFile;
	string baseDebuglogFile;
	string baseTestlogFile;


	

	map<string, string> fileMap;
	map<size_t, CLogInfo> logInfoMap;
};

