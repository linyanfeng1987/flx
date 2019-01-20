#include "continueJudgeGroup.h"


CContinueJudgeGroup::CContinueJudgeGroup( int maxObjNumber, double stepLevelPersent )
{
	this->maxObjNumber = maxObjNumber;
	this->stepLevelPersent = stepLevelPersent;
}

bool CContinueJudgeGroup::isContinueGoOn( int& level, CRateValue& curValue, CRateValue& startValue, CRateValue& tryEndValue, int curDirect )
{
	bool bIsContinue = true;
	auto pCurJudge = judgeGroup.find(level)->second;
	double curRetrcementSpead = 0;
	emumContinueStatus conStatus = pCurJudge->isContinueGoOn(curValue,startValue,tryEndValue,curDirect, curRetrcementSpead);
	if (continue_groupUp == conStatus)
	{
		tryEndValue =  curValue;
		int nextLevel = level + 1;
		while (nextLevel <= maxObjNumber)
		{
			// ³¢ÊÔ³É³¤
			auto pNextJudge = judgeGroup.find(nextLevel)->second;
			double stepPersent = CContinueJudgeObj::getStepPersent(curValue, startValue);
			bool bIsGroupUp = pNextJudge->isContinueStart(stepPersent);
			if (bIsGroupUp)
			{
				level = nextLevel;
			}
			else
			{
				break;
			}
			++nextLevel;
		}
	}
	else if (continue_lowDown == conStatus)
	{
		int nextLevel = level - 1;
		while (nextLevel >= 0)
		{
			// ³¢ÊÔ½µ¼¶
			auto pNextJudge = judgeGroup.find(nextLevel)->second;
			bool isLowDown = pNextJudge->isLowDown(curRetrcementSpead);
			if (isLowDown)
			{
				level = nextLevel;
			}
			else
			{
				break;
			}
			--nextLevel;
		}
	}
	else if (continue_stop == conStatus)
	{
		bIsContinue = false;
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
