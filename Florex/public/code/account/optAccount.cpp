#include "optAccount.h"

POptAccount COptAccount::gp = newOptAccount();

indexType COptAccount::optIn( string& tagName, string& rateName, indexType srcTagId, PRateValue curValue, int direct)
{
	PMonitor monitor = getMonitor(tagName, rateName);
	return monitor->addOpt(newFlxOptr(tagName, srcTagId, rateName, curValue, direct));
}

void COptAccount::optOut( string& tagName, string& rateName, indexType optTagId, PRateValue curValue )
{
	optOut(tagName, rateName, optTagId, curValue, string(""));
}

void COptAccount::optOut( string& tagName, string& rateName, indexType optTagId, PRateValue curValue, string& desc )
{
	PMonitor monitor = getMonitor(tagName, rateName);
	monitor->endOpt(optTagId, curValue, desc);
}

void COptAccount::record( string& tagName, string& rateName, PRateValue curValue )
{
	PMonitor monitor = getMonitor(tagName, rateName);
	monitor->getCurRes(curValue); 
}

PMonitor COptAccount::getMonitor( string& tagName, string& rateName )
{
	CAutoMutex autoMutex(&optMutex);
	PMonitor monitor = nullptr;
	auto monitorIter = monitors.find(tagName);
	if (monitors.end() != monitorIter)
	{
		monitor = monitorIter->second;
	}
	else
	{
		auto pr = monitors.insert(make_pair(tagName, newMonitor(tagName, rateName)));
		if (pr.second)
		{
			monitor = pr.first->second;
		}
	}
	return monitor;
}

POptAccount COptAccount::instence()
{
	return gp;
}
