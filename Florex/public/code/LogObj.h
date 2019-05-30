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
#include <memory>

#include "AutoMutex.h"
#include <windows.h>

using namespace std;

const int write_error = 1;
const int write_info = 2;
const int write_warn = 4;
const int write_debug = 8;
const int write_ext = 16;

const int log_ext = 16;
const int log_error = 15;
const int log_info = 14;
const int log_warn = 12;
const int log_debug = 8;
const int log_noLog = 0;

const int logByThreadId = 1;
const int logByModule = 2;

const int globlaLogType = write_debug;

const unsigned int maxFileLineCount = 20000;

typedef shared_ptr<ofstream> POfstream;
#define newOfstream() make_shared<ofstream>()

class CWriteInfo
{
public:
	CWriteInfo(int _writeType):writeType(_writeType),logFile(nullptr),lineCount(0),fileCount(0){}
	POfstream logFile;
	unsigned int lineCount;
	unsigned int fileCount;
	string filePath;
	int writeType;
};
typedef shared_ptr<CWriteInfo> PWriteInfo;
#define newWriteInfo(T) make_shared<CWriteInfo>(T)

class CLogInfo
{
public:
	CLogInfo(string _name, int _maxLogType);
	CLogInfo(string _name);
	//CLogInfo(size_t id, string name){this->id = id; this->name = name;}
	
	
	// id(线程id)
	size_t threadId;
	// 名称（线程名称）
	string name;
	// error info等
	int levelId;
	// 以线程为记录还是名称等
	int maxLogType;

	// key: tag（info，debug等）, value :path
	map<int, PWriteInfo> logObjs;
};
typedef shared_ptr<CLogInfo> PLogInfo;
#define newLogInfo(T) make_shared<CLogInfo>(T)
#define newLogInfo2(T,T2) make_shared<CLogInfo>(T,T2)

class CLogObj
{
public:
	static CLogObj& instance();

// 	void addLogInfo(size_t id, CLogInfo &info);
// 	void addLogInfo(CLogInfo &info);
	void error(PLogInfo logInfo, string& msg);
	void info(PLogInfo logInfo, string& msg);
	void warn(PLogInfo logInfo, string& msg);
	void debug(PLogInfo logInfo, string& msg);
	void ext(PLogInfo logInfo, string& msg);

	void error(string& msg){error(logInfo, msg);}
	void info( string& msg){info(logInfo, msg);}
	void warn(string& msg){warn(logInfo, msg);}
	void debug(string& msg){debug(logInfo, msg);}
	void ext(string& msg){ext(logInfo, msg);}

	void logString(PLogInfo logInfo, int logType, string& str);

	static string errorTag;
	static string infoTag;
	static string warnTag;
	static string debugTag;
	static string extTag;

protected:
// 	CLogInfo* getLogInfo();
// 	string makeFileName(string logFileFormat, string id="");
// 	string makeFileName( string tag, CLogInfo &logInfo, string id="");
	string makeLogStr(string levelTag, string& userMsg);
//	void writeLog(string fileName, string& str);
	
	void writeLog(PLogInfo logInfo, int logType, string& str);
	void writeLog(PWriteInfo writeInfo, string& str);
	void openNewFile(PLogInfo logInfo, PWriteInfo writeInfo, int logType);
	CLogObj();

	string logBasePathFormat;
	string logBaseTastPathFormat;
	string strPathBase;

	string baseErrorlogFile;
	string baseInfologFile;
	string baseWarnlogFile;
	string baseDebuglogFile;
	string baseTestlogFile;

	static const string logTag;
	PLogInfo logInfo;
	//map<string, string> fileMap;
	map<size_t, CLogInfo> logInfoMap;
};

