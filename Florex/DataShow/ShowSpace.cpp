// ShowSpace.cpp : 实现文件
//

#include "stdafx.h"
#include "DataShow.h"
#include "ShowSpace.h"


// ShowSpace

IMPLEMENT_DYNAMIC(ShowSpace, CEdit)

ShowSpace::ShowSpace()
{

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
	CPaintDC dc(this); // device context for painting
	CPen pen(PS_SOLID,1,RGB(255,0,0)); //创建绘制的画笔
	CBrush *pbrush=CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH)); //创建绘制时填充的画刷
	dc.SelectObject(&pen); //将画刷和画笔选入设备描述表中
	dc.SelectObject(pbrush);

	CPoint point1(0, 0);
	CPoint point2(1000, 500);
	dc.MoveTo(point1);
	dc.LineTo(point2);

	CRect rect;
	GetClientRect(&rect);

	CPaintDC* pDC = &dc;
	pDC->SetMapMode(MM_ANISOTROPIC);
	pDC->SetWindowExt(rect.Width(),rect.Height());
	pDC->SetViewportExt(rect.Width(),-rect.Height());
	pDC->SetViewportOrg(rect.Width()/2,rect.Height()/2);
	rect.OffsetRect(-rect.Width()/2,-rect.Height()/2);
	CPoint ld,rt;//

	//绘制外部黑色椭圆
	ld=CPoint(-200,-150),rt=CPoint(200,150);
	CBrush NewBrush, *pOldBrush;
	NewBrush.CreateSolidBrush(RGB(0,0,0));
	pOldBrush=pDC->SelectObject(&NewBrush);
	pDC->Ellipse(CRect(ld,rt));
	pDC->SelectObject(pOldBrush);
	NewBrush.DeleteObject();
		// TODO: 在此处添加消息处理程序代码
		// 不为绘图消息调用 CEdit::OnPaint()
}
