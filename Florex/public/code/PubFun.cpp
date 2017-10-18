#include "PubFun.h"
#include <time.h>
#include <fstream>
#include <ctime>
#include <fstream>
#include <io.h>

using namespace std;
string logFile = "f:/log/mt4Msg.log";

PubFun::PubFun(void)
{
}


PubFun::~PubFun(void)
{
}


list<string> PubFun::split(const string &str,const string &pattern)
{
	//const char* convert to char*
	size_t nlen = strlen(str.c_str())+1;
	char * strc = new char[nlen];
	strcpy_s(strc, nlen, str.c_str());
	list<string> resultVec;
	char *next_token = nullptr; 
	char* tmpStr = strtok_s(strc, pattern.c_str(), &next_token);
	while (tmpStr != NULL)
	{
		resultVec.push_back(std::string(tmpStr));
		tmpStr = strtok_s(NULL, pattern.c_str(), &next_token);
	}

	delete[] strc;

	return resultVec;
};

tuple<bool,string, string> PubFun::parseKeyValue(string strSrc)
{
	bool bRes = false;
	string strKey = "";
	string strValue = "";

	size_t index = strSrc.find(':');
	if(-1 != index)
	{
		bRes = true;
		strKey = strSrc.substr(0, index);
		strValue = strSrc.substr(index+1);
	}

	tuple<bool,string, string> res = make_tuple(bRes, strKey, strValue);
	return res;
}

int PubFun::stringToInt(string str)
{
	int i = 0;
	sscanf_s(str.c_str(),"%d",&i);
	return i;
}

double PubFun::stringToDouble(string str)
{
	double i = 0;
	sscanf_s(str.c_str(),"%lf",&i);
	return i;
}

void PubFun::log( string str )
{
	//return;
	static char ch[2048] = {0};
	memset(ch, 0, sizeof(ch));
	static ofstream ofile;
	if (!ofile.is_open())
	{
		ofile.open(logFile, std::ios_base::app);
	}
	
	static SYSTEMTIME s_time; 
	GetLocalTime(&s_time);  

	sprintf_s(ch, "[%d-%d-%d %d:%d:%d]:%s\n", s_time.wYear, s_time.wMonth, s_time.wDay, s_time.wHour, s_time.wMinute, s_time.wSecond, str.c_str());
 
	ofile<<ch<<endl;
	ofile.close();                
}

void PubFun::logFormat( const char * strFormat, ...)
{
	static char msgbuffer[2048] = {0};
	va_list va_list_ptr;
	va_start(va_list_ptr, strFormat);  
	memset(msgbuffer, 0, sizeof(msgbuffer));
	sprintf_s(msgbuffer, strFormat, va_list_ptr);
	log(msgbuffer);
	va_end(va_list_ptr);  
}

std::string PubFun::getValueFromMap( string strKey, map<string, string> mapObj )
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

double PubFun::calcPercentSpeadProS( long int startTime, long startMscd, double startPrice, long int endTime, long endMscd, double endPrice )
{
	double second = (endTime - startTime) + (endMscd - startMscd)/1000.0;
	double basePrice = startPrice < endPrice ? startPrice : endPrice;
	double percentSpead = 0;
	if ( second > 0.0001 || second < -0.0001 )
	{
		//percentSpead = ((endPrice-startPrice) / dMscd * 1000)/startPrice * 100;
		//万分之
		percentSpead = (endPrice-startPrice) / second /basePrice * 10000;
	}

	return percentSpead;
}

bool PubFun::readHisFile( ifstream &fin,list<string> &readRes )
{
	char ch[255] = {};
	int lineCount = 0;
	bool hasValue = false;
	while( fin.getline(ch, sizeof(ch)) )
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

void getFiles( string path, map<string, string> &files )
{
	//文件句柄
	long   hFile   =   0;
	//文件信息
	struct _finddata_t fileinfo;
	string p;
	if((hFile = _findfirst(p.assign(path).append("\\*").c_str(),&fileinfo)) !=  -1)
	{
		do
		{
			//如果是目录,迭代之
			//如果不是,加入列表
			if((fileinfo.attrib &  _A_SUBDIR))
			{
				if(strcmp(fileinfo.name,".") != 0  &&  strcmp(fileinfo.name,"..") != 0)
					getFiles( p.assign(path).append("\\").append(fileinfo.name), files );
			}
			else
			{
				files.insert(make_pair(fileinfo.name, p.assign(path).append("\\").append(fileinfo.name)));
				//files.push_back(p.assign(path).append("\\").append(fileinfo.name) );
			}
		}while(_findnext(hFile, &fileinfo)  == 0);
		_findclose(hFile);
	}
}

bool PubFun::getFileByPath( string path, map<string, string> &files )
{
	////获取该路径下的所有文件  
	getFiles(path, files);
	return true;
}


time_t PubFun::HisRateStringToDatetime(const char *str)  
{  
	tm tm_;  
	int year, month, day, hour, minute,second;  
	//20010102 231200
	sscanf_s(str,"%4d%2d%2d %2d%2d%2d", &year, &month, &day, &hour, &minute, &second);  
	tm_.tm_year  = year-1900;  
	tm_.tm_mon   = month-1;  
	tm_.tm_mday  = day;  
	tm_.tm_hour  = hour;  
	tm_.tm_min   = minute;  
	tm_.tm_sec   = second;  
	tm_.tm_isdst = 0;  

	time_t t_ = mktime(&tm_); //已经减了8个时区  
	return t_; //秒时间  
}  

std::string PubFun::strToLower( string str )
{
	char tmpCh[255] = {0};
	strcpy_s(tmpCh, str.c_str());
	return strlwr(tmpCh);
}

std::string PubFun::strToUpper( string str )
{
	char tmpCh[255] = {0};
	strcpy_s(tmpCh, str.c_str());
	return strupr(tmpCh);
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
