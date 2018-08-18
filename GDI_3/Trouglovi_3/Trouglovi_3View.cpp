
// Trouglovi_3View.cpp : implementation of the CTrouglovi_3View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Trouglovi_3.h"
#endif

#include "Trouglovi_3Doc.h"
#include "Trouglovi_3View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTrouglovi_3View

IMPLEMENT_DYNCREATE(CTrouglovi_3View, CView)

BEGIN_MESSAGE_MAP(CTrouglovi_3View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CTrouglovi_3View construction/destruction

CTrouglovi_3View::CTrouglovi_3View()
{
	// TODO: add construction code here

}

CTrouglovi_3View::~CTrouglovi_3View()
{
}

BOOL CTrouglovi_3View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CTrouglovi_3View drawing

void CTrouglovi_3View::OnDraw(CDC* pDC)
{
	CTrouglovi_3Doc* pDoc = GetDocument();
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

	//draw...

	//1
	XFORM translate1 = Translate(300, 300);
	XFORM reflect1 = Reflect(1.0, -1.0);
	XFORM out1;
	CombineTransform(&out1, &reflect1, &translate1);
	memDC->SetWorldTransform(&out1);
	DrawTriangle(memDC);
	memDC->SetWorldTransform(&form);

	//2
	XFORM translate2 = Translate(300, 300);
	XFORM rot2 = Rotate(90);
	XFORM refl2 = Reflect(-1.0, 1.0);
	XFORM out11, out22;
	CombineTransform(&out11, &rot2, &refl2);
	CombineTransform(&out22, &out11, &translate2);
	memDC->SetWorldTransform(&out22);
	DrawTriangle(memDC);
	memDC->SetWorldTransform(&form);

	//3
	XFORM translate3 = Translate(300, 300);
	XFORM rot3 = Rotate(90);
	XFORM out33;
	CombineTransform(&out33, &rot3, &translate3);
	memDC->SetWorldTransform(&out33);
	DrawTriangle(memDC);
	memDC->SetWorldTransform(&form);

	//4
	XFORM translate4 = Translate(300, 300);
	XFORM rot4 = Rotate(180);
	XFORM out44;
	CombineTransform(&out44, &rot4, &translate4);
	memDC->SetWorldTransform(&out44);
	DrawTriangle(memDC);
	memDC->SetWorldTransform(&form);
	//draw...

	memDC->SetWorldTransform(&form);
	memDC->SetGraphicsMode(oldMode);

	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), memDC, 0, 0, SRCCOPY);

	memDC->DeleteDC();
	delete memDC;
}

XFORM CTrouglovi_3View::Translate(float x, float y)
{
	XFORM form;

	form.eM11 = 1;
	form.eM12 = 0;
	form.eM21 = 0;
	form.eM22 = 1;

	form.eDx = x;
	form.eDy = y;

	return form;
}

XFORM CTrouglovi_3View::Rotate(float a)
{
	XFORM form;

	form.eM11 = cos(toRad(a));
	form.eM12 = sin(toRad(a));
	form.eM21 = -sin(toRad(a));
	form.eM22 = cos(toRad(a));

	form.eDx = 0;
	form.eDy = 0;

	return form;
}

XFORM CTrouglovi_3View::Reflect(float Sx, float Sy)
{
	XFORM form;
	
	form.eM11 = Sx;
	form.eM12 = 0;
	form.eM21 = 0;
	form.eM22 = Sy;

	form.eDx = 0;
	form.eDy = 0;

	return form;
}

void CTrouglovi_3View::DrawTriangle(CDC* pDC)
{
	CPen pen(PS_SOLID, 2, RGB(34, 177, 76));
	CPen *oldPen = pDC->SelectObject(&pen);

	CBrush brush;
	brush.CreateSolidBrush(RGB(68, 68, 68));
	CBrush *oldBrush = pDC->SelectObject(&brush);

	CPoint points[] {
		CPoint(0,0),
		CPoint(0,200),
		CPoint(100,0)
	};

	pDC->BeginPath();
	pDC->Polygon(points, 3);
	pDC->EndPath();
	pDC->StrokeAndFillPath();

	pDC->SelectObject(oldBrush);
	pDC->SelectObject(oldPen);
	pen.DeleteObject();
	brush.DeleteObject();
}

float CTrouglovi_3View::toRad(float angle) {
	return (angle * 3.14) / 180;
}
// CTrouglovi_3View printing

BOOL CTrouglovi_3View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTrouglovi_3View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTrouglovi_3View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CTrouglovi_3View diagnostics

#ifdef _DEBUG
void CTrouglovi_3View::AssertValid() const
{
	CView::AssertValid();
}

void CTrouglovi_3View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTrouglovi_3Doc* CTrouglovi_3View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTrouglovi_3Doc)));
	return (CTrouglovi_3Doc*)m_pDocument;
}
#endif //_DEBUG


// CTrouglovi_3View message handlers
