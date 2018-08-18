
// Tocak_1View.h : interface of the CTocak_1View class
//

#pragma once


class CTocak_1View : public CView
{
protected: // create from serialization only
	CTocak_1View();
	DECLARE_DYNCREATE(CTocak_1View)

// Attributes
public:
	CTocak_1Doc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	void Rotate(CDC* pDC, float angle, bool right);
	void Translate(CDC *pDC, float x, float y, bool right);
	void DrawWheel(CDC *pDC, double r1, double r2, double w);
	void DrawWP(CDC *pDC, double r1, double r2, double w, double L, double alpha, double d);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CTocak_1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Tocak_1View.cpp
inline CTocak_1Doc* CTocak_1View::GetDocument() const
   { return reinterpret_cast<CTocak_1Doc*>(m_pDocument); }
#endif

