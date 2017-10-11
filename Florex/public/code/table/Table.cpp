#include "Table.h"
#include "Exception.h"


CTable::CTable(void)
{
	m_rowIndex = 0;
}


CTable::~CTable(void)
{
}

void CTable::init( CTableStruct* tableStruct )
{
	m_tableStruct = tableStruct;
}

void CTable::addRow( CRow row )
{
	if (row.getTableStruct() != m_tableStruct)
	{
		throw Exception("error in addRow.");
	}
	else
	{
		std::pair<CTable::iterator, bool> pr = this->insert(make_pair(m_rowIndex++,row));
		if (!pr.second)
		{
			throw Exception("insert error in addRow.");
		}
	}
}
