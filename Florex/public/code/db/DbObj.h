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

	PRow selectOneData(const char * sql, PTableStruct tableStruct);

	void selectData(const char * sql, PTable resTable);

	void executeSql(const char * sql);

	void insertDatas(list<string> sqls);

	void connectDefDb();

	void startTransaction();

	void commit();

	void initMySQL();

	void connectMySQL(char *host,unsigned int port,char * Db,char * user,char* passwd,char * charset,string &strMsg);

	void throwSqlError();

	void tryConnect();

	bool checkContect();
private:
	bool isMySqlInit;
	std::mutex dbMutex;
	MYSQL mysql;
};

