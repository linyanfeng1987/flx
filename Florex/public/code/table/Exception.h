#pragma once
#include <exception>
#include <string>

using namespace std;
class Exception :public exception
{
public:
	Exception(string msg = ""):exception(msg.c_str()){}
	~Exception(void);
};

