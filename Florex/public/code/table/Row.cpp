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
	string strBaseSqlFormat = tableStruct->getBaseInsertSqlFormat();
	char chSql[2048] = {0};
	string strTmp = "";
	string strValue = "";
	for(auto field : *tableStruct){
		strValue = getStringValue(field.first);
		if (!strTmp.empty())
		{
			strTmp += ",";
		}
		strTmp +="'" + strValue + "'";	
	}

	memset(chSql, 0, sizeof(chSql));
	sprintf_s(chSql, strBaseSqlFormat.c_str(), strTmp.c_str());

	return string(chSql);
}



std::string CRow::getUpdateSql()
{
	string strBaseSqlFormat = tableStruct->getBaseUpdateSqlFormat();

	char chSql[2048] = {0};
	string strTmp = "";
	strTmp.clear();
	string strValue;
	for(auto field : *tableStruct){
		strValue = getStringValue(field.first);
		if (!strTmp.empty())
		{
			strTmp += ",";
			strTmp += " ";
		}
		strTmp += field.first + "='" + strValue + "'";
	}
	string strCondition = getCondition();
	memset(chSql, 0, sizeof(chSql));
	sprintf_s(chSql, strBaseSqlFormat.c_str(), strTmp.c_str(), strCondition.c_str());

	return string(chSql);
}

std::string CRow::getDeleteSql()
{
	string strSql = "delete from ";
	strSql += tableStruct->tableName;
	string strCondition = getCondition();
	strSql += strCondition;
	strSql += ";";
	return strSql;
}

// where a = A and b = B
std::string CRow::getCondition()
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
			strSql += "='";
			strSql += valueIter->second->getStrValue();
			strSql += "'";
		}
	}
	
	if (!strSql.empty())
	{
		strSql = " where " + strSql;
	}

	if (trim(strSql).empty())
	{
		//不允许不带条件删除，避免清空表
		throw CStrException("error condition");
	}

	return strSql;
}

void CRow::init( PTableStruct tableStruct )
{
	setTableStruct(tableStruct);
}

void CRow::setAndaddValue( string& strKey, string& strValue )
{
	if (tableStruct->find(strKey) != tableStruct->end())
	{
		CRow::iterator iter = this->find(strKey);
		if (iter != this->end())
		{
			iter->second->setValue(strValue);
		}
		else
		{
			std::pair<CRow::iterator, bool> pr = this->insert(make_pair(strKey, newValueP(strValue)));
			if (!pr.second)
			{
				throw CStrException("setAndaddValue error.");
			}
		}
	}
}

void CRow::addByList( list<string> valueList )
{
	if (valueList.size() != tableStruct->size())
	{
		throw CStrException("addByList error.");
	}
	list<string>::iterator valueIter= valueList.begin();
	for (auto fieldPair : *tableStruct)
	{
		setAndaddValue(fieldPair.first, *valueIter);
		valueIter++;
	}
}

std::string CRow::getValue( string& strKey )
{
	PValue destValue = nullptr;
	CRow::iterator iter = this->find(strKey);
	if (iter != this->end())
	{
		destValue = iter->second;
	}
	else
	{
		destValue = newValue();
	}
	return destValue->getStrValue();
}

void CRow::setValue( string& strKey, string& strValue )
{
	auto iter = this->find(strKey);
	if(iter != this->end())
	{
		iter->second->setValue(strValue);
	}
	else
	{
		this->insert(make_pair(strKey, newValueP(strValue)));
	}

	setDataStatus(m_dataStatus == DATA_SAME ? DATA_CHANGE : m_dataStatus);
}

void CRow::setValue( string& strKey, double dValue )
{
	auto iter = this->find(strKey);
	if(iter != this->end())
	{
		iter->second->setValue(dValue);
	}
	else
	{
		this->insert(make_pair(strKey, newValueP(dValue)));
	}

	setDataStatus(m_dataStatus == DATA_SAME ? DATA_CHANGE : m_dataStatus);
}


std::string CRow::getStringValue(string& strKey)
{
	return  emptyFind(strKey)->getStrValue();
}

long CRow::getIntValue(string& strKey)
{
	return emptyFind(strKey)->getIntValue();
}

time_t CRow::getTimeValue(string& strKey)
{
	return emptyFind(strKey)->getSizeTValue();
}

double CRow::getDoubleValue(string& strKey)
{
	return emptyFind(strKey)->getDoubleValue();
}

void CRow::setStringValue(string& strKey, string& strValue )
{
	this->setValue(strKey, strValue);
}

void CRow::setIntValue(string& strKey, long lValue )
{
	this->setValue(strKey, lValue);
}

void CRow::setIndexValue( string& strKey, indexType iValue )
{
	this->setValue(strKey, PubFun::indexToString(iValue));
}

void CRow::setTimeValue(string& strKey, time_t tValue )
{
	this->setValue(strKey, (double)tValue);
}

void CRow::setDoubleValue(string& strKey, double dValue )
{
	this->setValue(strKey, dValue);
}

bool CRow::save()
{
	string strSql = getSql();
	CDbObj::instance().executeSql(strSql.c_str());
	setDataStatus(DATA_SAME);
	return true;
}

void CRow::setDataStatus( DATA_STATUS status )
{
	m_dataStatus = status;
}

PValue CRow::emptyFind( string key )
{
	auto iter = find(key);
	if (this->end() != iter)
	{
		return iter->second;
	}
	else
	{
		return newValue();
	}	 
}


