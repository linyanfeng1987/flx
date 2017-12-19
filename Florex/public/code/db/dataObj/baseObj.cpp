#include "baseObj.h"

CTableStruct CBaseObj::tableStruct("");
CBaseObj::CBaseObj()
{
}

CBaseObj::~CBaseObj()
{
}

void CBaseObj::load( CRow *pRow )
{
	this->pRow = pRow;
}
