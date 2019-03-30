#include "averageDecision.h"
#include "PubFun.h"

CAverageDecisionTemplate::CAverageDecisionTemplate(double _optPersent )
{
	optInPersent = _optPersent;
	optOutPersent = _optPersent;
}

CAverageDecision::CAverageDecision( PAverageDecisionTemplate _decisionTemplate, double _averageStepTime, string _monitorName, PRateInfo _rateInfo)
{
	decisionTemplate = _decisionTemplate;
	optTagId = 0;
	tryDirect = 0;
	nowStatus = status_confusion;

	averageStepTime = _averageStepTime;
	optTime = averageStepTime * decisionTemplate->optInPersent;

	trySetStartTime = 0;

	optAccountr = COptAccount::instence();
	decisionName = PubFun::strFormat("average_%lf_%lf", decisionTemplate->optInPersent, decisionTemplate->optOutPersent);

	rateInfo = _rateInfo;
	monitorName = _monitorName;

	tagName = PubFun::strFormat("%s_%s", monitorName.c_str(), decisionName.c_str());
}

void CAverageDecision::record( PRateValue curValue )
{
	optAccountr->record(tagName, rateInfo->rateName, curValue);
}

void CAverageDecision::setTryDirect( double nowTime, int nowDirect )
{
	tryDirect = nowDirect;
	trySetStartTime = nowTime;
	nowStatus = status_dirTrySet;
}


void CAverageDecision::add( PRateValue curValue, PRateValue averageValue )
{
// 	switch (nowStatus)
// 	{
// 	case status_init:
// 		break;
// 	case status_dirTrySet:
// 		trySetDir(curValue, averageValue);
// 		break;
// 	case status_keep:
// 		break;
// 	}
	trySetDir(curValue, averageValue);
}

void CAverageDecision::trySetDir( PRateValue curValue, PRateValue averageValue )
{
	int nowDirect = curValue->value - averageValue->value > 0 ? direct_up : direct_down; 
	if (nowDirect == tryDirect)
	{
		if (isDirectSet(curValue->time - trySetStartTime))
		{
			if (0 != optTagId)
			{
				optAccountr->optOut(tagName, rateInfo->rateName, optTagId, curValue);
				optTagId = 0;
				nowStatus += status_tryOut;
			}
			optTagId = optAccountr->optIn(tagName, rateInfo->rateName, 0, curValue, nowDirect);
			nowStatus += status_tryIn;
		}			
	}
	else
	{
		setTryDirect(curValue->time, nowDirect);
	}
}

void CAverageDecision::keepOpt( PRateValue curValue, PRateValue averageValue )
{
	int nowDirect = curValue->value - averageValue->value > 0 ? direct_up : direct_down; 
	if (nowDirect != tryDirect)
	{
		setTryDirect(curValue->time, nowDirect);		
	}
}

void CAverageDecision::none( PRateValue curValue, PRateValue averageValue )
{

}

bool CAverageDecision::isDirectSet( double stepTime )
{
	return optTime < stepTime;
}

bool CAverageDecision::isDirectInit( double stepTime )
{
	return false;
}

void CAverageDecision::fun_confusion( PRateValue curValue, PRateValue averageValue )
{
	int nowDirect = curValue->value - averageValue->value > 0 ? direct_up : direct_down; 
	if (nowDirect == tryDirect)
	{
		if (isDirectSet(curValue->time - trySetStartTime))
		{
			if (0 == optTagId)
			{
				optTagId = optAccountr->optIn(tagName, rateInfo->rateName, 0, curValue, nowDirect);
				nowStatus += status_tryIn;
			}
			else
			{
				throw CStrException("fun_confusion_tryIn error");
			}
		}			
	}
	else
	{
		setTryDirect(curValue->time, nowDirect);
	}
}

void CAverageDecision::fun_confusion_tryIn( PRateValue curValue, PRateValue averageValue )
{
	int nowDirect = curValue->value - averageValue->value > 0 ? direct_up : direct_down; 
	if (nowDirect == tryDirect)
	{
		if (isDirectSet(curValue->time - trySetStartTime))
		{
			if (0 == optTagId)
			{
				optTagId = optAccountr->optIn(tagName, rateInfo->rateName, 0, curValue, nowDirect);
				nowStatus += status_tryIn;
			}
			else
			{
				throw CStrException("fun_confusion_tryIn error");
			}
		}			
	}
	else
	{
		setTryDirect(curValue->time, nowDirect);
	}
}

void CAverageDecision::fun_status_clear( PRateValue curValue, PRateValue averageValue )
{

}

void CAverageDecision::fun_status_clear_tryOut( PRateValue curValue, PRateValue averageValue )
{
	int nowDirect = curValue->value - averageValue->value > 0 ? direct_up : direct_down; 
	if (nowDirect == tryDirect)
	{
		if (isDirectSet(curValue->time - trySetStartTime))
		{

			if (0 != optTagId)
			{
				optAccountr->optOut(tagName, rateInfo->rateName, optTagId, curValue);
				optTagId = 0;
				nowStatus += status_tryOut;
			}
			else
			{
				throw CStrException("fun_status_clear_tryOut error");
			}
		}			
	}
	else
	{
		setTryDirect(curValue->time, nowDirect);
	}
}



