#include "continueObj.h"

CContinueObj::CContinueObj( PContinueJudgeGroup pJudgeGroup )
{
	pContinueValue = nullptr;
	this->pJudgeGroup  = pJudgeGroup;
}

void CContinueObj::init( CRateValue& startValue, CRateValue& tryEndValue, int& curDirect, int& judegLevel )
{
	this->startValue = startValue;
	this->tryEndValue = tryEndValue;
	this->curDirect = curDirect;
	this->judegLevel = judegLevel;
}

bool CContinueObj::isContinueGoOn(CRateValue& curValue )
{
	bool bRes = pJudgeGroup->isContinueGoOn(judegLevel, curValue, startValue, tryEndValue, curDirect);
	if (!bRes)
	{
		pContinueValue = newContinueValue();
		pContinueValue->startValue = startValue;
		pContinueValue->endValue = tryEndValue;
		pContinueValue->stopValue = curValue;
	}

	return bRes;
}

