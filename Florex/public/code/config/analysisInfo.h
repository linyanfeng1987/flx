#pragma once
#include <string>
#include "LogObj.h"
#include "baseCfgInfo.h"
#include "pipelineInfo.h"
using namespace std;
class CAnalysisInfo : public CBaseCfgInfo
{
public:
	using CBaseCfgInfo::CBaseCfgInfo;

	void loadByXml(TiXmlElement *node);

protected:
	PPipelineInfo pipelineInfo;
};
typedef shared_ptr<CAnalysisInfo> PAnalysisInfo;
#define newAnalysisInfo() make_shared<CAnalysisInfo>()
