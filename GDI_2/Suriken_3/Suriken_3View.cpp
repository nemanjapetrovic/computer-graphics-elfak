
// Suriken_3View.cpp : implementation of the CSuriken_3View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Suriken_3.h"
#endif

#include "Suriken_3Doc.h"
#include "Suriken_3View.h"
#include "DImage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSuriken_3View

IMPLEMENT_DYNCREATE(CSuriken_3View, CView)

BEGIN_MESSAGE_MAP(CSuriken_3View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_ERASEBKGND()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CSuriken_3View construction/destruction

DImage *sky, *bark;
int move = 0;
double rotAngle = 0;
bool enableMove = true;
double centX, centY;
int size = 100;
CSuriken_3View::CSuriken_3View()
{
	// TODO: add construction code here
	centX = 250;
	centY = 250;

	sky = new DImage();
	sky->Load((CString)"sky.jpg");
	
	bark = new DImage();
	bark->Load((CString)"bark.jpg");
}

CSuriken_3View::~CSuriken_3View()
{
	delete sky;
	delete bark;
}

BOOL CSuriken_3View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CSuriken_3View drawing

void CSuriken_3View::OnDraw(CDC* pDC)
{
	CSuriken_3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

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
	sky->Draw(memDC, CRect(0, 0, sky->Width(), sky->Height()), CRect(0, 0, rect.Width(), rect.Height()));
	bark->Draw(memDC, CRect(0, 0, bark->Width(), bark->Height()), CRect(rect.Width() - bark->Width(), 0, rect.Width(), rect.Height()));

	Rotate(memDC, rotAngle, false);
	Translate(memDC, centX, centY, true);
	DrawStar(memDC, size);
	//draw..

	memDC->SetWorldTransform(&form);
	memDC->SetGraphicsMode(oldMode);

	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), memDC, 0, 0, SRCCOPY);

	memDC->DeleteDC();
	delete memDC;
}

void CSuriken_3View::DrawBlade(CDC *pDC, int size)
{
	CBrush siva, tamnoSiva;
	siva.CreateSolidBrush(RGB(128, 128, 128));
	tamnoSiva.CreateSolidBrush(RGB(68, 68, 68));
	
	CPen pen;
	pen.CreatePen(PS_SOLID, 1, RGB(32,32,32));

	CBrush *oldBrush = pDC->SelectObject(&siva);
	CPen *oldPen = pDC->SelectObject(&pen);

	pDC->BeginPath();
	pDC->MoveTo(0, 0);
	pDC->LineTo(size, -size);
	pDC->LineTo(4 * size, 0);
	pDC->LineTo(0, 0);
	pDC->EndPath();
	pDC->StrokeAndFillPath();
	
	pDC->SelectObject(&tamnoSiva);
	pDC->BeginPath();
	pDC->MoveTo(0, 0);
	pDC->LineTo(size, size);
	pDC->LineTo(4 * size, 0);
	pDC->LineTo(0, 0);
	pDC->EndPath();
	pDC->StrokeAndFillPath();

	pDC->SelectObject(oldBrush);
	pDC->SelectObject(oldPen);
	pen.DeleteObject();
	tamnoSiva.DeleteObject();
	siva.DeleteObject();

	CFont font;
	font.CreateFont(0.7*size, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, (CString)"Monotype Corsiva");

	int oldBkMode = pDC->SetBkMode(TRANSPARENT);
	int oldTextAlign = pDC->SetTextAlign(TA_CENTER);
	COLORREF oldColor = pDC->SetTextColor(RGB(255, 255, 255));
	
	pDC->TextOut(2 * size + 2, -0.35*size , (CString)"Shuricane");

	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->TextOut(2 * size, -0.35*size, (CString)"Shuricane");

	pDC->SetTextColor(oldColor);
	pDC->SetTextAlign(oldTextAlign);
	pDC->SetBkMode(oldBkMode);
}

void CSuriken_3View::Translate(CDC* pDC, double x, double y, bool right)
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

void CSuriken_3View::Rotate(CDC *pDC, double angle, bool right)
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

double CSuriken_3View::toRad(double angle)
{
	return (angle * 3.14) / 180;
}

void CSuriken_3View::DrawStar(CDC* pDC, int size)
{
	for (int i = 0; i < 4; i++) 
	{
		double angle = i * 90;
		Rotate(pDC, angle, false);
		DrawBlade(pDC, size / 2);
	}
}

BOOL CSuriken_3View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSuriken_3View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSuriken_3View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CSuriken_3View diagnostics

#ifdef _DEBUG
void CSuriken_3View::AssertValid() const
{
	CView::AssertValid();
}

void CSuriken_3View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSuriken_3Doc* CSuriken_3View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSuriken_3Doc)));
	return (CSuriken_3Doc*)m_pDocument;
}
#endif //_DEBUG


// CSuriken_3View message handlers


BOOL CSuriken_3View::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return TRUE;
}


void CSuriken_3View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	CRect rect;
	GetClientRect(&rect);

	if (enableMove && nChar == 'W') {
		if ((centX + size / 2) - (rect.Width() - bark->Width()) >= (size * 0.10))
		{
			enableMove = false;
		}
		move += 20;
		rotAngle += 20;
		centX += move;
		Invalidate();
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
