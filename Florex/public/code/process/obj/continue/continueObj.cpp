#include "continueObj.h"

CContinueObj::CContinueObj(PContinueSubsection pCurSubsection, int curDir)
{
	pReserveSubsecton = nullptr;
	curObjStatus = continue_keep;
	this->curDir = curDir;
	this->pCurSubsection = pCurSubsection;
	pFinder = newContinueFinder(pCurSubsection->getJudgeGroup());
}



// 不是连续最高值，则尝试查找新的连续
// 当新的连续有了更高的值
// 切换连续段
// 当前连续段中断则，中断

//似乎需要一个对象，封装一个翻转连续查找的，这个过程中，查找器重复被重置，小连续不断被中断，直到替换成功

emumContinueStatus CContinueObj::isContinueGoOn(PRateValue curValue )
{
	emumContinueStatus curContinueStatus = pCurSubsection->isContinueGoOn(curValue);

	if (continue_stop != curContinueStatus)
	{
		if (continue_lowDown == curObjStatus)
		{
			curLowDown(curValue, curContinueStatus);
		}
		else if(continue_keep <= curObjStatus)
		{
			curKeep(curValue, curContinueStatus);
		}
	}
	else
	{
		subsections.push_back(pCurSubsection);
	}
	return curContinueStatus;
}



void CContinueObj::curLowDown(PRateValue curValue, emumContinueStatus curContinueStatus )
{
	emumContinueStatus resStatus = continue_stop;
	if (nullptr != pReserveSubsecton)
	{
		resStatus = pReserveSubsecton->isContinueGoOn(curValue);
		if (continue_keep <= resStatus 
			&& (pCurSubsection->getCurLevel() - lowDownLevel <= pReserveSubsecton->getCurLevel()
			|| continue_groupUp <= curContinueStatus))
		{
			pCurSubsection->stopContinue(curValue);
			subsections.push_back(pCurSubsection);
			pCurSubsection = pReserveSubsecton;
			pReserveSubsecton = nullptr;
			curObjStatus = continue_keep;
		}
	}
	else
	{
		if (!pFinder->isStart())
		{
			pFinder->setStart(curValue, curDir);
		}
		else
		{
			pReserveSubsecton = pFinder->tryFindNew(curValue);
		}
	}
}

void CContinueObj::curKeep( PRateValue curValue, emumContinueStatus curContinueStatus  )
{
	if (continue_lowDown == curContinueStatus)
	{
		curObjStatus = continue_lowDown;
		curLowDown(curValue, curContinueStatus);
	}
}

