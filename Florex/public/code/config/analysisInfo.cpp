#include "analysisInfo.h"
#include "PubFun.h"


void CAnalysisInfo::loadByXml(TiXmlElement *node)
{
	TiXmlElement *childNode = node->FirstChildElement();
	while (nullptr != childNode)
	{
		if(PubFun::isNodeNamed(childNode, "pipeline"))
		{
			pipelineInfo = newPipelineInfo();
			pipelineInfo->loadByXml(childNode);
		}

		childNode = childNode->NextSiblingElement(); 
	}
}
