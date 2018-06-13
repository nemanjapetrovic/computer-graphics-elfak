
// Suriken_2View.cpp : implementation of the CSuriken_2View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Suriken_2.h"
#endif

#include "Suriken_2Doc.h"
#include "Suriken_2View.h"
#include "DImage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSuriken_2View

IMPLEMENT_DYNCREATE(CSuriken_2View, CView)

BEGIN_MESSAGE_MAP(CSuriken_2View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CSuriken_2View construction/destruction

float centerX = 0;
float centerY = 0;
bool rotate = true;
float rotAngle = 0;
float move = 0;
DImage *sky, *bark;
CSuriken_2View::CSuriken_2View()
{
	// TODO: add construction code here
	sky = new DImage();
	sky->Load((CString)"sky.jpg");
	
	bark = new DImage();
	bark->Load((CString)"bark.jpg");
}

CSuriken_2View::~CSuriken_2View()
{
	delete sky;
	delete bark;
}

BOOL CSuriken_2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CSuriken_2View drawing

void CSuriken_2View::OnDraw(CDC* pDC)
{
	CSuriken_2Doc* pDoc = GetDocument();
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

	centerX = 100 + move;
	centerY = 200;

	Rotate(memDC, rotAngle, false);
	Translate(memDC, 100 + move, 200, true);
	DrawStar(memDC, 50);
	//draw..

	memDC->SetWorldTransform(&form);
	memDC->SetGraphicsMode(oldMode);

	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), memDC, 0, 0, SRCCOPY);

	memDC->DeleteDC();
	delete memDC;
}

float CSuriken_2View::toRad(float angle)
{
	return (angle * 3.14) / 180;
}

void CSuriken_2View::Translate(CDC* pDC, float x, float y, bool right)
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

void CSuriken_2View::Rotate(CDC *pDC, float angle, bool right)
{
	XFORM form;

	form.eM11 = cos(toRad(angle));
	form.eM12 = sin(toRad(angle));
	form.eM21 = -sin(toRad(angle));
	form.eM22 = cos(toRad(angle));

	form.eDx = 0;
	form.eDy = 0;

	if(right)
		pDC->ModifyWorldTransform(&form, MWT_RIGHTMULTIPLY);
	else
		pDC->ModifyWorldTransform(&form, MWT_LEFTMULTIPLY);
}

void CSuriken_2View::DrawBlade(CDC* pDC, int size)
{
	CBrush siva, tamna;
	siva.CreateSolidBrush(RGB(68, 68, 68));
	tamna.CreateSolidBrush(RGB(32, 32, 32));

	CBrush * oldBrush = pDC->SelectObject(&siva);
	pDC->BeginPath();
	pDC->MoveTo(0, 0);
	pDC->LineTo(size, -size);
	pDC->LineTo(4 * size, 0.0);
	pDC->LineTo(0.0, 0.0);
	pDC->EndPath();
	pDC->StrokeAndFillPath();

	pDC->SelectObject(&tamna);
	pDC->BeginPath();
	pDC->MoveTo(0, 0);
	pDC->LineTo(size, size);
	pDC->LineTo(4 * size, 0.0);
	pDC->LineTo(0.0, 0.0);
	pDC->EndPath();
	pDC->StrokeAndFillPath();

	pDC->SelectObject(oldBrush);
	siva.DeleteObject();
	tamna.DeleteObject();

	CFont font;
	font.CreateFont(0.7*size, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, (CString)"Monotype Corsiva");
	
	int oldTextAlign = pDC->SetTextAlign(TA_CENTER);
	int oldBkMode = pDC->SetBkMode(TRANSPARENT);
	COLORREF oldTexColor = pDC->SetTextColor(RGB(255, 255, 255));
	CFont *oldFont = pDC->SelectObject(&font);

	pDC->TextOut(2 * size + 2, -0.35 * size, (CString)"Shuricane");

	pDC->SetTextColor(RGB(98, 98, 98));
	pDC->TextOut(2 * size, -0.35 * size, (CString)"Shuricane");
	
	pDC->SetTextAlign(oldTextAlign);
	pDC->SetBkMode(oldBkMode);
	pDC->SetTextColor(oldTexColor);
	pDC->SelectObject(oldFont);
}

void CSuriken_2View::DrawStar(CDC *pDC, int size)
{
	float tmpAngle = 0;
	for (int i = 0; i < 4; i++) 
	{
		Rotate(pDC, tmpAngle, false);
		DrawBlade(pDC, size / 2);
		tmpAngle += 90;
	}
}




BOOL CSuriken_2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSuriken_2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSuriken_2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CSuriken_2View diagnostics

#ifdef _DEBUG
void CSuriken_2View::AssertValid() const
{
	CView::AssertValid();
}

void CSuriken_2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSuriken_2Doc* CSuriken_2View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSuriken_2Doc)));
	return (CSuriken_2Doc*)m_pDocument;
}
#endif //_DEBUG


// CSuriken_2View message handlers


void CSuriken_2View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default

	CRect rect;
	GetClientRect(&rect);

	if ('W' == nChar && rotate)
	{		
		float mestoSiljka = (centerX + 25);
		float pocetakStabla = rect.Width() - bark->Width();
		if ((mestoSiljka - pocetakStabla) >= (50 * 0.1))
		{
			rotate = false;
		}
	
		move += 20;
		rotAngle += 20;		
		Invalidate();
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


BOOL CSuriken_2View::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return TRUE;
}
