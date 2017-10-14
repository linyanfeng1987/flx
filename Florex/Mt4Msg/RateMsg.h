#pragma once
#include <string>

#include "rate/CurRate.h"
#include "rate/HisRate.h"

using namespace std;

const string msgType_cur = "realTime";
const string msgType_his = "history";

class RateMsg
{
public:
	RateMsg(void);
	~RateMsg(void);

	static RateMsg getRateMsg(string strInfo);

	string rateName;
	string msgType;
	int status;

	CurRate curRate;
	HisRate hisRate;

	string toString();
};

