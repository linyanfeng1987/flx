#include "continueObj.h"
#include "PubFun.h"

indexType CContinueObj::tagIdCount = 0;
CContinueObj::CContinueObj(PRateInfo _rateInfo, PContinueJudgeGroup _pJudgeGroup, list<PContinueDecision>* _decisions) :tagId(++tagIdCount)
{
	rateInfo = _rateInfo;
	pContinueValue = nullptr;
	pJudgeGroup = _pJudgeGroup;
	curStatus = continue_keep;

	for (PContinueDecision decison : *_decisions)
	{
		// 拷贝构造， 使用副本
		PContinueDecision newDecison = newContinueDecision(*decison);
		string monitorName = PubFun::strFormat("continue_%s", pJudgeGroup->name.c_str());
		newDecison->init(monitorName, rateInfo);
		decisions.push_back(newDecison);
	}
}

void CContinueObj::init(PRateValue startValue, PRateValue tryEndValue, int& curDirect, int& _curLevel)
{
	pContinueValue = newContinueValue();
	pContinueValue->setBaseValue(tagId, startValue, tryEndValue, curDirect, _curLevel);
	levelChange(_curLevel, tryEndValue);
	curStatus = continue_keep;

	// 	this->startValue = startValue;
	// 	this->tryEndValue = tryEndValue;
	// 	this->curDirect = curDirect;
	// 	//this->curLevel = curLevel;
	// 	this->maxLevel = curLevel;
	// 	levelStep.push_back(curLevel);
}

emumContinueStatus CContinueObj::isContinueGoOn(PRateValue curValue)
{
	int tmpLevel = pContinueValue->getCurLevel();
	curStatus = pJudgeGroup->isContinueGoOn(curValue, pContinueValue);
	if (continue_stop == curStatus)
	{
		stopContinue(curValue);
	}
	else
	{
		if (++keepCount >= 1000)
		{
			for (PContinueDecision decision : decisions)
			{
				decision->record(curValue);
				keepCount = 0;
			}
		}
		if (pContinueValue->getCurLevel() != tmpLevel)
		{
			levelChange(tmpLevel, curValue);
		}
	}

	return curStatus;
}

void CContinueObj::stopContinue(PRateValue curValue)
{
	for (PContinueDecision decision : decisions)
	{
		decision->continueStop(curValue);
	}
}

void CContinueObj::levelChange(int newLevel, PRateValue curValue)
{
	for (PContinueDecision decision : decisions)
	{
		decision->levelUp(newLevel, curValue, tagId, pContinueValue->direct);
	}
}