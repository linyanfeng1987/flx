// Mt4Msg.cpp : 定义 DLL 应用程序的导出函数。
//


#include "Mt4Msg.h"
#include "db/DbObj.h"
#include "PubFun.h"
#include <time.h>
#include <list>
#include <tuple>
#include <map>
#include "RateMsg.h"

const int step_mm = 1;
const int step_15mm = 2;
const int step_hh = 3;
const int step_4h = 4;
const int step_dd = 5;
const int step_ww = 6;

using namespace std;

char* msg_setHisValue( const char* strInfo )
{
	RateMsg rateMsg = RateMsg::getRateMsg(strInfo);
	if (rateMsg.msgType == msgType_his)
	{
		switch (rateMsg.hisRate.timeStepType)
		{
		case step_mm:
			break;
		case step_15mm:
			break;
		case step_hh:
			break;
		case step_4h:
			break;
		case step_dd:
			break;
		case step_ww:
			break;
		default:
			break;
		}
	}
	return "setHisValue return";
}

char* msg_setCurValue( const char* strInfo )
{
	static CDbObj& db = CDbObj::instance();
	static map<string, double> lastPriceMap;
	char logMsg[2048] = {0};
	memset(logMsg, 0, sizeof(logMsg));
	sprintf_s(logMsg, "msg_setCurValue begin\n%s", strInfo);
	PubFun::log(logMsg);
	RateMsg rateMsg = RateMsg::getRateMsg(strInfo);
	if (rateMsg.msgType == msgType_cur && rateMsg.status != 0)
	{
		CurRate curRate = rateMsg.curRate;
		double lastPrice = 0;
		map<string, double>::iterator iter =  lastPriceMap.find(rateMsg.rateName);
		if (iter != lastPriceMap.end())
		{
			lastPrice = iter->second;
		}
		else
		{
			lastPriceMap.insert(make_pair(rateMsg.rateName, lastPrice));
			iter = lastPriceMap.find(rateMsg.rateName);
		}
		
		double dTmp = abs(lastPrice - curRate.priceBuy);
		if (dTmp > 0.0001)
		{
			Operation oper;
			oper.amount = 11;

			string timeFormat = PubFun::getTimeFormat(curRate.time);
			string strSqlFormat = "insert into %s ( startTime, priceBuy, priceCell, volume, timeFormat ) value ( %d, %0.5f, %0.5f, %d, \"%s\" );";
			string strTableName = "currency_pair_";
			strTableName += rateMsg.rateName;

			char chSql[2048] = {0};
			memset(chSql, 0, sizeof(chSql));
			sprintf_s(chSql, strSqlFormat.c_str(), strTableName.c_str(), curRate.time, curRate.priceBuy, curRate.priceCell, curRate.volume, timeFormat.c_str());

			char msg[2048] = {};
			db.ExecuteSql(chSql, msg);
			iter->second = curRate.priceBuy;
		}
		else
		{
			char chLog[2048] = {0};
			memset(chLog, 0, sizeof(chLog));
			sprintf_s(chLog, "drop data, rateName;%s", rateMsg.rateName.c_str());
			PubFun::log(chLog);
		}
	}
	return "setCurValue return";
}

char* msg_beat()
{
	Operation oper;
	oper.amount = 11;
	return "hello mt4.^_^";
}
