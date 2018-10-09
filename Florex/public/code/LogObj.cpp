#include "LogObj.h"
#include "PubFun.h"



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

	logBasePathFormat = strPathBase + "/log/%u";

	baseErrorlogFile = "processError_%d%02d%02d.log";
	baseInfologFile = "processInfo_%d%02d%02d.log";
	baseWarnlogFile = "processWarn_%d%02d%02d.log";
	baseDebuglogFile = "processDebug_%d%02d%02d.log";
	baseTestlogFile = "processTest_%d%02d%02d_%s.log";
}

void CLogObj::error( string& msg )
{
	string logMsg = makeLogStr("error", msg);

	string fileName = "";
	fileName = makeFileName(baseErrorlogFile);
	writeLog(fileName, logMsg);

	fileName = makeFileName(baseInfologFile);
	writeLog(fileName, logMsg);

	fileName = makeFileName(baseWarnlogFile);
	writeLog(fileName, logMsg);

	fileName = makeFileName(baseDebuglogFile);
	writeLog(fileName, logMsg);
}

void CLogObj::info( string& msg )
{
	string logMsg = makeLogStr(string("info"), msg);

	string fileName = "";
	fileName = makeFileName(baseInfologFile);
	writeLog(fileName, logMsg);

	fileName = makeFileName(baseWarnlogFile);
	writeLog(fileName, logMsg);

	fileName = makeFileName(baseDebuglogFile);
	writeLog(fileName, logMsg);
}

void CLogObj::warn( string& msg )
{
	string logMsg = makeLogStr("warn", msg);

	string fileName = "";
	fileName = makeFileName(baseWarnlogFile);
	writeLog(fileName, logMsg);

	fileName = makeFileName(baseDebuglogFile);
	writeLog(fileName, logMsg);
}

void CLogObj::debug( string& msg )
{
	string logMsg = makeLogStr("debug", msg);

	string fileName = "";
	fileName = makeFileName(baseDebuglogFile);
	writeLog(fileName, logMsg);
}

void CLogObj::test( string& msg, string id )
{
	string logMsg = makeLogStr("test", msg);

	string fileName = "";
	fileName = makeFileName(baseTestlogFile, id);
	writeLog(fileName, logMsg);
}

std::string CLogObj::makeFileName( string logFileFormat, string id/*=""*/ )
{
	string fileAllPath = "";
	SYSTEMTIME s_time; 
	GetLocalTime(&s_time); 
	char ch[2048] = {0};
	size_t threadId = std::this_thread::get_id().hash();
	string fileKey = PubFun::strFormat("%u_%s", threadId, logFileFormat.c_str());
	map<string, string>::iterator fileIter = fileMap.find(fileKey);
	if (fileMap.end() == fileIter)
	{
		string logPath = PubFun::strFormat(logBasePathFormat.c_str(), threadId);
		if (id.empty())
		{
			sprintf_s(ch, logFileFormat.c_str(), s_time.wYear, s_time.wMonth, s_time.wDay);
		}
		else{
			sprintf_s(ch, logFileFormat.c_str(), s_time.wYear, s_time.wMonth, s_time.wDay, id.c_str());
		}
		string fileName(ch);
		PubFun::makeNewFile(logPath, fileName);
		fileAllPath = PubFun::strFormat("%s/%s",logPath.c_str(), fileName.c_str());

		fileMap.insert(make_pair(fileKey, fileAllPath));
	}
	else
	{
		fileAllPath = fileIter->second;
	}
	
	return fileAllPath;
}

std::string CLogObj::makeLogStr( string levelTag, string& userMsg )
{
	SYSTEMTIME s_time; 
	GetLocalTime(&s_time); 
	char ch[4096] = {0};
	size_t threadId = std::this_thread::get_id().hash();
	sprintf_s(ch, "[%d-%d-%d %d:%d:%d]:[threadId:%u][%s]%s\n", s_time.wYear, s_time.wMonth, s_time.wDay, 
		s_time.wHour, s_time.wMinute, s_time.wSecond, threadId, levelTag.c_str(), userMsg.c_str());
	string logMsg(ch);
	return logMsg;
}

void CLogObj::writeLog( string fileName, string& str )
{
	ofstream ofile;
	ofile.open(fileName, std::ios_base::app);
	if (ofile.is_open())
	{	
		ofile<<str<<endl;
		ofile.close();  
	}
}
