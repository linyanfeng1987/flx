#include "LogObj.h"
#include "PubFun.h"

string CLogObj::errorTag = "error";
string CLogObj::infoTag = "info";
string CLogObj::warnTag = "warn";
string CLogObj::debugTag = "debug";
string CLogObj::extTag = "ext";

const string CLogObj::logTag = "global";

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
	if(-1 != nIndex)
	{
		strPathBase = strPath.substr(0, nIndex);
	}

	logInfo = newLogInfo(logTag);

// 	logBasePathFormat = strPathBase + "/log/%s";
// 	logBaseTastPathFormat = strPathBase + "/log/%u";
// 
// 	baseErrorlogFile = "processError_%d%02d%02d.log";
// 	baseInfologFile = "processInfo_%d%02d%02d.log";
// 	baseWarnlogFile = "processWarn_%d%02d%02d.log";
// 	baseDebuglogFile = "processDebug_%d%02d%02d.log";
// 	baseTestlogFile = "processTest_%d%02d%02d_%s.log";
}

void CLogObj::error(PLogInfo logInfo, string& msg )
{
	string logMsg = makeLogStr("error", msg);
	logString(logInfo, log_error, logMsg);
// 	auto pLogInfo = getLogInfo();
// 
// 	string fileName = "";
// 	fileName = makeFileName(errorTag, *pLogInfo);
// 	writeLog(fileName, logMsg);
// 
// 	fileName = makeFileName(infoTag, *pLogInfo);
// 	writeLog(fileName, logMsg);
// 
// 	fileName = makeFileName(warnTag, *pLogInfo);
// 	writeLog(fileName, logMsg);
// 
// 	fileName = makeFileName(debugTag, *pLogInfo);
// 	writeLog(fileName, logMsg);
}

void CLogObj::info(PLogInfo logInfo, string& msg )
{
	string logMsg = makeLogStr(string("info"), msg);
	logString(logInfo, log_info, logMsg);
// 	auto pLogInfo = getLogInfo();
// 
// 	string fileName = "";
// 	fileName = makeFileName(infoTag, *pLogInfo);
// 	writeLog(fileName, logMsg);
// 
// 	fileName = makeFileName(warnTag, *pLogInfo);
// 	writeLog(fileName, logMsg);
// 
// 	fileName = makeFileName(debugTag, *pLogInfo);
// 	writeLog(fileName, logMsg);
}

void CLogObj::warn(PLogInfo logInfo, string& msg )
{
	string logMsg = makeLogStr("warn", msg);
	logString(logInfo, log_warn, logMsg);
// 	auto pLogInfo = getLogInfo();
// 
// 	string fileName = "";
// 	fileName = makeFileName(warnTag, *pLogInfo);
// 	writeLog(fileName, logMsg);
// 
// 	fileName = makeFileName(debugTag, *pLogInfo);
// 	writeLog(fileName, logMsg);
}

void CLogObj::debug(PLogInfo logInfo, string& msg )
{
	string logMsg = makeLogStr("debug", msg);
	logString(logInfo, log_debug, logMsg);
//	auto pLogInfo = getLogInfo();

	
// 	string fileName = "";
// 	fileName = makeFileName(debugTag, *pLogInfo);
// 	writeLog(fileName, logMsg);
}

void CLogObj::ext(PLogInfo logInfo, string& msg)
{
	string logMsg = makeLogStr("test", msg);
	logString(logInfo, log_ext, logMsg);
//	auto pLogInfo = getLogInfo();

	
// 	string fileName = "";
// 	fileName = makeFileName(extTag, *pLogInfo);
// 	writeLog(fileName, logMsg);
}


// std::string CLogObj::makeFileName( string tag, CLogInfo &logInfo, string id/*=""*/ )
// {
// 	string fileAllPath = "";
// 	size_t threadId = std::this_thread::get_id().hash();
// 	string fileKey = PubFun::strFormat("%u_%s", threadId, tag.c_str());
// 	map<string, string>::iterator fileIter = fileMap.find(fileKey);
// 	if (fileMap.end() == fileIter)
// 	{
// 		SYSTEMTIME s_time; 
// 		GetLocalTime(&s_time); 
// 		char ch[2048] = {0};
// 		string logPath = PubFun::strFormat(logBasePathFormat.c_str(), logInfo.name.c_str());
// 		string logFileFormat = "";
// 		if (id.empty())
// 		{
// 			logFileFormat = "%s_%d%02d%02d.log";
// 			sprintf_s(ch, logFileFormat.c_str(), tag.c_str(), s_time.wYear, s_time.wMonth, s_time.wDay);
// 		}
// 		else{
// 			logFileFormat = "%s_%d%02d%02d_%s.log";
// 			sprintf_s(ch, logFileFormat.c_str(), tag.c_str(), s_time.wYear, s_time.wMonth, s_time.wDay, id.c_str());
// 		}
// 		string fileName(ch);
// 		PubFun::makeNewFile(logPath, fileName);
// 		fileAllPath = PubFun::strFormat("%s/%s",logPath.c_str(), fileName.c_str());
// 
// 		logInfo.logPathMap.insert(make_pair(tag, fileAllPath));
// 		fileMap.insert(make_pair(fileKey, fileAllPath));
// 	}
// 	else
// 	{
// 		fileAllPath = fileIter->second;
// 	}
// 
// 	return fileAllPath;
// }
// 
// std::string CLogObj::makeFileName( string logFileFormat, string id/*=""*/ )
// {
// 	string fileAllPath = "";
// 	SYSTEMTIME s_time; 
// 	GetLocalTime(&s_time); 
// 	char ch[2048] = {0};
// 	size_t threadId = std::this_thread::get_id().hash();
// 	string fileKey = PubFun::strFormat("%u_%s", threadId, logFileFormat.c_str());
// 	map<string, string>::iterator fileIter = fileMap.find(fileKey);
// 	if (fileMap.end() == fileIter)
// 	{
// 		string logPath = PubFun::strFormat(logBaseTastPathFormat.c_str(), threadId);
// 		if (id.empty())
// 		{
// 			sprintf_s(ch, logFileFormat.c_str(), s_time.wYear, s_time.wMonth, s_time.wDay);
// 		}
// 		else{
// 			sprintf_s(ch, logFileFormat.c_str(), s_time.wYear, s_time.wMonth, s_time.wDay, id.c_str());
// 		}
// 		string fileName(ch);
// 		PubFun::makeNewFile(logPath, fileName);
// 		fileAllPath = PubFun::strFormat("%s/%s",logPath.c_str(), fileName.c_str());
// 
// 		fileMap.insert(make_pair(fileKey, fileAllPath));
// 	}
// 	else
// 	{
// 		fileAllPath = fileIter->second;
// 	}
// 	
// 	return fileAllPath;
// }

std::string CLogObj::makeLogStr( string levelTag, string& userMsg )
{
	SYSTEMTIME s_time; 
	GetLocalTime(&s_time); 
	size_t threadId = std::this_thread::get_id().hash();
	string logMsg = PubFun::strFormat("[%d-%d-%d %d:%d:%d]:[threadId:%u][%s]%s\n", s_time.wYear, s_time.wMonth, s_time.wDay, 
		s_time.wHour, s_time.wMinute, s_time.wSecond, threadId, levelTag.c_str(), userMsg.c_str());
	return logMsg;
}

// void CLogObj::writeLog( string fileName, string& str )
// {
// 	ofstream ofile;
// 	ofile.open(fileName, std::ios_base::app);
// 	if (ofile.is_open())
// 	{	
// 		ofile<<str<<endl;
// 		ofile.close();  
// 	}
// }

void CLogObj::writeLog( PWriteInfo writeInfo, string& str )
{
	if (writeInfo->logFile->is_open())
	{
		*(writeInfo->logFile)<<str<<endl;
		writeInfo->lineCount++;
	}
}

void CLogObj::logString( PLogInfo logInfo, int logType, string& str )
{
	static int writeFlags[] = {write_error, write_info, write_warn, write_debug, write_ext};
	for (int writeFlag : writeFlags)
	{
		if (0 != (logType & writeFlag))
		{
			if (writeFlag <= logInfo->maxLogType && writeFlag <= globlaLogType)
			{
				writeLog(logInfo, writeFlag, str);
			}
		}
	}
}

void CLogObj::writeLog( PLogInfo logInfo, int writeType, string& str )
{
	PWriteInfo writeInfo = nullptr;
	auto logObjIter = logInfo->logObjs.find(writeType);
	if (logInfo->logObjs.end() == logObjIter)
	{
		//根据logType 新建writeInfo
		writeInfo = newWriteInfo();
		logInfo->logObjs.insert(make_pair(writeType, writeInfo));
	}
	else
	{
		writeInfo = logObjIter->second;
	}

	if (maxFileLineCount <= writeInfo->lineCount)
	{
		writeInfo->logFile->close();  
		writeInfo->logFile = nullptr;
	}

	if (nullptr == writeInfo->logFile)
	{
		openNewFile(logInfo, writeInfo,writeType);
	}
	writeLog(writeInfo, str);
}

void CLogObj::openNewFile( PLogInfo logInfo, PWriteInfo writeInfo, int writeType )
{
	string strLogType = "";
	switch (writeType)
	{
	case write_ext:
		strLogType = "ext";
		break;
	case write_error:
		strLogType = "error";
		break;
	case write_info:
		strLogType = "info";
		break;
	case write_warn:
		strLogType = "warn";
		break;
	case write_debug:
		strLogType = "debug";
		break;
	}
	if (0 == logInfo->threadId )
	{
		logInfo->threadId = std::this_thread::get_id().hash();
	}

	// module, type, threadid, fileId
	string logPath = PubFun::strFormat("%s/log/%s/%s/",strPathBase.c_str(), strLogType.c_str(), logInfo->name.c_str());
	string fileName = PubFun::strFormat("%s_%u_%u.log", strLogType.c_str(), logInfo->threadId, writeInfo->fileCount++);
	PubFun::makeNewFile(logPath, fileName);
	string filePath = PubFun::strFormat("%s/%s",logPath.c_str(), fileName.c_str());
	writeInfo->filePath = filePath;
	writeInfo->logFile = newOfstream();
	writeInfo->logFile->open(filePath, std::ios_base::app);
	writeInfo->lineCount = 0;
}


// void CLogObj::addLogInfo( size_t id, CLogInfo &info )
// {
// 	map<size_t, CLogInfo>::iterator logInfoIter = logInfoMap.find(id);
// 	if (logInfoMap.end() != logInfoIter)
// 	{
// 		logInfoIter->second = info;
// 	}
// 	else
// 	{
// 		logInfoMap.insert(make_pair(id, info));
// 	}
// }

// void CLogObj::addLogInfo( CLogInfo &info )
// {
// 	size_t threadId = std::this_thread::get_id().hash();
// 	addLogInfo(threadId, info);
// }

// CLogInfo* CLogObj::getLogInfo()
// {
// 	CLogInfo* pLogInfo = nullptr;
// 	size_t threadId = std::this_thread::get_id().hash();
// 	map<size_t, CLogInfo>::iterator logInfoIter = logInfoMap.find(threadId);
// 	if (logInfoMap.end() != logInfoIter)
// 	{
// 		pLogInfo = &(logInfoIter->second);
// 	}
// 	else
// 	{
// 		CLogInfo logInfo(threadId, "def");
// 		auto res = logInfoMap.insert(make_pair(threadId, logInfo));
// 		pLogInfo = &(res.first->second);
// 	}
// 	return pLogInfo;
// }


CLogInfo::CLogInfo( string _name, int _maxLogType ):name(_name), maxLogType(_maxLogType),threadId(0)
{
	//id = std::this_thread::get_id().hash();
}

CLogInfo::CLogInfo( string _name ):name(_name), maxLogType(write_debug),threadId(0)
{

}
