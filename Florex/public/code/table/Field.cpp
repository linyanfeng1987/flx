#include "Field.h"



void CField::load( string strName, string strType/*=typeString*/, bool bIsPk /*= false*/ )
{
	this->strName = strName;
	this->strType = strType;
	this->bIsPk = bIsPk;
}

bool CField::isNumberType()
{
	if(typeInt == strType || typeDouble == strType || "float" == strType){
		return true;
	}
	else{
		return false;
	}
}
