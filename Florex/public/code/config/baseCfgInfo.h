#pragma once
#include <string>
#include <list>
#include <map>
#include "LogObj.h"
#include "PubFun.h"

#include "tinyXml/tinyxml.h"

using namespace std;
class CBaseCfgInfo
{
public:
	CBaseCfgInfo(void);
	virtual~CBaseCfgInfo(void);

	virtual void loadByXml(TiXmlElement *node);

	string tagName;
};

typedef shared_ptr<CBaseCfgInfo> PBaseCfgInfo;
#define newBaseCfgInfo() make_shared<CBaseCfgInfo>()