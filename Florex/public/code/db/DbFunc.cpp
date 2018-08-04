#include "DbFunc.h"
#include "DbObj.h"


CDbObj& CDbFunc::db = CDbObj::instance();
CGlobalData& CDbFunc::gData = CGlobalData::instance();
CDbFunc::CDbFunc(void)
{
}


CDbFunc::~CDbFunc(void)
{

}


CRow CDbFunc::getProcessStatusLine( string processName )
{
	string strSqlFormat = "select * from %s where processName = %s;";
	string strTableName = coreDbName + ".";
	strTableName += "processstatus";
	time_t lastTime = 0;

	char chSql[2048] = {0};
	memset(chSql, 0, sizeof(chSql));
	sprintf_s(chSql, strSqlFormat.c_str(), strTableName.c_str(), processName.c_str());
	CProcessStatusStruct* pProcessStatusStruct = CProcessStatusStruct::instence();
	CTable processStatusTable(pProcessStatusStruct);
	db.SelectData(chSql, processStatusTable);

	CTable::iterator iter = processStatusTable.begin();
	if (iter != processStatusTable.end())
	{
		return iter->second;
	}
	return nullptr;
}
