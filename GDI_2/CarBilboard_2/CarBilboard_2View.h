
// CarBilboard_2View.h : interface of the CCarBilboard_2View class
//

#pragma once


class CCarBilboard_2View : public CView
{
protected: // create from serialization only
	CCarBilboard_2View();
	DECLARE_DYNCREATE(CCarBilboard_2View)

// Attributes
public:
	CCarBilboard_2Doc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	void DrawBilboards(CDC *pDC);
	void DrawCar(CDC *pDC);
	float toRad(float angle);
	void TranslateAndRotate(CDC *pDC, float x, float y, float angle);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CCarBilboard_2View();
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

#ifndef _DEBUG  // debug version in CarBilboard_2View.cpp
inline CCarBilboard_2Doc* CCarBilboard_2View::GetDocument() const
   { return reinterpret_cast<CCarBilboard_2Doc*>(m_pDocument); }
#endif

