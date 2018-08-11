#include "Row.h"
#include "Exception.h"
#include "PubFun.h"
#include "db/DbObj.h"

std::string trim(std::string s) 
{
	if (s.empty()) 
	{
		return s;
	}

	s.erase(0,s.find_first_not_of(" "));
	s.erase(s.find_last_not_of(" ") + 1);
	return s;
}

CRow::CRow(PTableStruct tableStruct)
{
	setDataStatus(DATA_NEW);
	init(tableStruct);
}

CRow::~CRow(void)
{
}

std::string CRow::getSql()
{
	string strSql = "";
	switch (m_dataStatus)
	{
	case DATA_NEW:
		{
			strSql = getInsertSql();
		}
		
		break;
	case DATA_SAME:
		{
			strSql = "";
		}
		break;
	case DATA_CHANGE:
		{
			strSql = getUpdateSql();
		}
		break;
	case DATA_DELETE:
		{
			strSql = getDeleteSql();
		}
		break;
	default:
		{
			strSql = "";
		}
		break;
	}

	return strSql;
}

std::string CRow::getInsertSql()
{
	static string strBaseSqlFormat = "";
	if(strBaseSqlFormat.empty())
	{
		strBaseSqlFormat = getBaseInsertSqlFormat();
	}

	char chSql[2048] = {0};
	string strTmp = "";
	CRow::iterator rowIter;
	strTmp.clear();
	rowIter = this->begin();
	for (; rowIter != this->end(); rowIter++)
	{
		if (!strTmp.empty())
		{
			strTmp += ",";
			strTmp += " ";
		}
		strTmp += rowIter->second;	
	}
	memset(chSql, 0, sizeof(chSql));
	sprintf_s(chSql, strBaseSqlFormat.c_str(), strTmp.c_str());

	return string(chSql);
}

std::string CRow::getBaseInsertSqlFormat()
{
	string strBaseSqlFormat = "";
	strBaseSqlFormat += "insert into ";
	strBaseSqlFormat += tableStruct->tableName;
	strBaseSqlFormat += " (";
	auto fieldIter = tableStruct->begin();
	string strTmp = "";
	for(unsigned int i = 0;i < tableStruct->size();i++, fieldIter++)
	{
		if (!strTmp.empty())
		{
			strTmp += ",";
			strTmp += " ";
		}
		strTmp += fieldIter->first;
	}
	strBaseSqlFormat += strTmp;
	strBaseSqlFormat += ")";
	strBaseSqlFormat += " value";
	strBaseSqlFormat += " ( ";
	strBaseSqlFormat += "%s";
	strBaseSqlFormat += " )";
	strBaseSqlFormat += ";";

	return strBaseSqlFormat;
}

std::string CRow::getUpdateSql()
{
	static string strBaseSqlFormat = "";
	if(strBaseSqlFormat.empty())
	{
		strBaseSqlFormat = getBaseUpdateSqlFormat();
	}

	char chSql[2048] = {0};
	string strTmp = "";
	CRow::iterator rowIter;
	strTmp.clear();
	rowIter = this->begin();
	for (; rowIter != this->end(); rowIter++)
	{
		if (!strTmp.empty())
		{
			strTmp += ",";
			strTmp += " ";
		}
		strTmp += rowIter->first;
		strTmp += "=";
		strTmp += rowIter->second;
	}
	memset(chSql, 0, sizeof(chSql));
	sprintf_s(chSql, strBaseSqlFormat.c_str(), strTmp.c_str());

	return string(chSql);
}

//UPDATE tbl_name SET col_name1=value1, col_name2=value2, … WHERE conditions
std::string CRow::getBaseUpdateSqlFormat()
{
	string strBaseSqlFormat = "";
	strBaseSqlFormat += "update ";
	strBaseSqlFormat += tableStruct->tableName;
	strBaseSqlFormat += " set ";
	strBaseSqlFormat += "%s";
	strBaseSqlFormat += getConditionFormat();
	strBaseSqlFormat += ";";

	return strBaseSqlFormat;
}

std::string CRow::getDeleteSql()
{
	string strSql = "delete from ";
	strSql += tableStruct->tableName;
	string strCondition = getConditionFormat();
	if (trim(strCondition).empty())
	{
		//不允许不带条件删除，避免清空表
		throw Exception("error condition");
	}
	strSql += strCondition;
	strSql += ";";
	return strSql;
}

// where a = A and b = B
std::string CRow::getConditionFormat()
{
	string strSql = "";
	for (auto fieldPair : *tableStruct)
	{
		if (fieldPair.second.bIsPk)
		{
			auto valueIter = find(fieldPair.first);
			if (!strSql.empty())
			{
				strSql += " and ";
			}

			strSql += valueIter->first;
			strSql += "=";
			strSql += valueIter->second;
		}
	}
	
	if (!strSql.empty())
	{
		strSql = " where " + strSql;
	}

	return strSql;
}

void CRow::init( PTableStruct tableStruct )
{
	setTableStruct(tableStruct);
}

void CRow::setAndaddValue( string strKey, string strValue )
{
	if (tableStruct->find(strKey) != tableStruct->end())
	{
		CRow::iterator iter = this->find(strKey);
		if (iter != this->end())
		{
			iter->second = strValue;
		}
		else
		{
			std::pair<CRow::iterator, bool> pr = this->insert(make_pair(strKey,strValue));
			if (!pr.second)
			{
				throw Exception("setAndaddValue error.");
			}
		}
	}
}

void CRow::addByList( list<string> valueList )
{
	if (valueList.size() != tableStruct->size())
	{
		throw Exception("addByList error.");
	}
	list<string>::iterator valueIter= valueList.begin();
	for (auto fieldPair : *tableStruct)
	{
		setAndaddValue(fieldPair.first, *valueIter);
		valueIter++;
	}
}

std::string CRow::getValue( string strKey )
{
	string destValue = "";
	if (tableStruct->find(strKey) != tableStruct->end())
	{
		CRow::iterator iter = this->find(strKey);
		if (iter != this->end())
		{
			destValue = iter->second;
		}
		else
		{
			destValue = "";
		}
	}
	return destValue;
}

void CRow::setValue( string strKey, string strValue )
{
	auto iter = this->find(strKey);
	if(iter != this->end())
	{
		iter->second = strValue;
	}
	else
	{
		this->insert(make_pair(strKey, strValue));
	}

	setDataStatus(m_dataStatus == DATA_SAME ? DATA_CHANGE : m_dataStatus);
}


std::string CRow::getStringValue(string strKey)
{
	return this->getValue(strKey);
}

long CRow::getIntValue(string strKey)
{
	return PubFun::stringToInt(this->getValue(strKey));
}

time_t CRow::getTimeValue(string strKey)
{
	return PubFun::stringToInt(this->getValue(strKey));
}

double CRow::getDoubleValue(string strKey)
{
	return PubFun::stringToDouble(this->getValue(strKey));
}

void CRow::setStringValue(string strKey, string strValue )
{
	this->setValue(strKey, strValue);
}

void CRow::setIntValue(string strKey, long lValue )
{
	this->setValue(strKey, PubFun::intToString(lValue));
}

void CRow::setTimeValue(string strKey, time_t tValue )
{
	this->setValue(strKey, PubFun::intToString((long)tValue));
}

void CRow::setDoubleValue(string strKey, double dValue )
{
	this->setValue(strKey, PubFun::doubleToString(dValue));
}


bool CRow::save()
{
	string strSql = getSql();
	CDbObj::instance().ExecuteSql(strSql.c_str());
	setDataStatus(DATA_SAME);
	return true;
}

void CRow::setDataStatus( DATA_STATUS status )
{
	m_dataStatus = status;
}

