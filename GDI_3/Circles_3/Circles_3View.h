
// Circles_3View.h : interface of the CCircles_3View class
//

#pragma once


class CCircles_3View : public CView
{
protected: // create from serialization only
	CCircles_3View();
	DECLARE_DYNCREATE(CCircles_3View)

// Attributes
public:
	CCircles_3Doc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	void DrawMultiCircle(CDC *pDC, int radius, int nConc, COLORREF colFill, CString strText);
	void DrawFanyCircle(CDC *pDC, int radius, int nCircle, double dAlpha, int nConc, COLORREF colFillBig, COLORREF colFillSmall, CString strText);
	void SavePicture(CDC *pDC, CString pic, int radius);
	float toRad(float angle);
	void Rotate(CDC *pDC, float angle, bool right);
	void TranslateRotate(CDC *pDC, float x, float y, float angle, float distance);

protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CCircles_3View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Circles_3View.cpp
inline CCircles_3Doc* CCircles_3View::GetDocument() const
   { return reinterpret_cast<CCircles_3Doc*>(m_pDocument); }
#endif

