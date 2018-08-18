
// Rep_1View.cpp : implementation of the CRep_1View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Rep_1.h"
#endif

#include "Rep_1Doc.h"
#include "Rep_1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRep_1View

IMPLEMENT_DYNCREATE(CRep_1View, CView)

BEGIN_MESSAGE_MAP(CRep_1View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CRep_1View construction/destruction

CRep_1View::CRep_1View()
{
	// TODO: add construction code here

}

CRep_1View::~CRep_1View()
{
}

BOOL CRep_1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CRep_1View drawing

void CRep_1View::OnDraw(CDC* pDC)
{
	CRep_1Doc* pDoc = GetDocument();
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
	Translate(memDC, 200, 200, false);
	DrawTail(memDC, 25, 6, 20);
	//draw..

	memDC->SetWorldTransform(&form);
	memDC->SetGraphicsMode(oldMode);

	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), memDC, 0, 0, SRCCOPY);

	memDC->DeleteDC();
	delete memDC;
}

void CRep_1View::DrawTop(CDC *pDC, int size)
{
	CPen pen(PS_SOLID, 2, RGB(0, 0, 0));
	CPen *oldPen = pDC->SelectObject(&pen);

	CBrush brush;
	brush.CreateSolidBrush(RGB(255,127,39));
	CBrush *oldBrush = pDC->SelectObject(&brush);

	int archDir = pDC->SetArcDirection(AD_COUNTERCLOCKWISE);

	int r = (size / 4);
	
	pDC->BeginPath();
	pDC->Arc(CRect(100-r, 100 -r, 100+0, 100+r), CPoint(100+0, 100 -r), CPoint(100+0, 100+r));

	pDC->MoveTo(100 + 0, 100 - r);
	pDC->ArcTo(CRect(100 + 0, 100 - r, 100 + r, 100 + r + r), CPoint(100 + 0, 100 - r), CPoint(100 + 0, 100 + r + r));

	pDC->MoveTo(100 + 0, 100 + r + r);
	pDC->SetArcDirection(AD_CLOCKWISE);
	pDC->ArcTo(CRect(100 + 0, 100 + r, 100 + r, 100 + r + r), CPoint(100 + 0, 100 + r + r), CPoint(100 + 0, 100 + r));
	pDC->EndPath();
	pDC->StrokeAndFillPath();

	
	pDC->SelectObject(oldPen);
	pDC->SelectObject(oldBrush);
	pen.DeleteObject();
	brush.DeleteObject();
}

void CRep_1View::LoadIdentity(CDC *pDC)
{
	XFORM form;

	form.eM11 = 1;
	form.eM12 = 0;
	form.eM21 = 0;
	form.eM22 = 1;
	form.eDx = 0;
	form.eDy = 0;

	pDC->SetWorldTransform(&form);
}

void CRep_1View::Mirror(CDC *pDC, bool x, bool right)
{
	XFORM form;

	form.eM11 = x;
	form.eM12 = 0;
	form.eM21 = 0;
	form.eM22 = 1;
	form.eDx = 0;
	form.eDy = 0;

	if (right) {
		pDC->ModifyWorldTransform(&form, MWT_RIGHTMULTIPLY);
	}
	else {
		pDC->ModifyWorldTransform(&form, MWT_LEFTMULTIPLY);
	}
}

void CRep_1View::Translate(CDC *pDC, double x, double y, bool right)
{
	XFORM form;

	form.eM11 = 1;
	form.eM12 = 0;
	form.eM21 = 0;
	form.eM22 = 1;
	form.eDx = x;
	form.eDy = y;

	if (right) {
		pDC->ModifyWorldTransform(&form, MWT_RIGHTMULTIPLY);
	}
	else {
		pDC->ModifyWorldTransform(&form, MWT_LEFTMULTIPLY);
	}
}

void CRep_1View::Rotate(CDC *pDC, double alpha, bool right)
{
	float rot = (alpha*3.14) / 180;
	XFORM form;

	form.eM11 = cos(rot);
	form.eM12 = sin(rot);
	form.eM21 = -sin(rot);
	form.eM22 = cos(rot);
	form.eDx = 0;
	form.eDy = 0;

	if (right) {
		pDC->ModifyWorldTransform(&form, MWT_RIGHTMULTIPLY);
	}
	else {
		pDC->ModifyWorldTransform(&form, MWT_LEFTMULTIPLY);
	}
}

void CRep_1View::DrawTop2(CDC *pDC, int size)
{
	Rotate(pDC, 90, true);
	Mirror(pDC, 1, true);
	DrawTop(pDC, size);
}

void CRep_1View::DrawTail(CDC *pDC, int size, int count, double alpha)
{
	CPen pen(PS_SOLID, 2, RGB(0, 0, 0));
	CPen *oldPen = pDC->SelectObject(&pen);

	CBrush brush;
	brush.CreateSolidBrush(RGB(255, 127, 39));
	CBrush *oldBrush = pDC->SelectObject(&brush);

	int x = 0, y = 0;
	int w = size * 2;
	int h = size;
	int tmpx = 0;
	for (int i = 0; i < count; i++) {
		
		Translate(pDC, w, 0, false);
		Rotate(pDC, -alpha, false);
		
		pDC->Ellipse(CRect(x - w / 2, y - h / 2, x + w / 2, y + h / 2));		
	}

	pDC->SelectObject(oldPen);
	pDC->SelectObject(oldBrush);
	pen.DeleteObject();
	brush.DeleteObject();
}



// CRep_1View printing

BOOL CRep_1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CRep_1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CRep_1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CRep_1View diagnostics

#ifdef _DEBUG
void CRep_1View::AssertValid() const
{
	CView::AssertValid();
}

void CRep_1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CRep_1Doc* CRep_1View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRep_1Doc)));
	return (CRep_1Doc*)m_pDocument;
}
#endif //_DEBUG


// CRep_1View message handlers
