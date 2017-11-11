#include "Field.h"



void CField::load( string strName, string strType/*="string"*/, bool bIsPk /*= false*/ )
{
	this->strName = strName;
	this->strType = strType;
	this->bIsPk = bIsPk;
}
