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

	static PRow getProcessStatusLine(string rateName, string processTypeName);

private:
	//static CGlobalData& gData; 
};

