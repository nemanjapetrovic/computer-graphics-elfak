
// SatView.h : interface of the CSatView class
//

#pragma once


class CSatView : public CView
{
protected: // create from serialization only
	CSatView();
	DECLARE_DYNCREATE(CSatView)

// Attributes
public:
	CSatDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	
	void Translate(CDC *pDC, int x, int y, bool right);
	void TranslateRotate(CDC *pDC, int x, int y, float angle, int distance);
	void Rotate(CDC *pDC, float angle, bool right);
	float toRad(float angle);
	
	void DrawMarks(CDC *pDC, int distance, int width, int height);	
	void DrawNum(CDC *pDC, int distance);
	void SaveClock(CString name, int radius);
	void DrawS(CDC *pDC);
	void DrawM(CDC *pDC);
	void DrawH(CDC *pDC);
	void DrawNeedles(CDC *pDC,int sati,int minuti,int sekunde);
	void DrawClock(CDC *pDC, int sati,int minuti,int sekunde, int clockSize);
	
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CSatView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in SatView.cpp
inline CSatDoc* CSatView::GetDocument() const
   { return reinterpret_cast<CSatDoc*>(m_pDocument); }
#endif

