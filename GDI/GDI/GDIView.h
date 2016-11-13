
// GDIView.h : interface of the CGDIView class
//

#pragma once


class CGDIView : public CView
{
protected: // create from serialization only
	CGDIView();
	DECLARE_DYNCREATE(CGDIView)

	// Attributes
public:
	CGDIDoc* GetDocument() const;

	// Operations
public:
	// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	void ViewInit(CDC* pDC);

	void DrawLeftWindow(CDC* pDC, CRect rect);
	void DrawCenterWindow(CDC* pDC, CRect rect);
	void DrawRightWindow(CDC* pDC, CRect rect);
	void DrawDashboard(CDC* pDC, CRect rect);
	void DrawDataInstruments(CDC* pDC, CRect rect);

	void DrawSmoothLeftWindow(CDC* pDC, CRect rect);
	void DrawSmoothDashbouard(CDC* pDC, CRect rect);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	// Implementation
public:
	virtual ~CGDIView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in GDIView.cpp
inline CGDIDoc* CGDIView::GetDocument() const
{
	return reinterpret_cast<CGDIDoc*>(m_pDocument);
}
#endif

