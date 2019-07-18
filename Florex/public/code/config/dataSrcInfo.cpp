#include "dataSrcInfo.h"
#include "PubFun.h"

void CDataSrcInfo::loadByXml(TiXmlElement *node)
{
	srcType = PubFun::getStrAttrFromEle(node, "type");
	if (srcType == "sql")
	{
		srcSql = PubFun::getStrAttrFromEle(node, "sql");
	}
}
