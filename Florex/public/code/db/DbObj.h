#pragma once
#include "../table/Table.h"
#include <mutex>

#include "mysql.h"

using   namespace   std;
class CDbObj
{

protected:
	 CDbObj(void);

	 static CDbObj* g_db;

public:
	~CDbObj(void);
	
	static CDbObj& instance();

	PRow SelectOneData(const char * sql, PTableStruct tableStruct);

	void SelectData(const char * sql, PTable resTable);

	bool ExecuteSql(const char * sql);

	void insertDatas(list<string> sqls);

	void ConnectDb();

	void startTransaction();

	void commit();

	bool ConnMySQL(char *host,unsigned int port,char * Db,char * user,char* passwd,char * charset,string &strMsg);
private:
	bool isConnect;
	std::mutex dbMutex;
	MYSQL mysql;
};

