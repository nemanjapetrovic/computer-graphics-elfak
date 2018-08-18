
// Suriken_4View.h : interface of the CSuriken_4View class
//

#pragma once


class CSuriken_4View : public CView
{
protected: // create from serialization only
	CSuriken_4View();
	DECLARE_DYNCREATE(CSuriken_4View)

// Attributes
public:
	CSuriken_4Doc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);


	void DrawBlade(CDC* pDC, int size);
	float toRad(float angle);
	void Translate(CDC* pDC, double x, double y, bool right);
	void Rotate(CDC* pDC, float angle, bool right);
	void DrawStar(CDC* pDC, int size);

protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CSuriken_4View();
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

#ifndef _DEBUG  // debug version in Suriken_4View.cpp
inline CSuriken_4Doc* CSuriken_4View::GetDocument() const
   { return reinterpret_cast<CSuriken_4Doc*>(m_pDocument); }
#endif

