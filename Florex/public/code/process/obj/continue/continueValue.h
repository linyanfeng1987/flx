#pragma once
#include "process/obj/rateValue.h"
#include "table/Row.h"
#include <memory>
#include "ConstDef.h"
#include "db/dataStruct/continueValueStruct.h"

using namespace std;

// 连续的值
class CContinueValue
{
public:
	CContinueValue();
	void setBaseValue(indexType _tagId, PRateValue _startRateValue, PRateValue _tryEndRateValue, int _direct, int _curLevel);
	//void setValue(PRateValue startRateValue, PRateValue tryEndRateValue, PRateValue stopRateValue, int direct);
	void setEndValue(PRateValue _stopRateValue, double _curRetrcementValue, double _retrcementValue, double _judgeRetrcementValue);
	void buildLevels();

	int getCurLevel() { return curLevel; }
	void setCurLevel(int _curLevel);

	PRow buildDbRow(int groupId, PContinueValueStruct pSt);

	PRateValue startRateValue;
	PRateValue tryEndRateValue;
	// 停止相关信息
	PRateValue stopRateValue;

	// 停止的判断信息，类型暂定
	string stopType;

	// 上次上报的值
	//CRateValue lastValue;
	list<int> levelStep;

	indexType tagId;

	// 存表数据
	//double startValue;
	//double startTime;

	//double endValue;
	double stepTime;
	double stepValue;

	//double stopValue;
	//double stopTime;

	double minValue;

	int direct;

	int startLevel;
	int maxLevel;
	int stopLevel;
	string levels;

	string groupId;

	double curRetrcementValue;
	double retrcementValue;
	double judgeRetrcementValue;
protected:
	void calc();
	int curLevel;
};

typedef shared_ptr<CContinueValue> PContinueValue;
#define newContinueValue() make_shared<CContinueValue>()