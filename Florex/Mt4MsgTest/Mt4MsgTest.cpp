// Mt4MsgTest.cpp : 定义控制台应用程序的入口点。
//

#include <stdio.h>
#include <tchar.h>

#include "dllInclude.h"
#pragma comment(lib, "../Debug/Mt4Msg.lib")
#include <string>
#include <wchar.h>
#include <windows.h>
#include "PubFun.h"


using namespace std;
int _tmain(int argc, _TCHAR* argv[])
{
	//wstring msg = beat(_T("hello"));
	//wprintf_s(_T("beat msg is:%s"), msg.c_str());

	//double sp = PubFun::calcPercentSpeadProS(100,0,1, 101,0,2);

	wstring resMsg = setCurValue(_T("rateName:testRate,msgType:realTime,priceBuy:1,priceCell:1.89500,volume:100"));
	wprintf_s(_T("setCurValue msg is:%s"), resMsg.c_str());
	Sleep(1000);
	resMsg = setCurValue(_T("rateName:testRate,msgType:realTime,priceBuy:2,priceCell:1.89500,volume:100"));
	wprintf_s(_T("setCurValue msg is:%s"), resMsg.c_str());
	Sleep(1000);
	resMsg = setCurValue(_T("rateName:testRate,msgType:realTime,priceBuy:3,priceCell:1.89500,volume:100"));
	wprintf_s(_T("setCurValue msg is:%s"), resMsg.c_str());
	
	return 0;
}

