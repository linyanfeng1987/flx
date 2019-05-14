#include "DbFunc.h"
#include "DbObj.h"


//CGlobalData& CDbFunc::gData = CGlobalData::instance();
CDbFunc::CDbFunc(void)
{
}


CDbFunc::~CDbFunc(void)
{

}


PRow CDbFunc::getProcessStatusLine( string rateName, string processTypeName )
{
	PThreadStatusStruct tableSt = CThreadStatusStruct::instence();
	string sql = tableSt->getSelectSql(PubFun::strFormat("%s = %s and %s = %s",
		CThreadStatusStruct::key_rateName.c_str(), rateName.c_str(),
		CThreadStatusStruct::key_processTypeName.c_str(),  processTypeName.c_str()));

	return CDbObj::instance().selectOneData(sql.c_str(), tableSt);;
}
