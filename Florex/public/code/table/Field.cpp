#include "Field.h"

void CField::load(string _strName, string _strType/*=typeString*/, bool _bIsPk /*= false*/, bool _isIndex /*= false*/, bool _alowedEmpyt /*= false*/)
{
	strName = _strName;
	strType = _strType;
	bIsPk = _bIsPk;
	isIndex = _isIndex;
	alowedEmpyt = _alowedEmpyt;
}

bool CField::isNumberType()
{
	if (typeInt == strType || typeDouble == strType || "float" == strType) {
		return true;
	}
	else {
		return false;
	}
}