#include "dbTestTask.h"
#include "db/dataStruct/testDbInfoStruct.h"
#include "table/Table.h"
#include "db/DbObj.h"
#include "PubFun.h"

CDbTestTask::CDbTestTask( int step, string name): CBaseTask(name)
{
	this->step = step;
}

CDbTestTask::~CDbTestTask()
{
}

int CDbTestTask::completeTask()
{
	status = 2;
	return 0;
}

void CDbTestTask::runInThread( const char* argv )
{
	static string className = "CDbTestTask";
	status = 1;
	try
	{
		log.test(PubFun::strFormat("test db begin"), className);
		PTestDbInfoStruct testDbStruct = CTestDbInfoStruct::instence();
		PTable resTable = newTable(testDbStruct);

		string baseId("linTest1");
		string condition = "";
		condition.append(CTestDbInfoStruct::key_id).append("='").append(baseId).append("'");
		string sql = testDbStruct->getSelectSql(condition);
		CDbObj& db = CDbObj::instance();

		while (true)
		{
			PRow row = db.selectOneData(sql.c_str(), testDbStruct);
			if (nullptr == row)
			{
				row = newRow(testDbStruct);
				row->setStringValue(CTestDbInfoStruct::key_id, baseId);
				row->setIntValue(CTestDbInfoStruct::key_value, 0);

				log.test(PubFun::strFormat("insert new"), className);
			}
			else{
				int nSrcValue = row->getIntValue(CTestDbInfoStruct::key_value);
				int nDestValue = nSrcValue;
				if (-100 < nSrcValue && nSrcValue < 100)
				{
					nDestValue += step;
					row->setIntValue(CTestDbInfoStruct::key_value, nDestValue);
				}
				else
				{
					log.info(string("testDb end!"));
					break;
				}
				log.test(PubFun::strFormat("update,srcValue:%d, destValue:%d.", nSrcValue, nDestValue), className);
			}
			row->save();
		}
		
		completeTask();
		log.test(PubFun::strFormat("test db succ end"), className);
	}
	catch (CStrException& e)
	{
		log.error(string("runInThread Ê§°Ü£¡msg:").append(e.what()));
		log.test(PubFun::strFormat("test db error:%s", e.what()), className);
	}
	log.test(PubFun::strFormat("test db end"), className);
}