#pragma once
#include <string>
#include "LogObj.h"
#include "baseCfgInfo.h"
#include "pipelineNodeInfo.h"
using namespace std;
class CPipelineInfo : public CBaseCfgInfo
{
public:
	using CBaseCfgInfo::CBaseCfgInfo;

	void loadByXml(TiXmlElement* node);

protected:
	list<PPipelineNodeInfo> pipelineNodes;
};
typedef shared_ptr<CPipelineInfo> PPipelineInfo;
#define newPipelineInfo() make_shared<CPipelineInfo>()
