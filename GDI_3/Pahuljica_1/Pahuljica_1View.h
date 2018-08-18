
// Pahuljica_1View.h : interface of the CPahuljica_1View class
//

#pragma once


class CPahuljica_1View : public CView
{
protected: // create from serialization only
	CPahuljica_1View();
	DECLARE_DYNCREATE(CPahuljica_1View)

// Attributes
public:
	CPahuljica_1Doc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);


	void SetTransform(CDC *pDC, float cx, float cy, float alpha, XFORM *oldForm);
	void DrawSnowflakeCrystal(CDC *pDC, float cx, float cy, float h, float w, float alpha, COLORREF borderColor, COLORREF fillColor);
	void DrawSnowflakeArm(CDC *pDC, float cx, float cy, float angle, float * pattern, int n, COLORREF borderColor, COLORREF fillColor);
	void DrawSnowflake(CDC *pDC, float cx, float cy, float * pattern, int n, COLORREF borderColor, COLORREF fillColor);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CPahuljica_1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Pahuljica_1View.cpp
inline CPahuljica_1Doc* CPahuljica_1View::GetDocument() const
   { return reinterpret_cast<CPahuljica_1Doc*>(m_pDocument); }
#endif

