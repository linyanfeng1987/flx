#include "averageProcess.h"
#include "db/dataStruct/curRateAverageStruct.h"
#include "PubFun.h"

CAverageProcess::CAverageProcess( PRow pTaskInfo ):CBaseProcess(pTaskInfo)
{
	init(pTaskInfo);
}

CAverageProcess::~CAverageProcess()
{

}

void CAverageProcess::calc( list<PRateValue> &values )
{
	for (PRateValue rateValue : values)
	{
		averageAnalysis->add(rateValue);
	}
}

void CAverageProcess::init( PRow pTaskInfo )
{
	PRateInfo rateInfo = newRateInfo();
	rateInfo->rateName = pTaskInfo->getStringValue(CProcessTaskInfoStruct::key_rateType);
	averageAnalysis = newAverageAnalysis(rateInfo);
}
