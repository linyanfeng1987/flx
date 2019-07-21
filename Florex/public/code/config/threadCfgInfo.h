#pragma once
#include <string>
#include "LogObj.h"
#include "baseCfgInfo.h"
#include "dataSrcInfo.h"
#include "analysisInfo.h"
using namespace std;
class CThreadCfgInfo : public CBaseCfgInfo
{
public:
	using CBaseCfgInfo::CBaseCfgInfo;

	void loadByXml(TiXmlElement *node);

	time_t step;
	PDataSrcInfo dataSrcInfo;
	PAnalysisInfo analysisInfo;
};
typedef shared_ptr<CThreadCfgInfo> PThreadCfgInfo;
#define newThreadCfgInfo() make_shared<CThreadCfgInfo>()
