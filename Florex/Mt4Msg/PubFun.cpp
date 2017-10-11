
#include "PubFun.h"
#include <time.h>
#include <fstream>
#include <ctime>

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
	return;
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