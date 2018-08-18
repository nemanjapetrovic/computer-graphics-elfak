
// ClioDrive_1View.h : interface of the CClioDrive_1View class
//

#pragma once


class CClioDrive_1View : public CView
{
protected: // create from serialization only
	CClioDrive_1View();
	DECLARE_DYNCREATE(CClioDrive_1View)

// Attributes
public:
	CClioDrive_1Doc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	
	void DrawGround(CDC* pDC, float angle);
	void DrawCar(CDC* pDC, int x, int y, int w, int h);
	void DrawWheel(CDC* pDC, int x, int y, int r, float angle);

	float toRad(float angle);
	void Translate(CDC* pDC, float dX, float dY, bool rightMultiply);
	void Rotate(CDC* pDC, float angle, bool rightMultiply);
	void Scale(CDC* pDC, float sX, float sY, bool rightMultiply);

protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CClioDrive_1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // debug version in ClioDrive_1View.cpp
inline CClioDrive_1Doc* CClioDrive_1View::GetDocument() const
   { return reinterpret_cast<CClioDrive_1Doc*>(m_pDocument); }
#endif

