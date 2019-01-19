#include "continueJudgeObj.h"

CContinueJudgeObj::CContinueJudgeObj( int continueLevel )
{
	this->continueLevel = continueLevel;
}



void CContinueJudgeObj::init( double minStepValuePersent, double minStepSpeedPersent, double retrcementValue, double retrcementSpead, double stopSpead)
{
	this->minStepSpeedPersent = minStepSpeedPersent;
	this->minStepValuePersent = minStepValuePersent;
	this->retrcementSpead = retrcementSpead;
	this->retrcementValue = retrcementValue;
	this->stopSpead = stopSpead;
}

bool CContinueJudgeObj::isContinueGoOn(const CRateValue& curValue, CRateValue& startValue, CRateValue& tryEndValue, int& curDirect )
{
	bool bIsContinue = true;
	double tryEndStepValue = (startValue.value - tryEndValue.value)*curDirect;
	double tryEndStepTime = tryEndValue.time - startValue.time;
	double tryEndSpead = tryEndStepValue / tryEndStepTime;

	double curStepValue = (startValue.value - curValue.value)*curDirect;
	double curRetrcementValue = curStepValue / tryEndStepValue;
	if (curRetrcementValue < retrcementValue)
	{
		bIsContinue = false;
	}

	double curStepTime = curValue.time - startValue.time;
	double curSpead = curStepValue / curStepTime;
	double curRetrcementSpead = curSpead / tryEndSpead;
	if(curRetrcementSpead < retrcementSpead)
	{
		bIsContinue = false;
	}
	return bIsContinue;
}

bool CContinueJudgeObj::isContinueStart_s(const CRateValue& curValue, CRateValue& startValue )
{
	double stepValue = curValue.value - startValue.value;
	return false;
}

bool CContinueJudgeObj::isContinueStart( double& stepPersent )
{
	return stepPersent > minStepValuePersent;
}

bool CContinueJudgeObj::stopContinue(const CRateValue& stopValue, CRateValue& startValue, CRateValue& tryEndValue )
{
	CContinueValue curContinueValue;
	curContinueValue.startValue = startValue;
	curContinueValue.endValue = tryEndValue;
	curContinueValue.stopValue = stopValue;

	startValue = tryEndValue;
	if (isContinueStart(stopValue))
	{
		tryEndValue = stopValue;
	}
}


