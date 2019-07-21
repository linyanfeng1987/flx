#include "baseParamInfo.h"


CBaseParamInfo::CBaseParamInfo( void )
{

}

CBaseParamInfo::~CBaseParamInfo( void )
{

}

void CBaseParamInfo::loadByXml(TiXmlElement *node)
{
	CBaseCfgInfo::loadByXml(node);
	param = PubFun::getStrAttrFromEle(node, "value");
}

list<double>& CBaseParamInfo::getNumParams()
{
	if (numParams.empty())
	{
		numParams = PubFun::splitNumString(param);
	}
	return numParams;
}
