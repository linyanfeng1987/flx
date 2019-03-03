#include "LogObj.h"
#include "PubFun.h"

string CLogObj::errorTag = "error";
string CLogObj::infoTag = "info";
string CLogObj::warnTag = "warn";
string CLogObj::debugTag = "debug";
string CLogObj::extTag = "ext";

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

	logBasePathFormat = strPathBase + "/log/%s";
	logBaseTastPathFormat = strPathBase + "/log/%u";

	baseErrorlogFile = "processError_%d%02d%02d.log";
	baseInfologFile = "processInfo_%d%02d%02d.log";
	baseWarnlogFile = "processWarn_%d%02d%02d.log";
	baseDebuglogFile = "processDebug_%d%02d%02d.log";
	baseTestlogFile = "processTest_%d%02d%02d_%s.log";
}

void CLogObj::error( string& msg )
{
	string logMsg = makeLogStr("error", msg);
	auto pLogInfo = getLogInfo();

	string fileName = "";
	fileName = makeFileName(errorTag, *pLogInfo);
	writeLog(fileName, logMsg);

	fileName = makeFileName(infoTag, *pLogInfo);
	writeLog(fileName, logMsg);

	fileName = makeFileName(warnTag, *pLogInfo);
	writeLog(fileName, logMsg);

	fileName = makeFileName(debugTag, *pLogInfo);
	writeLog(fileName, logMsg);
}

void CLogObj::info( string& msg )
{
	string logMsg = makeLogStr(string("info"), msg);
	auto pLogInfo = getLogInfo();

	string fileName = "";
	fileName = makeFileName(infoTag, *pLogInfo);
	writeLog(fileName, logMsg);

	fileName = makeFileName(warnTag, *pLogInfo);
	writeLog(fileName, logMsg);

	fileName = makeFileName(debugTag, *pLogInfo);
	writeLog(fileName, logMsg);
}

void CLogObj::warn( string& msg )
{
	string logMsg = makeLogStr("warn", msg);
	auto pLogInfo = getLogInfo();

	string fileName = "";
	fileName = makeFileName(warnTag, *pLogInfo);
	writeLog(fileName, logMsg);

	fileName = makeFileName(debugTag, *pLogInfo);
	writeLog(fileName, logMsg);
}

void CLogObj::debug( string& msg )
{
	string logMsg = makeLogStr("debug", msg);
	auto pLogInfo = getLogInfo();

	string fileName = "";
	fileName = makeFileName(debugTag, *pLogInfo);
	writeLog(fileName, logMsg);
}

void CLogObj::ext( string& msg, string extTag )
{
	string logMsg = makeLogStr("test", msg);
	auto pLogInfo = getLogInfo();

	string fileName = "";
	fileName = makeFileName(extTag, *pLogInfo);
	writeLog(fileName, logMsg);
}

void CLogObj::test( string& msg, string id )
{
	/*
	string logMsg = makeLogStr("test", msg);
	auto pLogInfo = getLogInfo();

	string fileName = makeFileName(debugTag, *pLogInfo);
	writeLog(fileName, logMsg);
	*/
}

std::string CLogObj::makeFileName( string tag, CLogInfo &logInfo, string id/*=""*/ )
{
	string fileAllPath = "";
	size_t threadId = std::this_thread::get_id().hash();
	string fileKey = PubFun::strFormat("%u_%s", threadId, tag.c_str());
	map<string, string>::iterator fileIter = fileMap.find(fileKey);
	if (fileMap.end() == fileIter)
	{
		SYSTEMTIME s_time; 
		GetLocalTime(&s_time); 
		char ch[2048] = {0};
		string logPath = PubFun::strFormat(logBasePathFormat.c_str(), logInfo.name.c_str());
		string logFileFormat = "";
		if (id.empty())
		{
			logFileFormat = "%s_%d%02d%02d.log";
			sprintf_s(ch, logFileFormat.c_str(), tag.c_str(), s_time.wYear, s_time.wMonth, s_time.wDay);
		}
		else{
			logFileFormat = "%s_%d%02d%02d_%s.log";
			sprintf_s(ch, logFileFormat.c_str(), tag.c_str(), s_time.wYear, s_time.wMonth, s_time.wDay, id.c_str());
		}
		string fileName(ch);
		PubFun::makeNewFile(logPath, fileName);
		fileAllPath = PubFun::strFormat("%s/%s",logPath.c_str(), fileName.c_str());

		logInfo.logPathMap.insert(make_pair(tag, fileAllPath));
		fileMap.insert(make_pair(fileKey, fileAllPath));
	}
	else
	{
		fileAllPath = fileIter->second;
	}

	return fileAllPath;
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
		string logPath = PubFun::strFormat(logBaseTastPathFormat.c_str(), threadId);
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

void CLogObj::addLogInfo( size_t id, CLogInfo &info )
{
	map<size_t, CLogInfo>::iterator logInfoIter = logInfoMap.find(id);
	if (logInfoMap.end() != logInfoIter)
	{
		logInfoIter->second = info;
	}
	else
	{
		logInfoMap.insert(make_pair(id, info));
	}
}

void CLogObj::addLogInfo( CLogInfo &info )
{
	size_t threadId = std::this_thread::get_id().hash();
	addLogInfo(threadId, info);
}

CLogInfo* CLogObj::getLogInfo()
{
	CLogInfo* pLogInfo = nullptr;
	size_t threadId = std::this_thread::get_id().hash();
	map<size_t, CLogInfo>::iterator logInfoIter = logInfoMap.find(threadId);
	if (logInfoMap.end() != logInfoIter)
	{
		pLogInfo = &(logInfoIter->second);
	}
	else
	{
		CLogInfo logInfo(threadId, "def");
		auto res = logInfoMap.insert(make_pair(threadId, logInfo));
		pLogInfo = &(res.first->second);
	}
	return pLogInfo;
}

CLogInfo::CLogInfo( string name )
{
	this->id = std::this_thread::get_id().hash();
	this->name = name;
}
