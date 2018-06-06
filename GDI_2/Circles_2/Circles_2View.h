
// Circles_2View.h : interface of the CCircles_2View class
//

#pragma once


class CCircles_2View : public CView
{
protected: // create from serialization only
	CCircles_2View();
	DECLARE_DYNCREATE(CCircles_2View)

// Attributes
public:
	CCircles_2Doc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	void DrawMultiCircle(CDC *pDC, int radius, int nConc, COLORREF colFill, CString strText);
	void DrawFannyCircle(CDC *pDC, int radius, int nCricle, double dAlpha, int nCone, COLORREF colFillBig, COLORREF clFillSmall, CString strText);
	void DrawAndSavePicture(CDC *pDC, CString strPicture, int radius);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CCircles_2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Circles_2View.cpp
inline CCircles_2Doc* CCircles_2View::GetDocument() const
   { return reinterpret_cast<CCircles_2Doc*>(m_pDocument); }
#endif

