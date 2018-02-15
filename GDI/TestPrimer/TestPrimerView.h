
// TestPrimerView.h : interface of the CTestPrimerView class
//

#pragma once


class CTestPrimerView : public CView
{
protected: // create from serialization only
	CTestPrimerView();
	DECLARE_DYNCREATE(CTestPrimerView)

// Attributes
public:
	CTestPrimerDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	
	void Rotate(CDC* pDC, float angle, bool rightMultiply);	
	void Translate(CDC* pDC, float dX, float dY, bool rightMultiply);
	void TranslateRotate(CDC* pDC, float dX, float dY, float angle, float distance);
	float toRad(float angle);

protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CTestPrimerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in TestPrimerView.cpp
inline CTestPrimerDoc* CTestPrimerView::GetDocument() const
   { return reinterpret_cast<CTestPrimerDoc*>(m_pDocument); }
#endif

