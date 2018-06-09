
// Sat_2View.h : interface of the CSat_2View class
//

#pragma once


class CSat_2View : public CView
{
protected: // create from serialization only
	CSat_2View();
	DECLARE_DYNCREATE(CSat_2View)

// Attributes
public:
	CSat_2Doc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	float toRad(float angle);
	void TranslateRotate(CDC *pDC, float x, float y, float angle, float distance);
	void Rotate(CDC *pDC, float angle, bool right);
	void DrawNum(CDC *pDC);
	void DrawH(CDC * pDC);
	void DrawM(CDC * pDC);
	void DrawS(CDC * pDC);
	void DrawMarks(CDC *pDC);
	void DrawNeedles(CDC * pDC, int sati, int  minuti, int sekunde);
	void SaveClock(CString name);
	//void DrawClock(int sati,int minuti,int sekunde); to je funkcija DrawScene		
	
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CSat_2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Sat_2View.cpp
inline CSat_2Doc* CSat_2View::GetDocument() const
   { return reinterpret_cast<CSat_2Doc*>(m_pDocument); }
#endif

