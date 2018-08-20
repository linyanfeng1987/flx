#include "Table.h"
#include "Exception.h"


CTable::CTable(PTableStruct tableStruct)
{
	init(tableStruct);
	m_rowIndex = 0;
}


CTable::~CTable(void)
{

}

void CTable::init( PTableStruct tableStruct )
{
	this->tableStruct = tableStruct;
}

void CTable::addRow( PRow row )
{
	std::pair<CTable::iterator, bool> pr = this->insert(make_pair(m_rowIndex++,row));
	if (!pr.second)
	{
		throw CStrException("insert error in addRow.");
	}
}
