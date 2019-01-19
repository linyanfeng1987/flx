#include "continueJudgeGroup.h"


CContinueJudgeGroup::CContinueJudgeGroup( int maxObjNumber, double stepLevelPersent )
{
	this->maxObjNumber = maxObjNumber;
	this->stepLevelPersent = stepLevelPersent;
}

bool CContinueJudgeGroup::isContinueGoOn( int& level, const CRateValue& curValue, CRateValue& startValue, CRateValue& tryEndValue, int curDirect )
{
	auto pCurJudge = judgeGroup.find(level)->second;
	bool bIsContinue = pCurJudge->isContinueGoOn(curValue,startValue,tryEndValue,curDirect);
	if (bIsContinue)
	{
		tryEndValue =  curValue;
		int nextLevel = level + 1;
		if (nextLevel <= maxObjNumber)
		{
			// ³¢ÊÔ³É³¤
			auto pNextJudge = judgeGroup.find(nextLevel)->second;
			bool bIsGroupUp = pNextJudge->isContinueStart(curValue, startValue, curDirect);
			if (bIsGroupUp)
			{
				level = nextLevel;
			}
		}
	}
	return bIsContinue;
}

void CContinueJudgeGroup::init( double minStepValuePersent, double minStepSpeedPersent, double retrcementValue, double retrcementSpead, double stopSpead )
{
	this->minStepSpeedPersent = minStepSpeedPersent;
	this->minStepValuePersent = minStepValuePersent;
	this->retrcementSpead = retrcementSpead;
	this->retrcementValue = retrcementValue;
	this->stopSpead = stopSpead;

	for (int nLevelIndex = 0; nLevelIndex <= maxObjNumber ; nLevelIndex++)
	{
		PContinueJudgeObj pObj = newContinueJudgeObj(nLevelIndex);
		pObj->init(minStepValuePersent, minStepSpeedPersent, retrcementValue, retrcementSpead, stopSpead);
		minStepValuePersent /= stepLevelPersent;
		minStepSpeedPersent /= stepLevelPersent;
		retrcementValue /= stepLevelPersent;
		retrcementSpead /= stepLevelPersent;

		judgeGroup.insert(make_pair(nLevelIndex, pObj));
	}
}

int CContinueJudgeGroup::isContinueStart( double& stepPersent )
{
	int level = -1;
	
	for (auto objPair: judgeGroup)
	{
		if (objPair.second->isContinueStart(stepPersent))
		{
			level = objPair.second->getLevel();
		}
		else
		{
			break;
		}
	}
	return level;
}
