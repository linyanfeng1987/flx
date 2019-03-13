#pragma once
#include <memory>
#include "db/dataStruct/optValueStruct.h"
#include "process/obj/rateValue.h"

using namespace std;
class CFlxOpt
{
public:
	CFlxOpt(string _rateName, PRateValue _beginValue, int _direct);

	bool isEnd(){return nullptr != endValue;}
	void setEnd(PRateValue _endValue);
	PRateValue getEnd(){return endValue;}
	double getStartTime(){return beginValue->time;}

	double getCurResValue(PRateValue curValue);
	double getEndResValue();
	void saveToDb();
protected:
	int direct;
	string rateName;
	PRateValue beginValue;
	PRateValue endValue;

	double endRes;
	POptValueStruct optStruct;
};

typedef shared_ptr<CFlxOpt> PFlxOpt;
#define newFlxOptr(T1,T2,T3) make_shared<CFlxOpt>(T1,T2,T3)