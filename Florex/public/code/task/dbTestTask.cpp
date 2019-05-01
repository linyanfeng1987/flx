#include "dbTestTask.h"
#include "db/dataStruct/testDbInfoStruct.h"
#include "table/Table.h"
#include "db/DbObj.h"
#include "PubFun.h"

const string CDbTestTask::logTag = "dbTestTask";

CDbTestTask::CDbTestTask( int step, PTaskInfo taskInfo): CBaseTask(taskInfo)
{
	logInfo = newLogInfo(logTag);
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
	status = 1;
	try
	{
		log.ext(logInfo, PubFun::strFormat("test db begin"));
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

				log.ext(logInfo, PubFun::strFormat("insert new"));
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
					log.info(logInfo, string("testDb end!"));
					break;
				}
				log.ext(logInfo, PubFun::strFormat("update,srcValue:%d, destValue:%d.", nSrcValue, nDestValue));
			}
			row->save();
		}
		
		completeTask();
		log.ext(logInfo, PubFun::strFormat("test db succ end"));
	}
	catch (CStrException& e)
	{
		log.error(logInfo, string("runInThread Ê§°Ü£¡msg:").append(e.what()));
		log.ext(logInfo, PubFun::strFormat("test db error:%s", e.what()));
	}
	log.ext(logInfo, PubFun::strFormat("test db end"));
}