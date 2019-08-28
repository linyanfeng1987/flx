#include "Table.h"
#include "Exception.h"
#include "db/DbObj.h"

CTable::CTable(PTableStruct tableStruct)
{
	init(tableStruct);
	m_rowIndex = 0;
}

CTable::~CTable(void)
{
}

void CTable::init(PTableStruct tableStruct)
{
	this->tableStruct = tableStruct;
}

void CTable::addRow(PRow row)
{
	std::pair<CTable::iterator, bool> pr = this->insert(make_pair(m_rowIndex++, row));
	if (!pr.second)
	{
		throw CStrException("insert error in addRow.");
	}
}

void CTable::save()
{
	list<string> sqls;
	for (auto rowIter : *this)
	{
		sqls.push_back(rowIter.second->getSql());
		rowIter.second->setDataStatus(DATA_SAME);
	}

	CDbObj::instance().insertDatas(sqls);
}