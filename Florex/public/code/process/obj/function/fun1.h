#pragma once
#include "baseFun.h"

using namespace std;

// º¯Êý f(x) = 0.618*(1-0.4^x)
class CFun1 : public CBaseFun
{
public:
	CFun1(double param1, double param2){this->param1 = param1; this->param2 = param2;}
	virtual double calc(double xValue);
protected:
	double param1;
	double param2;
};

typedef shared_ptr<CFun1> PFun1;
#define newCFun1(T1,T2) make_shared<CFun1>(T1,T2)
