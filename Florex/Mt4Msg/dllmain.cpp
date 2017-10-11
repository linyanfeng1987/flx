// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "targetver.h"
#include <stdio.h>
#include <tchar.h>

#define WIN32_LEAN_AND_MEAN  
#include <windows.h>

#include <iostream>
#include "Mt4Msg.h"

const int maxMsgLen = 1024;

#define MT4_EXPFUNC __declspec(dllexport)

string ws2s(const wstring& ws){
	size_t convertedChars=0;
	string curLocale=setlocale(LC_ALL,NULL); //curLocale="C"
	setlocale(LC_ALL,"chs");
	const wchar_t* wcs=ws.c_str();
	size_t dByteNum=sizeof(wchar_t)*ws.size()+1;
	cout<<"ws.size():"<<ws.size()<<endl;            //5

	char* dest=new char[dByteNum];
	wcstombs_s(&convertedChars,dest,dByteNum,wcs,_TRUNCATE);
	cout<<"convertedChars:"<<convertedChars<<endl; //8
	string result=dest;
	delete[] dest;
	setlocale(LC_ALL,curLocale.c_str());
	return result;
}

wstring s2ws(const string& s){
	size_t convertedChars=0;
	string curLocale=setlocale(LC_ALL,NULL);   //curLocale="C"
	setlocale(LC_ALL,"chs");
	const char* source=s.c_str();
	size_t charNum=sizeof(char)*s.size()+1;
	cout<<"s.size():"<<s.size()<<endl;   //7

	wchar_t* dest=new wchar_t[charNum];
	mbstowcs_s(&convertedChars,dest,charNum,source,_TRUNCATE);
	cout<<"s2ws_convertedChars:"<<convertedChars<<endl; //6
	wstring result=dest;
	delete[] dest;
	setlocale(LC_ALL,curLocale.c_str());
	return result;
}

using namespace std;
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	HANDLE g_hModule;
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		cout<<"Dll is process attached!"<<endl;
		g_hModule = (HINSTANCE)hModule;
		break;
	case DLL_THREAD_ATTACH:
		cout<<"Dll is thread attached!"<<endl;
		g_hModule=NULL;
		break;

	case DLL_THREAD_DETACH:
		cout<<"Dll is thread detached!"<<endl;
		g_hModule=NULL;
		break;
	case DLL_PROCESS_DETACH:
		cout<<"Dll is process detached!"<<endl;
		g_hModule=NULL;
		break;
	}
	return TRUE;
}

MT4_EXPFUNC wchar_t* __stdcall beat(wchar_t* strInfo)
{
	static wchar_t msg[maxMsgLen];   
	wmemset(msg, 0, maxMsgLen);

	wstring wstr = s2ws(msg_beat());

	wcscpy_s(msg, wstr.c_str());
	return msg;
}
MT4_EXPFUNC wchar_t* __stdcall setHisValue(wchar_t* strInfo)
{
	static wchar_t msg[maxMsgLen];   
	wmemset(msg, 0, maxMsgLen);
	
	string str = ws2s(strInfo);
	wstring wstr =  s2ws(msg_setHisValue(str.c_str()));

	wcscpy_s(msg, wstr.c_str());
	return msg;
}
MT4_EXPFUNC wchar_t* __stdcall setCurValue(wchar_t* strInfo)
{
	static wchar_t msg[maxMsgLen];   
	wmemset(msg, 0, maxMsgLen);

	string str = ws2s(strInfo);
	wstring wstr =  s2ws(msg_setCurValue(str.c_str()));

	wcscpy_s(msg, wstr.c_str());
	return msg;
}
