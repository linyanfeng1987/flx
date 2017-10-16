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

void CDbObj::SelectData(const char * SQL,CTable table )
{
	string strLog = "selectData:";
	strLog += SQL;
	PubFun::log(strLog);
	if (!isConnect)
	{
		ConnectDb();
	}
	char* Msg = "";
	int cNum = (int)table.m_tableStruct->size();
	string strRes = db.SelectData(SQL, cNum, Msg);

	list<string> rows = PubFun::split(strRes, "\n");
	list<string>::iterator rowIter = rows.begin();
	for(;rowIter != rows.end(); rowIter++)
	{
		CRow rowObj;
		list<string> values = PubFun::split(*rowIter, ",");
		rowObj.addByList(values);
		
		table.addRow(rowObj);
	}
}

bool CDbObj::ExecuteSql( const char * SQL )
{
	string strLog = "excecuteSql:";
	strLog += SQL;
	PubFun::log(strLog);
	if(!isConnect)
	{
		ConnectDb();
		isConnect = true;
	}

	return db.ExecuteSql(SQL);
}

void CDbObj::ConnectDb()
{
	char* host="localhost";
	char* user="root";
	char* port ="3306";
	char* passwd="101050";
	char* dbname="florex"; 
	char* charset = "GBK";//支持中文
	string strMsg = "";//消息变量
	char* Msg = "";

	if(db.ConnMySQL(host,port,dbname,user,passwd,charset,strMsg) == 0)
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
}


