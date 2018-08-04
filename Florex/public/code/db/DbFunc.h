#pragma once
#include "db/DbObj.h"
#include "data/globalData.h"
#include "process/processType.h"
#include "PubFun.h"
#include "ConstDef.h"

#include "db/dataStruct/processTaskInfoStruct.h"
#include "db/dataStruct/curRateStruct.h"
#include "db/dataStruct/processStatusStruct.h"

class CDbFunc
{

protected:
	 CDbFunc(void);
public:
	~CDbFunc(void);
	
	static CDbFunc& instance();

	static CRow getProcessStatusLine(string processName);

private:
	static CDbObj& db; 
	static CGlobalData& gData; 
};

