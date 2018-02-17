
// TrougloviView.h : interface of the CTrougloviView class
//

#pragma once


class CTrougloviView : public CView
{
protected: // create from serialization only
	CTrougloviView();
	DECLARE_DYNCREATE(CTrougloviView)

// Attributes
public:
	CTrougloviDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	
	XFORM Translate(float x, float y);
	XFORM Rotate(float a);
	XFORM Reflect(float Sx, float Sy);
	void DrawTriangle(CDC* pDC);
	float toRad(float angle);
	
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CTrougloviView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in TrougloviView.cpp
inline CTrougloviDoc* CTrougloviView::GetDocument() const
   { return reinterpret_cast<CTrougloviDoc*>(m_pDocument); }
#endif

