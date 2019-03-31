#pragma once
#include <string>
#include <memory>

#include "rate/rateInfo.h"
#include "account/optAccount.h"
using namespace std;

class CAverageDecisionTemplate
{
public:
	CAverageDecisionTemplate(double _optInPersent, double _optOutPersent);
	~CAverageDecisionTemplate(){}

	double optInPersent;
	double optOutPersent;
};
typedef shared_ptr<CAverageDecisionTemplate> PAverageDecisionTemplate;
#define newAverageDecisionTemplate(T1,T2) make_shared<CAverageDecisionTemplate>(T1,T2)

class CAverageDecision
{
public:
	CAverageDecision(PAverageDecisionTemplate _decisionTemplate, double _averageStepTime, string _monitorName, PRateInfo _rateInfo);
	//CAverageDecision(double averageStepTime, double _optInPersent, double _optOutPersent);
	//void init(string _monitorName, PRateInfo _rateInfo);
	void add(PRateValue curValue, PRateValue averageValue);
	void record(PRateValue curValue);
protected:

	// 起始混乱状态，反复尝试定位方向
	// 方向确定后进入清晰状态， 偶尔触发方向转折
	static const int status_confusion = 0;
	static const int status_confusion_tryIn = 2;
	static const int status_clear = 1;
	static const int status_clear_tryOut = 3;

	void fun_confusion(PRateValue curValue, PRateValue averageValue);
	void fun_confusion_tryIn(PRateValue curValue, PRateValue averageValue);
	void fun_status_clear(PRateValue curValue, PRateValue averageValue);
	void fun_status_clear_tryOut(PRateValue curValue, PRateValue averageValue);

	static const int status_tryIn = 2;
	static const int status_tryOut = -2;
	static const int status_dirTrySet = 1;
	static const int status_find = 2;
	

	void setTryDirect(double nowTime, int nowDirect);
	void setTryStart(double nowTime);

	bool isDirectSet(double stepTime);
	bool isDirectInit(double stepTime);

	void trySetDir(PRateValue curValue, PRateValue averageValue);
	void none(PRateValue curValue, PRateValue averageValue);
	void keepOpt(PRateValue curValue, PRateValue averageValue);


	PAverageDecisionTemplate decisionTemplate;

	double averageStepTime;
	double optInTime;
	double optOutTime;

	PRateInfo rateInfo;
	string monitorName;
	string decisionName;
	string tagName;
	indexType optTagId;
	POptAccount optAccountr;

	int tryDirect;
	int nowStatus;
	double trySetStartTime;
};
typedef shared_ptr<CAverageDecision> PAverageDecision;
#define newAverageDecision(T1,T2,T3,T4) make_shared<CAverageDecision>(T1,T2,T3,T4)

