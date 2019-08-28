#pragma once
#include <string>
#include "LogObj.h"
#include "baseCfgInfo.h"
#include "dataSrcInfo.h"
#include "analysisInfo.h"
using namespace std;
class CProcessCfgInfo : public CBaseCfgInfo
{
public:
	using CBaseCfgInfo::CBaseCfgInfo;

	void loadByXml(TiXmlElement* node);

	time_t step;
	PDataSrcInfo dataSrcInfo;
	PAnalysisInfo analysisInfo;
};
typedef shared_ptr<CProcessCfgInfo> PProcessCfgInfo;
#define newProcessCfgInfo() make_shared<CProcessCfgInfo>()
