#pragma once
#include <exception>
#include <string>
#include <time.h>
#include <ctime>
#include <fstream>
#include <io.h>

#include <windows.h>

using namespace std;
class CLogObj
{
public:
	static CLogObj& instance();


	void error(string& msg);
	void info(string& msg);
	void warn(string& msg);
protected:
	void checkFile(string fileName);
	void baseLog(string baselogFile, string str);
	void writeLog(string fileName, string str);
	CLogObj();

	string baseErrorlogFile;
	string baseInfologFile;
	string baseWarnlogFile;
};

