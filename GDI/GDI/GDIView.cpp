
// GDIView.cpp : implementation of the CGDIView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "GDI.h"
#endif

#include "GDIDoc.h"
#include "GDIView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGDIView

IMPLEMENT_DYNCREATE(CGDIView, CView)

BEGIN_MESSAGE_MAP(CGDIView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CGDIView construction/destruction

CGDIView::CGDIView()
{
	// TODO: add construction code here

}

CGDIView::~CGDIView()
{
}

BOOL CGDIView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CGDIView drawing

void CGDIView::OnDraw(CDC* pDC)
{
	CGDIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	ViewInit(pDC);
}

void CGDIView::ViewInit(CDC* pDC)
{
	CRect rect;
	GetClientRect(&rect);
	pDC->SetMapMode(MM_ISOTROPIC);
	pDC->SetWindowExt(rect.right, -rect.bottom);
	pDC->SetViewportExt(rect.right, -rect.bottom);
	pDC->SetViewportOrg(0, 0);

	CBrush brush;
	brush.CreateSolidBrush(RGB(128, 128, 128));
	CBrush *oldBursh = pDC->SelectObject(&brush);
	pDC->FillRect(&rect, &brush);
	pDC->SelectObject(oldBursh);
	brush.DeleteObject();

	//Windows
	DrawLeftWindow(pDC, rect);
	DrawRightWindow(pDC, rect);
	DrawCenterWindow(pDC, rect);

	//Dashboard
	DrawDashboard(pDC, rect);

	//Instruments
	DrawInstruments(pDC, rect);
}

void CGDIView::DrawLeftWindow(CDC* pDC, CRect rect)
{
	CPen pen(PS_SOLID, 5, RGB(0, 0, 0));
	CBrush brush;
	brush.CreateSolidBrush(RGB(128, 244, 255));

	CPen *oldPen = pDC->SelectObject(&pen);
	CBrush *oldBrush = pDC->SelectObject(&brush);

	CPoint w11(0, 0.075*rect.bottom);
	CPoint w12(100, 0.2*rect.bottom);
	CPoint w13(150, 0.7*rect.bottom);
	CPoint w14(0, 0.85 *rect.bottom);
	CPoint array1[4];
	array1[0] = w11;
	array1[1] = w12;
	array1[2] = w13;
	array1[3] = w14;

	pDC->Polygon(array1, 4);

	pDC->SelectObject(oldBrush);
	pDC->SelectObject(oldPen);

	brush.DeleteObject();
	pen.DeleteObject();
}

void CGDIView::DrawCenterWindow(CDC* pDC, CRect rect)
{
	CPen pen(PS_SOLID, 5, RGB(0, 0, 0));
	CBrush brush;
	brush.CreateSolidBrush(RGB(128, 244, 255));

	CPen *oldPen = pDC->SelectObject(&pen);
	CBrush *oldBrush = pDC->SelectObject(&brush);

	CPoint w11(120, 0.095 * rect.bottom);
	CPoint w12(rect.right - 120, 0.095 * rect.bottom);
	CPoint w13(rect.right - 185, 0.7 * rect.bottom);
	CPoint w14(rect.right / 2, 0.6 *rect.bottom);
	CPoint w15(185, 0.7 * rect.bottom);
	CPoint array1[5];
	array1[0] = w11;
	array1[1] = w12;
	array1[2] = w13;
	array1[3] = w14;
	array1[4] = w15;

	pDC->Polygon(array1, 5);

	pDC->SelectObject(oldBrush);
	pDC->SelectObject(oldPen);

	brush.DeleteObject();
	pen.DeleteObject();
}

void CGDIView::DrawRightWindow(CDC* pDC, CRect rect)
{
	CPen pen(PS_SOLID, 5, RGB(0, 0, 0));
	CBrush brush;
	brush.CreateSolidBrush(RGB(128, 244, 255));

	CPen *oldPen = pDC->SelectObject(&pen);
	CBrush *oldBrush = pDC->SelectObject(&brush);

	CPoint w11(rect.right, 0.075*rect.bottom);
	CPoint w12(rect.right - 100, 0.2*rect.bottom);
	CPoint w13(rect.right - 150, 0.7*rect.bottom);
	CPoint w14(rect.right, 0.85 *rect.bottom);
	CPoint array1[4];
	array1[0] = w11;
	array1[1] = w12;
	array1[2] = w13;
	array1[3] = w14;

	pDC->Polygon(array1, 4);

	pDC->SelectObject(oldBrush);
	pDC->SelectObject(oldPen);

	brush.DeleteObject();
	pen.DeleteObject();
}

void CGDIView::DrawDashboard(CDC* pDC, CRect rect)
{
	CPen pen(PS_SOLID, 5, RGB(0, 0, 0));
	CBrush brush;
	brush.CreateSolidBrush(RGB(64, 64, 64));

	CPen *oldPen = pDC->SelectObject(&pen);
	CBrush *oldBrush = pDC->SelectObject(&brush);

	CPoint w11(150, rect.bottom);
	CPoint w12(155, 0.75 * rect.bottom);
	CPoint w13(rect.right / 2, 0.65 * rect.bottom);
	CPoint w14(rect.right - 155, 0.75 * rect.bottom);
	CPoint w15(rect.right - 150, rect.bottom);
	CPoint array1[5];
	array1[0] = w11;
	array1[1] = w12;
	array1[2] = w13;
	array1[3] = w14;
	array1[4] = w15;

	pDC->Polygon(array1, 5);

	pDC->SelectObject(oldPen);
	pDC->SelectObject(oldBrush);

	pen.DeleteObject();
	brush.DeleteObject();
}

void CGDIView::DrawInstruments(CDC* pDC, CRect rect)
{
	CPen pen(PS_SOLID, 3, RGB(255, 255, 255));
	CBrush brush;
	brush.CreateSolidBrush(RGB(32, 32, 32));

	CPen *oldPen = pDC->SelectObject(&pen);
	CBrush *oldBrush = pDC->SelectObject(&brush);

	int x1 = rect.right * 0.45 - 200;
	int y1 = 0.70* rect.bottom;
	int x2 = rect.right * 0.45;
	int y2 = 0.85* rect.bottom;
	int x3 = 20;
	int y3 = 20;

	pDC->RoundRect(x1, y1, x2, y2, x3, y3);

	pDC->SelectObject(oldBrush);
	pDC->SelectObject(oldPen);

	pen.DeleteObject();
	brush.DeleteObject();
}

// CGDIView printing

BOOL CGDIView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CGDIView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CGDIView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CGDIView diagnostics

#ifdef _DEBUG
void CGDIView::AssertValid() const
{
	CView::AssertValid();
}

void CGDIView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGDIDoc* CGDIView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGDIDoc)));
	return (CGDIDoc*)m_pDocument;
}
#endif //_DEBUG


// CGDIView message handlers
