
// Suriken_2View.h : interface of the CSuriken_2View class
//

#pragma once


class CSuriken_2View : public CView
{
protected: // create from serialization only
	CSuriken_2View();
	DECLARE_DYNCREATE(CSuriken_2View)

// Attributes
public:
	CSuriken_2Doc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	float toRad(float angle);
	void Translate(CDC* pDC, float x, float y, bool right);
	void Rotate(CDC *pDC, float angle, bool right);

	void DrawBlade(CDC* pDC, int size);
	void DrawStar(CDC *pDC, int size);

protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CSuriken_2View();
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
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // debug version in Suriken_2View.cpp
inline CSuriken_2Doc* CSuriken_2View::GetDocument() const
   { return reinterpret_cast<CSuriken_2Doc*>(m_pDocument); }
#endif

