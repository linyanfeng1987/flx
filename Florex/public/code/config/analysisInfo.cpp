#include "analysisInfo.h"
#include "PubFun.h"

void CAnalysisInfo::loadByXml(TiXmlElement* node)
{
	CBaseCfgInfo::loadByXml(node);
	analysisType = PubFun::getStrAttrFromEle(node, "type");
	TiXmlElement* childNode = node->FirstChildElement();
	while (nullptr != childNode)
	{
		if (PubFun::isNodeNamed(childNode, "pipeline"))
		{
			pipelineInfo = newPipelineInfo();
			pipelineInfo->loadByXml(childNode);
		}
		else if (PubFun::isNodeNamed(childNode, "param"))
		{
			PBaseParamInfo paramInfo = newBaseParamInfo();
			paramInfo->loadByXml(childNode);

			paramGroup.insert(make_pair(paramInfo->tagName, paramInfo));
		}

		childNode = childNode->NextSiblingElement();
	}
}