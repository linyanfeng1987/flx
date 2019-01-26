#pragma once
#include <list>
#include <map>
#include <memory>
#include "LinkedHashMap.h"

using namespace std;

class CRateValue
{
public:
	CRateValue(){
		time = 0;
		value = 0;
	}
	CRateValue(double time, double value){
		this->time = time;
		this->value = value;
	}

	bool isValid() const{return time != 0;} 
	double time;
	double value;
};

typedef shared_ptr<CRateValue> PRateValue;
#define newRateValue() make_shared<CRateValue>()
#define newRateValueP(T1,T2) make_shared<CRateValue>(T1,T2)

//const CRateValue zeroRateValue;
