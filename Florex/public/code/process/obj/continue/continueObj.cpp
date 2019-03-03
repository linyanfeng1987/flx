#include "continueObj.h"

CContinueObj::CContinueObj( PContinueJudgeGroup pJudgeGroup )
{
	pContinueValue = nullptr;
	this->pJudgeGroup  = pJudgeGroup;
	curStatus = continue_keep;
}

void CContinueObj::init( PRateValue startValue, PRateValue tryEndValue, int& curDirect, int& curLevel )
{
	this->startValue = startValue;
	this->tryEndValue = tryEndValue;
	this->curDirect = curDirect;
	this->curLevel = curLevel;
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
		if ( curLevel != tmpLevel )
		{
			maxLevel = tmpLevel > maxLevel ? tmpLevel : maxLevel;
			levelStep.push_back(tmpLevel);
			curLevel = tmpLevel;
		}
	}

	return curStatus;
}

void CContinueObj::stopContinue(PRateValue curValue)
{
	pContinueValue->setLevels(levelStep);
}
