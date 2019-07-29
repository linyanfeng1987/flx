#include "baseCfgInfo.h"


CBaseCfgInfo::CBaseCfgInfo( void )
{

}

CBaseCfgInfo::~CBaseCfgInfo( void )
{

}

void CBaseCfgInfo::loadByXml(TiXmlElement *node)
{
	tagName = PubFun::getStrAttrFromEle(node, "tagName");
}


