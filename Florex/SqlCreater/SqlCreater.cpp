// SqlCreater.cpp : 定义控制台应用程序的入口点。
//

#include <stdio.h>
#include <tchar.h>

#include <string>
#include <list>
#include "ConstDef.h"
#include "db/DbObj.h"

using namespace std;
const string dropFormat = "drop table `florex`.`%s`;";
const string createBaseTableFormat = "CREATE TABLE `florex`.`%s` (  \
									 `curTime` INT NOT NULL,		\
									 `curMsec` INT NOT NULL default 0,		\
									 `priceBuy` FLOAT NOT NULL,			\
									 `priceCell` FLOAT NOT NULL,			\
									 `volume` FLOAT NOT NULL,		\
									 `timeFormat` VARCHAR(45) NULL,	\
									 `percentSpead_s` FLOAT, \
									 PRIMARY KEY (`curTime`,`curMsec`));";

const string createHisTableFormat = " CREATE TABLE `florex`.`%s` (  \
	`startTime` INT NOT NULL,			\
	`openPrice` FLOAT NOT NULL,			\
	`lowPrice` FLOAT NOT NULL,			\
	`highPrice` FLOAT NOT NULL,			\
	`closePrice` FLOAT NOT NULL,		\
	`volume` FLOAT NOT NULL,			\
	`timeFormat` VARCHAR(45) NULL,		\
	`percentSpead_s` FLOAT, \
	PRIMARY KEY (`startTime`));";		

const string changeColumnFormat = "alter table `florex`.`%s` CHANGE `%s` `%s` %s;";
const string addColumnFormat = "alter table `florex`.`%s` add COLUMN `%s` %s;";

const string dropPkFormat = "ALTER TABLE `florex`.`%s` DROP PRIMARY KEY;";
const string addPkFormat = "ALTER TABLE `florex`.`%s` ADD PRIMARY KEY (%s);";

string rateName[] = {"testRate","eurusd","usdjpy","xauusd","gbpusd","audusd"};
//string rateName[] = {"testRate"};

string getChangeColumnSql(string strTable, string strOldCol, string strNewCol, string colInfo)
{
	char chSql[2048] = {0};
	sprintf_s(chSql, changeColumnFormat.c_str(), strTable.c_str(), strOldCol.c_str(), strNewCol.c_str(), colInfo.c_str());
	return chSql;
}

string getAddColumnSql(string strTable, string strNewCol, string colInfo)
{
	char chSql[2048] = {0};
	sprintf_s(chSql, addColumnFormat.c_str(), strTable.c_str(), strNewCol.c_str(), colInfo.c_str());
	return chSql;
}

list<string> getCurTableName()
{
	list<string> tables;
	string tableName = "";
	for(string rateName : rateName)
	{
		tableName = "currency_pair_";
		tableName += rateName;
		tables.push_back(tableName);
	}

	return tables;
}

list<string> getHisTableName()
{
	list<string> tables;
	string tableName = "";
	for(string rateName : rateName)
	{
		tableName = "currency_pair_";
		tableName += rateName;
		tableName += tableTimeStepEnd_mm;
		tables.push_back(tableName);
	}

	for(string rateName : rateName)
	{
		tableName = "currency_pair_";
		tableName += rateName;
		tableName += tableTimeStepEnd_15m;
		tables.push_back(tableName);
	}

	for(string rateName : rateName)
	{
		tableName = "currency_pair_";
		tableName += rateName;
		tableName += tableTimeStepEnd_hh;
		tables.push_back(tableName);
	}

	for(string rateName : rateName)
	{
		tableName = "currency_pair_";
		tableName += rateName;
		tableName += tableTimeStepEnd_4h;
		tables.push_back(tableName);
	}

	for(string rateName : rateName)
	{
		tableName = "currency_pair_";
		tableName += rateName;
		tableName += tableTimeStepEnd_dd;
		tables.push_back(tableName);
	}

	return tables;
}

void createCurTable()
{
	list<string> tableNames = getCurTableName();
	//list<string>::iterator iter 
	char chSqlDrop[2048] = {0};
	char chSqlCreat[2048] = {0};
	char msg[2048] = {};
	CDbObj& db = CDbObj::instance();
	for(string tableName : tableNames)
	{
		memset(chSqlDrop, 0, sizeof(chSqlDrop));
		memset(chSqlCreat, 0, sizeof(chSqlCreat));
		sprintf_s(chSqlDrop, dropFormat.c_str(), tableName.c_str());
		sprintf_s(chSqlCreat, createBaseTableFormat.c_str(), tableName.c_str());
		db.ExecuteSql(chSqlDrop, msg);
		db.ExecuteSql(chSqlCreat, msg);
	}
}

void createHisTable()
{
	list<string> tableNames = getHisTableName();
	//list<string>::iterator iter 
	char chSqlDrop[2048] = {0};
	char chSqlCreat[2048] = {0};
	char msg[2048] = {};
	CDbObj& db = CDbObj::instance();
	for(string tableName : tableNames)
	{
		memset(chSqlDrop, 0, sizeof(chSqlDrop));
		memset(chSqlCreat, 0, sizeof(chSqlCreat));
		sprintf_s(chSqlDrop, dropFormat.c_str(), tableName.c_str());
		sprintf_s(chSqlCreat, createHisTableFormat.c_str(), tableName.c_str());
		db.ExecuteSql(chSqlDrop, msg);
		db.ExecuteSql(chSqlCreat, msg);
	}
}

void alterCurTable()
{
	list<string> tableNames = getCurTableName();
	char msg[2048] = {};
	CDbObj& db = CDbObj::instance();
	for(string tableName : tableNames)
	{
		string strChange = getChangeColumnSql(tableName, "price", "priceBuy", "FLOAT NOT NULL");
		string strAdd = getAddColumnSql(tableName, "priceCell", "FLOAT NOT NULL");

		db.ExecuteSql(strChange.c_str(), msg);
		db.ExecuteSql(strAdd.c_str(), msg);
	}
}

void alterCurTable_addSpead()
{
	list<string> tableNames = getCurTableName();
	char msg[2048] = {};
	CDbObj& db = CDbObj::instance();
	for(string tableName : tableNames)
	{
		string strAdd = getAddColumnSql(tableName, "percentSpead_s", "FLOAT");

		db.ExecuteSql(strAdd.c_str(), msg);
	}
}

void alterHisTable_addSpead()
{
	list<string> tableNames = getHisTableName();
	char msg[2048] = {};
	CDbObj& db = CDbObj::instance();
	for(string tableName : tableNames)
	{
		string strAdd = getAddColumnSql(tableName, "percentSpead_s", "FLOAT");

		db.ExecuteSql(strAdd.c_str(), msg);
	}
}

void alterCurTable_addCurMsec()
{
	list<string> tableNames = getCurTableName();
	char msg[2048] = {};
	CDbObj& db = CDbObj::instance();
	for(string tableName : tableNames)
	{
		string strAdd = getAddColumnSql(tableName, "curMsec", "INT NOT NULL default 0");

		db.ExecuteSql(strAdd.c_str(), msg);
	}
}

void alterCurTablePk()
{
	list<string> tableNames = getCurTableName();
	char msg[2048] = {};
	CDbObj& db = CDbObj::instance();
	for(string tableName : tableNames)
	{

		char chSql[2048] = {0};
		sprintf_s(chSql, dropPkFormat.c_str(), tableName.c_str());
		string strDropPk = chSql;

		char chSql2[2048] = {0};
		sprintf_s(chSql2, addPkFormat.c_str(), tableName.c_str(), "startTime,curMsec");
		string strAddPk = chSql2;

		db.ExecuteSql(strDropPk.c_str(), msg);
		printf("msg: %s", msg);
		db.ExecuteSql(strAddPk.c_str(), msg);
		printf("msg: %s", msg);
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	//createCurTable();
	//createHisTable();
	//alterCurTable();
	//alterCurTable_addSpead();
	//alterCurTable_addCurMsec();
	//alterCurTablePk();
	alterHisTable_addSpead();
	return 0;
}

