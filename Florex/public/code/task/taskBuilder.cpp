#include "taskBuilder.h"
#include "ConstDef.h"

CDbObj& CTaskBuilder::db = CDbObj::instance();

CTaskBuilder::CTaskBuilder()
{
}

CTaskBuilder::~CTaskBuilder()
{
}

void CTaskBuilder::run()
{
	for (string rateName : rateNames)
	{
		runOneRate(rateName);
	}
}

void CTaskBuilder::runOneRate( string rateName )
{
	string strSqlFormat = "select * from %s order by curTime desc, curMsec desc limit 1;";
	string strTableName = florexDbName + ".";
	strTableName += "currency_pair_";
	strTableName += rateName;

	char chSql[2048] = {0};
	memset(chSql, 0, sizeof(chSql));
	sprintf_s(chSql, strSqlFormat.c_str(), strTableName.c_str());
	CTable resTable;
	db.SelectData(chSql, resTable);

	CTable::iterator iter = resTable.begin();
	if (iter != resTable.end())
	{

	}

}

void CTaskBuilder::runOneProcess( string processName )
{

}
