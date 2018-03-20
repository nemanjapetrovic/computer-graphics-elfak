
// GLKView.h : interface of the CGLKView class
//

#pragma once

#include "GLRenderer.h"

class CGLKView : public CView
{
protected: // create from serialization only
	CGLKView();
	DECLARE_DYNCREATE(CGLKView)

// Attributes
public:
	CGLKDoc* GetDocument() const;

protected:
	CGLRenderer m_glRenderer;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CGLKView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual void OnInitialUpdate();
};

#ifndef _DEBUG  // debug version in GLKView.cpp
inline CGLKDoc* CGLKView::GetDocument() const
   { return reinterpret_cast<CGLKDoc*>(m_pDocument); }
#endif

