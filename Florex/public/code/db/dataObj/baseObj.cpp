#include "baseObj.h"

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
