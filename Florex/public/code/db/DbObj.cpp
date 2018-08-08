#include "../PubFun.h"
#include "DbObj.h"

CDbObj* CDbObj::g_db = nullptr;

CDbObj::CDbObj(void)
{
	isConnect = false;
}


CDbObj::~CDbObj(void)
{
	if (isConnect)
	{
		db.CloseMySQLConn();
	}
}

PRow CDbObj::SelectOneData( const char * SQL, PTableStruct tableStruct )
{
	PRow pFirstRow = nullptr;
	string strLog = "selectData:";
	strLog += SQL;
	PubFun::log(strLog);
	{
		dbMutex.lock();
		if (!isConnect)
		{
			ConnectDb();
		}
		char* Msg = "";
		int cNum = (int)tableStruct->size();
		string strRes = db.SelectData(SQL, cNum, Msg);
		list<string> rows = PubFun::split(strRes, "\n");
		list<string>::iterator rowIter = rows.begin();
		for(;rowIter != rows.end(); rowIter++)
		{
			PRow pRowObj = newRow(tableStruct);
			list<string> values = PubFun::split(*rowIter, ",");
			pRowObj->addByList(values);
			pRowObj->setDataStatus(DATA_SAME);
			pFirstRow = pRowObj;
			break;
		}
		dbMutex.unlock();
	}
	return pFirstRow;
}

void CDbObj::SelectData( const char * SQL, PTable resTable)
{
	string strLog = "selectData:";
	strLog += SQL;
	PubFun::log(strLog);
	{
		dbMutex.lock();
		if (!isConnect)
		{
			ConnectDb();
		}
		char* Msg = "";
		int cNum = (int)resTable->tableStruct->size();
		string strRes = db.SelectData(SQL, cNum, Msg);
		list<string> rows = PubFun::split(strRes, "\n");
		list<string>::iterator rowIter = rows.begin();
		for(;rowIter != rows.end(); rowIter++)
		{
			PRow row = newRow(resTable->tableStruct);
			list<string> values = PubFun::split(*rowIter, ",");
			row->addByList(values);
			row->setDataStatus(DATA_SAME);
			resTable->addRow(row);
		}
		dbMutex.unlock();
	}
}

bool CDbObj::ExecuteSql( const char * SQL )
{
	dbMutex.lock();
	string strLog = "excecuteSql:";
	strLog += SQL;
	PubFun::log(strLog);
	if(!isConnect)
	{
		ConnectDb();
		isConnect = true;
	}

	bool bRes = db.ExecuteSql(SQL);
	dbMutex.unlock();
	return bRes;
}

void CDbObj::ConnectDb()
{
	char* host="localhost";
	char* user="root";
	char* port ="3306";
	char* passwd="101050";
	char* dbname=""; 
	char* charset = "GBK";//支持中文
	string strMsg = "";//消息变量
	char* Msg = "";

	if(db.ConnMySQL(host,port,dbname,user,passwd,charset,strMsg))
		printf("连接成功\r\n");
	else
		printf(Msg);

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

	db.startTransaction();
	for (string sql : sqls)
	{
		db.ExecuteSql(sql.c_str());;
	}
	db.commit();
	dbMutex.unlock();
}



