#pragma once
#include <string>
#include <list>
#include <memory>

using namespace std;

//const int valueType_def = -1;
const int valueType_str = 0;
const int valueType_int = 1;
const int valueType_sizet  = 2;
const int valueType_double = 3;

const string emptyString = "";
const string zeroString = "0";

class CValue
{
public:
	CValue();
	CValue(string strValue);
	CValue(double dValue);

	bool empty();

	string& getStrValue();
	int getIntValue();
	size_t getSizeTValue();
	double getDoubleValue();

	void setValue(double dValue);
	void setValue(string &strValue);
protected:
	void init();
	void buildDoubleValue();
	void buildStringValue();

	int dataType;

	shared_ptr<string> pStrValue;
	shared_ptr<int> pIntValue;
	shared_ptr<size_t> pSizeTValue;
	shared_ptr<double> pDoubleValue;

};

typedef shared_ptr<CValue> PValue;
#define newValue() make_shared<CValue>()
#define newValueP(T) make_shared<CValue>(T)
