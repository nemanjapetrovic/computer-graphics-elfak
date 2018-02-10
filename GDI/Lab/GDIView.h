
// GDIView.h : interface of the CGDIView class
//

#pragma once


class CGDIView : public CView
{
protected: // create from serialization only
	CGDIView();
	DECLARE_DYNCREATE(CGDIView)

	// Attributes
public:
	CGDIDoc* GetDocument() const;

	// Operations
public:
	// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	//---------------------
	//My functions
	//---------------------

	//Init for drawing
	void ViewInit(CDC* pDC);

	//Sharp windows
	void DrawLeftWindow(CDC* pDC, CRect rect);
	void DrawCenterWindow(CDC* pDC, CRect rect);
	void DrawRightWindow(CDC* pDC, CRect rect);
	//Sharp Dashboard
	void DrawDashboard(CDC* pDC, CRect rect);

	//Smooth window
	void DrawSmoothWindows(CDC* pDC, CRect rect);
	//Smooth dashboard
	void DrawSmoothDashbouard(CDC* pDC, CRect rect);

	//Central instruments
	void DrawDataInstruments(CDC* pDC, CRect rect);

	//Other circle instruments
	void DrawAnyWatch(CDC* pDC, CRect rect, CRect rcWatch, int nNotch, CString arsValues[], int nValues, double dAngleStart, double dAngleStop, int typeNeedle, double dAngleNeedle);
	void DrawWatchTilt(CDC* pDC, CRect rect, CRect rcWatch, double dAngleTilt);
	void DrawFuelWatch(CDC* pDC, CRect rcView, CRect rcWatch, double ardProportion[], int nParts, COLORREF arClrProportion[], double dAngleNeedle);

	//Needles
	void DrawNeedle(CDC* pDC, CRect rcView, CRect rcWatch, double dAngleNeedle, int typeNeedle);
	HENHMETAFILE CreateNeedleFuel(CDC* pDC, CRect rcView);
	HENHMETAFILE CreateNeedleStandrad(CDC* pDC, CRect rcView);
	HENHMETAFILE CreateNeedlePlane(CDC* pDC, CRect rcView);

	//Bitmaps
	void DrawMap(CDC* pDC, CRect rect, CRect rcMap, CString strImage);
	void DrawSky(CDC* pDC, CRect rcView, double dAngle, CString strImage);
	void DrawPlane(CDC* pDC, CRect rcView, CSize szOffset, double dScale, CString strImage);

	//Tranform
	void NoTransform(CDC* pDC);
	void Translate(CDC* pDC, int x, int y);
	void Rotate(CDC* pDC, double angle);
	void TranslateRotate(CDC* pDC, double angle, int x, int y);

	//Lab 03
	void ChangeImage(CBitmap& image, double  dBrightness, double dContrast);

protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	// Implementation
public:
	virtual ~CGDIView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // debug version in GDIView.cpp
inline CGDIDoc* CGDIView::GetDocument() const
{
	return reinterpret_cast<CGDIDoc*>(m_pDocument);
}
#endif

