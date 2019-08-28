#pragma once
#include "Row.h"
#include "Field.h"
#include "TableStruct.h"
#include <vector>
#include <memory>

using namespace std;
class CTable : public Linked_map<int, PRow>
{
public:
	CTable(PTableStruct tableStruct);
	~CTable(void);

	void init(PTableStruct tableStruct);
	void addRow(PRow row);
	void save();

	PTableStruct tableStruct;

private:

	CTable(const CTable& otherOne); // 私有的拷贝构造函数
	CTable& operator = (const CTable& otherOne);
	int m_rowIndex;
};

typedef shared_ptr<CTable> PTable;
#define newTable(T) make_shared<CTable>(T)
