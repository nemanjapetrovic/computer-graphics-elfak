
// Trouglovi_3View.h : interface of the CTrouglovi_3View class
//

#pragma once


class CTrouglovi_3View : public CView
{
protected: // create from serialization only
	CTrouglovi_3View();
	DECLARE_DYNCREATE(CTrouglovi_3View)

// Attributes
public:
	CTrouglovi_3Doc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	float toRad(float angle);
	void DrawTriangle(CDC* pDC);
	XFORM Reflect(float Sx, float Sy);
	XFORM Rotate(float a);
	XFORM Translate(float x, float y);

protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CTrouglovi_3View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Trouglovi_3View.cpp
inline CTrouglovi_3Doc* CTrouglovi_3View::GetDocument() const
   { return reinterpret_cast<CTrouglovi_3Doc*>(m_pDocument); }
#endif

