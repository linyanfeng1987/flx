#pragma once
#include <memory>
#include "process/obj/rateValue.h"

using namespace std;
class CFlxOpt
{
public:
	CFlxOpt(PRateValue _beginValue, int _direct);

	bool isEnd(){return nullptr != endValue;}
	void setEnd(PRateValue _endValue){endValue = _endValue;}
	PRateValue getEnd(){return endValue;}
	double getStartTime(){return beginValue->time;}

	double getCurResValue(PRateValue curValue){return (beginValue->value-curValue->value)*direct;}
	double getEndResValue(){return (beginValue->value-endValue->value)*direct;}
protected:
	int direct;
	PRateValue beginValue;
	PRateValue endValue;
};

typedef shared_ptr<CFlxOpt> PFlxOpt;
#define newFlxOptr(T1,T2) make_shared<CFlxOpt>(T1,T2)