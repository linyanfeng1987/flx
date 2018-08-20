#include "../PubFun.h"
#include "Exception.h"
#include "DbObj.h"
#include "AutoMutex.h"
#pragma comment(lib, "libmysql.lib")  

CDbObj* CDbObj::g_db = nullptr;

CDbObj::CDbObj(void)
{
	isMySqlInit = false;
}


CDbObj::~CDbObj(void)
{
	CAutoMutex localMutex(&dbMutex);
	mysql_close(&mysql);
}

void CDbObj::startTransaction()
{
	CAutoMutex localMutex(&dbMutex);
	mysql_query(&mysql,"START TRANSACTION"); // 开启事务， 如果没有开启事务，那么效率会变得非常低下！
}

void CDbObj::commit()
{
	CAutoMutex localMutex(&dbMutex);
	mysql_query(&mysql,"COMMIT"); // 提交事务 
}

PRow CDbObj::selectOneData( const char * sql, PTableStruct tableStruct )
{
	string strLog = "selectData:" + string(sql);
	PRow row = nullptr;
	PubFun::log(strLog);
	{
		tryConnect();
		CAutoMutex localMutex(&dbMutex);

		int nRes = mysql_query(&mysql,sql);
		string strMsg = "";
		if(0 == nRes)
		{
			MYSQL_ROW pRow = nullptr;
			MYSQL_RES *pRes = nullptr;
			pRes = mysql_store_result(&mysql);
			if(pRes==nullptr)
			{
				strMsg = mysql_error(&mysql);
			}
			while(pRow = mysql_fetch_row(pRes))
			{
				row = newRow(tableStruct);
				char* pDataValue = *pRow;
				auto fieldIter = tableStruct->begin();
				while (tableStruct->end() != fieldIter)
				{
					row->setAndaddValue(fieldIter->first, pDataValue);
					pDataValue = *(++pRow);
					fieldIter++;
					break;
				}
				row->setDataStatus(DATA_SAME);
			}
			mysql_free_result(pRes);
		}
		else
		{
			throwSqlError();
		}
	}
	return row;
}

void CDbObj::selectData( const char * sql, PTable resTable)
{
	string strLog = "selectData:" + string(sql);
	PubFun::log(strLog);
	{
		tryConnect();
		CAutoMutex localMutex(&dbMutex);
		
		int nRes = mysql_query(&mysql,sql);
		string strMsg = "";
		if(0 == nRes)
		{
			MYSQL_ROW pRow = nullptr;
			MYSQL_RES *pRes = nullptr;
			pRes = mysql_store_result(&mysql);
			if(pRes==nullptr)
			{
				throwSqlError();
			}
			while(pRow = mysql_fetch_row(pRes))
			{
				PRow row = newRow(resTable->tableStruct);
				char* pDataValue = *pRow;
				auto fieldIter = resTable->tableStruct->begin();
				while (resTable->tableStruct->end() != fieldIter)
				{
					row->setAndaddValue(fieldIter->first, pDataValue);
					pDataValue = *(++pRow);
					fieldIter++;
				}
				row->setDataStatus(DATA_SAME);
				resTable->addRow(row);
			}
			mysql_free_result(pRes);
		}
		else
		{
			throwSqlError();
		}
	}
}

void CDbObj::executeSql( const char * sql )
{
	string strLog = "excecuteSql:";
	strLog += sql;
	PubFun::log(strLog);
	tryConnect();

	CAutoMutex localMutex(&dbMutex);
	if(mysql_query(&mysql,sql) != 0)
	{
		throwSqlError();
	}
}

void CDbObj::tryConnect()
{
	if (!isMySqlInit)
	{
		initMySQL();
	}

	if (!checkContect())
	{
		CAutoMutex localMutex(&dbMutex);
		connectDefDb();
	}
}

bool CDbObj::checkContect()
{
	CAutoMutex localMutex(&dbMutex);
	if (isMySqlInit)
	{
		// 0为链接正常
		if (0 == mysql_ping(&mysql))
		{
			return true;
		}
	}
	
	return false;
}


void CDbObj::connectDefDb()
{
	char* host="localhost";
	char* user="root";
	unsigned int port = 3306;
	char* passwd="101050";
	char* dbname=""; 
	char* charset = "GBK";//支持中文
	string strMsg = "";//消息变量
	char* Msg = "";

	connectMySQL(host,port,dbname,user,passwd,charset,strMsg);
	printf("连接成功\r\n");
}

void CDbObj::connectMySQL(char *host,unsigned int port ,char * Db,char * user,char* passwd,char * charset, string &strMsg)
{
	if ( nullptr == mysql_real_connect(&mysql,host,user,passwd,NULL,port,NULL,0))
	{
		throwSqlError();
	}   
}

void CDbObj::initMySQL()
{
	CAutoMutex localMutex(&dbMutex);
	bool bRes = false;
	int nRes =mysql_library_init(0, NULL, NULL);
	if (0 == nRes) {
		if( NULL != mysql_init(&mysql) )
		{
			connectDefDb();
			if(0 == mysql_set_character_set(&mysql,"GBK"))
			{
				bRes  = true;
				isMySqlInit = true;
			}
		}    
	}
	string strMsg = mysql_error(NULL);
	if (!bRes)
	{
		throwSqlError();
	}
}


CDbObj& CDbObj::instance()
{
	if(g_db == nullptr)
	{
		g_db = new CDbObj;
	}
	return *g_db;
}

void CDbObj::insertDatas( list<string> sqls )
{
	tryConnect();

	startTransaction();
	for (string sql : sqls)
	{
		executeSql(sql.c_str());;
	}
	commit();
}



void CDbObj::throwSqlError()
{
	string strMsg = mysql_error(&mysql);
	throw CStrException(strMsg);
}




