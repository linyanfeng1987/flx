#pragma once
#include <string>
#include <memory>

#include "rate/rateInfo.h"

#include "account/optAccount.h"
using namespace std;
class CContinueDecision
{
public:
	CContinueDecision(int _startLevel);
	void init(string _monitorName, PRateInfo _rateInfo);
	void levelUp(int curLevel, PRateValue curValue, indexType srcTagId, int direct);
	void continueStop(PRateValue curValue);
	void record(PRateValue curValue);
protected:
	PRateInfo rateInfo;
	int startLevel;
	string monitorName;
	string decisionName;
	string tagName;
	indexType optTagId;
	POptAccount optAccountr;
};
typedef shared_ptr<CContinueDecision> PContinueDecision;
#define newContinueDecision(T1) make_shared<CContinueDecision>(T1)

