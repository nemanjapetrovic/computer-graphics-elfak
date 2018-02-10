
// SurikenView.h : interface of the CSurikenView class
//

#pragma once


class CSurikenView : public CView
{
protected: // create from serialization only
	CSurikenView();
	DECLARE_DYNCREATE(CSurikenView)

// Attributes
public:
	CSurikenDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	
	void DrawBlade(CDC* pDC, int size);
	void Translate(CDC *pDC, float x, float y, bool right);
	void Rotate(CDC *pDC, float angle, bool right);
	void DrawStar(CDC* pDC, int size);
	float toRad(float angle);
	
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CSurikenView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // debug version in SurikenView.cpp
inline CSurikenDoc* CSurikenView::GetDocument() const
   { return reinterpret_cast<CSurikenDoc*>(m_pDocument); }
#endif

