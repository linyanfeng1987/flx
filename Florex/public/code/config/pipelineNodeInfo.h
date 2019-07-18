#pragma once
#include <string>
#include "LogObj.h"
#include "baseCfgInfo.h"

using namespace std;
class CPipelineNodeInfo : public CBaseCfgInfo
{
public:
	using CBaseCfgInfo::CBaseCfgInfo;

	void loadByXml(TiXmlElement *node);

	string strType;
	string strParam;
protected:
	
};
typedef shared_ptr<CPipelineNodeInfo> PPipelineNodeInfo;
#define newPipelineNodeInfo() make_shared<CPipelineNodeInfo>()
