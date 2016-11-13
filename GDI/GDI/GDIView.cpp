
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

	//Windows smooth
	//DrawSmoothDashbouard(pDC, rect);

	//Dashboard
	DrawDashboard(pDC, rect);

	//Dashboard smooth
	//DrawSmoothLeftWindow(pDC, rect);

	//Instruments
	DrawDataInstruments(pDC, rect);
}

void CGDIView::DrawLeftWindow(CDC* pDC, CRect rect)
{
	CPen pen(PS_SOLID, 5, RGB(0, 0, 0));
	CBrush brush;
	brush.CreateSolidBrush(RGB(128, 244, 255));

	CPen *oldPen = pDC->SelectObject(&pen);
	CBrush *oldBrush = pDC->SelectObject(&brush);

	CPoint w11(0, 0.075*rect.bottom);
	CPoint w12(rect.right * 0.15, 0.2*rect.bottom);
	CPoint w13(rect.right * 0.20, 0.7*rect.bottom);
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

	CPoint w11(rect.right * 0.15, 0.095 * rect.bottom);
	CPoint w12(rect.right * 0.85, 0.095 * rect.bottom);
	CPoint w13(rect.right * 0.79, 0.7 * rect.bottom);
	CPoint w14(rect.right / 2, 0.6 *rect.bottom);
	CPoint w15(rect.right * 0.21, 0.7 * rect.bottom);
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
	CPoint w12(rect.right * 0.85, 0.2*rect.bottom);
	CPoint w13(rect.right * 0.80, 0.7*rect.bottom);
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

	CPoint w11(rect.right * 0.21, rect.bottom);
	CPoint w12(rect.right * 0.21, 0.75 * rect.bottom);
	CPoint w13(rect.right / 2, 0.65 * rect.bottom);
	CPoint w14(rect.right * 0.79, 0.75 * rect.bottom);
	CPoint w15(rect.right * 0.79, rect.bottom);
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

void CGDIView::DrawDataInstruments(CDC* pDC, CRect rect)
{
	//Rects
	CPen pen(PS_SOLID, 3, RGB(255, 255, 255));
	CBrush brush;
	brush.CreateSolidBrush(RGB(32, 32, 32));

	CPen *oldPen = pDC->SelectObject(&pen);
	CBrush *oldBrush = pDC->SelectObject(&brush);

	pDC->RoundRect(0.39*rect.right, 0.79*rect.bottom, 0.49*rect.right, 0.99*rect.bottom, 0.01*rect.right, 0.01*rect.right);
	pDC->RoundRect(0.51*rect.right, 0.79*rect.bottom, 0.61*rect.right, 0.99*rect.bottom, 0.01*rect.right, 0.01*rect.right);

	pDC->SelectObject(oldBrush);
	pDC->SelectObject(oldPen);

	pen.DeleteObject();
	brush.DeleteObject();

	//Text
	CFont font;
	CFont *oldFont = pDC->SelectObject(&font);
	LPCTSTR fontStyle = (LPCTSTR)"Arial";
	int fontSize = rect.right * 0.012;
	font.CreateFont(fontSize, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, fontStyle);
	pDC->SelectObject(&font);

	pDC->SetTextAlign(TA_LEFT);
	int oldMode = pDC->SetBkMode(TRANSPARENT);

	COLORREF oldColor = pDC->SetTextColor(RGB(0, 153, 0));

	int x = 0.395*rect.right;
	int y = 0.81*rect.bottom;

	//Left align text
	CString s[] = {
		(CString)"353mph",
		(CString)"H: 23'",
		(CString)"A: 284'",
		(CString)"1217lpm'"
	};
	for (int i = 0; i < 4; i++)
	{
		if (i == 0)
		{
			pDC->TextOut(x, y, s[i]);
			continue;
		}
		pDC->TextOut(x, y + fontSize * i * 1.5, s[i]);
	}

	//Right align text
	pDC->SetTextAlign(TA_RIGHT);
	CString s1[] = {
		(CString)"1285m",
		(CString)"43°1478'",
		(CString)"12°13'18'",
		(CString)"13:48"
	};
	x = 0.485*rect.right;
	for (int i = 0; i < 4; i++)
	{
		if (i == 0)
		{
			pDC->TextOut(x, y, s1[i]);
			continue;
		}
		pDC->TextOut(x, y + fontSize * i*1.5, s1[i]);
	}

	pDC->SetTextColor(oldColor);
	pDC->SelectObject(oldFont);
	pDC->SetBkMode(oldMode);

	font.DeleteObject();
}

void CGDIView::DrawSmoothLeftWindow(CDC* pDC, CRect rect)
{

	CPen pen(PS_SOLID, 5, RGB(0, 0, 0));
	CBrush brush;
	brush.CreateSolidBrush(RGB(128, 224, 255));

	CPen* oldPen = pDC->SelectObject(&pen);
	CBrush* oldBrush = pDC->SelectObject(&brush);

	CPoint left[] = {
		CPoint(0, 0.075 * rect.bottom),
		CPoint(0.16 * rect.right,0.2*rect.bottom),
		CPoint(0.18 * rect.right , 0.3 * rect.bottom),
		CPoint(0.188*rect.right,0.6*rect.bottom),
		CPoint(0.19*rect.right,0.7*rect.bottom),
		CPoint(0.19*rect.right,0.7*rect.bottom),
		CPoint(0, 0.85*rect.bottom)
	};

	CPoint right[]{
		CPoint(rect.right, 0.075 * rect.bottom),
		CPoint(0.84 * rect.right,0.2*rect.bottom),
		CPoint(0.82 * rect.right , 0.3 * rect.bottom),
		CPoint(0.812*rect.right,0.6*rect.bottom),
		CPoint(0.81*rect.right,0.7*rect.bottom),
		CPoint(0.81*rect.right,0.7*rect.bottom),
		CPoint(rect.right, 0.85*rect.bottom)
	};

	CPoint center[]
	{
		CPoint(0.2*rect.right, 0.05*rect.bottom),
		CPoint(0.15*rect.right, 0.05*rect.bottom),//
		CPoint(0.15*rect.right, 0.1*rect.bottom),//
		CPoint(0.2*rect.right, 0.55*rect.bottom),
		CPoint(0.2*rect.right, 0.65*rect.bottom),//
		CPoint(0.35*rect.right, 0.65*rect.bottom),//
		CPoint(0.5*rect.right, 0.6*rect.bottom),
		CPoint(0.65*rect.right, 0.65*rect.bottom),//
		CPoint(0.8*rect.right, 0.65*rect.bottom),//
		CPoint(0.8*rect.right, 0.55*rect.bottom),
		CPoint(0.85*rect.right, 0.1*rect.bottom),//
		CPoint(0.85*rect.right, 0.05*rect.bottom),
		CPoint(0.8*rect.right, 0.05*rect.bottom),
		CPoint(0.5*rect.right, 0.1*rect.bottom),//
		CPoint(0.5*rect.right, 0.1*rect.bottom),//
		CPoint(0.2*rect.right, 0.05*rect.bottom)
	};
	pDC->BeginPath();

	pDC->PolyBezier(left, 7);
	pDC->PolyBezier(right, 7);
	pDC->PolyBezier(center, 13);

	pDC->EndPath();
	pDC->StrokeAndFillPath();


	pDC->SelectObject(oldPen);
	pDC->SelectObject(oldBrush);

	brush.DeleteObject();
	pen.DeleteObject();
}

void CGDIView::DrawSmoothDashbouard(CDC* pDC, CRect rect)
{
	CPen pen(PS_SOLID, 5, RGB(0, 0, 0));
	CBrush brush;
	brush.CreateSolidBrush(RGB(64, 64, 64));

	CPen *oldPen = pDC->SelectObject(&pen);
	CBrush *oldBrush = pDC->SelectObject(&brush);

	CPoint dashboard[]
	{
		CPoint(0.80*rect.right,rect.bottom),
		CPoint(0.80*rect.right, 0.90*rect.bottom),
		CPoint(0.80*rect.right, 0.80*rect.bottom),
		CPoint(0.80*rect.right, 0.68*rect.bottom),
		CPoint(0.78*rect.right, 0.58*rect.bottom),
		CPoint(0.74*rect.right, 0.7*rect.bottom),
		CPoint(0.5*rect.right, 0.62*rect.bottom),
		CPoint(0.26*rect.right, 0.70*rect.bottom),
		CPoint(0.22*rect.right, 0.58*rect.bottom),
		CPoint(0.20*rect.right, 0.68*rect.bottom),
		CPoint(0.2*rect.right, 0.80*rect.bottom),
		CPoint(0.2*rect.right, 0.9*rect.bottom),
		CPoint(0.2*rect.right, rect.bottom)
	};

	pDC->BeginPath();
	pDC->PolyBezier(dashboard, 13);
	pDC->EndPath();
	pDC->StrokeAndFillPath();

	pDC->SelectObject(oldPen);
	pDC->SelectObject(oldBrush);

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
