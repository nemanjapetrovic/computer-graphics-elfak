
// Rep_1View.h : interface of the CRep_1View class
//

#pragma once


class CRep_1View : public CView
{
protected: // create from serialization only
	CRep_1View();
	DECLARE_DYNCREATE(CRep_1View)

// Attributes
public:
	CRep_1Doc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	void DrawTop(CDC *pDC, int size);
	void LoadIdentity(CDC *pDC);
	void Mirror(CDC *pDC, bool x, bool right);
	void Translate(CDC *pDC, double x, double y, bool right);
	void Rotate(CDC *pDC, double alpha, bool right);
	void DrawTop2(CDC *pDC, int size);
	void DrawTail(CDC *pDC, int size, int count, double alpha);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CRep_1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Rep_1View.cpp
inline CRep_1Doc* CRep_1View::GetDocument() const
   { return reinterpret_cast<CRep_1Doc*>(m_pDocument); }
#endif

