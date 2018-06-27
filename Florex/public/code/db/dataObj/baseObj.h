#pragma once
#include "table/TableStruct.h"
#include "table/Field.h"
#include "table/Row.h"
#include <string>

using namespace std;
class CBaseObj
{
public:
	CBaseObj();
	~CBaseObj();

	CTableStruct *pTableStruct;

	void load(CRow *pRow);

	CRow* pRow;
};

