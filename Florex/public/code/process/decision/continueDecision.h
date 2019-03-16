#pragma once
#include <string>
#include <memory>

#include "account/optAccount.h"
using namespace std;
class CContinueDecision
{
public:
	CContinueDecision(int _startLevel, string _rateName, string _monitorName, string _decisionName);
	void levelUp(int curLevel, PRateValue curValue, int direct);
	void continueStop(PRateValue curValue);
	void record(PRateValue curValue);
protected:
	int startLevel;
	string rateName;
	string monitorName;
	string decisionName;
	string tagName;
	bool isIn;
	static POptAccount optAccountr;
};
typedef shared_ptr<CContinueDecision> PContinueDecision;
#define newContinueDecision(T1,T2,T3,T4) make_shared<CContinueDecision>(T1,T2,T3,T4)

