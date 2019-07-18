#include "pipelineNodeInfo.h"
#include "PubFun.h"


void CPipelineNodeInfo::loadByXml(TiXmlElement *node)
{
	strType = PubFun::getStrAttrFromEle(node, "type");
	strParam = PubFun::getStrAttrFromEle(node, "param");
}
