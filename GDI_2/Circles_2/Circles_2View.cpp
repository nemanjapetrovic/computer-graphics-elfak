
// Circles_2View.cpp : implementation of the CCircles_2View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Circles_2.h"
#endif

#include "Circles_2Doc.h"
#include "Circles_2View.h"
#include "DImage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCircles_2View

IMPLEMENT_DYNCREATE(CCircles_2View, CView)

BEGIN_MESSAGE_MAP(CCircles_2View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CCircles_2View construction/destruction

CCircles_2View::CCircles_2View()
{
	// TODO: add construction code here

}

CCircles_2View::~CCircles_2View()
{
}

BOOL CCircles_2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CCircles_2View drawing

void CCircles_2View::OnDraw(CDC* pDC)
{
	CCircles_2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here

	CRect rect;
	GetClientRect(&rect);

	CDC *memDC = new CDC();
	memDC->CreateCompatibleDC(pDC);

	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	memDC->SelectObject(&bmp);

	int oldmode = memDC->SetGraphicsMode(GM_ADVANCED);
	XFORM form;
	memDC->GetWorldTransform(&form);

	//draw..
	DrawAndSavePicture(memDC, (CString) "bla.bmp", 200);
	//draw..
	
	memDC->SetWorldTransform(&form);
	memDC->SetGraphicsMode(oldmode);

	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), memDC, 0, 0, SRCCOPY);

	memDC->DeleteDC();
	delete memDC;
}

void CCircles_2View::DrawMultiCircle(CDC *pDC, int radius, int nConc, COLORREF colFill, CString strText)
{
	if (nConc < 1 || nConc > 10) {
		exit(-1);
	}
	
	float tmpRadius = radius;
	float r = GetRValue(colFill);
	float g = GetGValue(colFill);
	float b = GetBValue(colFill);

	CFont font;
	font.CreateFont(12, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, (CString)"Arial");
	
	int oldTextAlign = pDC->SetTextAlign(TA_CENTER);
	int oldBkMode = pDC->SetBkMode(TRANSPARENT);
	COLORREF oldColor = pDC->SetTextColor(RGB(0, 0, 0));
	CFont *oldFont = pDC->SelectObject(&font);
	
	for (int i = 0; i < nConc; i++) 
	{
		CBrush brush;
		brush.CreateSolidBrush(RGB(r, g, b));
		CBrush *oldBrush = pDC->SelectObject(&brush);
		
		pDC->Ellipse(CRect(-tmpRadius, -tmpRadius, tmpRadius, tmpRadius));
		pDC->TextOut(0, -6, strText);

		tmpRadius = tmpRadius - (tmpRadius * 0.1);
		r = r - (r * 0.05);
		g = g - (g * 0.05);
		b = b - (b * 0.05);

		pDC->SelectObject(oldBrush);
		brush.DeleteObject();
	}

	pDC->SelectObject(oldFont);
	pDC->SetTextColor(oldColor);
	pDC->SetBkMode(oldBkMode);
	pDC->SetTextAlign(oldTextAlign);
	font.DeleteObject();
}

void CCircles_2View::DrawFannyCircle(CDC *pDC, int radius, int nCricle, double dAlpha, int nCone, COLORREF colFillBig, COLORREF clFillSmall, CString strText)
{
	// veliki krug
	
	DrawMultiCircle(pDC, radius, nCone, colFillBig, strText);

	// mali krugovi	
	float angle = 360 / nCricle;
	float tmpAngle = 0;
	int smallRadius = 0.05 * radius;
	for (int i = 0; i < nCricle; i++) 
	{	
		CString broj;
		broj.Format(_T("%d"), i++);

		XFORM form;
		pDC->GetWorldTransform(&form);
		
		TranslateRotate(pDC, 0, 0, tmpAngle, radius);
		Rotate(pDC, dAlpha, false);
		DrawMultiCircle(pDC, smallRadius, 2, clFillSmall, broj);

		tmpAngle += angle;
		pDC->SetWorldTransform(&form);
	}
}

void CCircles_2View::DrawAndSavePicture(CDC *pDC, CString strPicture, int radius)
{	
	int tmpRadius = radius * 2;
	int width = tmpRadius + (tmpRadius * 0.2);
	int height = width;

	CDC *memDC = new CDC();
	memDC->CreateCompatibleDC(NULL);

	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC, width, height);
	memDC->SelectObject(&bmp);

	DrawFannyCircle(pDC, radius, 6, 270, 4, RGB(255, 255, 255), RGB(65,122,234), (CString)"blaTruc");	

	memDC->BitBlt(0, 0, width, height, pDC, -width / 2, -height / 2, SRCCOPY);

	DImage img(bmp);
	img.Save(strPicture);

	memDC->DeleteDC();
	delete memDC;
}

void CCircles_2View::TranslateRotate(CDC * pDC, float x, float y, float angle, float distance)
{
	XFORM form;
	form.eM11 = cos(toRad(angle));
	form.eM12 = sin(toRad(angle));
	form.eM21 = -sin(toRad(angle));
	form.eM22 = cos(toRad(angle));

	form.eDx = x + (distance * cos(toRad(angle)));
	form.eDy = y + (distance * sin(toRad(angle)));

	pDC->SetWorldTransform(&form);
}

void CCircles_2View::Rotate(CDC* pDC, float angle, bool right)
{
	XFORM form;
	form.eM11 = cos(toRad(angle));
	form.eM12 = sin(toRad(angle));
	form.eM21 = -sin(toRad(angle));
	form.eM22 = cos(toRad(angle));

	form.eDx = 0;
	form.eDy = 0;

	if (right) {
		pDC->ModifyWorldTransform(&form, MWT_RIGHTMULTIPLY);
	}
	else
	{
		pDC->ModifyWorldTransform(&form, MWT_LEFTMULTIPLY);
	}
}

float CCircles_2View::toRad(float angle)
{
	return (angle * 3.14) / 180;
}


BOOL CCircles_2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCircles_2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCircles_2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CCircles_2View diagnostics

#ifdef _DEBUG
void CCircles_2View::AssertValid() const
{
	CView::AssertValid();
}

void CCircles_2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCircles_2Doc* CCircles_2View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCircles_2Doc)));
	return (CCircles_2Doc*)m_pDocument;
}
#endif //_DEBUG


// CCircles_2View message handlers
