
// Suriken_3View.h : interface of the CSuriken_3View class
//

#pragma once


class CSuriken_3View : public CView
{
protected: // create from serialization only
	CSuriken_3View();
	DECLARE_DYNCREATE(CSuriken_3View)

// Attributes
public:
	CSuriken_3Doc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	void DrawBlade(CDC *pDC, int size);
	void Translate(CDC* pDC, double x, double y, bool right);
	void Rotate(CDC *pDC, double angle, bool right);
	double toRad(double angle);
	void DrawStar(CDC* pDC, int size);

protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CSuriken_3View();
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

#ifndef _DEBUG  // debug version in Suriken_3View.cpp
inline CSuriken_3Doc* CSuriken_3View::GetDocument() const
   { return reinterpret_cast<CSuriken_3Doc*>(m_pDocument); }
#endif

