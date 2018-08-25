#include "LogObj.h"
#include "PubFun.h"

#include<direct.h>

CLogObj& CLogObj::instance()
{
	static CLogObj* pdata = nullptr;

	if (nullptr == pdata)
	{
		pdata = new CLogObj();
	}

	return *pdata;
}

CLogObj::CLogObj()
{
	wchar_t* path = nullptr;
	_get_wpgmptr(&path);
	string strPath = PubFun::wcharToChar(path);
	int nIndex = strPath.find_last_of('\\');
	string strPathBase = "";
	if(-1 != nIndex)
	{
		strPathBase = strPath.substr(0, nIndex);
	}

	string logPath = strPathBase + "/log";
	_mkdir(logPath.c_str());

	baseErrorlogFile = logPath + "/processError_%d%02d%02d.log";
	baseInfologFile = logPath + "/processInfo_%d%02d%02d.log";
	baseWarnlogFile = logPath + "/processWarn_%d%02d%02d.log";
}

void CLogObj::error( string& msg )
{
	baseLog(baseErrorlogFile, msg);
}

void CLogObj::info( string& msg )
{
	baseLog(baseInfologFile, msg);
}

void CLogObj::warn( string& msg )
{
	baseLog(baseWarnlogFile, msg);
}

void CLogObj::baseLog(string logFileFormat, string userMsg )
{
	static SYSTEMTIME s_time; 
	GetLocalTime(&s_time);  

	static char ch[2048] = {0};
	memset(ch, 0, sizeof(ch));
	sprintf_s(ch, "[%d-%d-%d %d:%d:%d]:%s\n", s_time.wYear, s_time.wMonth, s_time.wDay, s_time.wHour, s_time.wMinute, s_time.wSecond, userMsg.c_str());
	string logMsg(ch);

	memset(ch, 0, sizeof(ch));
	sprintf_s(ch, logFileFormat.c_str(),  s_time.wYear, s_time.wMonth, s_time.wDay);
	string fileName(ch);

	writeLog(fileName, logMsg);
}

void CLogObj::writeLog( string fileName, string str )
{
	checkFile(fileName);
	ofstream ofile;
	ofile.open(fileName, std::ios_base::app);
	ofile<<str<<endl;
	ofile.close();  
}

void CLogObj::checkFile( string fileName )
{
	FILE* file = nullptr;
	fopen_s(&file, fileName.c_str(),"a"); 
	fclose(file);
}
