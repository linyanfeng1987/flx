#include "continueJudgeGroup.h"

CContinueJudgeGroup::CContinueJudgeGroup(int maxObjNumber, double stepLevelPersent, PBaseFun retrcementCalcFun)
{
	this->maxObjNumber = maxObjNumber;
	this->stepLevelPersent = stepLevelPersent;
	this->retrcementCalcFun = retrcementCalcFun;
}

/*
emumContinueStatus CContinueJudgeGroup::isContinueGoOn( int& level, PRateValue curValue, PRateValue startValue,
													   PRateValue& tryEndValue, int curDirect, PContinueValue& pContinueValue )
{
	//int correcteLevel=0;@@@@
	// 计算简化的可能性，讲时间作为中断计算的一部分，随着时间的增长，中断比例越少，时间趋于0，则中断校正系数趋于1
	// level越高，时效性越长，衰减越慢，反之衰减越快
	// 0.618(1-0.4^x)^t
	auto pCurJudge = judgeGroup.find(level)->second;
	double curRetrcementSpead = 0;
	emumContinueStatus conStatus = pCurJudge->isContinueGoOn(curValue,startValue,tryEndValue,curDirect, curRetrcementSpead, pContinueValue);
	if (continue_groupUp == conStatus)
	{
		tryEndValue =  curValue;
		int nextLevel = level + 1;
		while (nextLevel <= maxObjNumber)
		{
			// 尝试成长
			// 成长的目的是保持连续承受的风险，是之统计不容易中断
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
			// 降低的目的，是易于中断，和成长的目的冲突，抉择点在哪？方向？
			auto pNextJudge = judgeGroup.find(nextLevel)->second;
			@@@降速的抉择有问题，需要重新思考, 降级的目的是更换更小的度量
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
	return conStatus;
}
*/

emumContinueStatus CContinueJudgeGroup::isContinueGoOn(PRateValue curValue, PContinueValue pContinueValue)
{
	//int correcteLevel=0;@@@@
	// 计算简化的可能性，讲时间作为中断计算的一部分，随着时间的增长，中断比例越少，时间趋于0，则中断校正系数趋于1
	// level越高，时效性越长，衰减越慢，反之衰减越快
	// 0.618(1-0.4^x)^t
	int curLevel = pContinueValue->getCurLevel();
	auto pCurJudge = judgeGroup.find(curLevel)->second;
	double curRetrcementSpead = 0;
	emumContinueStatus conStatus = pCurJudge->isContinueGoOn(curValue, pContinueValue);
	if (continue_groupUp == conStatus)
	{
		pContinueValue->tryEndRateValue = curValue;
		int nextLevel = curLevel + 1;
		while (nextLevel <= maxObjNumber)
		{
			// 尝试成长
			// 成长的目的是保持连续承受的风险，是之统计不容易中断
			auto pNextJudge = judgeGroup.find(nextLevel)->second;
			double stepPersent = CContinueJudgeObj::getStepPersent(curValue, pContinueValue->startRateValue);
			bool bIsGroupUp = pNextJudge->isContinueStart(stepPersent);
			if (bIsGroupUp)
			{
				pContinueValue->setCurLevel(nextLevel);
			}
			else
			{
				break;
			}
			++nextLevel;
		}
	}
	/*
	else if (continue_lowDown == conStatus)
	{
		int nextLevel = level - 1;
		while (nextLevel >= 0)
		{
			// 尝试降级
			// 降低的目的，是易于中断，和成长的目的冲突，抉择点在哪？方向？
			auto pNextJudge = judgeGroup.find(nextLevel)->second;
			@@@降速的抉择有问题，需要重新思考, 降级的目的是更换更小的度量
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
	}*/
	return conStatus;
}

void CContinueJudgeGroup::init(double minStepValuePersent, double retrcementSpead)
{
	this->minStepValuePersent = minStepValuePersent;
	this->retrcementSpead = retrcementSpead;
	double retrcementValue = 0;
	for (int nLevelIndex = 0; nLevelIndex <= maxObjNumber; nLevelIndex++)
	{
		PContinueJudgeObj pObj = newContinueJudgeObj(nLevelIndex);
		// 回撤值需要动态变更，暂定函数 0.618*(1-0.4^x)
		retrcementValue = retrcementCalcFun->calc(nLevelIndex);
		pObj->init(minStepValuePersent, retrcementValue, retrcementSpead);

		minStepValuePersent /= stepLevelPersent;

		judgeGroup.insert(make_pair(nLevelIndex, pObj));
	}
}

int CContinueJudgeGroup::isContinueStart(double& stepPersent)
{
	int level = -1;

	for (auto objPair : judgeGroup)
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