#pragma once
#include "db/DbObj.h"
#include "data/globalData.h"
#include "process/processType.h"
#include "PubFun.h"
#include "ConstDef.h"

#include "db/dataStruct/processTaskInfoStruct.h"
#include "db/dataStruct/curRateStruct.h"
#include "db/dataStruct/threadStatusStruct.h"

class CDbFunc
{
protected:
	CDbFunc(void);
public:
	~CDbFunc(void);

	static CDbFunc& instance();

	static PRow getThreadStatusLine(string rateName, string processTypeName);

	static void getThreadInfos(list<PThreadInfo>& threadInfos);

	static int getThreadLastId();

	static void zeroThreadStatus();

private:
	//static CGlobalData& gData;
};
