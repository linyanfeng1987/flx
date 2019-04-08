// ShowSpace.cpp : 实现文件
//

#include "stdafx.h"
#include "DataShow.h"
#include "ShowSpace.h"


// ShowSpace

IMPLEMENT_DYNAMIC(ShowSpace, CEdit)

ShowSpace::ShowSpace()
{
	maxRateValue = 0;
	minRateValue = 0;
	maxTime = 0;
	minTime = 0;
}

ShowSpace::~ShowSpace()
{
}


BEGIN_MESSAGE_MAP(ShowSpace, CEdit)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// ShowSpace 消息处理程序
void ShowSpace::OnPaint()
{
// 	CPaintDC dc(this); // device context for painting
// 	CPen pen(PS_SOLID,1,RGB(255,0,0)); //创建绘制的画笔
// 	CBrush *pbrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH)); //创建绘制时填充的画刷
// 	dc.SelectObject(&pen); //将画刷和画笔选入设备描述表中
// 	dc.SelectObject(pbrush);
// 
// 	CPoint point1(0, 0);
// 	CPoint point2(1000, 500);
// 	dc.MoveTo(point1);
// 	dc.LineTo(point2);
// 
// 	CRect rect;
// 	GetClientRect(&rect);
// 
// 	CPaintDC* pDC = &dc;
// 	pDC->SetMapMode(MM_ANISOTROPIC);
// 	pDC->SetWindowExt(rect.Width(),rect.Height());
// 	pDC->SetViewportExt(rect.Width(),-rect.Height());
// 	pDC->SetViewportOrg(rect.Width()/2,rect.Height()/2);
// 	rect.OffsetRect(-rect.Width()/2,-rect.Height()/2);
// 	CPoint ld,rt;//
// 
// 	//绘制外部黑色椭圆
// 	ld=CPoint(-200,-150),rt=CPoint(200,150);
// 	CBrush NewBrush, *pOldBrush;
// 	NewBrush.CreateSolidBrush(RGB(0,0,0));
// 	pOldBrush=pDC->SelectObject(&NewBrush);
// 	pDC->Ellipse(CRect(ld,rt));
// 	pDC->SelectObject(pOldBrush);
// 	NewBrush.DeleteObject();
		// TODO: 在此处添加消息处理程序代码
		// 不为绘图消息调用 CEdit::OnPaint()


	CPaintDC dc(this);
	if (0 != maxRateValue)
	{
		CPen pen1(PS_SOLID,1,RGB(255,0,0));
		for (auto tablePair : rateTables)
		{
			PTable table = tablePair.second;
			paintRateValue(CCurRateStruct::priceBuy, CCurRateStruct::curTime, table, dc, pen1);
		}

		CPen pen2(PS_SOLID,1,RGB(0,255,0));
		for (auto tablePair : averageRateTables)
		{
			PTable table = tablePair.second;
			paintRateValue(CCurRateAverageStruct::curValue, CCurRateAverageStruct::curTime, table, dc, pen2);
		}
	}
	
	CEdit::OnPaint();
}

void ShowSpace::clear()
{
	rateTables.clear();
	averageRateTables.clear();
	optTables.clear();
	OnPaint();
}

void ShowSpace::addRateValueTable( string tagName, PTable rateValueTable )
{
	auto pr = rateTables.insert(make_pair(tagName, rateValueTable));
	if (pr.second)
	{
		loadValueBorder(CCurRateStruct::priceBuy, CCurRateStruct::curTime, rateValueTable);
	}
}

void ShowSpace::addAverageRateValueTable( string tagName, PTable rateValueTable )
{
	auto pr = averageRateTables.insert(make_pair(tagName, rateValueTable));
	if (pr.second)
	{
		loadValueBorder(CCurRateAverageStruct::curValue, CCurRateAverageStruct::curTime, rateValueTable);
	}
}

void ShowSpace::addOptValueTable( string tagName, PTable optValueTable )
{
	optTables.insert(make_pair(tagName, optValueTable));
}

void ShowSpace::loadValueBorder( string rateValueField, string timeField, PTable table )
{
	for (auto rowPr : *table)
	{
		PRow row = rowPr.second;
		double curValue = row->getDoubleValue(rateValueField);
		double curTime = row->getDoubleValue(timeField);

		maxRateValue = maxRateValue < curValue ? curValue : maxRateValue;
		minRateValue = minRateValue > curValue ? curValue : minRateValue;
		maxTime = maxTime < curTime ? curTime : maxTime; 
		minTime = minTime > curTime ? curTime : minTime;
	}
}

void ShowSpace::paintRateValue( string rateValueField, string timeField, PTable table, CPaintDC &dc, CPen &pen )
{
	shared_ptr<CPoint> point = nullptr;
	shared_ptr<CPoint> pointTo = nullptr;
	for (auto rowPr : *table)
	{
		PRow row = rowPr.second;
		double curValue = row->getDoubleValue(rateValueField);
		double curTime = row->getDoubleValue(timeField);

		int x = (curTime - minTime)/bigTimeStep * maxShowW;
		int y = (curValue - minRateValue)/bigValueStep * maxShowH;
		
		if (nullptr == point)
		{
			point = make_shared<CPoint>(x, y);
			dc.MoveTo(*point);
		}
		else
		{
			point = make_shared<CPoint>(x, y);
			dc.LineTo(*point);
		}
	}
}
