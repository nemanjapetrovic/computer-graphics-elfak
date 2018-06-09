
// Trouglovi_2View.h : interface of the CTrouglovi_2View class
//

#pragma once


class CTrouglovi_2View : public CView
{
protected: // create from serialization only
	CTrouglovi_2View();
	DECLARE_DYNCREATE(CTrouglovi_2View)

// Attributes
public:
	CTrouglovi_2Doc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	XFORM Translate(float x, float y);
	XFORM Rotate(float a);
	XFORM Reflect(float Sx, float Sy);
	void DrawTriangle(CDC* pDC);
	void SaveImg();
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CTrouglovi_2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Trouglovi_2View.cpp
inline CTrouglovi_2Doc* CTrouglovi_2View::GetDocument() const
   { return reinterpret_cast<CTrouglovi_2Doc*>(m_pDocument); }
#endif

