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

CRow::CRow(PTableStruct tableStruct):log(CLogObj::instance())
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
	string strTmp = "";
	string strValue = "";
	for(auto field : *tableStruct){
		strValue = getStringValue(field.first);
		if (!strTmp.empty())
		{
			strTmp += ",";
		}
		//strTmp +="'" + strValue + "'";	
		if (typeCount == field.second.strType)
		{
			strTmp.append("0");
		}
		else
		{
			strTmp.append(PubFun::strFormat("'%s'", strValue.c_str()));
		}
	}

	string strSql = PubFun::strFormat(strBaseSqlFormat.c_str(), strTmp.c_str());

	return strSql;
}



std::string CRow::getUpdateSql()
{
	string strBaseSqlFormat = tableStruct->getBaseUpdateSqlFormat();

	string strTmp = "";
	strTmp.clear();
	string strValue;
	for(auto field : *tableStruct){
		auto valueIter = find(field.first);
		if (end() != valueIter && !valueIter->second->isDataSame())
		{
			strValue = valueIter->second->getStrValue();
			if (!strTmp.empty())
			{
				strTmp.append(", ");
			}
			//strTmp += field.first + "='" + strValue + "'";
			if (typeCount == field.second.strType)
			{
				strTmp.append(PubFun::strFormat("%s=%s+1",field.first.c_str(), field.first.c_str()));
			}
			else
			{
				strTmp.append(PubFun::strFormat("%s='%s'",field.first.c_str(), strValue.c_str()));
			}
		}
	}
	string strSql = "";
	if (!strTmp.empty())
	{
		string strCondition = getCondition();
		strSql = PubFun::strFormat(strBaseSqlFormat.c_str(), strTmp.c_str(), strCondition.c_str());
	}
	
	return strSql;
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

void CRow::setValue( string& strKey, int& nValue )
{
	auto iter = this->find(strKey);
	if(iter != this->end())
	{
		iter->second->setValue(nValue);
	}
	else
	{
		this->insert(make_pair(strKey, newValueP(nValue)));
	}

	setDataStatus(m_dataStatus == DATA_SAME ? DATA_CHANGE : m_dataStatus);
}

void CRow::setValue( string& strKey, time_t tValue )
{
	auto iter = this->find(strKey);
	if(iter != this->end())
	{
		iter->second->setValue(tValue);
	}
	else
	{
		this->insert(make_pair(strKey, newValueP(tValue)));
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
	return emptyFind(strKey)->getTimeTValue();
}

double CRow::getDoubleValue(string& strKey)
{
	return emptyFind(strKey)->getDoubleValue();
}

void CRow::setStringValue(string& strKey, string& strValue )
{
	this->setValue(strKey, strValue);
}

void CRow::setIntValue(string& strKey, int nValue )
{
	this->setValue(strKey, nValue);
}

void CRow::setIndexValue( string& strKey, indexType iValue )
{
	this->setValue(strKey, PubFun::indexToString(iValue));
}

void CRow::setTimeValue(string& strKey, time_t tValue )
{
	this->setValue(strKey, tValue);
}

void CRow::setDoubleValue(string& strKey, double dValue )
{
	this->setValue(strKey, dValue);
}

bool CRow::isExit()
{
	bool bIsExit = false;
	string strValue = "";
	string conditicon = "";
	for(auto field : *tableStruct){
		if (field.second.bIsPk)
		{
			strValue = getStringValue(field.first);
			if (!conditicon.empty())
			{
				conditicon += "and ";
			}
			//conditicon +="'" + strValue + "'";	
			conditicon.append(PubFun::strFormat("%s='%s'",field.first.c_str(), strValue.c_str()));
		}
	}

	string strSql = tableStruct->getSelectSql(conditicon);
	CDbObj& dbObj = CDbObj::instance();
	try
	{
		PRow row = dbObj.selectOneData(strSql.c_str(), tableStruct);
		if (nullptr != row)
		{
			bIsExit = true;
		}
	}
	catch (CStrException& e)
	{
		log.error(string(e.what()));
	}
	return bIsExit;
}

bool CRow::save()
{
	string strSql = getSql();
	if (!strSql.empty())
	{
		try
		{
			CDbObj::instance().executeSql(strSql.c_str());
			setDataStatus(DATA_SAME);
		}
		catch (CStrException &e)
		{
			log.error(string(e.what()));
		}
	}

	return true;
}

bool CRow::save2()
{
	string strSql = getSql();
	if (!strSql.empty())
	{
		try
		{
			CDbObj::instance().executeSql(strSql.c_str());
			setDataStatus(DATA_SAME);
		}
		catch (CStrException &e)
		{
			string strMsg = e.what();
			if (-1 == strMsg.find("for key 'PRIMARY'"))
			{
				log.info(PubFun::strFormat("插入失败，使用修改方式,sql:%s",strSql.c_str()));
				setDataStatus(DATA_CHANGE);
				save();
			}
		}
	}

	return true;
}

void CRow::setDataStatus( DATA_STATUS status )
{
	if (DATA_SAME ==  status)
	{
		for (auto valuePair : *this)
		{
			valuePair.second->setSame();
		}
	}
	
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



