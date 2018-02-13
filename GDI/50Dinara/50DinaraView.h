
// 50DinaraView.h : interface of the CMy50DinaraView class
//

#pragma once


class CMy50DinaraView : public CView
{
protected: // create from serialization only
	CMy50DinaraView();
	DECLARE_DYNCREATE(CMy50DinaraView)

// Attributes
public:
	CMy50DinaraDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	void DrawBackground(CDC *pDC, CPoint ptCenter, int radius);
	void DrawCoin(CDC *pDC, CPoint ptCenter, int radius, CString strText, int fsizeText, CString strCoin, int fsizeCoin, COLORREF clrText);
	void SaveBMP(CString name, CDC *pDC, CPoint ptCenter, int radius);
	float toRad(float angle);
	void TranslateRotate(CDC *pDC,float x, float y, float angle,float distance);
	void Translate(CDC *pDC, float x, float y, bool right);
	void Rotate(CDC *pDC, float angle,bool right);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CMy50DinaraView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in 50DinaraView.cpp
inline CMy50DinaraDoc* CMy50DinaraView::GetDocument() const
   { return reinterpret_cast<CMy50DinaraDoc*>(m_pDocument); }
#endif

