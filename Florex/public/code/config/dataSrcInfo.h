#pragma once
#include <string>
#include "LogObj.h"
#include "baseCfgInfo.h"

using namespace std;
class CDataSrcInfo : public CBaseCfgInfo
{
public:
	using CBaseCfgInfo::CBaseCfgInfo;

	void loadByXml(TiXmlElement *node);

protected:
	string srcType;
	string srcSql;
};
typedef shared_ptr<CDataSrcInfo> PDataSrcInfo;
#define newDataSrcInfo() make_shared<CDataSrcInfo>()
