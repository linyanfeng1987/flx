#include "TableStruct.h"


CTableStruct::CTableStruct(string strName)
{
	setName(strName);
}

CTableStruct::CTableStruct()
{

}


CTableStruct::~CTableStruct(void)
{
}

std::string CTableStruct::getCreateSql()
{
	return "";
}

std::string CTableStruct::getDeleteSql()
{
	return "";
}

void CTableStruct::setName( string strName )
{
	tableName = strName;
}

// 
// std::string CTableStruct::getInsertSql()
// {
// 	static string strBaseSqlFormat = "";
// 	if(strBaseSqlFormat.empty())
// 	{
// 		strBaseSqlFormat = getBaseInsertSqlFormat();
// 	}
// 
// 	char chSql[2048] = {0};
// 	string strTmp = "";
// 	CTableStruct::iterator rowIter;
// 	strTmp.clear();
// 	rowIter = this->begin();
// 	for (; rowIter != this->end(); rowIter++)
// 	{
// 		strTmp += " ";
// 		strTmp += rowIter->second;
// 		strTmp += ",";
// 	}
// 	strTmp = strTmp.substr(0, strTmp.length()-2);
// 	memset(chSql, 0, sizeof(chSql));
// 	sprintf_s(chSql, strBaseSqlFormat.c_str(), strTmp);
// 
// 	return string(chSql);
// }
// 
// std::string CTableStruct::getInsertSqlFormat()
// {
// 	string strBaseSqlFormat = "";
// 	strBaseSqlFormat += "insert into ";
// 	strBaseSqlFormat += tableName;
// 	strBaseSqlFormat += " (";
// 	CTableStruct::iterator fieldIter = this->begin();
// 	for(int i = 0;i < m_pField->size();i++, fieldIter++)
// 	{
// 		strBaseSqlFormat += " ";
// 		strBaseSqlFormat += fieldIter->first;
// 		strBaseSqlFormat += ",";
// 	}
// 	strBaseSqlFormat = strBaseSqlFormat.substr(0, strBaseSqlFormat.length()-2);
// 	strBaseSqlFormat += ")";
// 	strBaseSqlFormat += " value";
// 	strBaseSqlFormat += " ( ";
// 	strBaseSqlFormat += "%s";
// 	strBaseSqlFormat += " )";
// 	strBaseSqlFormat += ";";
// 
// 	return strBaseSqlFormat;
// }
// 
// std::string CTableStruct::getUpdateSql()
// {
// 	static string strBaseSqlFormat = "";
// 	if(strBaseSqlFormat.empty())
// 	{
// 		strBaseSqlFormat = getBaseUpdateSqlFormat();
// 	}
// 
// 	char chSql[2048] = {0};
// 	string strTmp = "";
// 	CTableStruct::iterator rowIter;
// 	strTmp.clear();
// 	rowIter = this->begin();
// 	for (; rowIter != this->end(); rowIter++)
// 	{
// 		strTmp += " ";
// 		strTmp += rowIter->first;
// 		strTmp += "=";
// 		strTmp += rowIter->second;
// 		strTmp += ",";
// 	}
// 	strTmp = strTmp.substr(0, strTmp.length()-2);
// 	memset(chSql, 0, sizeof(chSql));
// 	sprintf_s(chSql, strBaseSqlFormat.c_str(), strTmp);
// 
// 	return string(chSql);
// }
// 
// //UPDATE tbl_name SET col_name1=value1, col_name2=value2, бн WHERE conditions
// std::string CTableStruct::getUpdateSqlFormat()
// {
// 	string strBaseSqlFormat = "";
// 	strBaseSqlFormat += "update ";
// 	strBaseSqlFormat += tableName;
// 	strBaseSqlFormat += " set";
// 	strBaseSqlFormat += "%s";
// 	strBaseSqlFormat = strBaseSqlFormat.substr(0, strBaseSqlFormat.length()-2);
// 	strBaseSqlFormat += " ";
// 	strBaseSqlFormat += getCondition();
// 
// 	return strBaseSqlFormat;
// }
// 
// std::string CTableStruct::getDeleteSql()
// {
// 	string strSql = "delete from ";
// 	strSql += *m_pTableName;
// 	strSql += " ";
// 	strSql += getCondition();
// 	return strSql;
// }
// 
// // where a = A and b = B
// std::string CTableStruct::getCondition()
// {
// 	string strSql = "";
// 	KeyList keyFiled = m_pField->getKeyField();
// 	KeyList::iterator iter = keyFiled.begin();
// 	if (iter != keyFiled.end())
// 	{
// 		while (true)
// 		{
// 			strSql += *iter;
// 			strSql += "=";
// 			strSql += "%s";
// 			iter++;
// 			if(iter == keyFiled.end())
// 			{
// 				break;
// 			}
// 			strSql += " and ";
// 		}
// 	}
// 
// 	if (!strSql.empty())
// 	{
// 		strSql = "where " + strSql;
// 	}
// 
// 	return "";
// }
// 
// void CTableStruct::init( CField *pField )
// {
// 	setField(pField);
// }
// 
// bool CTableStruct::setAndaddValue( string strKey, string strValue )
// {
// 	if (m_pField->find(strKey) != m_pField->end())
// 	{
// 		CTableStruct::iterator iter = this->find(strKey);
// 		if (iter != this->end())
// 		{
// 			iter->second = strValue;
// 		}
// 		else
// 		{
// 			std::pair<CTableStruct::iterator, bool> p = this->insert(make_pair(strKey,strValue));
// 			if (!p.second)
// 			{
// 				throw Exception("setAndaddValue error.");
// 			}
// 		}
// 	}
// }
// 
// void CTableStruct::addByList( list<string> valueList )
// {
// 	list<string>::iterator iter= valueList.begin();
// 	for (; iter != valueList.end();iter++)
// 	{
// 
// 	}
// }
