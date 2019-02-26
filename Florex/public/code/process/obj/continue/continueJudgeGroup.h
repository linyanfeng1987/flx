#pragma once
#include "continueJudgeObj.h"
#include "LinkedHashMap.h"
#include "process/obj/function/fun1.h"
using namespace std;


class CContinueJudgeGroup
{
public:
	CContinueJudgeGroup(int maxObjNumber, double stepLevelPersent, PBaseFun retrcementCalcFun);

	emumContinueStatus isContinueGoOn(int& level, PRateValue curValue, PRateValue startValue, PRateValue& tryEndValue, int curDirect );
	int isContinueStart(double& stepPersent);

	void init(double minStepValuePersent, double retrcementSpead);
protected:
	Linked_map<int, PContinueJudgeObj> judgeGroup;

	int maxObjNumber;
	// 每级比例 高等级*比例= 低等级
	double stepLevelPersent;


	// 必须达到最小便宜比例，才算在此区间上连续, 单位：千分比
	double minStepValuePersent;
	//double minStepSpeedPersent;
	//////////////////////////////////////////////////////////////////////////
	// 连续判断变量
	// 回撤值，当回撤小于次值认为连续未中断，否则认为连续终端
	double retrcementValue;
	PBaseFun retrcementCalcFun;
	// 从起始值算起，最小速率，单位 s?h？
	//double stopSpead;
	// 回撤速率
	double retrcementSpead;
};

typedef shared_ptr<CContinueJudgeGroup> PContinueJudgeGroup;
#define newContinueJudgeGroup(T1,T2,T3) make_shared<CContinueJudgeGroup>(T1,T2,T3)