
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
#define _USE_MATH_DEFINES // for C++
#include <cmath>
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


	//----------------
	//DRAW
	//----------------
	//Windows sharp
	//DrawLeftWindow(pDC, rect);
	//DrawRightWindow(pDC, rect);
	//DrawCenterWindow(pDC, rect);
	//Dashboard sharp
	//DrawDashboard(pDC, rect);

	//Windows smooth
	DrawSmoothDashbouard(pDC, rect);
	//Dashboard smooth
	DrawSmoothWindows(pDC, rect);
	//Instruments - central instruments
	DrawDataInstruments(pDC, rect);

	//Watch size
	int startX = 0.22*rect.right;
	int startY = 0.80*rect.bottom;
	int dodatak = startX * 0.35;

	//Watch left window 1 - lower - left
	CRect leftWatchRect1(startX, startY, startX + dodatak, startY + dodatak);
	CString leftWatchText1[] =
	{
		(CString)"4",
		(CString)"8",
		(CString)"12",
		(CString)"16",
		(CString)"20",
		(CString)"24",
		(CString)"28",
		(CString)"32"
	};
	//DrawWatch(pDC, rect, leftWatchRect1, 29, leftWatchText1, 8, M_PI / 3, 2 * M_PI / 3, 0, 0);
	DrawAnyWatch(pDC, rect, leftWatchRect1, 29, leftWatchText1, 8, M_PI / 3, (-4 * M_PI) / 3, 0, 0);

	//Watch left window 2 - upper - right
	startX = 0.30*rect.right;
	startY = 0.70*rect.bottom;
	CRect leftWatchRect2(startX, startY, startX + dodatak, startY + dodatak);
	CString leftWatchText2[] =
	{
		(CString)"N",
		(CString)"NE",
		(CString)"E",
		(CString)"SE",
		(CString)"S",
		(CString)"SW",
		(CString)"W",
		(CString)"NW"
	};
	//	DrawWatch(pDC, rect, leftWatchRect2, 17, leftWatchText2, 8, M_PI / 2, M_PI / 2, 0, 0);
	DrawAnyWatch(pDC, rect, leftWatchRect2, 17, leftWatchText2, 8, 0.0, 2 * M_PI, 0, 0);

	//Watch right window 1 - lower - right
	startX = (0.78*rect.right) - dodatak;
	startY = 0.80*rect.bottom;
	CRect rightWatchRect1(startX, startY, startX + dodatak, startY + dodatak);
	CString rightWatchText1[] =
	{
		(CString)"-3",
		(CString)"-2",
		(CString)"-1",
		(CString)"0",
		(CString)"1",
		(CString)"2",
		(CString)"3"
	};
	DrawAnyWatch(pDC, rect, rightWatchRect1, 13, rightWatchText1, 7, 11 * M_PI / 6, M_PI / 6, 0, 0);

	//Tilt Plane watch
	startX = (0.70*rect.right) - dodatak;
	startY = 0.70*rect.bottom;
	Rotate(pDC, M_PI / 6);
	CRect tiltPlaneWatch(startX, startY, startX + dodatak, startY + dodatak);
	DrawWatchTilt(pDC, rect, tiltPlaneWatch, M_PI / 9);
	NoTransform(pDC);
}

//Sharp Window
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
//Sharp Window
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
//Sharp Window
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
//Sharp Dashboard
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

//Smooth Window
void CGDIView::DrawSmoothWindows(CDC* pDC, CRect rect)
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
//Smooth Dashboard
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

//Central instruments
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
	int fontHeight = 0.032*rect.bottom;
	int fontWidth = 0.0055*rect.right;
	font.CreateFont(fontHeight, fontWidth, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, fontStyle);
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
		pDC->TextOut(x, y + fontHeight * i * 1.5, s[i]);
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
		pDC->TextOut(x, y + fontHeight * i*1.5, s1[i]);
	}

	pDC->SetTextColor(oldColor);
	pDC->SelectObject(oldFont);
	pDC->SetBkMode(oldMode);

	font.DeleteObject();
}

void CGDIView::DrawAnyWatch(CDC* pDC, CRect rect, CRect rcWatch, int nNotch, CString arsValues[], int nValues, double dAngleStart, double dAngleStop, int typeNeedle, double dAngleNeedle)
{
	//Draw circle
	CPen pen(PS_SOLID, 1, RGB(255, 255, 255));
	CBrush brush;
	brush.CreateSolidBrush(RGB(0, 0, 0));

	CPen *oldPen = pDC->SelectObject(&pen);
	CBrush *oldBrush = pDC->SelectObject(&brush);

	pDC->Ellipse(rcWatch);

	pDC->SelectObject(oldPen);
	pDC->SelectObject(oldBrush);

	pen.DeleteObject();
	brush.DeleteObject();
	//Change graphics mode
	int oldMode = pDC->SetGraphicsMode(GM_ADVANCED);

	//Change coordinate org
	pDC->SetViewportOrg(rcWatch.left + rcWatch.Width() / 2, rcWatch.top + rcWatch.Height() / 2);

	//Draw notches
	CPen penLarge(PS_SOLID, 2, RGB(255, 255, 255));
	CPen penSmall(PS_SOLID, 1, RGB(255, 255, 255));

	CPen *oldPen2 = pDC->SelectObject(&penLarge);

	//Data for drawing notches
	double angle_between_notches = (dAngleStop - dAngleStart) / (nNotch - 1);
	XFORM xform;

	for (int i = 0; i < nNotch; i++)
	{
		Rotate(pDC, (dAngleStart + i * angle_between_notches));

		if (i % 2 == 0)
		{
			pDC->SelectObject(&penLarge);
			pDC->MoveTo(0.8 * rcWatch.Width() / 2, 0);
			pDC->LineTo(0.9 * rcWatch.Width() / 2, 0);
		}
		else
		{
			pDC->SelectObject(&penSmall);
			pDC->MoveTo(0.81 * rcWatch.Width() / 2, 0);
			pDC->LineTo(0.9 * rcWatch.Width() / 2, 0);
		}
	}

	pDC->SelectObject(oldPen2);

	penLarge.DeleteObject();
	penSmall.DeleteObject();

	//Reset coordinate org
	pDC->SetViewportOrg(0, 0);

	//Remove transformation
	NoTransform(pDC);

	//Reset graphics mode
	pDC->SetGraphicsMode(oldMode);
}

void CGDIView::DrawWatchTilt(CDC* pDC, CRect rect, CRect rcWatch, double dAngleTilt)
{
	//Top parth brush
	CBrush brushBlue;
	brushBlue.CreateSolidBrush(RGB(48, 176, 224));
	CBrush *oldBrush = pDC->SelectObject(&brushBlue);

	int oldDirection = pDC->SetArcDirection(AD_CLOCKWISE);

	//Top parth of watch
	pDC->BeginPath();
	pDC->Arc(rcWatch, CPoint(rcWatch.left, rcWatch.top + rcWatch.Height() / 2), CPoint(rcWatch.left + rcWatch.Width(), rcWatch.top + rcWatch.Height() / 2));
	pDC->EndPath();
	pDC->FillPath();

	//Bottom parth brush
	CBrush brushYellow;
	brushYellow.CreateSolidBrush(RGB(208, 176, 128));
	pDC->SelectObject(&brushYellow);

	//Bottom parth of watch
	pDC->BeginPath();
	pDC->Arc(rcWatch, CPoint(rcWatch.left + rcWatch.Width(), rcWatch.top + rcWatch.Height() / 2), CPoint(rcWatch.left, rcWatch.top + rcWatch.Height() / 2));
	pDC->EndPath();
	pDC->FillPath();

	//Reset
	pDC->SelectObject(oldBrush);
	pDC->SetArcDirection(oldDirection);
	brushBlue.DeleteObject();
	brushYellow.DeleteObject();
	NoTransform(pDC);
}

void CGDIView::NoTransform(CDC* pDC)
{
	XFORM xform;
	xform.eM11 = 1;
	xform.eM12 = 0;
	xform.eM21 = 0;
	xform.eM22 = 1;
	xform.eDx = 0;
	xform.eDy = 0;

	pDC->SetWorldTransform(&xform);
}

void CGDIView::Rotate(CDC* pDC, double angle)
{
	XFORM xform;
	xform.eM11 = cos(angle);
	xform.eM12 = -sin(angle);
	xform.eM21 = sin(angle);
	xform.eM22 = cos(angle);
	xform.eDx = 0;
	xform.eDy = 0;

	pDC->SetWorldTransform(&xform);
}

//Draw any watch
void CGDIView::DrawWatch(CDC* pDC, CRect rect, CRect rcWatch, int nNotch, CString arsValues[], int nValues, double dAngleStart, double dAngleStop, int typeNeedle, double dAngleNeedle)
{
	//rcWatch - pravougaonik za sat
	//nNotch - broj podeoka
	//arsValues - niz stringova za svaki podeok
	//nValues - broj stringova koje treba prikazati
	//dAngleStart - ugao od koga pocinju da se iscrtavaju podeoci
	//dAngleStop - ugao sa kojim se zavrsava iscrtavanje podeoka
	//typeNeedle - tip kazaljke koju treba prikazati
	//dAngleNeedle - ugao pod kojim se iscrtava kazaljka
	CPen pen(PS_SOLID, 1, RGB(255, 255, 255));
	CBrush brush;
	brush.CreateSolidBrush(RGB(0, 0, 0));

	CPen *oldPen = pDC->SelectObject(&pen);
	CBrush *oldBrush = pDC->SelectObject(&brush);

	//Crtanje kruga
	pDC->Ellipse(rcWatch);

	pDC->SelectObject(oldPen);
	pDC->SelectObject(oldBrush);

	pen.DeleteObject();
	brush.DeleteObject();

	double angleTotal = 2 * M_PI - abs(dAngleStop - dAngleStart);
	double angleStep = angleTotal / (nNotch - 1);
	double angle = M_PI / 2 - dAngleStart;

	int oldBKMode = pDC->SetBkMode(TRANSPARENT);
	int i;
	int j = 0;
	XFORM Xform, XformOld;
	BOOL b = GetWorldTransform(pDC->m_hDC, &XformOld);

	int jump = (nNotch - 1) / nValues;
	if ((nNotch - 1) % nValues != 0)
		jump++;

	int prevMode = SetGraphicsMode(pDC->m_hDC, GM_ADVANCED);
	for (i = 0; i < nNotch; i++)
	{
		int a = i % 2 ? 1 : 3;

		CPen pen(PS_SOLID, a, RGB(255, 255, 255));
		CPen* pOldPen = pDC->SelectObject(&pen);

		double length = i % 2 ? rcWatch.Width() / 25 : rcWatch.Width() / 22;

		Xform.eM11 = 1;
		Xform.eM12 = 0;
		Xform.eM21 = 0;
		Xform.eM22 = 1;
		Xform.eDx = -rcWatch.left - rcWatch.Width() / 2;
		Xform.eDy = -rcWatch.top - rcWatch.Height() / 2;
		b = SetWorldTransform(pDC->m_hDC, &Xform);

		Xform.eM11 = cos(angle);
		Xform.eM12 = sin(angle);
		Xform.eM21 = -sin(angle);
		Xform.eM22 = cos(angle);
		Xform.eDx = rcWatch.left + rcWatch.Width() / 2;
		Xform.eDy = rcWatch.top + rcWatch.Height() / 2;
		b = ModifyWorldTransform(pDC->m_hDC, &Xform, MWT_RIGHTMULTIPLY);

		angle += angleStep;
		pDC->MoveTo(rcWatch.left + rcWatch.Width() / 2, rcWatch.top + 10);
		pDC->LineTo(rcWatch.left + rcWatch.Width() / 2, rcWatch.top + 10 + length);

		if (i%jump == 0)
		{
			if (j != nValues)
			{
				CFont font;

				font.CreateFontW(12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, CString("Arial"));
				CFont* pOldFont = pDC->SelectObject(&font);
				COLORREF oldColor = pDC->SetTextColor(RGB(255, 255, 255));
				pDC->TextOut(rcWatch.left + (rcWatch.bottom*0.02) + rcWatch.Width() / 2 - pDC->GetTextExtent(arsValues[j]).cx / 2, rcWatch.top + length + 10, arsValues[j]);
				j++;
				pDC->SelectObject(pOldFont);
				font.DeleteObject();
				pDC->SetTextColor(oldColor);
			}
		}
		pDC->SelectObject(pOldPen);
		pen.DeleteObject();
	}
	b = SetWorldTransform(pDC->m_hDC, &XformOld);
	SetGraphicsMode(pDC->m_hDC, prevMode);
	pDC->SetBkMode(oldBKMode);
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
