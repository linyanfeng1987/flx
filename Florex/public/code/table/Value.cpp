#include "Value.h"
#include "PubFun.h"

CValue::CValue()
{
// 	setValue(string(""));
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

CValue::CValue( int nValue )
{
	setValue(nValue);
	dataStatus = DATA_SAME;
}

CValue::CValue( time_t tValue )
{
	setValue(tValue);
	dataStatus = DATA_SAME;
}

void CValue::init()
{
	pIntValue = nullptr;
	pTimeTValue = nullptr;
	pStrValue = nullptr;
	pDoubleValue = nullptr;
	dataStatus = DATA_SAME;
	dataType = valueType_def;
}

int CValue::getIntValue()
{
	if (nullptr == pIntValue)
	{
		buildIntValue();
	}
	return *pIntValue;
}

double CValue::getDoubleValue()
{
	if (nullptr == pDoubleValue)
	{
		buildDoubleValue();
	}
	return *pDoubleValue;
}

time_t CValue::getTimeTValue()
{
	if (nullptr == pTimeTValue)
	{
		buildTimeTValue();
	}
	return *pTimeTValue;
}

string& CValue::getStrValue()
{
	if (nullptr == pStrValue)
	{
		buildStringValue();
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

void CValue::setValue( int nValue )
{
	init();
	dataType = valueType_int;
	pIntValue = make_shared<int>(nValue);
	dataStatus = DATA_CHANGE;
}

void CValue::setValue( string &strValue )
{
	init();
	dataType = valueType_str;
	pStrValue = make_shared<string>(strValue);
	dataStatus = DATA_CHANGE;
}

void CValue::setValue( time_t tValue )
{
	init();
	dataType = valueType_timet;
	pTimeTValue = make_shared<time_t>(tValue);
	dataStatus = DATA_CHANGE;
}

void CValue::buildDoubleValue()
{
	if (valueType_str == dataType)
	{
		pDoubleValue = make_shared<double>(PubFun::stringToDouble(*pStrValue));
	}
	else if (valueType_int == dataType)
	{
		pDoubleValue = make_shared<double>(*pIntValue);
	}
	else if (valueType_timet == dataType)
	{
		pDoubleValue = make_shared<double>((double)(*pTimeTValue));
	}
	else
	{
		pDoubleValue = make_shared<double>(0);
	}
}

void CValue::buildStringValue()
{
	if (valueType_double == dataType)
	{
		pStrValue = make_shared<string>(PubFun::doubleToString(*pDoubleValue));
	}
	else if (valueType_int == dataType)
	{
		pStrValue = make_shared<string>(PubFun::intToString(*pIntValue));
	}
	else if (valueType_timet == dataType)
	{
		pStrValue = make_shared<string>(PubFun::timetToString(*pTimeTValue));
	}
	else
	{
		pStrValue = make_shared<string>(""); 
	}
}

void CValue::buildIntValue()
{ 
	if (valueType_str == dataType)
	{
		pIntValue = make_shared<int>(PubFun::stringToInt(*pStrValue));
	}
	else if (valueType_double == dataType)
	{
		pIntValue = make_shared<int>((int)(*pDoubleValue));
	}
	else if (valueType_timet == dataType)
	{
		pIntValue = make_shared<int>((int)(*pTimeTValue));
	}
	else
	{
		pIntValue = make_shared<int>(0);
	}
}

void CValue::buildTimeTValue()
{
	if (valueType_str == dataType)
	{
		pTimeTValue = make_shared<time_t>(PubFun::stringToTimet(*pStrValue));
	}
	else if (valueType_double == dataType)
	{
		pTimeTValue = make_shared<time_t>((time_t)(*pDoubleValue));
	}
	else if (valueType_int == dataType)
	{
		pTimeTValue = make_shared<time_t>(*pIntValue);
	}
	else
	{
		pIntValue = make_shared<int>(0);
	}
}

bool CValue::empty()
{
	return valueType_def == dataType;
}


