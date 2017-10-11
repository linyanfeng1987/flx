#pragma once

/*
#ifdef DLL_MT4MSG_EXPORTS

#define DLL_MT4MSG_API __declspec(dllexport)

#else

#define DLL_MT4MSG_API __declspec(dllimport)

#endif
*/

#include <string>

using namespace std;


struct Operation
{
	char* oper;
	double amount;
	double price;
};

char* msg_beat();
char* msg_setHisValue(const char* strInfo);
char* msg_setCurValue(const char* strInfo);

