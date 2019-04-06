#pragma once


// ShowSpace

class ShowSpace : public CEdit
{
	DECLARE_DYNAMIC(ShowSpace)

public:
	ShowSpace();
	virtual ~ShowSpace();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};


