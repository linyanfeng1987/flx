#include "continueDecision.h"
#include "PubFun.h"

POptAccount CContinueDecision::optAccountr = COptAccount::instence();

CContinueDecision::CContinueDecision( int _startLevel, string _rateName, string _monitorName, string _decisionName ):startLevel(_startLevel),rateName(_rateName),monitorName(_monitorName),decisionName(_decisionName)
{
	tagName = PubFun::strFormat("%s_%s", monitorName.c_str(), decisionName.c_str());
}


void CContinueDecision::levelUp( int curLevel, PRateValue curValue, int direct )
{
	if (curLevel >= startLevel)
	{
		optAccountr->optIn(tagName, rateName, curValue, direct);
	}
}

void CContinueDecision::continueStop( PRateValue curValue )
{
	optAccountr->optOut(tagName, rateName, curValue);
}

void CContinueDecision::record( PRateValue curValue )
{
	optAccountr->record(tagName, rateName, curValue);
}

