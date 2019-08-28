#pragma once
#include <memory>

using namespace std;
class CBaseFun
{
public:
	CBaseFun() {};
	virtual ~CBaseFun() {};
	virtual double calc(double xValue) = 0;
};

typedef shared_ptr<CBaseFun> PBaseFun;