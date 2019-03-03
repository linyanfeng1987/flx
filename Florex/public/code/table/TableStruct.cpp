#include "TableStruct.h"
#include "PubFun.h"
#include <regex>

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

std::string CTableStruct::getCreateTableSql()
{
	string fields = "";
	string pkFields = "";
	for(auto field : *this){
		string strField = PubFun::strFormat("`%s`", field.first.c_str());
		if(field.second.bIsPk){
			if (!pkFields.empty())
			{
				pkFields.append(",");
			}
			pkFields.append(strField);
		}

		string fieldType = "";
		if(typeInt == field.second.strType){
			fieldType = "int";
		}else if(typeDouble == field.second.strType){
			fieldType = "double";
		}else if(typeString == field.second.strType){
			fieldType = "CHAR(45)";
		}else if(typeString2 == field.second.strType){
			fieldType = "VARCHAR(4096)";
		}
		string fieldDefSql = PubFun::strFormat("%s %s NOT NULL", strField.c_str(), fieldType.c_str());
		if(!fields.empty())
		{
			fields.append(",\n");
		}
		fields.append(fieldDefSql);
	}
	string pkSql = "";
	if (!pkFields.empty())
	{
		pkSql = PubFun::strFormat(",\nPRIMARY KEY (%s)", pkFields.c_str());
	}

	string strSql = PubFun::strFormat("create table %s \n(%s%s);", tableName.c_str(), fields.c_str(), pkSql.c_str());

	return strSql;
}

std::string CTableStruct::getDeleteTableSql()
{
	return "";
}

void CTableStruct::setName( string strName )
{
	tableName = strName;
}

std::string CTableStruct::getSelectSql( string conditicon )
{
	string strSql = PubFun::strFormat("select %s from %s", getFieldsStr().c_str(), tableName.c_str());
	if(!conditicon.empty())
	{
		strSql.append(" where ");
		strSql.append(conditicon);
	}
	strSql.append(";");
	return strSql;
}

std::string CTableStruct::getBaseInsertSqlFormat()
{
	if (strInsertSqlFormat.empty())
	{
		strInsertSqlFormat = "insert into ";
		strInsertSqlFormat += tableName;
		strInsertSqlFormat += " (";
		strInsertSqlFormat += getFieldsStr();
		strInsertSqlFormat += ") value ( %s );";
	}

	return strInsertSqlFormat;
}

//UPDATE tbl_name SET col_name1=value1, col_name2=value2, … WHERE conditions
std::string CTableStruct::getBaseUpdateSqlFormat()
{
	if(strUpdateSqlFormat.empty())
	{
		strUpdateSqlFormat = "update " + tableName + " set %s %s;";
	}

	return strUpdateSqlFormat;
}

std::string CTableStruct::getFieldsStr( string split /*= ","*/ )
{
	string fields = "";
	for(auto field : *this){
		if (!fields.empty())
		{
			fields.append(split);
		}
		fields.append(field.first);
	}
	return fields;
}

bool CTableStruct::tableExist()
{
	string strSql = PubFun::strFormat("select * from %s limit 1;", tableName.c_str());
	CDbObj& dbObj = CDbObj::instance();
	try
	{
		dbObj.executeSql(strSql.c_str());
	}
	catch (CStrException& e)
	{
		// 这里要处理表不存在的情况
		string msg = e.what();
		regex reg1("Table '[\\w\\.]+' doesn't exist");
		smatch r1;
		if(regex_match(msg, r1, reg1))
		{
			return false;
		}
	}
	
	return true;
}

void CTableStruct::ensureExist()
{
	if (!tableExist())
	{
		string createTableSql = this->getCreateTableSql();
		CDbObj::instance().executeSql(createTableSql.c_str());
	}
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
// //UPDATE tbl_name SET col_name1=value1, col_name2=value2, … WHERE conditions
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
