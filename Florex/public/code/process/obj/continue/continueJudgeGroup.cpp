#include "continueJudgeGroup.h"


CContinueJudgeGroup::CContinueJudgeGroup( int maxObjNumber, double stepLevelPersent, PBaseFun retrcementCalcFun )
{
	this->maxObjNumber = maxObjNumber;
	this->stepLevelPersent = stepLevelPersent;
	this->retrcementCalcFun = retrcementCalcFun;
}

bool CContinueJudgeGroup::isContinueGoOn( int& level, PRateValue curValue, PRateValue startValue, PRateValue tryEndValue, int curDirect )
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
			// 尝试成长
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
			// 尝试降级
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

void CContinueJudgeGroup::init( double minStepValuePersent, double retrcementSpead )
{
	this->minStepValuePersent = minStepValuePersent;
	this->retrcementSpead = retrcementSpead;
	double retrcementValue = 0;
	for (int nLevelIndex = 0; nLevelIndex <= maxObjNumber ; nLevelIndex++)
	{
		PContinueJudgeObj pObj = newContinueJudgeObj(nLevelIndex);
		// 回撤值需要动态变更，暂定函数 0.618*(1-0.4^x)
		retrcementValue = retrcementCalcFun->calc(nLevelIndex);
		pObj->init(minStepValuePersent, retrcementValue, retrcementSpead);

		minStepValuePersent /= stepLevelPersent;
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
