#include "continueDecision.h"
#include "PubFun.h"

POptAccount CContinueDecision::optAccountr = COptAccount::instence();

CContinueDecision::CContinueDecision( int _startLevel, string _rateName, string _monitorName, string _decisionName ):startLevel(_startLevel),rateName(_rateName),monitorName(_monitorName),decisionName(_decisionName),isIn(false)
{
	tagName = PubFun::strFormat("%s_%s", monitorName.c_str(), decisionName.c_str());
}


void CContinueDecision::levelUp( int curLevel, PRateValue curValue, indexType srcTagId, int direct )
{
	if (!isIn && curLevel >= startLevel)
	{
		optAccountr->optIn(tagName, rateName, srcTagId, curValue, direct);
		isIn = true;
	}
}

void CContinueDecision::continueStop( PRateValue curValue )
{
	optAccountr->optOut(tagName, rateName, curValue);
	isIn = false;
}

void CContinueDecision::record( PRateValue curValue )
{
	optAccountr->record(tagName, rateName, curValue);
}

