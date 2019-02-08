#include "continueValue.h"
#include "PubFun.h"

CContinueValue::CContinueValue()
{
	startLevel = -1;
	maxLevel = -1;
	stopLevel = -1;
}

void CContinueValue::calc()
{
	startValue = startRateValue->value;
	endValue = endRateValue->value;
	stopValue = stopRateValue->value;

	startTime = startRateValue->time;
	stepTime = stopRateValue->time - startRateValue->time;
}

void CContinueValue::setValue( PRateValue startRateValue, PRateValue endRateValue, PRateValue stopRateValue, int direct )
{
	this->startRateValue = startRateValue;
	this->endRateValue = endRateValue;
	this->stopRateValue = stopRateValue;
	this->direct = direct;
}

PRow CContinueValue::buildDbRow(int groupId, PContinueValueStruct pSt)
{
	PRow pRow = newRow(pSt);

	pRow->setIntValue(CContinueValueStruct::groupId, groupId);
	pRow->setDoubleValue(CContinueValueStruct::startTime, startTime);
	pRow->setDoubleValue(CContinueValueStruct::stepTime, stepTime);

	pRow->setIntValue(CContinueValueStruct::direct, direct);
	pRow->setDoubleValue(CContinueValueStruct::startValue, startValue);
	pRow->setDoubleValue(CContinueValueStruct::endValue, endValue);
	pRow->setDoubleValue(CContinueValueStruct::stopValue, stopValue);

	pRow->setIntValue(CContinueValueStruct::startLevel, startLevel);
	pRow->setIntValue(CContinueValueStruct::maxLevel, maxLevel);
	pRow->setIntValue(CContinueValueStruct::stopLevel, stopLevel);

	pRow->setStringValue(CContinueValueStruct::levels, levels);

	return pRow;
}

void CContinueValue::setLevels( list<int> &nLevels )
{
	levels = "";
	for (int curLevel : nLevels)
	{
		startLevel = startLevel == -1 ? curLevel : startLevel;
		maxLevel = maxLevel < curLevel ? curLevel : maxLevel;
		stopLevel = curLevel;
		if (!levels.empty())
		{
			levels.append(",");
		}
		levels.append(PubFun::intToString(curLevel));
	}
}
