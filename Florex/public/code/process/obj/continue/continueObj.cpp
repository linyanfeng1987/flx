#include "continueObj.h"

CContinueObj::CContinueObj( PContinueJudgeGroup pJudgeGroup )
{
	pContinueValue = nullptr;
	this->pJudgeGroup  = pJudgeGroup;
}

void CContinueObj::init( PRateValue startValue, PRateValue tryEndValue, int& curDirect, int& curLevel )
{
	this->startValue = startValue;
	this->tryEndValue = tryEndValue;
	this->curDirect = curDirect;
	this->curLevel = curLevel;
	this->maxLevel = curLevel;
}

bool CContinueObj::isContinueGoOn(PRateValue curValue )
{
	int tmpLevel = curLevel;
	bool bRes = pJudgeGroup->isContinueGoOn(tmpLevel, curValue, startValue, tryEndValue, curDirect);
	if (!bRes)
	{
		pContinueValue = newContinueValue();
		pContinueValue->setValue(startValue, tryEndValue, curValue, curDirect);
		pContinueValue->setLevels(levelStep);
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

	return bRes;
}

