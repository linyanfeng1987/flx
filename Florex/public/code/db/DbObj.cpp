#include "../PubFun.h"
#include "Exception.h"
#include "DbObj.h"
#include <regex>
//#include "AutoMutex.h"
#include "tools/FunctionLog.h"
#pragma comment(lib, "libmysql.lib")  

CDbObj* CDbObj::g_db = nullptr;
map<size_t,CDbObj*>* CDbObj::pDbMap = nullptr;
//recursive_mutex CDbObj::dbMutex;

CDbObj& CDbObj::instance()
{
	if (nullptr == pDbMap)
	{
		pDbMap = new map<size_t,CDbObj*>;
	}

	size_t threadId = std::this_thread::get_id().hash();
	auto findRes = pDbMap->find(threadId);
	if (pDbMap->end() == findRes)
	{
		auto insertRes = pDbMap->insert(make_pair(threadId, new CDbObj));
		findRes = insertRes.first;
	}

	return *(findRes->second);
}

void CDbObj::release()
{
	size_t threadId = std::this_thread::get_id().hash();
	auto findRes = pDbMap->find(threadId);
	if (pDbMap->end() != findRes)
	{
		delete findRes->second;
		findRes->second = nullptr;
		pDbMap->erase(findRes);
	}
}

CDbObj::CDbObj(void):log(CLogObj::instance())
{
	isMySqlInit = false;
}

CDbObj::~CDbObj(void)
{
	CFunctionLog funLog(__FUNCTION__, __LINE__);
	mysql_close(&mysql);
}

void CDbObj::startTransaction()
{
	mysql_query(&mysql,"START TRANSACTION"); // 开启事务， 如果没有开启事务，那么效率会变得非常低下！
}

void CDbObj::commit()
{
	mysql_query(&mysql,"COMMIT"); // 提交事务 
}

PRow CDbObj::selectOneData( const char * sql, PTableStruct tableStruct )
{
	string strLog = "selectData:" + string(sql);
	PRow row = nullptr;
	PubFun::log(strLog);
	{
		//CAutoMutex localMutex(&dbMutex);
		CFunctionLog funLog(__FUNCTION__, __LINE__);
		tryConnect();

		int nRes = mysql_query(&mysql,sql);
		string strMsg = "";
		if(0 == nRes)
		{
			MYSQL_ROW pRow = nullptr;
			MYSQL_RES *pRes = nullptr;
			pRes = mysql_store_result(&mysql);
			if(pRes==nullptr)
			{
				throwSqlError(sql);
			}
			while(pRow = mysql_fetch_row(pRes))
			{
				row = newRow(tableStruct);
				char* pDataValue = *pRow;
				auto fieldIter = tableStruct->begin();
				while (tableStruct->end() != fieldIter)
				{
					row->setAndaddValue(fieldIter->first, string(pDataValue));
					pDataValue = *(++pRow);
					fieldIter++;
				}
				
				row->setDataStatus(DATA_SAME);
				break;
			}
			mysql_free_result(pRes);
		}
		else
		{
			throwSqlError(sql);
		}
	}
	return row;
}

void CDbObj::selectData( const char * sql, PTable resTable)
{
	string strLog = "selectData:" + string(sql);
	log.debug(strLog);
	{
		resTable->clear();
		//CAutoMutex localMutex(&dbMutex);
		CFunctionLog funLog(__FUNCTION__, __LINE__);
		log.test(PubFun::strFormat("%s::tryConnect", __FUNCTION__), "dbObj");
		tryConnect();
		
		log.test(PubFun::strFormat("%s::mysql_query", __FUNCTION__), "dbObj");
		int nRes = mysql_query(&mysql,sql);
		string strMsg = "";
		if(0 == nRes)
		{
			MYSQL_ROW pRow = nullptr;
			MYSQL_RES *pRes = nullptr;
			log.test(PubFun::strFormat("%s::mysql_store_result", __FUNCTION__), "dbObj");
			pRes = mysql_store_result(&mysql);
			if(pRes==nullptr)
			{
				throwSqlError(sql);
			}
			log.test(PubFun::strFormat("%s::mysql_fetch_row", __FUNCTION__), "dbObj");
			long nCount = 0;
			while(pRow = mysql_fetch_row(pRes))
			{
				log.test(PubFun::strFormat("%s::mysql_fetch_row count %d", __FUNCTION__, nCount++), "dbObj");
				PRow row = newRow(resTable->tableStruct);
				char* pDataValue = *pRow;
				auto fieldIter = resTable->tableStruct->begin();
				while (resTable->tableStruct->end() != fieldIter)
				{
					row->setAndaddValue(fieldIter->first, string(pDataValue));
					pDataValue = *(++pRow);
					fieldIter++;
				}
				row->setDataStatus(DATA_SAME);
				resTable->addRow(row);
			}
			log.test(PubFun::strFormat("%s::mysql_free_result", __FUNCTION__), "dbObj");
			mysql_free_result(pRes);
		}
		else
		{
			log.test(PubFun::strFormat("%s::throwSqlError", __FUNCTION__), "dbObj");
			throwSqlError(sql);
		}
	}
}

void CDbObj::executeSql( const char * sql )
{
	string strLog = "excecuteSql:";
	strLog += sql;
	PubFun::log(strLog);
	{
		//CAutoMutex localMutex(&dbMutex);
		CFunctionLog funLog(__FUNCTION__, __LINE__);
		log.test(PubFun::strFormat("%s::tryConnect", __FUNCTION__), "dbObj");
		tryConnect();
		log.test(PubFun::strFormat("%s::baseExecuteSql", __FUNCTION__), "dbObj");
		baseExecuteSql(sql);
	}
}

void CDbObj::baseExecuteSql( const char * sql )
{
	if(mysql_query(&mysql,sql) == 0)
	{
		MYSQL_RES *pRes = nullptr;
		pRes = mysql_store_result(&mysql);
		if(pRes!=nullptr)
		{
			mysql_free_result(pRes);
		}
		
	}
	else
	{
		throwSqlError(sql);
	}
}

void CDbObj::tryConnect()
{
	if (!isMySqlInit)
	{
		initMySQL();
	}

	// 0为链接正常
	int pinRes = mysql_ping(&mysql);
	string strMsg = mysql_error(&mysql);
	log.test(PubFun::strFormat("%s::mysql_ping, res:%d", __FUNCTION__, pinRes), "dbObj");
	if (0 != pinRes)
	{
		connectDefDb();
	}
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
	log.test(PubFun::strFormat("%s::connectMySQL", __FUNCTION__), "dbObj");
	if ( nullptr == mysql_real_connect(&mysql,host,user,passwd,NULL,port,NULL,0))
	{
		throwSqlError();
	}   
}

void CDbObj::initMySQL()
{
	//CAutoMutex localMutex(&dbMutex);
	CFunctionLog funLog(__FUNCTION__, __LINE__);
	bool bRes = false;
	log.test(PubFun::strFormat("%s::mysql_library_init", __FUNCTION__), "dbObj");
	int nRes =mysql_library_init(0, NULL, NULL);
	if (0 == nRes) {
		log.test(PubFun::strFormat("%s::mysql_init", __FUNCTION__), "dbObj");
		if( NULL != mysql_init(&mysql) )
		{
			log.test(PubFun::strFormat("%s::connectDefDb", __FUNCTION__), "dbObj");
			connectDefDb();
			log.test(PubFun::strFormat("%s::mysql_set_character_set", __FUNCTION__), "dbObj");
			if(0 == mysql_set_character_set(&mysql,"GBK"))
			{
				bRes  = true;
				isMySqlInit = true;
			}
		}    
	}

	if (!bRes)
	{
		log.test(PubFun::strFormat("%s::throwSqlError", __FUNCTION__), "dbObj");
		throwSqlError();
	}
}

void CDbObj::insertDatas( list<string> sqls )
{
	//CAutoMutex localMutex(&dbMutex);
	CFunctionLog funLog(__FUNCTION__, __LINE__);
	tryConnect();

	startTransaction();
	for (string sql : sqls)
	{
		baseInsert(sql);;
	}
	commit();
}

void CDbObj::insertData( string sql )
{
	tryConnect();
	baseInsert(sql);
}

void CDbObj::baseInsert( string sql )
{
	string strLog = "insertSql:";
	strLog += sql;
	PubFun::log(strLog);
	{
		try
		{
			baseExecuteSql(sql.c_str());
		}
		catch (CStrException& e)
		{
			// 主键冲突的暂时不处理了
			string msg = e.what();
			regex reg1("^Duplicate entry.*?for key 'PRIMARY'$");
			smatch r1;
			if(!regex_match(msg, r1, reg1))
			{
				//不是主键冲突
				throw e;
			}
		}
	}
}


void CDbObj::throwSqlError(string sql)
{
	string strMsg = mysql_error(&mysql);
	log.error(PubFun::strFormat("执行sql失败:sql:\"%s\", errorMsg=\"%s\"", sql.c_str(), strMsg.c_str()));
	throw CStrException(strMsg);
}








