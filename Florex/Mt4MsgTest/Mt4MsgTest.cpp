// Mt4MsgTest.cpp : 定义控制台应用程序的入口点。
//

#include <stdio.h>
#include <tchar.h>

#include "dllInclude.h"
#pragma comment(lib, "../Debug/Mt4Msg.lib")
#include <string>
#include <wchar.h>


using namespace std;
int _tmain(int argc, _TCHAR* argv[])
{
	wstring msg = beat(_T("hello"));
	wprintf_s(_T("beat msg is:%s"), msg.c_str());

	wstring resMsg = setCurValue(_T("rateName:eurusd,msgType:realTime,priceBuy:1.89626,priceCell:1.89500,volume:100"));
	wprintf_s(_T("setCurValue msg is:%s"), resMsg.c_str());

	return 0;
}

