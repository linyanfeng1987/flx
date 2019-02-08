#include "continueFinder.h"
#include <list>
#include "table/Table.h"

CContinueFinder::CContinueFinder( PContinueJudgeGroup pJudgeGroup)
{
	objIndex = 0;
	startValue = nullptr;
	this->pJudgeGroup = pJudgeGroup;
}


// 只记录生成最小连续的起始信息即可
bool CContinueFinder::add(PRateValue curValue, PContinueValueStruct pTableStruct)
{
	addToObj(curValue,pTableStruct);
	tryFindNew(curValue);
	return true;
}

void CContinueFinder::tryFindNew( PRateValue curValue )
{
	if (nullptr == startValue)
	{
		startValue = curValue;
	}
	else
	{
		// 确定方向
		double stepValue = startValue->value - curValue->value;
		int curDirect = stepValue > 0 ? 1 : -1;
		auto curContinueObjIter = curObjs.find(curDirect);
		if (curObjs.end() == curContinueObjIter)
		{
			// 当前容器内没有同方向的连续对象的时候，尝试判断是否生成新的
			double stepPersent = abs(stepValue / curValue->value * basePersentStep);
			int continueLevel = pJudgeGroup->isContinueStart(stepPersent);
			if (-1 != continueLevel)
			{
				// 连续达成
				PContinueObj pObj = newContinueObj(pJudgeGroup);
				pObj->init(startValue, curValue, curDirect, continueLevel);
				pObj->setId(++objIndex);
				curObjs.insert(make_pair(curDirect, pObj));

				// 重置起点
				startValue = curValue;
			}
		}
	}
}

void CContinueFinder::addToObj( PRateValue curValue, PContinueValueStruct pTableStruct )
{
	static list<int> rmObjs;
	for (auto objPair : curObjs)
	{
		if (!objPair.second->isContinueGoOn(curValue))
		{
			// 连续中断
			hisObjs.insert(make_pair(objPair.second->getId(), objPair.second));
			rmObjs.push_back(objPair.first);
		}
	}

	if (1000 < hisObjs.size())
	{
		saveHisObj(pTableStruct);
	}

	for (int rmId : rmObjs)
	{
		curObjs.erase(rmId);
	}

	if (!rmObjs.empty())
	{
		rmObjs.clear();
	}
}

void CContinueFinder::saveHisObj(PContinueValueStruct pTableStruct)
{
	PTable pTable = newTable(pTableStruct);
	for (auto hisObjPair : hisObjs)
	{
		PRow pRow = hisObjPair.second->getContinueValue()->buildDbRow(finderId, pTableStruct);
		pTable->addRow(pRow);
	}

	pTable->save();
	hisObjs.clear();
}
