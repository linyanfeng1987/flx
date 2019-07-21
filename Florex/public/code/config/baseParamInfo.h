#pragma once
#include <string>
#include <list>

#include "baseCfgInfo.h"

using namespace std;
class CBaseParamInfo:public CBaseCfgInfo
{
public:
	CBaseParamInfo(void);
	virtual~CBaseParamInfo(void);

	virtual void loadByXml(TiXmlElement *node);
	string param;

	list<double>& getNumParams();
protected:
	list<double> numParams;
};

typedef shared_ptr<CBaseParamInfo> PBaseParamInfo;
#define newBaseParamInfo() make_shared<CBaseParamInfo>()