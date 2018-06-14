
// Cvet_2View.h : interface of the CCvet_2View class
//

#pragma once


class CCvet_2View : public CView
{
protected: // create from serialization only
	CCvet_2View();
	DECLARE_DYNCREATE(CCvet_2View)

// Attributes
public:
	CCvet_2Doc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	void Rotate(CDC *pDC, float angle, bool right);
	void TranslateRotate(CDC *pDC, float x, float y, float angle, float distance);
	float toRad(float angle);

	void DrawRosete(CDC *pDC, int x, int y, int size, int count);
	void CreateTriangleBmp(CString fileName);

protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CCvet_2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Cvet_2View.cpp
inline CCvet_2Doc* CCvet_2View::GetDocument() const
   { return reinterpret_cast<CCvet_2Doc*>(m_pDocument); }
#endif

