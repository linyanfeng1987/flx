#pragma once
#include <string>
#include <list>
#include <memory>

using namespace std;

const int valueType_def = -1;
const int valueType_str = 0;
const int valueType_int = 1;
const int valueType_timet = 2;
const int valueType_double = 3;

const string emptyString = "";
const string zeroString = "0";

enum DATA_STATUS
{
	DATA_NEW,
	DATA_SAME,
	DATA_CHANGE,
	DATA_DELETE,
};

class CValue
{
public:
	CValue();
	CValue(string strValue);
	CValue(double dValue);
	CValue(int nValue);
	CValue(time_t stValue);

	bool empty();

	string& getStrValue();
	int getIntValue();
	time_t getTimeTValue();
	double getDoubleValue();

	void setValue(double dValue);
	void setValue(int nValue);
	void setValue(time_t tValue);
	void setValue(string& strValue);

	bool isDataSame() { return DATA_SAME == dataStatus; }
	void setSame() { dataStatus = DATA_SAME; }
protected:
	void init();
	void buildDoubleValue();
	void buildStringValue();
	void buildIntValue();
	void buildTimeTValue();

	int dataType;

	shared_ptr<string> pStrValue;
	shared_ptr<int> pIntValue;
	shared_ptr<time_t> pTimeTValue;
	shared_ptr<double> pDoubleValue;

	DATA_STATUS dataStatus;
};

typedef shared_ptr<CValue> PValue;
#define newValue() make_shared<CValue>()
#define newValueP(T) make_shared<CValue>(T)
