#include "calcRateStruct.h"
#include "PubFun.h"
#include "ConstDef.h"

string CCalcRateStruct::curValue = "curValue"; 
string CCalcRateStruct::curTime = "curTime"; 
string CCalcRateStruct::timeFormat = "timeFormat"; 

CCalcRateStruct::CCalcRateStruct(string _rateName,string _timeName, string _typeName) 
{
	rateName = _rateName;
	timeName = _timeName;
	typeName = _typeName;
	buildTableName();	
	init();
}

CCalcRateStruct::CCalcRateStruct()
{
	addField();
}


CCalcRateStruct::~CCalcRateStruct()
{
	
}

void CCalcRateStruct::init()
{
	addField();
	this->ensureExist();
}

void CCalcRateStruct::addField()
{
	CField field;

	field.load(curTime, typeDouble, true);
	this->insert(make_pair(field.strName, field));

	field.load(curValue, typeDouble);
	this->insert(make_pair(field.strName, field));

	field.load(timeFormat, typeString);
	this->insert(make_pair(field.strName, field));
}


void CCalcRateStruct::buildTableName()
{
	string str;
	if (!typeName.empty()&&!timeName.empty() )
	{
		str = PubFun::strFormat("%s.currency_pair_%s_%s%s", calcDbName.c_str(), rateName.c_str(), typeName.c_str(), timeName.c_str());
	}
	else
	{
		str = PubFun::strFormat("%s.currency_pair_%s", calcDbName.c_str(), rateName.c_str());
	}
	
	this->setName(str);
}

PCalcRateStruct CCalcRateStruct::instence()
{
	static PCalcRateStruct p = make_shared<CCalcRateStruct>();
	return p;
}

std::string CCalcRateStruct::getLastRecordSql()
{
	string order = PubFun::strFormat("order by %s desc", curTime.c_str());
	return getSelectSqlLimit1(string(""), order);
}

double CCalcRateStruct::getLastRecordTime( PCalcRateStruct calcRateStruct )
{
	double lastTime = -1;
	try
	{
		CDbObj &dbObj = CDbObj::instance();
		string sql = calcRateStruct->getLastRecordSql();
		PRow row = dbObj.selectOneData(sql.c_str(), calcRateStruct);
		if (nullptr != row)
		{
			lastTime = row->getDoubleValue(CCalcRateStruct::curTime);
		}
	}
	catch (CStrException &e)
	{
		e.what();
	}

	return lastTime;
}

