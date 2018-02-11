
// PacmanView.h : interface of the CPacmanView class
//

#pragma once


class CPacmanView : public CView
{
protected: // create from serialization only
	CPacmanView();
	DECLARE_DYNCREATE(CPacmanView)

// Attributes
public:
	CPacmanDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	
	void DrawPacman(CDC* pDC, CRect rect, float angle);
	void DrawGhost(CDC* pDC, CRect rect);
	float toRad(float angle);
	void Translate(CDC *pDC, int x, int y, bool right);
	void Rotate(CDC *pDC, float angle, bool right);
	void Reflect(CDC *pDC, int x, int y, bool right);
	
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CPacmanView();
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

#ifndef _DEBUG  // debug version in PacmanView.cpp
inline CPacmanDoc* CPacmanView::GetDocument() const
   { return reinterpret_cast<CPacmanDoc*>(m_pDocument); }
#endif

