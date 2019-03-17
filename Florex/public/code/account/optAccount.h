#pragma once
#include "monitor.h"
#include "AutoMutex.h"

class COptAccount;
typedef shared_ptr<COptAccount> POptAccount;
#define newOptAccount() make_shared<COptAccount>()

class COptAccount
{
public:
	COptAccount(){}
	~COptAccount(){}
	static POptAccount instence();
	
	void optIn(string& tagName, string& rateName, indexType srcTagId, PRateValue curValue, int direct);
	void optOut(string& tagName, string& rateName, PRateValue curValue);
	void record(string& tagName, string& rateName, PRateValue curValue);
protected:
	
	PMonitor getMonitor(string& tagName, string& rateName);
	map<string, PMonitor> monitors;
	static POptAccount gp;
	recursive_mutex optMutex;
};

