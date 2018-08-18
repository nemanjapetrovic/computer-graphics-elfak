
// Suriken_4View.cpp : implementation of the CSuriken_4View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Suriken_4.h"
#endif

#include "Suriken_4Doc.h"
#include "Suriken_4View.h"
#include "DImage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSuriken_4View

IMPLEMENT_DYNCREATE(CSuriken_4View, CView)

BEGIN_MESSAGE_MAP(CSuriken_4View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CSuriken_4View construction/destruction

bool stop;
DImage *sky, *bark;
int size;
float move;
float rotAngle;
float centerX, centerY;
CSuriken_4View::CSuriken_4View()
{
	// TODO: add construction code here
	stop = false;
	size = 40;
	move = 20.0;
	rotAngle = 0.0;
	centerX = 100;
	centerY = 200;

	sky = new DImage();
	sky->Load((CString)"sky.jpg");
	bark = new DImage();
	bark->Load((CString)"bark.jpg");
}

CSuriken_4View::~CSuriken_4View()
{
	delete sky;
	delete bark;
}

BOOL CSuriken_4View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CSuriken_4View drawing

void CSuriken_4View::OnDraw(CDC* pDC)
{
	CSuriken_4Doc* pDoc = GetDocument();
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
	sky->Draw(memDC, CRect(0, 0, sky->Width(), sky->Height()), CRect(0, 0, rect.Width(), rect.Height()));
	bark->Draw(memDC, CRect(0, 0, bark->Width(), bark->Height()), CRect(rect.Width() - bark->Width(), 0, rect.Width(), rect.Height()));
	
	Translate(memDC, centerX, centerY, false);
	Rotate(memDC, rotAngle, false);	
	DrawStar(memDC, size);
	//draw..

	memDC->SetWorldTransform(&form);
	memDC->SetGraphicsMode(oldMode);

	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), memDC, 0, 0, SRCCOPY);

	memDC->DeleteDC();
	delete memDC;
}

float CSuriken_4View::toRad(float angle)
{
	return (angle * 3.14) / 180;
}

void CSuriken_4View::Translate(CDC* pDC, double x, double y, bool right)
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

void CSuriken_4View::Rotate(CDC* pDC, float angle, bool right)
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

void CSuriken_4View::DrawBlade(CDC* pDC, int size)
{
	CPen pen(PS_SOLID, 1, RGB(68, 68, 68));
	CPen *oldPen = pDC->SelectObject(&pen);

	CBrush tamno, svetlo;
	tamno.CreateSolidBrush(RGB(32, 32, 32));
	svetlo.CreateSolidBrush(RGB(128, 128, 128));
	CBrush *oldBrush = pDC->SelectObject(&svetlo);

	pDC->BeginPath();
	pDC->MoveTo(0, 0);
	pDC->LineTo(4 * size, 0);
	pDC->LineTo(size, size);
	pDC->LineTo(0, 0);
	pDC->EndPath();
	pDC->StrokeAndFillPath();

	pDC->SelectObject(&tamno);
	pDC->BeginPath();
	pDC->MoveTo(0, 0);
	pDC->LineTo(4 * size, 0);
	pDC->LineTo(size, -size);
	pDC->LineTo(0, 0);
	pDC->EndPath();
	pDC->StrokeAndFillPath();

	pDC->SelectObject(oldBrush);
	pDC->SelectObject(oldPen);
	tamno.DeleteObject();
	svetlo.DeleteObject();
	pen.DeleteObject();

	CFont font;
	font.CreateFont(0.7*size, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, (CString)"Monotype Corsiva");
	CFont *oldFont = pDC->SelectObject(&font);

	int oldBkMode = pDC->SetBkMode(TRANSPARENT);
	int oldAlign = pDC->SetTextAlign(TA_CENTER);
	COLORREF col = pDC->SetTextColor(RGB(12, 12, 12));

	pDC->TextOut(2*size, -0.35*size, (CString)"Shuricane");

	pDC->SetTextColor(RGB(200, 200, 200));
	pDC->TextOut(2*size - 3, -0.33*size, (CString)"Shuricane");

	pDC->SetTextColor(col);
	pDC->SetTextAlign(oldAlign);
	pDC->SetBkMode(oldBkMode);
	pDC->SelectObject(oldFont);
	font.DeleteObject();
}


void CSuriken_4View::DrawStar(CDC* pDC, int size)
{
	float angle = 360 / 4;
	float tmpAngle = 0;	
	for (int i = 0; i < 4; i++) {		
		Rotate(pDC, tmpAngle, false);
		DrawBlade(pDC, size / 2);
		tmpAngle += angle;
	}
}



// CSuriken_4View printing

BOOL CSuriken_4View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSuriken_4View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSuriken_4View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CSuriken_4View diagnostics

#ifdef _DEBUG
void CSuriken_4View::AssertValid() const
{
	CView::AssertValid();
}

void CSuriken_4View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSuriken_4Doc* CSuriken_4View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSuriken_4Doc)));
	return (CSuriken_4Doc*)m_pDocument;
}
#endif //_DEBUG


// CSuriken_4View message handlers


void CSuriken_4View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	
	CRect rect;
	GetClientRect(&rect);

	if (!stop && nChar == 'W') {
		centerX += move;
		rotAngle += 10;
		if ((centerX + (2 * size)) - (rect.Width() - bark->Width()) >= ((2*size)*0.1))
		{
			stop = true;
		}
		Invalidate();
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


BOOL CSuriken_4View::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return TRUE;
}
