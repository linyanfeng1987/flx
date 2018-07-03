#pragma once
#include <map>
#include <list>
#include <string>

#include "TableStruct.h"
#include "Field.h"

using namespace std;

enum DBTYPE
{
	DBTYPE_NEW,
	DBTYPE_SAME,
	DBTYPE_CHANGE,
	DETYPE_DELETE,
};

class CRow : public map<string, string>
{
public:
	CRow(CTableStruct *pTableStruct);
	~CRow(void);

	void init(CTableStruct *pTableStruct);

	void setTableStruct(CTableStruct *pTableStruct){m_pTableStruct = pTableStruct;}
	CTableStruct* getTableStruct(){return m_pTableStruct;}

	string getSql();
	string getInsertSql();
	string getUpdateSql();
	string getDeleteSql();

	void setAndaddValue(string strKey, string strValue);
	void addByList(list<string> valueList);
	string getValue(string strKey);
	void setValue(string strKey, string strValue);

	DBTYPE m_dbType;

protected:
	string getBaseInsertSqlFormat();
	string getBaseUpdateSqlFormat();
	string getConditionFormat();

	CTableStruct *m_pTableStruct;
};

