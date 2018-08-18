
// Reduce_1View.h : interface of the CReduce_1View class
//

#pragma once


class CReduce_1View : public CView
{
protected: // create from serialization only
	CReduce_1View();
	DECLARE_DYNCREATE(CReduce_1View)

// Attributes
public:
	CReduce_1Doc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	CDC * ReduceSize();
	void TestRotate(CDC *pDC, bool right);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CReduce_1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Reduce_1View.cpp
inline CReduce_1Doc* CReduce_1View::GetDocument() const
   { return reinterpret_cast<CReduce_1Doc*>(m_pDocument); }
#endif

