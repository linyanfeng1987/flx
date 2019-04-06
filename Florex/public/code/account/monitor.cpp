#include "monitor.h"
#include "table/Row.h"

CMonitor::CMonitor( string _name, string _rateName ):endRes(0),name(_name),rateName(_rateName)
{
	monitorStruct = CMonitorValueStruct::instence();
	monitorTopStruct = CMonitorValueStruct::instenceTop();
}

indexType CMonitor::addOpt( PFlxOpt flxOpt )
{
	curOpts.insert(make_pair(flxOpt->getTagId(), flxOpt));
	return flxOpt->getTagId();
}

void CMonitor::endOpt( indexType optTagId, PRateValue endValue, string& desc )
{
	auto optIter = curOpts.find(optTagId);
	if (curOpts.end() != optIter)
	{
		optIter->second->setEnd(endValue, desc);
		addEndOpt(*optIter);
		curOpts.erase(optTagId);
		saveToDb(CMonitorValueStruct::monitorDataType_endOpt, endValue->time, endValue->timeDesc, endRes);
	}
}

void CMonitor::endOpt( PRateValue endValue )
{
	for (auto optPair : curOpts)
	{
		optPair.second->setEnd(endValue);
		addEndOpt(optPair);
	}

	if (0 < curOpts.size())
	{
		saveToDb(CMonitorValueStruct::monitorDataType_endOpt, endValue->time, endValue->timeDesc, endRes);
		curOpts.clear();
	}
}

double CMonitor::getCurRes( PRateValue curValue )
{
	double res = 0;
	for (auto optPair : curOpts)
	{
		res += optPair.second->getCurResValue(curValue);
	}
	res += endRes;
	saveToDb(CMonitorValueStruct::monitorDataType_recordOpt, curValue->time, curValue->timeDesc, res);
	return res;
}

double CMonitor::getEndRes()
{
	return endRes;
}

void CMonitor::addEndOpt( pair<indexType, PFlxOpt> pr )
{
	endOpts.insert(pr);
	endRes += pr.second->getEndResValue();
}

void CMonitor::saveToDb( int dataType, double curTime, string curTimeDesc, double sumValue )
{
	PRow row = newRow(monitorStruct);

	row->setStringValue(CMonitorValueStruct::rateName, rateName);
	row->setStringValue(CMonitorValueStruct::monitorName, name);
	row->setDoubleValue(CMonitorValueStruct::curTime, curTime);
	row->setStringValue(CMonitorValueStruct::curTimeDesc, curTimeDesc);
	row->setDoubleValue(CMonitorValueStruct::sumValue, sumValue);
	row->setIntValue(CMonitorValueStruct::dataType, dataType);

	row->save();

	// ´æ´¢topÐÅÏ¢
	row->setTableStruct(monitorTopStruct);
	row->setDataStatus(DATA_NEW);
	if (row->isExit())
	{
		row->setDataStatus(DATA_CHANGE);
	}
	row->save();
}

