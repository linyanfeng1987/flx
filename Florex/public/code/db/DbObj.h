#pragma once
#include "../table/Table.h"
#include "LogObj.h"
#include "Exception.h"
#include <mutex>
#include "mysql.h"

using namespace   std;
class CDbObj
{

protected:
	 CDbObj(void);

	 static CDbObj* g_db;
	 static map<size_t,CDbObj*>* pDbMap;
public:
	~CDbObj(void);
	
	static CDbObj& instance();
	static void release();

	PRow selectOneData(const char * sql, PTableStruct tableStruct);

	void selectData(const char * sql, PTable resTable);

	void executeSql(const char * sql);

	void insertDatas(list<string> sqls);
	void insertData(string sql);

	void initMySQL();
	
protected:
	void baseInsert(string sql);
	void tryConnect();
	void connectDefDb();
	void connectMySQL(char *host,unsigned int port,char * Db,char * user,char* passwd,char * charset,string &strMsg);

	void baseExecuteSql(const char * sql);

	void startTransaction();
	void commit();
	
	void throwSqlError(string sql="");

	bool isMySqlInit;
	MYSQL mysql;
	CLogObj& log;

	PLogInfo testLogInfo;
	PLogInfo dbLogInfo;

	const static string logTag;

	//static recursive_mutex dbMutex;
};
