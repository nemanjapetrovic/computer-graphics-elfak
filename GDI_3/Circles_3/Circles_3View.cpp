
// Circles_3View.cpp : implementation of the CCircles_3View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Circles_3.h"
#endif

#include "Circles_3Doc.h"
#include "Circles_3View.h"
#include "DImage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCircles_3View

IMPLEMENT_DYNCREATE(CCircles_3View, CView)

BEGIN_MESSAGE_MAP(CCircles_3View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CCircles_3View construction/destruction

CCircles_3View::CCircles_3View()
{
	// TODO: add construction code here

}

CCircles_3View::~CCircles_3View()
{
}

BOOL CCircles_3View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CCircles_3View drawing

void CCircles_3View::OnDraw(CDC* pDC)
{
	CCircles_3Doc* pDoc = GetDocument();
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

	int oldMode = memDC->SetGraphicsMode(GM_ADVANCED);
	XFORM form;
	memDC->GetWorldTransform(&form);

	//draw..
	int radius = 200;

	DrawFanyCircle(memDC, radius, 8, 90, 4, RGB(255, 255, 255), RGB(255,255,255), (CString)"YES");
	SavePicture(memDC, (CString)"screenshot.bmp", radius);
	//draw..

	memDC->SetWorldTransform(&form);
	memDC->SetGraphicsMode(oldMode);

	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), memDC, 0, 0, SRCCOPY);

	memDC->DeleteDC();
	delete memDC;
}

void CCircles_3View::DrawMultiCircle(CDC *pDC, int radius, int nConc, COLORREF colFill, CString strText)
{
	if (nConc < 1 || nConc > 10) {
		exit(-1);
	}

	CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
	CPen *oldPen = pDC->SelectObject(&pen);		

	//krugovi
	int tmpRadius = radius;
	int tmpR = GetRValue(colFill);
	int tmpG = GetGValue(colFill);
	int tmpB = GetBValue(colFill);
	for (int i = 0; i < nConc; i++) {
		CBrush brush;
		brush.CreateSolidBrush(RGB(tmpR,tmpG,tmpB));
		CBrush *oldBrush = pDC->SelectObject(&brush);

		CRect elipse(-tmpRadius, -tmpRadius, tmpRadius, tmpRadius);
		pDC->Ellipse(elipse);
		
		tmpRadius = tmpRadius - (tmpRadius * 0.10);
		tmpR = tmpR - (tmpR*0.05);
		tmpG = tmpG - (tmpG*0.05);
		tmpB = tmpB - (tmpB*0.05);

		pDC->SelectObject(oldBrush);
		brush.DeleteObject();
	}

	//text
	CFont font;
	font.CreateFont(12, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, (CString)"Arial");
	CFont *oldFont = pDC->SelectObject(&font);

	int oldTextMode = pDC->SetBkMode(TRANSPARENT);
	int oldTextAlign = pDC->SetTextAlign(TA_CENTER);
	COLORREF oldCol = pDC->SetTextColor(RGB(0, 0, 0));

	pDC->TextOut(0, -12 / 2, strText);

	pDC->SetTextColor(oldCol);
	pDC->SetTextAlign(oldTextAlign);
	pDC->SetBkMode(oldTextMode);
	pDC->SelectObject(oldFont);
	pDC->SelectObject(oldPen);
	
	pen.DeleteObject();	
	font.DeleteObject();
}

void CCircles_3View::DrawFanyCircle(CDC *pDC, int radius, int nCircle, double dAlpha, int nConc, COLORREF colFillBig, COLORREF colFillSmall, CString strText)
{
	//veliki krug
	DrawMultiCircle(pDC, radius, nConc, colFillBig, strText);
	
	//mali krugovi
	float angle = 360 / nCircle;
	float tmpAngle = 0;
	for (int i = 0; i < nCircle; i++) 
	{
		XFORM form;
		pDC->GetWorldTransform(&form);

		TranslateRotate(pDC, 0, 0, tmpAngle, radius);
		Rotate(pDC, -tmpAngle + dAlpha, false);

		CString str;
		str.Format(_T("%d"), (i + 1));
		DrawMultiCircle(pDC, 0.15*radius, 2, colFillSmall, (CString)str);

		pDC->SetWorldTransform(&form);

		tmpAngle += angle;
	}
}

void CCircles_3View::SavePicture(CDC *pDC, CString pic, int radius)
{
	int width = (radius * 2) + (2 * radius * 0.2);
	int height = (radius * 2) + (2 * radius * 0.2);

	CDC *memDC = new CDC();
	memDC->CreateCompatibleDC(NULL);

	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC, width, height);
	memDC->SelectObject(&bmp);

	memDC->BitBlt(0, 0, width, height, pDC, -width /2 , -height / 2, SRCCOPY);

	DImage *img = new DImage(bmp);
	img->Save(pic);

	delete img;

	memDC->DeleteDC();
	delete memDC;
}

float CCircles_3View::toRad(float angle)
{
	return (angle * 3.14) / 180;
}

void CCircles_3View::Rotate(CDC *pDC, float angle, bool right)
{
	XFORM form;
	form.eM11 = cos(toRad(angle));
	form.eM12 = sin(toRad(angle));
	form.eM21 = -sin(toRad(angle));
	form.eM22 = cos(toRad(angle));

	form.eDx = 0;
	form.eDy = 0;

	if (right)
		pDC->ModifyWorldTransform(&form, MWT_RIGHTMULTIPLY);
	else
		pDC->ModifyWorldTransform(&form, MWT_LEFTMULTIPLY);
}

void CCircles_3View::TranslateRotate(CDC *pDC, float x, float y, float angle, float distance)
{
	XFORM form;
	form.eM11 = cos(toRad(angle));
	form.eM12 = sin(toRad(angle));
	form.eM21 = -sin(toRad(angle));
	form.eM22 = cos(toRad(angle));

	form.eDx = x + (distance *cos(toRad(angle)));
	form.eDy = y + (distance * sin(toRad(angle)));

	pDC->SetWorldTransform(&form);
}


// CCircles_3View printing

BOOL CCircles_3View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCircles_3View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCircles_3View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CCircles_3View diagnostics

#ifdef _DEBUG
void CCircles_3View::AssertValid() const
{
	CView::AssertValid();
}

void CCircles_3View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCircles_3Doc* CCircles_3View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCircles_3Doc)));
	return (CCircles_3Doc*)m_pDocument;
}
#endif //_DEBUG


// CCircles_3View message handlers
