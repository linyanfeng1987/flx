#include "Value.h"
#include "PubFun.h"

CValue::CValue()
{
	setValue(string(""));
	dataStatus = DATA_SAME;
}

CValue::CValue( string strValue )
{
	setValue(strValue);
	dataStatus = DATA_SAME;
}

CValue::CValue( double dValue )
{
	setValue(dValue);
	dataStatus = DATA_SAME;
}

void CValue::init()
{
	pIntValue = nullptr;
	pSizeTValue = nullptr;
	pStrValue = nullptr;
	pDoubleValue = nullptr;
}

int CValue::getIntValue()
{
	if (nullptr == pIntValue)
	{
		if (valueType_str == dataType)
		{
			buildDoubleValue();
		}
		pIntValue = make_shared<int>((int)*pDoubleValue);
	}
	return *pIntValue;
}

double CValue::getDoubleValue()
{
	if (nullptr == pDoubleValue)
	{
		if (valueType_str == dataType)
		{
			buildDoubleValue();
		}
	}
	return *pDoubleValue;
}

size_t CValue::getSizeTValue()
{
	if (nullptr == pSizeTValue)
	{
		if (valueType_str == dataType)
		{
			buildDoubleValue();
		}
		pSizeTValue = make_shared<size_t>((size_t)*pDoubleValue);
	}
	return *pSizeTValue;
}

string& CValue::getStrValue()
{
	if (nullptr == pStrValue)
	{
		if (valueType_double == dataType)
		{
			buildStringValue();
		}
	}
	return *pStrValue;
}

void CValue::setValue( double dValue )
{
	// 一旦修改，旧的数据就废掉了
	init();
	dataType = valueType_double;
	pDoubleValue = make_shared<double>(dValue);
	dataStatus = DATA_CHANGE;
}

void CValue::setValue( string &strValue )
{
	init();
	dataType = valueType_str;
	pStrValue = make_shared<string>(strValue);
	dataStatus = DATA_CHANGE;
}

void CValue::buildDoubleValue()
{
	if (nullptr != pStrValue)
	{
		pDoubleValue = make_shared<double>(PubFun::stringToDouble(*pStrValue));
	}
	else
	{
		pDoubleValue = make_shared<double>(0);
	}
}

void CValue::buildStringValue()
{
	if (nullptr != pDoubleValue)
	{
		pStrValue = make_shared<string>(PubFun::doubleToString(*pDoubleValue));
	}
	else
	{
		pStrValue = make_shared<string>(""); 
	}
}

bool CValue::empty()
{
	bool isEmpty = false;
	if (valueType_str == dataType && pStrValue->empty())
	{
		isEmpty = true;
	}
	else if(valueType_double == dataType && 0 == *pDoubleValue)
	{
		isEmpty = true;
	}

	return isEmpty;
}


