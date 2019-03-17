#pragma once
#include "flxOpt.h"
#include "db/dataStruct/monitorValueStruct.h"

#include <map>
using namespace std;
class CMonitor
{
public:
	CMonitor(string _name, string _rateName);

	void addOpt(PFlxOpt flxOpt);
	void endOpt(double key, PRateValue endValue);
	void endOpt(PRateValue endValue);

	double getCurRes(PRateValue curValue);
	double getEndRes();
protected:
	void saveToDb(int dataType, double curTime, string curTimeDesc, double sumValue);
	void addEndOpt(pair<double, PFlxOpt> pr);
	map<double, PFlxOpt> curOpts;

	string name;
	string rateName;
	double endRes;
	map<double, PFlxOpt> endOpts;

	PMonitorValueStruct monitorStruct;
};

typedef shared_ptr<CMonitor> PMonitor;
#define newMonitor(T1,T2) make_shared<CMonitor>(T1,T2)