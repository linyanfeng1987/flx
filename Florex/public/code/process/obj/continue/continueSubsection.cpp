#include "continueSubsection.h"

CContinueSubsection::CContinueSubsection( PContinueJudgeGroup pJudgeGroup )
{
	pContinueValue = nullptr;
	this->pJudgeGroup  = pJudgeGroup;
	curStatus = continue_keep;
}

void CContinueSubsection::init( PRateValue startValue, PRateValue tryEndValue, int& curDirect, int& curLevel )
{
	this->startValue = startValue;
	this->tryEndValue = tryEndValue;
	this->curDirect = curDirect;
	this->curLevel = curLevel;
	this->maxLevel = curLevel;
	levelStep.push_back(curLevel);
	curStatus = continue_keep;
}

emumContinueStatus CContinueSubsection::isContinueGoOn(PRateValue curValue )
{
	int tmpLevel = curLevel;
	curStatus = pJudgeGroup->isContinueGoOn(tmpLevel, curValue, startValue, tryEndValue, curDirect);
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

void CContinueSubsection::stopContinue(PRateValue curValue)
{
	pContinueValue = newContinueValue();
	pContinueValue->setValue(startValue, tryEndValue, curValue, curDirect);
	pContinueValue->setLevels(levelStep);
}
