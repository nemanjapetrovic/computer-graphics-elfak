
// Sat_2View.cpp : implementation of the CSat_2View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Sat_2.h"
#endif

#include "Sat_2Doc.h"
#include "Sat_2View.h"
#include "DImage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSat_2View

IMPLEMENT_DYNCREATE(CSat_2View, CView)

BEGIN_MESSAGE_MAP(CSat_2View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CSat_2View construction/destruction

CSat_2View::CSat_2View()
{
	// TODO: add construction code here

}

CSat_2View::~CSat_2View()
{
}

BOOL CSat_2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CSat_2View drawing

void CSat_2View::OnDraw(CDC* pDC)
{
	CSat_2Doc* pDoc = GetDocument();
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

	int oldmode = memDC->SetGraphicsMode(GM_ADVANCED);
	XFORM form;
	memDC->GetWorldTransform(&form);

	//draw..
	CBrush brush;
	brush.CreateSolidBrush(RGB(255, 255, 255));
	CBrush * oldBrush = memDC->SelectObject(&brush);
	
	DrawNum(memDC);
	DrawMarks(memDC);
	DrawNeedles(memDC, 4, 25, 29);	

	brush.DeleteObject();
	memDC->SelectObject(oldBrush);
	//draw.

	memDC->SetWorldTransform(&form);
	memDC->SetGraphicsMode(oldmode);

	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), memDC, 0, 0, SRCCOPY);

	SaveClock((CString)"clock.bmp");

	memDC->DeleteDC();
	delete memDC;
}

float CSat_2View::toRad(float angle)
{
	return (angle * 3.14) / 180;
}

void CSat_2View::TranslateRotate(CDC *pDC, float x, float y, float angle, float distance)
{
	XFORM form;

	form.eM11 = cos(toRad(angle));
	form.eM12 = sin(toRad(angle));
	form.eM21 = -sin(toRad(angle));
	form.eM22 = cos(toRad(angle));

	form.eDx = x + (distance * cos(toRad(angle)));
	form.eDy = y + (distance * sin(toRad(angle)));

	pDC->SetWorldTransform(&form);
}

void CSat_2View::Rotate(CDC *pDC, float angle, bool right)
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

void CSat_2View::DrawNum(CDC *pDC)
{
	CFont font;
	font.CreateFont(16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, (CString)"Arial");

	int oldTextAlign = pDC->SetTextAlign(TA_CENTER);
	int oldBkMode = pDC->SetBkMode(TRANSPARENT);
	COLORREF oldColor = pDC->SetTextColor(RGB(255, 255, 255));
	CFont *oldFont = pDC->SelectObject(&font);

	float tmpAngle = -60;
	float angle = 360 / 12;
	for (int i = 0; i < 12; i++) 
	{
		XFORM form;
		pDC->GetWorldTransform(&form);

		TranslateRotate(pDC, 0, 0, tmpAngle, 90);
		Rotate(pDC, -tmpAngle, false);
	
		//tacke
		pDC->Ellipse(CRect(-1, -1, 1, 1));

		//brojevi
		CString broj;
		broj.Format(_T("%d"), (i+1));
		pDC->TextOut(0, -8, broj);		
				
		tmpAngle += angle;
		pDC->SetWorldTransform(&form);
	}

	pDC->SelectObject(oldFont);
	pDC->SetTextColor(oldColor);
	pDC->SetBkMode(oldBkMode);
	pDC->SetTextAlign(oldTextAlign);
	font.DeleteObject();
}

void CSat_2View::DrawMarks(CDC *pDC)
{
	float tmpAngle = 0;
	float angle = 360 / 12;
	for (int i = 0; i < 12; i++)
	{
		XFORM form;
		pDC->GetWorldTransform(&form);

		TranslateRotate(pDC, 0, 0, tmpAngle, 70);

		//marks
		pDC->Ellipse(CRect(-4.5,-2.5,4.5,2.5));

		tmpAngle += angle;
		pDC->SetWorldTransform(&form);
	}
}

void CSat_2View::DrawNeedles(CDC *pDC, int sati, int  minuti, int sekunde)
{
	XFORM form;
	pDC->GetWorldTransform(&form);

	float hAngle = ((360 / 12) * sati) - 90;
	float mAngle = ((360 / 60) * minuti) - 90;
	float sAngle = ((360 / 60) * sekunde) - 90;

	Rotate(pDC, hAngle, false);
	DrawH(pDC);
	pDC->SetWorldTransform(&form);
	
	Rotate(pDC, mAngle, false);
	DrawM(pDC);
	pDC->SetWorldTransform(&form);

	Rotate(pDC, sAngle, false);
	DrawS(pDC);
	pDC->SetWorldTransform(&form);
}

void CSat_2View::SaveClock(CString name)
{
	CDC * pDC = GetDC();

	CDC *memDC = new CDC();
	memDC->CreateCompatibleDC(NULL);

	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC, 200, 200);
	memDC->SelectObject(&bmp);

	memDC->BitBlt(0, 0, 200, 200, pDC, -100, -100, SRCCOPY);

	DImage img(bmp);
	img.Save(name);

	memDC->DeleteDC();
	delete memDC;
}

void CSat_2View::DrawH(CDC * pDC)
{
	CBrush white;
	white.CreateSolidBrush(RGB(255, 255, 255));
	CBrush * oldBrush = pDC->SelectObject(&white);
	CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
	CPen *oldPen = pDC->SelectObject(&pen);

	pDC->BeginPath();
		pDC->MoveTo(-5.0, 0.0);
		pDC->LineTo(0.0, 5.0);
		pDC->LineTo(50.0, 0.0);
		pDC->LineTo(0.0, -5.0);
		pDC->LineTo(-5.0, 0.0);
	pDC->EndPath();
	pDC->StrokeAndFillPath();

	pDC->SelectObject(oldBrush);
	pDC->SelectObject(oldPen);
	pen.DeleteObject();
	white.DeleteObject();
}

void CSat_2View::DrawM(CDC * pDC)
{
	CBrush white;
	white.CreateSolidBrush(RGB(255, 255, 255));
	CBrush * oldBrush = pDC->SelectObject(&white);
	CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
	CPen *oldPen = pDC->SelectObject(&pen);

	pDC->BeginPath();
	pDC->MoveTo(-5.0, 0.0);
	pDC->LineTo(0.0, 5.0);
	pDC->LineTo(70.0, 0.0);
	pDC->LineTo(0.0, -5.0);
	pDC->LineTo(-5.0, 0.0);
	pDC->EndPath();
	pDC->StrokeAndFillPath();

	pDC->SelectObject(oldBrush);
	pDC->SelectObject(oldPen);
	pen.DeleteObject();
	white.DeleteObject();
}

void CSat_2View::DrawS(CDC * pDC)
{
	CBrush white;
	white.CreateSolidBrush(RGB(255, 255, 255));
	CBrush * oldBrush = pDC->SelectObject(&white);
	CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
	CPen *oldPen = pDC->SelectObject(&pen);

	pDC->BeginPath();
	pDC->MoveTo(-1.0,1.0);
	pDC->LineTo(80.0, 1.0);
	pDC->LineTo(80.0, -1.0);
	pDC->LineTo(-1.0, -1.0);	
	pDC->EndPath();
	pDC->StrokeAndFillPath();

	pDC->SelectObject(oldBrush);
	pDC->SelectObject(oldPen);
	pen.DeleteObject();
	white.DeleteObject();
}

// CSat_2View printing

BOOL CSat_2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSat_2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSat_2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CSat_2View diagnostics

#ifdef _DEBUG
void CSat_2View::AssertValid() const
{
	CView::AssertValid();
}

void CSat_2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSat_2Doc* CSat_2View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSat_2Doc)));
	return (CSat_2Doc*)m_pDocument;
}
#endif //_DEBUG


// CSat_2View message handlers
