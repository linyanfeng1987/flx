#include "globalData.h"

CGlobalData::CGlobalData()
{
}

CGlobalData::~CGlobalData()
{
}

CGlobalData& CGlobalData::instance()
{
	static CGlobalData* pdata = nullptr;

	if (nullptr == pdata)
	{
		pdata = new CGlobalData();
	}

	return *pdata;
}

void CGlobalData::loadConfig()
{

}


