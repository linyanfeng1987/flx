#include "PubFun.h"

#include "numCalc.h"

#include "LogObj.h"
#include <fstream>
#include <io.h>
#include <regex>

#include<direct.h>
using namespace std;
string baselogFile = "f:/log/mt4Msg.log";

PubFun::PubFun(void)
{
}

PubFun::~PubFun(void)
{
}

list<string> PubFun::split(const string& str, const string& pattern)
{
	//const char* convert to char*
	size_t nlen = strlen(str.c_str()) + 1;
	char* strc = new char[nlen];
	strcpy_s(strc, nlen, str.c_str());
	list<string> resultVec;
	char* next_token = nullptr;
	char* tmpStr = strtok_s(strc, pattern.c_str(), &next_token);
	while (tmpStr != NULL)
	{
		resultVec.push_back(std::string(tmpStr));
		tmpStr = strtok_s(NULL, pattern.c_str(), &next_token);
	}

	delete[] strc;

	return resultVec;
};

tuple<bool, string, string> PubFun::parseKeyValue(string strSrc)
{
	bool bRes = false;
	string strKey = "";
	string strValue = "";

	size_t index = strSrc.find(':');
	if (-1 != index)
	{
		bRes = true;
		strKey = strSrc.substr(0, index);
		strValue = strSrc.substr(index + 1);
	}

	tuple<bool, string, string> res = make_tuple(bRes, strKey, strValue);
	return res;
}

long PubFun::stringToInt(string str)
{
	long i = 0;
	if (!str.empty())
	{
		sscanf_s(str.c_str(), "%d", &i);
	}
	return i;
}

double PubFun::stringToDouble(string str)
{
	double i = 0;
	if (!str.empty())
	{
		sscanf_s(str.c_str(), "%lf", &i);
	}
	return i;
}

time_t PubFun::stringToTimet(string str)
{
	long i = 0;
	if (!str.empty())
	{
		sscanf_s(str.c_str(), "%ld", &i);
	}
	return (time_t)i;
}

std::string PubFun::intToString(int nValue)
{
	char tmpCh[255] = { 0 };
	_itoa_s(nValue, tmpCh, 10);
	return tmpCh;
}

std::string PubFun::indexToString(indexType nValue)
{
	char tmpCh[255] = { 0 };
	_itoa_s(nValue, tmpCh, 10);
	return tmpCh;
}

std::string PubFun::timetToString(time_t tValue)
{
	char str[256] = { 0 };
	sprintf_s(str, "%ld", (long)tValue);
	return string(str);
}

std::string PubFun::doubleToString(double dValue)
{
	char str[256] = { 0 };
	sprintf_s(str, "%lf", dValue);
	return string(str);
}

void PubFun::log(string str)
{
	CLogObj::instance().debug(str);
}
// void PubFun::log( string str )
// {
// 	//return;
// 	static char ch[2048] = {0};
// 	memset(ch, 0, sizeof(ch));
// 	static ofstream ofile;
// 	if (!ofile.is_open())
// 	{
// 		ofile.open(baselogFile, std::ios_base::app);
// 	}
//
// 	static SYSTEMTIME s_time;
// 	GetLocalTime(&s_time);
//
// 	sprintf_s(ch, "[%d-%d-%d %d:%d:%d]:%s\n", s_time.wYear, s_time.wMonth, s_time.wDay, s_time.wHour, s_time.wMinute, s_time.wSecond, str.c_str());
//
// 	ofile<<ch<<endl;
// 	ofile.close();
// }

void PubFun::logFormat(const char* strFormat, ...)
{
	static char msgbuffer[4096] = { 0 };
	va_list va_list_ptr;
	va_start(va_list_ptr, strFormat);
	memset(msgbuffer, 0, sizeof(msgbuffer));
	sprintf_s(msgbuffer, strFormat, va_list_ptr);
	log(msgbuffer);
	va_end(va_list_ptr);
}

std::string PubFun::strFormat(const char* strFormat, ...)
{
	// 	static char msgbuffer[2048] = {0};
	// 	va_list va_list_ptr;
	// 	va_start(va_list_ptr, strFormat);
	// 	sprintf_s(msgbuffer, strFormat, va_list_ptr);
	// 	va_end(va_list_ptr);
	// 	return msgbuffer;

	char* pszStr = NULL;
	string strResult = "";
	if (NULL != strFormat)
	{
		va_list va_list_ptr = NULL;
		va_start(va_list_ptr, strFormat); //初始化变量参数
		size_t nLength = _vscprintf(strFormat, va_list_ptr) + 1; //获取格式化字符串长度
		pszStr = new char[nLength];
		memset(pszStr, '\0', nLength);
		_vsnprintf_s(pszStr, nLength, nLength, strFormat, va_list_ptr);
		va_end(va_list_ptr); //重置变量参数
		strResult = string(pszStr);
		delete[]pszStr;
	}

	return strResult;
}

std::string PubFun::getValueFromMap(string strKey, map<string, string> mapObj)
{
	string strValue = "";
	map<string, string>::iterator iter = mapObj.find(strKey);
	if (iter != mapObj.end())
	{
		strValue = iter->second;
	}

	return strValue;
}

std::string PubFun::getTimeFormat(time_t timep)
{
	char tmp[64];
	tm tmpTm;
	localtime_s(&tmpTm, &timep);
	strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", &tmpTm);
	return tmp;
}
/*
double PubFun::calcPercentSpeadProS( long int startTime, long startMscd, double startPrice, long int endTime, long endMscd, double endPrice )
{
	long int dMscd = (endTime - startTime) * 1000 + endMscd - startMscd;
	double percentSpead = 0;
	if ( 0 != dMscd)
	{
		//percentSpead = ((endPrice-startPrice) / dMscd * 1000)/startPrice * 100;
		percentSpead = (endPrice-startPrice) / dMscd /startPrice * 100000;
	}

	return percentSpead;
}
*/

double PubFun::calcPercentSpeadProS(time_t startTime, int startMscd, double startPrice, time_t endTime, int endMscd, double endPrice)
{
	double second = (endTime - startTime) + (endMscd - startMscd) / 1000.0;
	return calcPercentSpeadProS(startPrice, endPrice, second);
}

double PubFun::calcPercentSpeadProS(double startPrice, double endPrice, double second)
{
	double basePrice = startPrice < endPrice ? startPrice : endPrice;
	double percentSpead = 0;
	if (second > 0.0001 || second < -0.0001)
	{
		//percentSpead = ((endPrice-startPrice) / dMscd * 1000)/startPrice * 100;
		//万分之
		percentSpead = (endPrice - startPrice) / second / basePrice * 10000;
	}

	return percentSpead;
}

bool PubFun::readHisFile(ifstream& fin, list<string>& readRes)
{
	char ch[255] = {};
	int lineCount = 0;
	bool hasValue = false;
	while (fin.getline(ch, sizeof(ch)))
	{
		lineCount++;
		readRes.push_back(ch);
		if (lineCount >= maxLineRead)
		{
			hasValue = true;
			break;
		}
	}

	return hasValue;
}

void getFiles(string path, map<string, string>& files)
{
	//文件句柄
	long   hFile = 0;
	//文件信息
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			//如果是目录,迭代之
			//如果不是,加入列表
			if ((fileinfo.attrib & _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					getFiles(p.assign(path).append("\\").append(fileinfo.name), files);
			}
			else
			{
				files.insert(make_pair(fileinfo.name, p.assign(path).append("\\").append(fileinfo.name)));
				//files.push_back(p.assign(path).append("\\").append(fileinfo.name) );
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}

bool PubFun::getFileByPath(string path, map<string, string>& files)
{
	////获取该路径下的所有文件
	getFiles(path, files);
	return true;
}

time_t PubFun::HisRateStringToDatetime(const char* str)
{
	tm tm_;
	int year, month, day, hour, minute, second;
	//20010102 231200
	sscanf_s(str, "%4d%2d%2d %2d%2d%2d", &year, &month, &day, &hour, &minute, &second);
	tm_.tm_year = year - 1900;
	tm_.tm_mon = month - 1;
	tm_.tm_mday = day;
	tm_.tm_hour = hour;
	tm_.tm_min = minute;
	tm_.tm_sec = second;
	tm_.tm_isdst = 0;

	time_t t_ = mktime(&tm_); //已经减了8个时区
	return t_; //秒时间
}

time_t PubFun::formartTimeToDatetime(const char* str)
{
	tm tm_;
	int year, month, day, hour, minute, second;
	//2019-6-5 22:15:23
	sscanf_s(str, "%4d-%2d-%2d %2d:%2d:%2d", &year, &month, &day, &hour, &minute, &second);
	tm_.tm_year = year - 1900;
	tm_.tm_mon = month - 1;
	tm_.tm_mday = day;
	tm_.tm_hour = hour;
	tm_.tm_min = minute;
	tm_.tm_sec = second;
	tm_.tm_isdst = 0;

	time_t t_ = mktime(&tm_); //已经减了8个时区
	return t_; //秒时间
}

std::string PubFun::strToLower(string str)
{
	char tmpCh[255] = { 0 };
	strcpy_s(tmpCh, str.c_str());
	_strlwr_s(tmpCh);
	return tmpCh;
}

std::string PubFun::strToUpper(string str)
{
	char tmpCh[255] = { 0 };
	strcpy_s(tmpCh, str.c_str());
	_strupr_s(tmpCh);
	return tmpCh;
}

std::string PubFun::get14CurTimeString()
{
	SYSTEMTIME s_time;
	GetLocalTime(&s_time);

	return get14TimeString(s_time);
}

std::string PubFun::get14TimeString(SYSTEMTIME& s_time)
{
	char ch[1024] = { 0 };
	sprintf_s(ch, "%d%d%d%d%d%d", s_time.wYear, s_time.wMonth, s_time.wDay, s_time.wHour, s_time.wMinute, s_time.wSecond);
	return ch;
}

void PubFun::getIntListByStep(list<time_t>& destList, double startValue, double endValue, int step)
{
	destList.clear();
	if (step > 0)
	{
		time_t startInt = (time_t)(startValue + 0.5);
		time_t tempInt = startInt;
		while (true)
		{
			if (tempInt > endValue)
			{
				break;
			}

			destList.push_back(tempInt);
			tempInt += step;
		}
	}
}

double PubFun::timeConvert(time_t ts, double msec)
{
	double dTime = ts + msec / 1000;
	return dTime;
}

pair<time_t, int> PubFun::timeConvert(double dTime)
{
	time_t ts = (time_t)dTime;
	int msec = (int)((dTime - ts) * 1000);

	return make_pair(ts, msec);
}

double PubFun::getFileSize(string filePath)
{
	// C++获取文件大小方法二
	int fileSize = -1;
	FILE* file = nullptr;
	fopen_s(&file, filePath.c_str(), "rb");
	if (file)
	{
		fileSize = _filelength(_fileno(file));
		fclose(file);
	}
	return fileSize;
}

char* PubFun::wcharToChar(const wchar_t* wp)
{
	char* m_char;
	int len = WideCharToMultiByte(CP_ACP, 0, wp, wcslen(wp), NULL, 0, NULL, NULL);
	m_char = new char[len + 1];
	WideCharToMultiByte(CP_ACP, 0, wp, wcslen(wp), m_char, len, NULL, NULL);
	m_char[len] = '\0';
	return m_char;
}

void PubFun::makeNewFile(string filePath, string fileName)
{
	makePath(filePath);
	FILE* file = nullptr;
	string fileAll = strFormat("%s/%s", filePath.c_str(), fileName.c_str());
	fopen_s(&file, fileAll.c_str(), "w");
	if (nullptr != file)
	{
		fclose(file);
	}
}

void PubFun::makePath(string filePath)
{
	if (-1 == _access(filePath.c_str(), 0))
	{
		int n1 = filePath.rfind('\\');
		int n2 = filePath.rfind('/');
		int nIndex = n1 > n2 ? n1 : n2;
		if (-1 != nIndex)
		{
			string parentPath = filePath.substr(0, nIndex);
			makePath(parentPath);
		}
		_mkdir(filePath.c_str());
	}
}

void PubFun::buildValueList(time_t startValue, time_t endValue, long step, map<time_t, time_t>& resValueMap)
{
	time_t tmpValue = 0;
	for (time_t i = startValue; i < endValue; )
	{
		tmpValue = i + step;
		tmpValue = tmpValue < endValue ? tmpValue : endValue;
		resValueMap.insert(make_pair(i, tmpValue));
		i = tmpValue + 1;
	}
}

void PubFun::splitParamStr(string paramters, map<string, string>& resMap)
{
	regex reg1("(\\w+)=(\\w+),?");
	vector<int> vec;
	vec.push_back(1);
	vec.push_back(2);

	sregex_token_iterator iter(paramters.begin(), paramters.end(), reg1, vec);
	sregex_token_iterator end;
	for (; iter != end; ++iter)
	{
		string strKey = iter->str();
		string strValue = (++iter)->str();
		resMap.insert(make_pair(strKey, strValue));
	}
}

std::string PubFun::getStepNameByType(int nStepType)
{
	string strStep = "";
	switch (nStepType)
	{
	case timeStepStep_mm:
		strStep = tableTimeStepEnd_mm;
		break;
	case timeStepStep_15m:
		strStep = tableTimeStepEnd_15m;
		break;
	case timeStepStep_hh:
		strStep = tableTimeStepEnd_hh;
		break;
	case timeStepStep_4h:
		strStep = tableTimeStepEnd_4h;
		break;
	case timeStepStep_dd:
		strStep = tableTimeStepEnd_dd;
		break;
	case timeStepStep_ww:
		strStep = tableTimeStepEnd_ww;
		break;
	case timeStepStep_def:
		strStep = "";
		break;
	default:
		strStep = "";
		break;
	}
	return strStep;
}

int PubFun::getStepType(time_t second)
{
	int stepType = 0;
	switch (second)
	{
	case 60:
		stepType = timeStepStep_mm;
		break;
	case 900:
		stepType = timeStepStep_15m;
		break;
	case 3600:
		stepType = timeStepStep_hh;
		break;
	case 14400:
		stepType = timeStepStep_4h;
		break;
	case 86400:
		stepType = timeStepStep_dd;
		break;
	case 604800:
		stepType = timeStepStep_ww;
		break;
	case timeStepStep_def:
		stepType = timeStepStep_def;
		break;
	default:
		stepType = timeStepStep_def;
		break;
	}
	return stepType;
}

std::string PubFun::getStepNameBySecond(time_t second)
{
	int stepType = getStepType(second);
	return getStepNameByType(stepType);
}

void PubFun::removeDir(string dirPath)
{
	struct _finddata_t fb;   //find the storage structure of the same properties file.
	string path;
	long    handle;
	//int  resultone;
	int   noFile;            // the tag for the system's hidden files

	noFile = 0;
	handle = 0;

	path = dirPath + "/*";

	//string tempPath = "F:/gitCode/*";
	handle = _findfirst(path.c_str(), &fb);

	//find the first matching file
	if (handle != -1)
	{
		//find next matching file
		while (0 == _findnext(handle, &fb))
		{
			// "." and ".." are not processed
			noFile = strcmp(fb.name, "..");

			if (0 != noFile)
			{
				path.clear();
				path = dirPath + "/" + fb.name;

				//fb.attrib == 16 means folder
				if (fb.attrib == 16)
				{
					removeDir(path);
				}
				else
				{
					//not folder, delete it. if empty folder, using _rmdir istead.
					remove(path.c_str());
				}
			}
		}
		// close the folder and delete it only if it is closed. For standard c, using closedir instead(findclose -> closedir).
		// when Handle is created, it should be closed at last.
		_rmdir(dirPath.c_str());
		_findclose(handle);
	}
}

std::string PubFun::getStrAttrFromEle(TiXmlElement* eleNode, const char* attrName)
{
	const char* chValue = eleNode->Attribute(attrName);
	if (nullptr != chValue)
	{
		return string(chValue);
	}
	else
	{
		return string("");
	}
}

time_t PubFun::getNumAttrFromEle(TiXmlElement* eleNode, const char* attrName)
{
	const char* chValue = eleNode->Attribute(attrName);
	if (nullptr != chValue)
	{
		return stringToTimet(chValue);
	}
	else
	{
		return 0;
	}
}

bool PubFun::isNodeNamed(TiXmlElement* eleNode, const char* nodeName)
{
	string nameValue = eleNode->Value();
	if (nameValue == nodeName)
	{
		return true;
	}
	else
	{
		return false;
	}
}

list<double> PubFun::splitNumString(string& str)
{
	list<double> numValues;
	list<string> strValues = split(str, ",");
	for (string strValue : strValues)
	{
		numValues.push_back(calcString(strValue));
	}
	return numValues;
}

double PubFun::calcString(string& str)
{
	return countSuxfix(str.c_str());
}

/*
unsigned long long PubFun::GetCurrentTimeMsec()
{
#ifdef _WIN32
	struct timeval tv;
	time_t clock;
	struct tm tm;
	SYSTEMTIME wtm;

	GetLocalTime(&wtm);
	tm.tm_year = wtm.wYear - 1900;
	tm.tm_mon = wtm.wMonth - 1;
	tm.tm_mday = wtm.wDay;
	tm.tm_hour = wtm.wHour;
	tm.tm_min = wtm.wMinute;
	tm.tm_sec = wtm.wSecond;
	tm.tm_isdst = -1;
	clock = mktime(&tm);
	tv.tv_sec = clock;
	tv.tv_usec = wtm.wMilliseconds * 1000;
	return ((unsigned long long)tv.tv_sec * 1000 + (unsigned long long)tv.tv_usec / 1000);
#else
	struct timeval tv;
	gettimeofday(&tv,NULL);
	return ((unsigned long long)tv.tv_sec * 1000 + (unsigned long long)tv.tv_usec / 1000);
#endif
} */