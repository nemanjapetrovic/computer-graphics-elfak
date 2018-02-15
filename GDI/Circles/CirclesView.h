
// CirclesView.h : interface of the CCirclesView class
//

#pragma once


class CCirclesView : public CView
{
protected: // create from serialization only
	CCirclesView();
	DECLARE_DYNCREATE(CCirclesView)

// Attributes
public:
	CCirclesDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	
	void Rotate(CDC *memDC, float angle, bool right);
	void Translate(CDC *memDC, int x, int y, bool right);
	void TranslateRotate(CDC *pDC, float x, float y, float angle, float distance);
	float toRad(float angle);
	
	void DrawMultiCircle(CDC *pDC, int radius, int nConc, COLORREF colFill, CString strText);
	void DrawFannyCircle(CDC *pDC, int radius, int nCricle, double dAlpha, int nCone, COLORREF colFillBig, COLORREF clFillSmall, CString strText);
	void DrawAndSavePicture(CDC *pDC, CString strPicture, int radius);
	
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CCirclesView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in CirclesView.cpp
inline CCirclesDoc* CCirclesView::GetDocument() const
   { return reinterpret_cast<CCirclesDoc*>(m_pDocument); }
#endif

