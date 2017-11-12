#pragma once
#include <list>
#include "Field.h"

class KeyList: public list<string>
{
public:

};


class CTableStruct: public map<string, CField>
{
public:
	CTableStruct(string strName);
	~CTableStruct();

	string getCreateSql();
	string getDeleteSql();

// 	string getSql();
// 	string getInsertSql();
// 	string getUpdateSql();
// 	string getDeleteSql();
// 
// 	string getInsertSqlFormat();
// 	string getUpdateSqlFormat();
// 	string getCondition();

	string tableName;

	//KeyList& getKeyFields(){return m_keyFiled;}
	
	//void setKeyField(KeyList tmpList){std::copy(tmpList.begin(), tmpList.end(), std::back_inserter(m_keyFiled)); }

protected:
	//KeyList m_keyFiled;
};