#include "averageDecision.h"
#include "PubFun.h"

CAverageDecisionTemplate::CAverageDecisionTemplate(double _optInPersent, double _optOutPersent)
{
	optInPersent = _optInPersent;
	optOutPersent = _optOutPersent;
}

CAverageDecision::CAverageDecision( PAverageDecisionTemplate _decisionTemplate, double _averageStepTime, string _monitorName, PRateInfo _rateInfo)
{
	decisionTemplate = _decisionTemplate;
	optTagId = 0;
	tryDirect = 0;
	nowStatus = status_wait;

	averageStepTime = _averageStepTime;
	optInTime = averageStepTime * decisionTemplate->optInPersent;
	optOutTime = averageStepTime * decisionTemplate->optOutPersent;

	trySetStartTime = 0;

	optAccountr = COptAccount::instence();
	decisionName = PubFun::strFormat("average_%d_%d", (int)(decisionTemplate->optInPersent*100), (int)(decisionTemplate->optOutPersent*100));

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
	//nowStatus = status_confusion;
}


void CAverageDecision::add( PRateValue curValue, PRateValue averageValue )
{
	if (recordValue.empty())
	{
		recordValue.append("begin");
	}
	recordValue.append(PubFun::strFormat(",%.4lf/%.4lf", curValue->value,averageValue->value));
	switch (nowStatus)
	{
	case status_wait:
		wait(curValue, averageValue);
		break;
	case status_keep:
		keep(curValue, averageValue);
		break;
	}
	//trySetDir(curValue, averageValue);
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
	return false;
}

bool CAverageDecision::isDirectInit( double stepTime )
{
	return false;
}

void CAverageDecision::wait( PRateValue curValue, PRateValue averageValue )
{
	int nowDirect = curValue->value - averageValue->value > 0 ? direct_up : direct_down; 
	if (nowDirect == tryDirect)
	{
		double stepTime = curValue->time - trySetStartTime;
		if (stepTime > optInTime)
		{
			if (0 == optTagId)
			{
				optDirect = nowDirect;
				recordValue.append(",optIn");
				optTagId = optAccountr->optIn(tagName, rateInfo->rateName, 0, curValue, optDirect);
				nowStatus = status_keep;
				tryDirect = 0;
			}
			else
			{
				throw CStrException("fun_confusion error");
			}
		}			
	}
	else
	{
		setTryDirect(curValue->time, nowDirect);
		recordValue.clear();
	}
}

void CAverageDecision::tryIn( PRateValue curValue, PRateValue averageValue )
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

void CAverageDecision::keep( PRateValue curValue, PRateValue averageValue )
{
	int nowDirect = curValue->value - averageValue->value > 0 ? direct_up : direct_down; 
	if (nowDirect != optDirect)
	{
		if (nowDirect == tryDirect)
		{
			double stepTime = curValue->time - trySetStartTime;
			if (stepTime > optOutTime)
			{
				if (0 != optTagId)
				{
					recordValue.append(",optOut;");
					optAccountr->optOut(tagName, rateInfo->rateName, optTagId, curValue, recordValue);
					optTagId = 0;
					optDirect = 0;
					nowStatus = status_wait;
					recordValue.clear();
				}
				else
				{
					throw CStrException("fun_status_clear error");
				}
			}	
		}
		else
		{
			setTryDirect(curValue->time, nowDirect);
		}		
	}
	
}

void CAverageDecision::tryOut( PRateValue curValue, PRateValue averageValue )
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



