
// 50Dinara_2View.h : interface of the CMy50Dinara_2View class
//

#pragma once


class CMy50Dinara_2View : public CView
{
protected: // create from serialization only
	CMy50Dinara_2View();
	DECLARE_DYNCREATE(CMy50Dinara_2View)

// Attributes
public:
	CMy50Dinara_2Doc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	
	float toRad(float angle);
	void TranslateRotate(CDC *pDC, float x, float y, float angle, float distance);
	void Rotate(CDC *pDC, float angle, bool rightMultiply);
	void DrawBackground(CDC *pDC, CPoint ptCenter, int radius);
	void DrawCoin(CDC *pDC, CPoint ptCenter, int radius, CString strText, int fsizeText, CString strCoin, int fsizeCoin, COLORREF clrText);
	void SaveBMP(CString name, CDC *pDC, CPoint ptCenter, int radius);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CMy50Dinara_2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in 50Dinara_2View.cpp
inline CMy50Dinara_2Doc* CMy50Dinara_2View::GetDocument() const
   { return reinterpret_cast<CMy50Dinara_2Doc*>(m_pDocument); }
#endif

