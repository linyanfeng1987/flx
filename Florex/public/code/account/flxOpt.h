#pragma once
#include <memory>
#include "db/dataStruct/optValueStruct.h"
#include "process/obj/rateValue.h"

using namespace std;
class CFlxOpt
{
public:
	CFlxOpt(string _tagName, indexType _srcTagId, string _rateName, PRateValue _beginValue, int _direct);

	bool isEnd(){return nullptr != endValue;}
	void setEnd(PRateValue _endValue);
	void setEnd(PRateValue _endValue, string &_desc);
	PRateValue getEnd(){return endValue;}
	double getStartTime(){return beginValue->time;}

	double getCurResValue(PRateValue curValue);
	double getEndResValue();
	void saveToDb();
	indexType getTagId(){return optTagId;}
protected:
	static indexType optTagIdCount;
	indexType optTagId;
	int direct;
	string tagName;
	indexType srcTagId;
	string rateName;
	PRateValue beginValue;
	PRateValue endValue;
	string desc;

	double endRes;
	POptValueStruct optStruct;
};

typedef shared_ptr<CFlxOpt> PFlxOpt;
#define newFlxOptr(T1,T2,T3,T4,T5) make_shared<CFlxOpt>(T1,T2,T3,T4,T5)