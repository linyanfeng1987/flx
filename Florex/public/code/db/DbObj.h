#pragma once
#include "VspdCToMySQL.h"
#include "../table/Table.h"

class CDbObj
{

protected:
	 CDbObj(void);

	 static CDbObj* g_db;
public:
	~CDbObj(void);
	
	static CDbObj& instance();

	void SelectData(const char * SQL,CTable& table);

	bool ExecuteSql(const char * SQL);

	void insertDatas(list<string> sqls);

	void ConnectDb();

private:
	bool isConnect;
	VspdCToMySQL db;
};

