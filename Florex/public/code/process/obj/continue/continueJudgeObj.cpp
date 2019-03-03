#include "continueJudgeObj.h"

CContinueJudgeObj::CContinueJudgeObj( int continueLevel )
{
	this->continueLevel = continueLevel;
}

void CContinueJudgeObj::init( double minStepValuePersent, double retrcementValue, double retrcementSpead)
{
	//this->minStepSpeedPersent = minStepSpeedPersent;
	this->minStepValuePersent = minStepValuePersent;
	this->retrcementSpead = retrcementSpead;
	this->retrcementValue = retrcementValue;
	//this->stopSpead = stopSpead;
}

emumContinueStatus CContinueJudgeObj::isContinueGoOn(PRateValue curValue, PRateValue startValue, PRateValue tryEndValue,
													 int& curDirect, double& curRetrcementSpead, PContinueValue& pContinueValue )
{
	emumContinueStatus conStatus = continue_keep;
	double tryEndStepValue = (startValue->value - tryEndValue->value)*curDirect;
	double tryEndStepTime = tryEndValue->time - startValue->time;
	double tryEndSpead = tryEndStepValue / tryEndStepTime;

	double curStepValue = (startValue->value - curValue->value)*curDirect;
	double curRetrcementValue = curStepValue / tryEndStepValue;
	double curStepTime = curValue->time - startValue->time;
	// 0.618*(1-0.4^x)*(0.9998^t) tµ¥Î»4h
	double judgeRetrcementValue = 1-retrcementValue * pow(timeAttenuation, curStepTime);
	if (1 < curRetrcementValue)
	{
		conStatus = continue_groupUp;
	}
	else if (curRetrcementValue < judgeRetrcementValue)
	{
		conStatus = continue_stop;
		pContinueValue = newContinueValue();
		pContinueValue->setValue(startValue, tryEndValue, curValue, curDirect);
		pContinueValue->setJudgeValue(curRetrcementValue, retrcementValue,judgeRetrcementValue);
		
	}
	else
	{
		conStatus = continue_keep;
		/*
		double curSpead = curStepValue / curStepTime;
		curRetrcementSpead = curSpead / tryEndSpead;
		conStatus = isLowDown(curRetrcementSpead) ? continue_lowDown : continue_keep;
		*/
	}

	return conStatus;
}

bool CContinueJudgeObj::isContinueStart_s(const PRateValue curValue, PRateValue startValue )
{
	double stepValue = curValue->value - startValue->value;
	return false;
}

bool CContinueJudgeObj::isContinueStart( double& stepPersent )
{
	return stepPersent > minStepValuePersent;
}

double CContinueJudgeObj::getStepPersent(PRateValue curValue, PRateValue startValue)
{
	double stepValue = startValue->value - curValue->value;
	double stepPersent = abs(stepValue / curValue->value * basePersentStep);
	return stepPersent;
}

bool CContinueJudgeObj::isLowDown( double& curRetrcementSpead )
{
	return curRetrcementSpead < retrcementSpead;
}





// bool CContinueJudgeObj::stopContinue(PRateValue stopValue, PRateValue startValue, PRateValue tryEndValue )
// {
// 	CContinueValue curContinueValue;
// 	curContinueValue.startValue = startValue;
// 	curContinueValue.endValue = tryEndValue;
// 	curContinueValue.stopValue = stopValue;
// 
// 	startValue = tryEndValue;
// 	if (isContinueStart(stopValue.value))
// 	{
// 		tryEndValue = stopValue;
// 	}
// 	return true;
// }


