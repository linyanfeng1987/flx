#pragma once
#include <exception>
#include <string>

using namespace std;
class CStrException :public exception
{
public:
	CStrException(string msg = "") :exception(msg.c_str()), errorNo(0) {}
	CStrException(int _errorNo, string msg = "") :exception(msg.c_str()), errorNo(_errorNo) {}
	~CStrException(void);

	int errorNo;
};
