#pragma once
#include <exception>
#include <string>
#include <time.h>
#include <ctime>
#include <fstream>
#include <io.h>
#include <mutex>
#include <thread>

#include "AutoMutex.h"
#include <windows.h>

using namespace std;
class CLogObj
{
public:
	static CLogObj& instance();


	void error(string& msg);
	void info(string& msg);
	void warn(string& msg);
	void debug(string& msg);
	void test(string& msg, string id);
protected:
	string makeFileName(string logFileFormat, string id="");
	string makeLogStr(string levelTag, string& userMsg);
	void checkFile(string fileName);
	void writeLog(string fileName, string& str);
	CLogObj();

	string baseErrorlogFile;
	string baseInfologFile;
	string baseWarnlogFile;
	string baseDebuglogFile;
	string baseTestlogFile;
};

