
// Cvet_3View.h : interface of the CCvet_3View class
//

#pragma once


class CCvet_3View : public CView
{
protected: // create from serialization only
	CCvet_3View();
	DECLARE_DYNCREATE(CCvet_3View)

// Attributes
public:
	CCvet_3Doc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	void DrawRosete(CDC *pDC, int x, int y, int size, int count);
	void TranslateRotate(CDC *pDC, int x, int y, float angle, float distance);
	void CreateTriangleBmp();

protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CCvet_3View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Cvet_3View.cpp
inline CCvet_3Doc* CCvet_3View::GetDocument() const
   { return reinterpret_cast<CCvet_3Doc*>(m_pDocument); }
#endif

