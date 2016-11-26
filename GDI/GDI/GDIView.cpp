
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
	DrawAnyWatch(pDC, rect, leftWatchRect1, 29, leftWatchText1, 8, M_PI / 3, (-4 * M_PI) / 3, 2, M_PI / 6);

	//Watch left window 2 - upper - right
	startX = 0.30*rect.right;
	startY = 0.70*rect.bottom;
	CRect leftWatchRect2(startX, startY, startX + dodatak, startY + dodatak);
	CString leftWatchText2[] =
	{
		(CString)"E",
		(CString)"NE",
		(CString)"N",
		(CString)"NW",
		(CString)"W",
		(CString)"SW",
		(CString)"S",
		(CString)"SE"
	};
	DrawAnyWatch(pDC, rect, leftWatchRect2, 17, leftWatchText2, 8, 0.0, 2 * M_PI, 3, M_PI / 3);

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
	DrawAnyWatch(pDC, rect, rightWatchRect1, 13, rightWatchText1, 7, 11 * M_PI / 6, M_PI / 6, 2, M_PI / 6);

	//Tilt Plane watch
	startX = (0.70*rect.right) - dodatak;
	startY = 0.70*rect.bottom;
	CRect tiltPlaneWatch(startX, startY, startX + dodatak, startY + dodatak);
	DrawWatchTilt(pDC, rect, tiltPlaneWatch, M_PI / 9);

	//Left fuel
	CRect rectFuelLeft(0.39*rect.right, 0.67*rect.bottom, 0.49*rect.right, 0.77*rect.bottom);
	double proportionLeft[]
	{
		1.0,
		2.0,
		1.0
	};
	COLORREF colorLeft[]
	{
		RGB(255,0,0),
		RGB(0,255,0),
		RGB(255,255,0)
	};
	DrawFuelWatch(pDC, rect, rectFuelLeft, proportionLeft, 3, colorLeft, M_PI / 3);

	//Right fuel
	CRect rectFuelRight(0.51*rect.right, 0.67*rect.bottom, 0.61*rect.right, 0.77*rect.bottom);
	double proportionRight[]
	{
		1.0,
		1.0,
		1.0
	};
	COLORREF colorRight[]
	{
		RGB(255,255,0),
		RGB(0,255,0),
		RGB(255,0,0)
	};
	DrawFuelWatch(pDC, rect, rectFuelRight, proportionRight, 3, colorRight, M_PI / 4);

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

	//Notches pens
	CPen penLarge(PS_SOLID, 2, RGB(255, 255, 255));
	CPen penSmall(PS_SOLID, 1, RGB(255, 255, 255));
	CPen *oldPen2 = pDC->SelectObject(&penLarge);

	//Set transformation data
	int oldMode = pDC->SetGraphicsMode(GM_ADVANCED);
	pDC->SetViewportOrg(rcWatch.left + rcWatch.Width() / 2, rcWatch.top + rcWatch.Height() / 2);

	//Font
	CFont font;
	LPCTSTR fontStyle = (LPCTSTR)"Arial";
	int fontHeight = 0.025*rect.bottom;
	int fontWidth = 0.0055 *rect.right;
	font.CreateFont(fontHeight, fontWidth, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, fontStyle);
	CFont *oldFont = pDC->SelectObject(&font);
	pDC->SetTextAlign(TA_LEFT);
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(255, 255, 255));

	//Ratio between text and notches
	int nNotch_to_nValues_ratio;
	if (nNotch != 0 && nValues != 00)
		nNotch_to_nValues_ratio = nNotch / (nValues - 1);
	else
		nNotch_to_nValues_ratio = 0;

	//Data for drawing notches
	double angle_between_notches = (dAngleStop - dAngleStart) / (nNotch - 1);
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

		//Here goes the text drawing
		//ispis teksta
		if (nNotch_to_nValues_ratio != 0 && i%nNotch_to_nValues_ratio == 0)
		{
			if (i / nNotch_to_nValues_ratio < nValues) {
				TranslateRotate(pDC, -M_PI / 2, 0.8*rcWatch.Width() / 2, -0.8*rcWatch.Width() / 2 - (arsValues[i / nNotch_to_nValues_ratio].GetLength()*0.0055*rect.right) / 2);
				pDC->TextOut(0.75*rcWatch.Width() / 2, 0, arsValues[i / nNotch_to_nValues_ratio]);
			}
		}
	}

	//Reset transformation
	NoTransform(pDC);
	//Reset data
	pDC->SelectObject(oldPen2);
	penLarge.DeleteObject();
	penSmall.DeleteObject();

	//Reset transformation
	NoTransform(pDC);
	pDC->SetViewportOrg(0, 0);
	pDC->SetGraphicsMode(oldMode);

	DrawNeedle(pDC, rect, rcWatch, dAngleNeedle, typeNeedle);
}

void CGDIView::DrawWatchTilt(CDC* pDC, CRect rect, CRect rcWatch, double dAngleTilt)
{
	//White pen
	CPen pen(PS_SOLID, 6, RGB(255, 255, 255));
	CPen *oldPen = pDC->SelectObject(&pen);

	//Draw circle
	pDC->Ellipse(rcWatch);

	//SaveOldDirection of the ARC
	int oldDirection = pDC->SetArcDirection(AD_CLOCKWISE);

	//Top parth brush
	CBrush brushBlue;
	brushBlue.CreateSolidBrush(RGB(48, 176, 224));
	CBrush *oldBrush = pDC->SelectObject(&brushBlue);

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
	pDC->SelectObject(oldPen);//Pen
	pDC->SelectObject(oldBrush);//Brush
	pDC->SetArcDirection(oldDirection);//ARC-direction
	pen.DeleteObject();
	brushBlue.DeleteObject();
	brushYellow.DeleteObject();

	//Set for transformation
	int oldMode = pDC->SetGraphicsMode(GM_ADVANCED);
	pDC->SetViewportOrg(rcWatch.left + rcWatch.Width() / 2, rcWatch.top + rcWatch.Height() / 2);
	double rotationAngle = M_PI / 9 - dAngleTilt;//Used to rotate the whole watch but without background
	Rotate(pDC, rotationAngle);

	//Pens
	CPen penSmall(PS_SOLID, 1, RGB(255, 255, 255));
	CPen penLarge(PS_SOLID, 2, RGB(255, 255, 255));
	CPen *oldPen2 = pDC->SelectObject(&penLarge);

	//Middle line
	pDC->MoveTo(-rcWatch.Width() / 2, 0);
	pDC->LineTo(rcWatch.Width() / 2, 0);

	//Reset transformation
	NoTransform(pDC);

	//Top watch notches
	int numNotches = 13;
	double angleStart = M_PI / 6;
	double angleEnd = 5 * M_PI / 6;
	double angle_between_notches = (angleEnd - angleStart) / (numNotches - 1);
	for (int i = 0; i < numNotches; i++)
	{
		//Set new rotation transformation
		Rotate(pDC, angleStart + i * angle_between_notches + rotationAngle);

		if (i % 3 == 0)
		{
			//Large notches
			pDC->SelectObject(&penLarge);
			pDC->MoveTo(0.8*rcWatch.Width() / 2, 0);
			pDC->LineTo(0.9*rcWatch.Width() / 2, 0);
		}
		else
		{
			//Small notches
			if (i == 1 || i == 2 || i == 10 || i == 11)
			{
				continue;
			}
			pDC->SelectObject(&penSmall);
			pDC->MoveTo(0.81*rcWatch.Width() / 2, 0);
			pDC->LineTo(0.9*rcWatch.Width() / 2, 0);
		}
	}

	//Reset transformation
	NoTransform(pDC);

	//Down lines - long notches
	numNotches = 5;
	angleStart = -M_PI / 6;
	angleEnd = -5 * M_PI / 6;
	angle_between_notches = (angleEnd - angleStart) / (numNotches - 1);
	for (int i = 0; i < numNotches; i++)
	{
		Rotate(pDC, angleStart + i*angle_between_notches + rotationAngle);
		pDC->MoveTo(0, 0);
		pDC->LineTo(0.8*rcWatch.Width() / 2, 0);
	}

	//Reset transformation
	NoTransform(pDC);
	pDC->SetViewportOrg(0, 0);
	pDC->SetGraphicsMode(oldMode);

	//Reset
	pDC->SelectObject(oldPen);
	penSmall.DeleteObject();
	penLarge.DeleteObject();
}

void CGDIView::DrawFuelWatch(CDC* pDC, CRect rcView, CRect rcWatch, double ardProportion[], int nParts, COLORREF arClrProportion[], double dAngleNeedle)
{
	CPen pen(PS_SOLID, 2, RGB(255, 255, 255));
	CBrush brush;
	brush.CreateSolidBrush(RGB(0, 0, 0));

	CPen *oldPen = pDC->SelectObject(&pen);
	CBrush *oldBrush = pDC->SelectObject(&brush);


	//Drawing fule watch border
	//Top part
	pDC->BeginPath();
	pDC->MoveTo(rcWatch.left, rcWatch.top + rcWatch.Height()*0.5);
	CPoint top[]
	{
		CPoint(rcWatch.left , rcWatch.top + rcWatch.Height()*0.5),
		CPoint(rcWatch.left + rcWatch.Width() / 2,rcWatch.top - rcWatch.Height()*0.5),
		CPoint(rcWatch.left + rcWatch.Width(),rcWatch.top + rcWatch.Height()*0.5)
	};
	pDC->PolyBezierTo(top, 3);

	//Right line
	pDC->LineTo(rcWatch.left + rcWatch.Width()*0.8, rcWatch.top + rcWatch.Height() - 1);

	//Bottom part
	CPoint bottom[]
	{
		CPoint(rcWatch.left + rcWatch.Width()*0.8,rcWatch.top + rcWatch.Height()),
		CPoint(rcWatch.left + rcWatch.Width() / 2,rcWatch.top + rcWatch.Height()*0.5),
		CPoint(rcWatch.left + rcWatch.Width()*0.2,rcWatch.top + rcWatch.Height())
	};
	pDC->PolyBezierTo(bottom, 3);

	//Left line
	pDC->LineTo(rcWatch.left, rcWatch.top + rcWatch.Height()*0.5);
	pDC->EndPath();
	pDC->StrokeAndFillPath();

	//iscrtanjave indikatorske linije
	CRect arc_rect(CPoint(rcWatch.left, rcWatch.top + rcWatch.Height()*0.25), CPoint(rcWatch.left + rcWatch.Width(), rcWatch.top + rcWatch.Width()));

	int total_part_proportion = 0;
	for (int j = 0; j < nParts; j++)
		total_part_proportion += ardProportion[j];

	//pocetni ugao
	double angle = M_PI / 5;
	pDC->SetArcDirection(AD_CLOCKWISE);
	for (int i = 0; i < nParts; i++)
	{
		//x i y koordinata za zadati pocetni ugao na elipsi upisanoj u arc_rect za trenutni arc
		double x_start = rcWatch.left + rcWatch.Width()* 0.5 - rcWatch.Width()*cos(angle);
		double y_start = rcWatch.top + arc_rect.Height()*0.5 - arc_rect.Height()*sin(angle);
		CPoint arc_start(x_start, y_start);

		int start_prop = 0, end_prop = 0;

		for (int j = 0; j < i; j++)
			start_prop += ardProportion[j];

		for (int j = 0; j <= i; j++)
			end_prop += ardProportion[j];

		//ugao arc-a koji crtam - maksimalni moguci pomnozen procentom koji je dodeljen tom arc-u
		double angle_add = 3 * M_PI / 5 * (end_prop - start_prop) / total_part_proportion;

		angle += angle_add;

		///x i y koordinata za zadati krajnji ugao na elipsi upisanoj u arc_rect za trenutni arc
		double x_end = rcWatch.left + rcWatch.Width()* 0.5 - rcWatch.Width()*cos(angle);
		double y_end = rcWatch.top + arc_rect.Height()*0.5 - arc_rect.Height()*sin(angle);

		CPoint arc_end(x_end, y_end);

		LOGBRUSH logBrush;
		logBrush.lbStyle = BS_SOLID;
		logBrush.lbColor = arClrProportion[i];
		CPen* pen_arc = new CPen(PS_GEOMETRIC | PS_ENDCAP_FLAT | PS_SOLID, 6, &logBrush);
		CPen* old_pen_arc = pDC->SelectObject(pen_arc);

		pDC->Arc(arc_rect, arc_start, arc_end);

		pDC->SelectObject(old_pen_arc);
		pen_arc->DeleteObject();

	}

	pDC->SelectObject(oldPen);
	pDC->SelectObject(oldBrush);

	pen.DeleteObject();
	brush.DeleteObject();

	//needle
	int oldGraphicMode = pDC->SetGraphicsMode(GM_ADVANCED);
	pDC->SetViewportOrg(rcWatch.left + rcWatch.Width() / 2, rcWatch.top + rcWatch.Height());
	Rotate(pDC, dAngleNeedle);

	CRect rectNeedle(0.12*rcWatch.Width(), -0.05*rcWatch.Height(), 0.3*rcWatch.Width(), 0.05*rcWatch.Height());
	HENHMETAFILE handler = CreateNeedleFuel(pDC, rectNeedle);
	PlayEnhMetaFile(pDC->m_hDC, handler, rectNeedle);
	DeleteEnhMetaFile(handler);

	NoTransform(pDC);
	pDC->SetViewportOrg(0, 0);
	pDC->SetGraphicsMode(oldGraphicMode);


}

void CGDIView::DrawNeedle(CDC* pDC, CRect rcView, CRect rcWatch, double dAngleNeedle, int typeNeedle)
{
	int oldGraphicMode = pDC->SetGraphicsMode(GM_ADVANCED);
	pDC->SetViewportOrg(rcWatch.left + rcWatch.Width() / 2, rcWatch.top + rcWatch.Height() / 2);
	Rotate(pDC, dAngleNeedle);

	switch (typeNeedle)
	{
	case 1:
	{
		CRect rect(-0.15*rcWatch.Width(), -0.007*rcView.Height(), 0.3*rcWatch.Width(), 0.007*rcView.Height());
		HENHMETAFILE handler = CreateNeedleFuel(pDC, rcView);
		PlayEnhMetaFile(pDC->m_hDC, handler, rect);
		DeleteEnhMetaFile(handler);
		break;
	}
	case 2:
	{
		CRect rect(-0.15*rcWatch.Width(), -0.01*rcView.Height(), 0.3*rcWatch.Width(), 0.01*rcView.Height());
		HENHMETAFILE handler = CreateNeedleStandrad(pDC, rcView);
		PlayEnhMetaFile(pDC->m_hDC, handler, rect);
		DeleteEnhMetaFile(handler);
		break;
	}
	case 3:
	{
		CRect rect(-0.2*rcWatch.Width(), -0.035*rcView.Height(), 0.3*rcWatch.Width(), 0.035*rcView.Height());
		HENHMETAFILE handler = CreateNeedlePlane(pDC, rcView);
		PlayEnhMetaFile(pDC->m_hDC, handler, rect);
		DeleteEnhMetaFile(handler);
		break;
	}
	}

	NoTransform(pDC);
	pDC->SetViewportOrg(0, 0);
	pDC->SetGraphicsMode(oldGraphicMode);

}

HENHMETAFILE CGDIView::CreateNeedleFuel(CDC* pDC, CRect rcView)
{
	CMetaFileDC metaDC;
	HENHMETAFILE handler;

	float pix = pDC->GetDeviceCaps(HORZRES);
	float mm = pDC->GetDeviceCaps(HORZSIZE);
	float x = rcView.Width() * 100 * mm / pix;
	float y = rcView.Height() * 100 * mm / pix;

	metaDC.CreateEnhanced(pDC, CString("needl1meta.emf"), CRect(0, 0, x, y), NULL);

	CPoint points[]
	{
		CPoint(0,0),
		CPoint(rcView.right,rcView.bottom*0.5),
		CPoint(0,rcView.bottom)
	};

	CPen pen(PS_SOLID, 1, RGB(255, 255, 255));
	CBrush brush;
	brush.CreateSolidBrush(RGB(255, 255, 255));

	metaDC.SelectObject(&pen);
	metaDC.SelectObject(&brush);

	metaDC.Polygon(points, 3);

	handler = metaDC.CloseEnhanced();
	metaDC.DeleteDC();
	return handler;
}

HENHMETAFILE CGDIView::CreateNeedleStandrad(CDC* pDC, CRect rcView)
{
	CMetaFileDC metaDC;
	HENHMETAFILE handler;

	float pix = pDC->GetDeviceCaps(HORZRES);
	float mm = pDC->GetDeviceCaps(HORZSIZE);
	float x = rcView.Width() * 100 * mm / pix;
	float y = rcView.Height() * 100 * mm / pix;

	metaDC.CreateEnhanced(pDC, (CString)"needle2meta.emf", CRect(0, 0, x, y), NULL);

	CPen pen(PS_SOLID, 1, RGB(245, 245, 245));
	CBrush brush(RGB(245, 245, 245));
	metaDC.SelectObject(&pen);
	metaDC.SelectObject(&brush);

	//CRect za prvi arc
	CRect rect1(0, 0, 0.132*rcView.right, rcView.bottom);

	double arc1_start_x = 0.5*rect1.Width() + cos(M_PI / 9) * (0.5*rect1.Width()); //elipsa pocinje i zavrsava se za istu vrednost x
	double arc_start_y = 0.5*rect1.Height() - sin(M_PI / 9) * (0.5*rect1.Height());
	double arc_end_y = 0.5*rect1.Height() + sin(M_PI / 9) * (0.5*rect1.Height());

	CPoint arc1_start(arc1_start_x, arc_start_y);
	CPoint arc1_end(arc1_start_x, arc_end_y);

	metaDC.Arc(rect1, arc1_start, arc1_end);
	metaDC.MoveTo(arc1_start);
	metaDC.LineTo(0.269*rcView.right, arc_start_y);
	metaDC.MoveTo(arc1_end);
	metaDC.LineTo(0.269*rcView.right, arc_end_y);

	//CRect za drugi i treci arc
	CRect rect2(0.264*rcView.right, 0, 0.396*rcView.right, rcView.bottom);

	int arc2_start_x = 0.264*rcView.right + (0.066*rcView.right - cos(M_PI / 9)*0.066*rcView.right);		//isto za arc3_start_x
	int arc2_end_x = 0.396*rcView.right - (0.066*rcView.right - cos(M_PI / 9)*0.066*rcView.right);		//isto za arc3_end_x

	CPoint arc2_start(arc2_start_x, arc_start_y); //arc2
	CPoint arc2_end(arc2_end_x, arc_start_y);

	metaDC.SetArcDirection(AD_CLOCKWISE);
	metaDC.Arc(rect2, arc2_start, arc2_end);
	metaDC.MoveTo(arc2_end.x, arc2_end.y);
	metaDC.LineTo(0.5*rcView.right, arc_start_y);


	CPoint arc3_start(arc2_start_x, arc_end_y); //arc3
	CPoint arc3_end(arc2_end_x, arc_end_y);
	metaDC.SetArcDirection(AD_COUNTERCLOCKWISE);
	metaDC.Arc(rect2, arc3_start, arc3_end);
	metaDC.MoveTo(arc3_end.x, arc3_end.y);
	metaDC.LineTo(0.5*rcView.right, arc_end_y);

	//kruzic oko kog treba kazaljka da se rotira
	metaDC.Ellipse(0.32*rcView.right, 0.48*rcView.bottom, 0.34*rcView.right, 0.48*rcView.bottom + 0.02*rcView.right);

	CPoint point_array[] =
	{
		CPoint(0.5*rcView.right, arc_start_y),
		CPoint(0.95* rcView.right, arc_start_y),
		CPoint(rcView.right, 0.5*rcView.bottom),
		CPoint(0.95* rcView.right, arc_end_y),
		CPoint(0.5*rcView.right, arc_end_y)
	};

	metaDC.Polygon(point_array, 5);

	handler = metaDC.CloseEnhanced();
	metaDC.DeleteDC();
	return handler;
}

HENHMETAFILE CGDIView::CreateNeedlePlane(CDC* pDC, CRect rcView)
{
	CMetaFileDC metaDC;
	HENHMETAFILE handler;

	float pix = pDC->GetDeviceCaps(HORZRES);
	float mm = pDC->GetDeviceCaps(HORZSIZE);
	float x = rcView.Width() * 100 * mm / pix;
	float y = rcView.Height() * 100 * mm / pix;

	metaDC.CreateEnhanced(pDC, (CString)"planemeta.emf", CRect(0, 0, x, y), NULL);


	CPen pen(PS_SOLID, 1, RGB(255, 0, 0));
	metaDC.SelectObject(&pen);

	metaDC.BeginPath();

	metaDC.MoveTo(0, 0.5*rcView.bottom);
	metaDC.LineTo(0.11*rcView.right, 0.44*rcView.bottom);
	metaDC.LineTo(0, 0.2*rcView.bottom);
	metaDC.LineTo(0.11*rcView.right, 0.2*rcView.bottom);
	metaDC.LineTo(0.22*rcView.right, 0.44*rcView.bottom);
	metaDC.LineTo(0.41*rcView.right, 0.4*rcView.bottom);
	metaDC.LineTo(0.34*rcView.right, 0);
	metaDC.LineTo(0.5*rcView.right, 0);
	metaDC.LineTo(0.65*rcView.right, 0.4*rcView.bottom);

	metaDC.LineTo(rcView.right, 0.5*rcView.bottom); //vrh aviJonceta

	metaDC.LineTo(0.65*rcView.right, 0.6*rcView.bottom);
	metaDC.LineTo(0.5*rcView.right, rcView.bottom);
	metaDC.LineTo(0.34*rcView.right, rcView.bottom);
	metaDC.LineTo(0.41*rcView.right, 0.6*rcView.bottom);
	metaDC.LineTo(0.22*rcView.right, 0.56*rcView.bottom);
	metaDC.LineTo(0.11*rcView.right, 0.8*rcView.bottom);
	metaDC.LineTo(0, 0.8*rcView.bottom);
	metaDC.LineTo(0.11*rcView.right, 0.56*rcView.bottom);
	metaDC.LineTo(0, 0.5*rcView.bottom);

	metaDC.EndPath();
	metaDC.StrokePath();

	handler = metaDC.CloseEnhanced();
	metaDC.DeleteDC();
	return handler;
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

void CGDIView::TranslateRotate(CDC* pDC, double angle, int x, int y)
{
	XFORM xform;
	xform.eM11 = cos(angle);
	xform.eM12 = -sin(angle);
	xform.eM21 = sin(angle);
	xform.eM22 = cos(angle);
	xform.eDx = x;
	xform.eDy = y;

	pDC->ModifyWorldTransform(&xform, MWT_LEFTMULTIPLY);
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
