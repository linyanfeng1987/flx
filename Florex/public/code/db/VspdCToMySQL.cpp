#include <stdio.h>
#include "VspdCToMySQL.h"
#pragma comment(lib, "libmysql.lib")  

VspdCToMySQL::VspdCToMySQL(void)
{
}


VspdCToMySQL::~VspdCToMySQL(void)
{
}

//初始化数据
bool VspdCToMySQL::ConnMySQL(char *host,char * port ,char * Db,char * user,char* passwd,char * charset, string &strMsg)
{
	bool bRes = true;

	int nRes =mysql_library_init(0, NULL, NULL);
	if (nRes) {
		fprintf(stderr, "could not initialize MySQL client library\n");
		strMsg = mysql_error(NULL);
	}

	if( mysql_init(&mysql) == NULL )
	{
		bRes  = false;
	}    

	if (bRes && mysql_real_connect(&mysql,host,user,passwd,NULL,3306,NULL,0) == NULL)
	{
		bRes  = false;
	}    

	if(bRes && mysql_set_character_set(&mysql,"GBK") != 0)
	{
		bRes  = false;
	}
	
	if (!bRes)
	{
		strMsg = mysql_error(NULL);
		return false;
	}
	return true;
}

//查询数据
string VspdCToMySQL::SelectData(const char * SQL,int Cnum,char * Msg)
{
	MYSQL_ROW m_row;
	MYSQL_RES *m_res;
	char sql[2048];
	sprintf_s(sql,SQL);
	int rnum = 0;
	char rg = '\n';//行隔开
	char cg = ',';//字段隔开

	int nRes = mysql_query(&mysql,sql);
	if(nRes != 0)
	{
		string strMsg = mysql_error(&mysql);
		return "";
	}
	m_res = mysql_store_result(&mysql);

	if(m_res==NULL)
	{
		Msg = "select username Error";
		return "";
	}
	string str("");
	while(m_row = mysql_fetch_row(m_res))
	{
		for(int i = 0;i < Cnum;i++)
		{
			str += m_row[i];
			str += cg;
		}
		str += rg;             
		rnum++;
	}

	mysql_free_result(m_res);

	return str;
}

//更新数据
bool VspdCToMySQL::ExecuteSql(const char * SQL)
{
// 	char sql[2048];
// 	sprintf_s(sql,SQL);
	if(mysql_query(&mysql,SQL) != 0)
	{
		string error = mysql_error(&mysql);
		printf("errorMsg:%s\n", error.c_str());
		return false;
	}
	return true;
}



//关闭数据库连接
void VspdCToMySQL::CloseMySQLConn()
{
	mysql_close(&mysql);
}

void VspdCToMySQL::startTransaction()
{
	mysql_query(&mysql,"START TRANSACTION"); // 开启事务， 如果没有开启事务，那么效率会变得非常低下！
}

void VspdCToMySQL::commit()
{
	mysql_query(&mysql,"COMMIT"); // 提交事务 
}
