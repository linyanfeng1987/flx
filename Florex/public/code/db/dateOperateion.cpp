#include "dateOperateion.h"
#include "Exception.h"
#include "PubFun.h"
#include "db/dataStruct/curRateStruct.h"

CDataOperation::CDataOperation() :log(CLogObj::instance())
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

time_t CDataOperation::GetLastTimeFromeRate(string rateName, int nType /*= timeStepStep_def*/)
{
	string sqlFormat = "select * from %s.currency_pair_%s%s order by curTime desc, curMsec desc limit 1";

	string strStep = PubFun::getStepNameByType(nType);
	char chSql[2048] = { 0 };
	sprintf_s(chSql, sqlFormat.c_str(), florexDbName.c_str(), rateName.c_str(), strStep.c_str());

	PCurRateStruct rateStruct = newCurRateStruct(rateName);
	PTable table = newTable(rateStruct);
	time_t curTime = -1;
	try
	{
		CDbObj::instance().selectData(chSql, table);
		curTime = table->begin()->second->find("curTime")->second->getTimeTValue();
	}
	catch (CStrException& e)
	{
		log.error(string("GetLastTimeFromeRate Ê§°Ü£¡msg:").append(e.what()));
	}

	return curTime;
}