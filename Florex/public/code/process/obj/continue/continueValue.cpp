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
	//startValue = startRateValue->value;
	//endValue = tryEndRateValue->value;
	//stopValue = stopRateValue->value;
	stepValue = (startRateValue->value - tryEndRateValue->value) * direct;

	//startTime = startRateValue->time;
	stepTime = tryEndRateValue->time - startRateValue->time;
	buildLevels();
}

PRow CContinueValue::buildDbRow(int groupId, PContinueValueStruct pSt)
{
	PRow pRow = newRow(pSt);
	pRow->setIndexValue(CContinueValueStruct::tagId, tagId);
	pRow->setIntValue(CContinueValueStruct::direct, direct);
	pRow->setIntValue(CContinueValueStruct::groupId, groupId);

	pRow->setDoubleValue(CContinueValueStruct::startValue, startRateValue->value);
	pRow->setDoubleValue(CContinueValueStruct::startTime, startRateValue->time);
	pRow->setStringValue(CContinueValueStruct::startTimeDesc, startRateValue->timeDesc);

	pRow->setDoubleValue(CContinueValueStruct::stopValue, stopRateValue->value);
	pRow->setDoubleValue(CContinueValueStruct::stopTime, stopRateValue->time);
	pRow->setStringValue(CContinueValueStruct::stopTimeDesc, stopRateValue->timeDesc);

	pRow->setDoubleValue(CContinueValueStruct::endValue, tryEndRateValue->value);
	pRow->setDoubleValue(CContinueValueStruct::stepValue, stepValue);
	pRow->setDoubleValue(CContinueValueStruct::stepTime, stepTime);

	pRow->setIntValue(CContinueValueStruct::startLevel, startLevel);
	pRow->setIntValue(CContinueValueStruct::maxLevel, maxLevel);
	pRow->setIntValue(CContinueValueStruct::stopLevel, stopLevel);

	pRow->setDoubleValue(CContinueValueStruct::curRetrcementValue, curRetrcementValue);
	pRow->setDoubleValue(CContinueValueStruct::retrcementValue, retrcementValue);
	pRow->setDoubleValue(CContinueValueStruct::judgeRetrcementValue, judgeRetrcementValue);

	pRow->setStringValue(CContinueValueStruct::levels, levels);

	return pRow;
}

void CContinueValue::buildLevels()
{
	levels = "";
	for (int curLevel : levelStep)
	{
		startLevel = startLevel == -1 ? curLevel : startLevel;
		//maxLevel = maxLevel < curLevel ? curLevel : maxLevel;
		stopLevel = curLevel;
		if (!levels.empty())
		{
			levels.append(",");
		}
		levels.append(PubFun::intToString(curLevel));
	}
}

void CContinueValue::setBaseValue(indexType _tagId, PRateValue _startRateValue, PRateValue _tryEndRateValue, int _direct, int _curLevel)
{
	tagId = _tagId;
	startRateValue = _startRateValue;
	tryEndRateValue = _tryEndRateValue;
	direct = _direct;
	curLevel = _curLevel;
}

void CContinueValue::setEndValue(PRateValue _stopRateValue, double _curRetrcementValue, double _retrcementValue, double _judgeRetrcementValue)
{
	stopRateValue = _stopRateValue;
	curRetrcementValue = _curRetrcementValue;
	retrcementValue = _retrcementValue;
	judgeRetrcementValue = _judgeRetrcementValue;
	calc();
}

void CContinueValue::setCurLevel(int _curLevel)
{
	curLevel = _curLevel;
	maxLevel = curLevel > maxLevel ? curLevel : maxLevel;
	levelStep.push_back(curLevel);
}