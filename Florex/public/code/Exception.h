#pragma once
#include <exception>
#include <string>

using namespace std;
class CStrException :public exception
{
public:
	CStrException(string msg = ""):exception(msg.c_str()){}
	~CStrException(void);
};

