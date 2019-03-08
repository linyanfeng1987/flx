#include "optAccount.h"

POptAccountr COptAccount::gp = newOptAccount();

void COptAccount::optIn( string& tagName, string& rateName, PRateValue curValue, int direct)
{
	PMonitor monitor = getMonitor(tagName, rateName);
	monitor->addOpt(newFlxOptr(curValue, direct));
}

void COptAccount::optOut( string& tagName, string& rateName, PRateValue curValue )
{
	PMonitor monitor = getMonitor(tagName, rateName);
	monitor->endOpt(curValue);
}

void COptAccount::record( string& tagName, string& rateName, PRateValue curValue )
{
	PMonitor monitor = getMonitor(tagName, rateName);
	monitor->getCurRes(curValue); 
}

PMonitor COptAccount::getMonitor( string& tagName, string& rateName )
{
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

POptAccountr COptAccount::instence()
{
	return gp;
}
