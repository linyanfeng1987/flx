#pragma once
#include <map>
#include <list>
#include <string>

#include "TableStruct.h"
#include "Field.h"

using namespace std;

enum DATA_STATUS
{
	DATA_NEW,
	DATA_SAME,
	DATA_CHANGE,
	DATA_DELETE,
};

class CRow : public map<string, string>
{
public:
	// 可以进行sql交互的
	CRow(CTableStruct *pTableStruct);
	~CRow(void);

	void init(CTableStruct *pTableStruct);

	void setTableStruct(CTableStruct *pTableStruct){m_pTableStruct = pTableStruct;}
	CTableStruct* getTableStruct(){return m_pTableStruct;}

	bool save();

	void setDataStatus(DATA_STATUS status);

	string getSql();
	string getInsertSql();
	string getUpdateSql();
	string getDeleteSql();

	void setAndaddValue(string strKey, string strValue);
	void addByList(list<string> valueList);
	string getValue(string strKey);
	void setValue(string strKey, string strValue);


	string getStringValue(string strKey);
	long getIntValue(string strKey);
	time_t getTimeValue(string strKey);
	double getDoubleValue(string strKey);


	void setStringValue(string strKey, string strValue);
	void setIntValue(string strKey, long lValue);
	void setTimeValue(string strKey, time_t tValue);
	void setDoubleValue(string strKey, double dValue);


	DATA_STATUS m_dataStatus;

protected:
	string getBaseInsertSqlFormat();
	string getBaseUpdateSqlFormat();
	string getConditionFormat();

	CTableStruct *m_pTableStruct;
};

