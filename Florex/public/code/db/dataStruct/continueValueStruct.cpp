#include "continueValueStruct.h"
#include "PubFun.h"
#include "ConstDef.h"

string CContinueValueStruct::tagId = "tagId";

string CContinueValueStruct::direct = "direct";
string CContinueValueStruct::groupId = "groupId";

string CContinueValueStruct::startValue = "startValue";
string CContinueValueStruct::startTime = "startTime";
string CContinueValueStruct::startTimeDesc = "startTimeDesc";

string CContinueValueStruct::stopValue = "stopValue";
string CContinueValueStruct::stopTime = "stopTime";
string CContinueValueStruct::stopTimeDesc = "stopTimeDesc";

string CContinueValueStruct::endValue = "endValue";
string CContinueValueStruct::stepValue = "stepValue";
string CContinueValueStruct::stepTime = "stepTime";

string CContinueValueStruct::startLevel = "startLevel";
string CContinueValueStruct::maxLevel = "maxLevel";
string CContinueValueStruct::stopLevel = "stopLevel";

string CContinueValueStruct::levels = "levels";

string CContinueValueStruct::curRetrcementValue = "curRetrcementValue";
string CContinueValueStruct::retrcementValue = "retrcementValue";
string CContinueValueStruct::judgeRetrcementValue = "judgeRetrcementValue";

CContinueValueStruct::CContinueValueStruct(string rateName)
{
	string tableName = PubFun::strFormat("%s.%s_continueValue", calcDbName.c_str(), rateName.c_str());
	setName(tableName);
	init();
}

CContinueValueStruct::~CContinueValueStruct()
{
}

void CContinueValueStruct::init()
{
	CField field;

	field.load(tagId, typeIndex, false, true);
	this->insert(make_pair(field.strName, field));

	field.load(direct, typeInt, true);
	this->insert(make_pair(field.strName, field));

	field.load(groupId, typeInt, true);
	this->insert(make_pair(field.strName, field));

	field.load(startTime, typeDouble, true);
	this->insert(make_pair(field.strName, field));
	field.load(startTimeDesc, typeString);
	this->insert(make_pair(field.strName, field));
	field.load(startValue, typeDouble);
	this->insert(make_pair(field.strName, field));

	field.load(stopTime, typeDouble);
	this->insert(make_pair(field.strName, field));
	field.load(stopTimeDesc, typeString);
	this->insert(make_pair(field.strName, field));
	field.load(stopValue, typeDouble);
	this->insert(make_pair(field.strName, field));

	field.load(endValue, typeDouble);
	this->insert(make_pair(field.strName, field));
	field.load(stepValue, typeDouble);
	this->insert(make_pair(field.strName, field));
	field.load(stepTime, typeDouble);
	this->insert(make_pair(field.strName, field));

	field.load(curRetrcementValue, typeDouble);
	this->insert(make_pair(field.strName, field));
	field.load(retrcementValue, typeDouble);
	this->insert(make_pair(field.strName, field));
	field.load(judgeRetrcementValue, typeDouble);
	this->insert(make_pair(field.strName, field));

	field.load(startLevel, typeInt);
	this->insert(make_pair(field.strName, field));
	field.load(maxLevel, typeInt);
	this->insert(make_pair(field.strName, field));
	field.load(stopLevel, typeInt);
	this->insert(make_pair(field.strName, field));
	field.load(levels, typeString2);
	this->insert(make_pair(field.strName, field));

	ensureExist();
}