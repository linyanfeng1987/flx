#pragma once
#include <string>
#include "LogObj.h"
#include "baseCfgInfo.h"
#include "baseParamInfo.h"
#include "pipelineInfo.h"

using namespace std;
class CAnalysisInfo : public CBaseCfgInfo
{
public:
	using CBaseCfgInfo::CBaseCfgInfo;

	virtual void loadByXml(TiXmlElement *node);

	string analysisType;
	map<string, PBaseParamInfo> paramGroup;
	PPipelineInfo pipelineInfo;
};
typedef shared_ptr<CAnalysisInfo> PAnalysisInfo;
#define newAnalysisInfo() make_shared<CAnalysisInfo>()
