#pragma once

#include "db/dataStruct/curRateStruct.h"
#include "db/dataStruct/calcRateStruct.h"
#include "db/dataStruct/optValueStruct.h"

#include "process/obj/rateValue.h"
#include "table/Table.h"
// ShowSpace

class ShowSpace : public CEdit
{
	DECLARE_DYNAMIC(ShowSpace)

public:
	//void addRateValueTable(string tagName, PTable rateValueTable);
	void addRateValueTable(string tagName, PTable rateValueTable);
	void addOptValueTable(string tagName, PTable optValueTable);

	void clear();

	ShowSpace();
	virtual ~ShowSpace();

	void setShowRect(int x, int y){maxShowW = x; maxShowH = y;}
	void spOnPaint();
protected:
	DECLARE_MESSAGE_MAP()

	void loadValueBorder(string rateValueField, string timeField, PTable table);
	void paintRateValue(string rateValueField, string timeField, PTable rateValueTable, CPaintDC &dc);

	bool borderInit;
	double maxRateValue;
	double minRateValue;
	double bigValueStep;
	double maxTime;
	double minTime;
	double bigTimeStep;

	int maxShowW;
	int maxShowH;

	map<string, PTable> rateTables;
	map<string, PTable> averageRateTables;
	map<string, PTable> optTables;
public:
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


