#include "continueObj.h"

CContinueObj::CContinueObj( PContinueJudgeGroup pJudgeGroup, list<PContinueDecision> *_decisions)
{
	pContinueValue = nullptr;
	this->pJudgeGroup  = pJudgeGroup;
	curStatus = continue_keep;
	decisions = _decisions;
}

void CContinueObj::init( PRateValue startValue, PRateValue tryEndValue, int& curDirect, int& _curLevel )
{
	this->startValue = startValue;
	this->tryEndValue = tryEndValue;
	this->curDirect = curDirect;
	//this->curLevel = curLevel;
	levelChange(_curLevel, tryEndValue);
	this->maxLevel = curLevel;
	levelStep.push_back(curLevel);
	curStatus = continue_keep;
}

emumContinueStatus CContinueObj::isContinueGoOn(PRateValue curValue )
{
	int tmpLevel = curLevel;
	curStatus = pJudgeGroup->isContinueGoOn(tmpLevel, curValue, startValue, tryEndValue, curDirect, pContinueValue);
	if ( continue_stop == curStatus )
	{
		stopContinue(curValue);
	}
	else
	{
		if (++keepCount >= 1000)
		{
			for (PContinueDecision decision: *decisions)
			{
				decision->record(curValue);
				keepCount = 0;
			}
		}
		if ( curLevel != tmpLevel )
		{
			maxLevel = tmpLevel > maxLevel ? tmpLevel : maxLevel;
			levelStep.push_back(tmpLevel);
			curLevel = tmpLevel;
			levelChange(tmpLevel, curValue);
		}
	}

	return curStatus;
}

void CContinueObj::stopContinue(PRateValue curValue)
{
	pContinueValue->setLevels(levelStep);
	for (PContinueDecision decision: *decisions)
	{
		decision->continueStop(curValue);
	}
}

void CContinueObj::levelChange( int newLevel, PRateValue curValue )
{
	curLevel = newLevel;
	for (PContinueDecision decision: *decisions)
	{
		decision->levelUp(newLevel, curValue, curDirect);
	}
}
