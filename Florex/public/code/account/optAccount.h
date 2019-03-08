#pragma once
#include "monitor.h"

class COptAccount;
typedef shared_ptr<COptAccount> POptAccountr;
#define newOptAccount() make_shared<COptAccount>()

class COptAccount
{
public:
	COptAccount(){}
	~COptAccount(){}
	static POptAccountr instence();
	
	void optIn(string& tagName, string& rateName, PRateValue curValue, int direct);
	void optOut(string& tagName, string& rateName, PRateValue curValue);
	void record(string& tagName, string& rateName, PRateValue curValue);
protected:
	
	PMonitor getMonitor(string& tagName, string& rateName);
	map<string, PMonitor> monitors;
	static POptAccountr gp;
};

