
// Tocak_1View.cpp : implementation of the CTocak_1View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Tocak_1.h"
#endif

#include "Tocak_1Doc.h"
#include "Tocak_1View.h"
#include "DImage.h"
#include "MipMap.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTocak_1View

IMPLEMENT_DYNCREATE(CTocak_1View, CView)

BEGIN_MESSAGE_MAP(CTocak_1View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CTocak_1View construction/destruction
CMipMap *mipmap;
DImage *img;
CTocak_1View::CTocak_1View()
{
	// TODO: add construction code here
	img = new DImage();
	img->Load((CString)"tocak.png");

	mipmap = new CMipMap((CString)"bg.jpg");
}

CTocak_1View::~CTocak_1View()
{
	delete img;
	delete mipmap;
}

BOOL CTocak_1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CTocak_1View drawing

void CTocak_1View::OnDraw(CDC* pDC)
{
	CTocak_1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	/*
		Zadatak pod a,b iscrtavanje tocka
	*/

	/*
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

	//draw...
	DrawWP(memDC, 120, 100, 20, 500, 25, 100);
	//draw..

	memDC->SetWorldTransform(&form);
	memDC->SetGraphicsMode(oldMode);
	
	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), memDC, 0, 0, SRCCOPY);

	memDC->DeleteDC();
	delete memDC;
*/
	/*
		Poziv CMipMap klase za iscrtavanje zadatka pod C (sve moguce slike umanjenje za w/2 i h/2 do w>1 && h>1)
	*/
	
	CRect rect;
	GetClientRect(&rect);

	CDC *memDC = mipmap->DrawToDC(pDC, rect);

	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), memDC, 0, 0, SRCCOPY);

	memDC->DeleteDC();
	delete memDC;
	
	
}


void CTocak_1View::DrawWheel(CDC *pDC, double r1, double r2, double w) 
{
	CPen pen(PS_SOLID, 1, RGB(255,255,255));
	CPen *oldPen = pDC->SelectObject(&pen);
	CBrush brush;
	brush.CreateSolidBrush(RGB(68, 68, 68));
	CBrush *oldBrush = pDC->SelectObject(&brush);

	//r1 spoljasnji
	pDC->Ellipse(-r1, -r1, r1, r1);

	//r2 unutrasnji
	pDC->SelectStockObject(NULL_BRUSH);
	pDC->Ellipse(-r2, -r2, r2, r2);

	//precke
	pDC->SelectObject(&brush);
	CRect precka(-r2 , -w / 2, r2, w / 2);
	float angle = 360 / 3;
	float tmpAngle = 90;
	for (int i = 0; i < 3; i++) {
		XFORM form;
		pDC->GetWorldTransform(&form);

		Rotate(pDC, tmpAngle, false);
		pDC->Rectangle(precka);

		pDC->SetWorldTransform(&form);

		tmpAngle += angle;
	}

	pDC->SelectObject(oldBrush);
	pDC->SelectObject(oldPen);
	brush.DeleteObject();
	pen.DeleteObject();
}

void CTocak_1View::DrawWP(CDC *pDC, double r1, double r2, double w, double L, double alpha, double d) 
{
	CRect rect;
	GetClientRect(&rect);

	CPen pen(PS_SOLID, 1, RGB(255, 255, 255));
	CPen *oldPen = pDC->SelectObject(&pen);
	CBrush brush;
	brush.CreateSolidBrush(RGB(68, 68, 68));
	CBrush *oldBrush = pDC->SelectObject(&brush);

	//postolje
	float nasp = tan((alpha * 3.14) / 180) * L;

	pDC->BeginPath();
	pDC->MoveTo(0, rect.Height());
	pDC->LineTo(L, rect.Height());
	pDC->LineTo(0, rect.Height() - nasp);
	pDC->LineTo(0, rect.Height());
	pDC->EndPath();
	pDC->StrokeAndFillPath();

	float tmpNalegla = cos((alpha * 3.14) / 180) * d;	
	float tmpNaspramna = tan((alpha * 3.14) / 180) * tmpNalegla;
	XFORM form;
	pDC->GetWorldTransform(&form);
	
	float rotAngle = d / (2 * 3.14);
	Rotate(pDC, rotAngle, false);
	Translate(pDC, tmpNalegla, rect.Height() - nasp - r1 + tmpNaspramna, true);	

	DrawWheel(pDC, r1, r2, w);

	pDC->SetWorldTransform(&form);		  

	pDC->SelectObject(oldBrush);
	pDC->SelectObject(oldPen);
	brush.DeleteObject();
	pen.DeleteObject();
}

void CTocak_1View::Translate(CDC *pDC, float x, float y, bool right)
{
	XFORM form;
	form.eM11 = 1;
	form.eM12 = 0;
	form.eM21 = 0;
	form.eM22 = 1;

	form.eDx = x;
	form.eDy = y;

	if (right)
		pDC->ModifyWorldTransform(&form, MWT_RIGHTMULTIPLY);
	else
		pDC->ModifyWorldTransform(&form, MWT_LEFTMULTIPLY);
}


void CTocak_1View::Rotate(CDC* pDC, float angle, bool right)
{
	float tmpAngle = (angle * 3.14) / 180;
	XFORM form;
	form.eM11 = cos(tmpAngle);
	form.eM12 = sin(tmpAngle);
	form.eM21 = -sin(tmpAngle);
	form.eM22 = cos(tmpAngle);

	form.eDx = 0;
	form.eDy = 0;

	if (right)
		pDC->ModifyWorldTransform(&form, MWT_RIGHTMULTIPLY);
	else
		pDC->ModifyWorldTransform(&form, MWT_LEFTMULTIPLY);
}

BOOL CTocak_1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTocak_1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTocak_1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CTocak_1View diagnostics

#ifdef _DEBUG
void CTocak_1View::AssertValid() const
{
	CView::AssertValid();
}

void CTocak_1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTocak_1Doc* CTocak_1View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTocak_1Doc)));
	return (CTocak_1Doc*)m_pDocument;
}
#endif //_DEBUG


// CTocak_1View message handlers
