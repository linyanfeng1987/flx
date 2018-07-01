#include "dateOperateion.h"
#include "PubFun.h"
#include "db/dataStruct/curRateStruct.h"

CDbObj &g_db = CDbObj::instance();

CDataOperation::CDataOperation()
{
}

CDataOperation::~CDataOperation()
{
}

CDataOperation& CDataOperation::getDataOperation()
{
	static CDataOperation g_dao;
	return g_dao;
}

time_t CDataOperation::GetLastTimeFromeRate( string rateName, int nType /*= timeStepStep_def*/ )
{
	string sqlFormat = "select * from %s.currency_pair_%s%s order by curTime desc, curMsec desc limit 1";

	string strStep = PubFun::getStepStr(nType);
	char chSql[2048] = {0};
	sprintf_s(chSql, sqlFormat.c_str(), florexDbName.c_str(), rateName.c_str(), strStep.c_str());

	CCurRateStruct rateStruct;
	CTable table(&rateStruct);
	g_db.SelectData(chSql, table);

	string strCurTime = table.begin()->second.find("curTime")->second;
	
	return PubFun::stringToInt(strCurTime);
}

