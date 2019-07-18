#include "pipelineInfo.h"
#include "PubFun.h"


void CPipelineInfo::loadByXml(TiXmlElement *node)
{
	TiXmlElement *childNode = node->FirstChildElement();
	while (nullptr != childNode)
	{
		if(PubFun::isNodeNamed(childNode, "pipeline"))
		{
			PPipelineNodeInfo pipelineNodeInfo = newPipelineNodeInfo();
			pipelineNodeInfo->loadByXml(childNode);
			pipelineNodes.push_back(pipelineNodeInfo);
		}

		childNode = childNode->NextSiblingElement(); 
	}
}
