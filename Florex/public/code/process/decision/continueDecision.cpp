#include "continueDecision.h"
#include "PubFun.h"

CContinueDecision::CContinueDecision(int _startLevel) :startLevel(_startLevel), optTagId(0)
{
	optAccountr = COptAccount::instence();
	decisionName = PubFun::strFormat("continue_%d", startLevel);
}

void CContinueDecision::init(string _monitorName, PRateInfo _rateInfo)
{
	rateInfo = _rateInfo;
	monitorName = _monitorName;

	tagName = PubFun::strFormat("%s_%s", monitorName.c_str(), decisionName.c_str());
}

void CContinueDecision::levelUp(int curLevel, PRateValue curValue, indexType srcTagId, int direct)
{
	if (0 == optTagId && curLevel >= startLevel)
	{
		optTagId = optAccountr->optIn(tagName, rateInfo->rateName, srcTagId, curValue, direct);
	}
}

void CContinueDecision::continueStop(PRateValue curValue)
{
	if (0 != optTagId)
	{
		optAccountr->optOut(tagName, rateInfo->rateName, optTagId, curValue);
	}
}

void CContinueDecision::record(PRateValue curValue)
{
	optAccountr->record(tagName, rateInfo->rateName, curValue);
}