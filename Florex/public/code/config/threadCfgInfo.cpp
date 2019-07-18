#include "threadCfgInfo.h"
#include "PubFun.h"


void CThreadCfgInfo::loadByXml(TiXmlElement *node)
{
	step = PubFun::getNumAttrFromEle(node, "step");
	TiXmlElement *childNode = node->FirstChildElement();
	while (nullptr != childNode)
	{
		if(PubFun::isNodeNamed(childNode, "dataSrc"))
		{
			dataSrcInfo = newDataSrcInfo();
			dataSrcInfo->loadByXml(childNode);
		}
		else if (PubFun::isNodeNamed(childNode, "analysis"))
		{
			analysisInfo = newAnalysisInfo();
			analysisInfo->loadByXml(childNode);
		}

		childNode = childNode->NextSiblingElement(); 
	}
}
