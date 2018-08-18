
// Sat_3View.h : interface of the CSat_3View class
//

#pragma once


class CSat_3View : public CView
{
protected: // create from serialization only
	CSat_3View();
	DECLARE_DYNCREATE(CSat_3View)

// Attributes
public:
	CSat_3Doc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	float toRad(float angle);
	void TranslateRotate(CDC *pDC, float x, float y, float angle, float distance);
	void Translate(CDC *pDC, float x, float y, bool right);
	void Rotate(CDC *pDC, float angle, bool right);
	void DrawNum(CDC *pDC, int x, int y);
	void DrawMarks(CDC *pDC, int x, int y);
	void DrawH(CDC *pDC, int x, int y);
	void DrawS(CDC *pDC, int x, int y);
	void DrawM(CDC *pDC, int x, int y);
	void DrawNeedles(CDC *pDC, int x, int y, int sati, int minuti, int sekunde);
	void SaveClock(int x, int y);

protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CSat_3View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Sat_3View.cpp
inline CSat_3Doc* CSat_3View::GetDocument() const
   { return reinterpret_cast<CSat_3Doc*>(m_pDocument); }
#endif

