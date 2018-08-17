#include "../PubFun.h"
#include "DbObj.h"
#pragma comment(lib, "libmysql.lib")  

CDbObj* CDbObj::g_db = nullptr;

CDbObj::CDbObj(void)
{
	isConnect = false;
}


CDbObj::~CDbObj(void)
{
	if (isConnect)
	{
		mysql_close(&mysql);
	}
}

PRow CDbObj::SelectOneData( const char * sql, PTableStruct tableStruct )
{
	string strLog = "selectData:" + string(sql);
	PRow row = nullptr;
	PubFun::log(strLog);
	{
		dbMutex.lock();
		if (!isConnect)
		{
			ConnectDb();
		}

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
			strMsg = mysql_error(&mysql);
		}
		dbMutex.unlock();
	}
	return row;
}

void CDbObj::SelectData( const char * sql, PTable resTable)
{
	string strLog = "selectData:" + string(sql);
	PubFun::log(strLog);
	{
		dbMutex.lock();
		if (!isConnect)
		{
			ConnectDb();
		}
		
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
			strMsg = mysql_error(&mysql);
		}
		dbMutex.unlock();
	}
}

bool CDbObj::ExecuteSql( const char * sql )
{
	dbMutex.lock();
	string strLog = "excecuteSql:";
	strLog += sql;
	PubFun::log(strLog);
	if(!isConnect)
	{
		ConnectDb();
		isConnect = true;
	}

	bool bRes = true;
	if(mysql_query(&mysql,sql) != 0)
	{
		string error = mysql_error(&mysql);
		printf("errorMsg:%s\n", error.c_str());
		bRes =  false;
	}
	dbMutex.unlock();
	return bRes;
}

void CDbObj::ConnectDb()
{
	char* host="localhost";
	char* user="root";
	unsigned int port = 3366;
	char* passwd="101050";
	char* dbname=""; 
	char* charset = "GBK";//支持中文
	string strMsg = "";//消息变量
	char* Msg = "";

	if(ConnMySQL(host,port,dbname,user,passwd,charset,strMsg))
		printf("连接成功\r\n");
	else
		printf(Msg);

}

bool CDbObj::ConnMySQL(char *host,unsigned int port ,char * Db,char * user,char* passwd,char * charset, string &strMsg)
{
	bool bRes = false;

	int nRes =mysql_library_init(0, NULL, NULL);
	if (0 == nRes) {
		if( nullptr != mysql_init(&mysql) )
		{
			if ( nullptr != mysql_real_connect(&mysql,host,user,passwd,NULL,3306,NULL,0))
			{
				if(0 == mysql_set_character_set(&mysql,"GBK"))
				{
					bRes  = true;
				}
			}   
		}    
	}

	if (!bRes)
	{
		strMsg = mysql_error(NULL);
	}
	else
	{
		isConnect = true;
	}
	return bRes;
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
	dbMutex.lock();
	if(!isConnect)
	{
		ConnectDb();
		isConnect = true;
	}

	startTransaction();
	for (string sql : sqls)
	{
		ExecuteSql(sql.c_str());;
	}
	commit();
	dbMutex.unlock();
}

void CDbObj::startTransaction()
{
	mysql_query(&mysql,"START TRANSACTION"); // 开启事务， 如果没有开启事务，那么效率会变得非常低下！
}

void CDbObj::commit()
{
	mysql_query(&mysql,"COMMIT"); // 提交事务 
}

