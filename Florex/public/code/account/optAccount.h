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
	
	indexType optIn(string& tagName, string& rateName, indexType srcTagId, PRateValue curValue, int direct);
	void optOut(string& tagName, string& rateName, indexType optTagId, PRateValue curValue);
	void optOut(string& tagName, string& rateName, indexType optTagId, PRateValue curValue, string& desc);
	void record(string& tagName, string& rateName, PRateValue curValue);
protected:
	
	PMonitor getMonitor(string& tagName, string& rateName);
	map<string, PMonitor> monitors;
	static POptAccount gp;
	recursive_mutex optMutex;
};

