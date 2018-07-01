#pragma once
#include "Row.h"
#include "Field.h"
#include "TableStruct.h"
#include <vector>

class CTable: public map<int, CRow>
{
public:
	CTable(CTableStruct* tableStruct);
	~CTable(void);

	void init(CTableStruct* tableStruct);
	void addRow(CRow row);

	CTableStruct* m_tableStruct;
	int m_rowIndex;
};

