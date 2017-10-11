

#include <list>
#include <map>

#include "RateMsg.h"
#include "PubFun.h"

RateMsg::RateMsg(void)
{
	rateName = "";
	msgType = "";
	status = 0;
}


RateMsg::~RateMsg(void)
{
}

std::string RateMsg::toString()
{
	char tmp[1024] = {0};
	string strRateInfo = "";
	if (msgType == msgType_cur)
	{
		strRateInfo = curRate.toString();
	}
	else if (msgType == msgType_his)
	{
		strRateInfo = hisRate.toString();
	}

	sprintf_s(tmp, "rateName:%s, msgType:%s, status:%d, rateInfo:%s", rateName.c_str(), msgType.c_str(), status,  strRateInfo.c_str());

	return string(tmp);
}


RateMsg RateMsg::getRateMsg(string strInfo)
{
	RateMsg rateMsg;

	list<string> keyValues = PubFun::split(strInfo, ",");
	bool bRes;
	string strKey;
	string strValue;
	map<string, string> keyValueMap;

	for (string strKeyValue : keyValues)
	{
		tuple<bool,string, string> res = PubFun::parseKeyValue(strKeyValue);
		std::tie(bRes, strKey, strValue) = res;

		if (bRes)
		{
			keyValueMap.insert(make_pair(strKey, strValue));
		}
	}

	try
	{
		map<string, string>::iterator iter = keyValueMap.find("msgType");
		string strMsgType = "";
		if (iter != keyValueMap.end())
		{
			strMsgType = iter->second;
			if (strMsgType == msgType_cur)
			{
				CurRate curRate;
				curRate.time = PubFun::stringToInt(PubFun::getValueFromMap("time", keyValueMap));
				curRate.priceBuy = PubFun::stringToDouble(PubFun::getValueFromMap("priceBuy", keyValueMap));
				curRate.priceCell = PubFun::stringToDouble(PubFun::getValueFromMap("priceCell", keyValueMap));
				curRate.volume = PubFun::stringToInt(PubFun::getValueFromMap("volume", keyValueMap));

				if (0 == curRate.time)
				{
					curRate.time = (long int)time(0);
				}

				rateMsg.curRate = curRate;
			}
			else if (strMsgType == msgType_his)
			{
				HisRate hisRat;
				hisRat.time = PubFun::stringToInt(PubFun::getValueFromMap("time", keyValueMap));
				hisRat.timeStepType = PubFun::stringToInt(PubFun::getValueFromMap("timeStepType", keyValueMap));
				hisRat.open = PubFun::stringToDouble(PubFun::getValueFromMap("open", keyValueMap));
				hisRat.high = PubFun::stringToDouble(PubFun::getValueFromMap("high", keyValueMap));
				hisRat.low = PubFun::stringToDouble(PubFun::getValueFromMap("low", keyValueMap));
				hisRat.close = PubFun::stringToDouble(PubFun::getValueFromMap("close", keyValueMap));
				hisRat.tick_volume = PubFun::stringToInt(PubFun::getValueFromMap("tick_volume", keyValueMap));
				hisRat.spread = PubFun::stringToInt(PubFun::getValueFromMap("spread", keyValueMap));
				hisRat.real_volume = PubFun::stringToInt(PubFun::getValueFromMap("real_volume", keyValueMap));

				rateMsg.hisRate = hisRat;
			}

			rateMsg.rateName = keyValueMap.find("rateName")->second;
			rateMsg.msgType = keyValueMap.find("msgType")->second;
			rateMsg.status = 1;
		}
	}
	catch (...)
	{
		PubFun::log("catch error in getRateMsg");
	}

	char logMsg[2048] = {0};
	memset(logMsg, 0, sizeof(logMsg));
	sprintf_s(logMsg, "getRateMsg::rateMsg:%s", rateMsg.toString().c_str());
	PubFun::log(logMsg);
	return rateMsg;
}