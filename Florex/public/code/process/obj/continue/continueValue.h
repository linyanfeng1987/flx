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
	void setValue(PRateValue startRateValue, PRateValue endRateValue, PRateValue stopRateValue, int direct);
	void setLevels(list<int> &nLevels);
	
	PRow buildDbRow(int groupId, PContinueValueStruct pSt);
	
	PRateValue startRateValue;
	PRateValue endRateValue;
	// 停止相关信息
	PRateValue stopRateValue;
	
	// 停止的判断信息，类型暂定
	string stopType;

	// 存表数据 
	double startValue;
	double endValue;
	double stopValue;
	double stepValue;

	double minValue;

	double startTime;
	double stepTime;
	
	int direct;

	int startLevel;
	int maxLevel;
	int stopLevel;
	string levels;

	string groupId;
protected:
	void calc();
};

typedef shared_ptr<CContinueValue> PContinueValue;
#define newContinueValue() make_shared<CContinueValue>()