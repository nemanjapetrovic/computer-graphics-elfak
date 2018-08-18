
// Sat_3View.cpp : implementation of the CSat_3View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Sat_3.h"
#endif

#include "Sat_3Doc.h"
#include "Sat_3View.h"
#include "DImage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSat_3View

IMPLEMENT_DYNCREATE(CSat_3View, CView)

BEGIN_MESSAGE_MAP(CSat_3View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CSat_3View construction/destruction

CSat_3View::CSat_3View()
{
	// TODO: add construction code here

}

CSat_3View::~CSat_3View()
{
}

BOOL CSat_3View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CSat_3View drawing

void CSat_3View::OnDraw(CDC* pDC)
{
	CSat_3Doc* pDoc = GetDocument();
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
	DrawNum(memDC, 250, 250);
	DrawMarks(memDC, 250, 250);	
	DrawNeedles(memDC, 250,250, 4, 23, 18);
	//draw..

	memDC->SetWorldTransform(&form);
	memDC->SetGraphicsMode(oldMode);

	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), memDC, 0, 0, SRCCOPY);

	SaveClock(250, 250);

	memDC->DeleteDC();
	delete memDC;
}

float CSat_3View::toRad(float angle) 
{
	return (angle * 3.14) / 180;
}

void CSat_3View::TranslateRotate(CDC *pDC, float x, float y, float angle, float distance) 
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

void CSat_3View::Translate(CDC *pDC, float x, float y, bool right)
{
	XFORM form;

	form.eM11 = 1;
	form.eM12 = 0;
	form.eM21 = 0;
	form.eM22 = 1;

	form.eDx = x;
	form.eDy = y;

	if (right)
	{
		pDC->ModifyWorldTransform(&form, MWT_RIGHTMULTIPLY);
	}
	else
	{
		pDC->ModifyWorldTransform(&form, MWT_LEFTMULTIPLY);
	}

}
void CSat_3View::Rotate(CDC *pDC, float angle, bool right) 
{
	XFORM form;

	form.eM11 = cos(toRad(angle));
	form.eM12 = sin(toRad(angle));
	form.eM21 = -sin(toRad(angle));
	form.eM22 = cos(toRad(angle));

	form.eDx = 0;
	form.eDy = 0;

	if (right) 
	{
		pDC->ModifyWorldTransform(&form, MWT_RIGHTMULTIPLY);
	}
	else
	{
		pDC->ModifyWorldTransform(&form, MWT_LEFTMULTIPLY);
	}
}

void CSat_3View::DrawNum(CDC *pDC, int x, int y)
{
	// telo sata - background
	CBrush grey;
	grey.CreateSolidBrush(RGB(68, 68, 68));
	CBrush *oldBrush = pDC->SelectObject(&grey);

	pDC->Rectangle(x - 100, y - 100, x + 100, y + 100);

	CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
	CPen *oldPen = pDC->SelectObject(&pen);

	CBrush brush;
	brush.CreateSolidBrush(RGB(255, 255, 255));
	pDC->SelectObject(&brush);

	//bele tacke
	float angle = 360 / 12;
	float tmpAngle = 0;
	for (int i = 0; i < 12; i++) 
	{
		XFORM form;
		pDC->GetWorldTransform(&form);

		TranslateRotate(pDC, x, y, tmpAngle, 90);
		pDC->Ellipse(-1, -1, 1, 1);

		pDC->SetWorldTransform(&form);

		tmpAngle += angle;
	}

	//brojevi
	CFont font;
	font.CreateFont(16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, (CString)"Arial");
	CFont *oldFont = pDC->SelectObject(&font);

	int oldBkMode = pDC->SetBkMode(TRANSPARENT);
	int oldTextAlign = pDC->SetTextAlign(TA_CENTER);
	COLORREF oldColTex = pDC->SetTextColor(RGB(0, 0, 0));

	angle = 360 / 12;
	tmpAngle = -90 + angle;
	for (int i = 0; i < 12; i++) 
	{
		XFORM form;
		pDC->GetWorldTransform(&form);

		TranslateRotate(pDC, x, y, tmpAngle, 90);
		Rotate(pDC, -tmpAngle, false);

		CString str;
		str.Format(_T("%d"), (i + 1));
		pDC->TextOut(0, -8, str);

		pDC->SetWorldTransform(&form);
		
		tmpAngle += angle;
	}

	pDC->SetTextColor(oldColTex);
	pDC->SetTextAlign(oldTextAlign);
	pDC->SetBkMode(oldBkMode);

	pDC->SelectObject(oldFont);
	pDC->SelectObject(oldPen);
	pDC->SelectObject(oldBrush);
	grey.DeleteObject();
	font.DeleteObject();
	brush.DeleteObject();
	pen.DeleteObject();
}

void CSat_3View::DrawMarks(CDC *pDC, int x, int y)
{
	CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
	CPen *oldPen = pDC->SelectObject(&pen);

	CBrush brush;
	brush.CreateSolidBrush(RGB(255, 255, 255));
	CBrush *oldBrush = pDC->SelectObject(&brush);

	float angle = 360 / 12;
	float tmpAngle = 0;
	for (int i = 0; i < 12; i++) 
	{
		XFORM form;
		pDC->GetWorldTransform(&form);

		TranslateRotate(pDC, x, y, tmpAngle, 80);
		pDC->Rectangle(-4.5, -2.5, 4.5, 2.5);//9x5

		pDC->SetWorldTransform(&form);

		tmpAngle += angle;
	}

	pDC->SelectObject(oldPen);
	pDC->SelectObject(oldBrush);
	brush.DeleteObject();
	pen.DeleteObject();
}

void CSat_3View::DrawH(CDC *pDC, int x, int y)
{
	CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
	CPen *oldPen = pDC->SelectObject(&pen);

	CBrush brush;
	brush.CreateSolidBrush(RGB(255, 255, 255));
	CBrush *oldBrush = pDC->SelectObject(&brush);

	XFORM oldForm;
	pDC->GetWorldTransform(&oldForm);

	Translate(pDC, x, y, true);

	pDC->BeginPath();
	pDC->MoveTo(-5, 0);
	pDC->LineTo(0, 5);
	pDC->LineTo(50, 0);
	pDC->LineTo(0, -5);
	pDC->LineTo(-5, 0);
	pDC->EndPath();
	pDC->StrokeAndFillPath();

	pDC->SetWorldTransform(&oldForm);

	pDC->SelectObject(oldPen);
	pDC->SelectObject(oldBrush);
	brush.DeleteObject();
	pen.DeleteObject();
}

void CSat_3View::DrawM(CDC *pDC, int x, int y)
{
	CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
	CPen *oldPen = pDC->SelectObject(&pen);

	CBrush brush;
	brush.CreateSolidBrush(RGB(255, 255, 255));
	CBrush *oldBrush = pDC->SelectObject(&brush);

	XFORM oldForm;
	pDC->GetWorldTransform(&oldForm);

	Translate(pDC, x, y, true);

	pDC->BeginPath();
	pDC->MoveTo(-5, 0);
	pDC->LineTo(0, 5);
	pDC->LineTo(70, 0);
	pDC->LineTo(0, -5);
	pDC->LineTo(-5, 0);
	pDC->EndPath();
	pDC->StrokeAndFillPath();

	pDC->SetWorldTransform(&oldForm);

	pDC->SelectObject(oldPen);
	pDC->SelectObject(oldBrush);
	brush.DeleteObject();
	pen.DeleteObject();
}

void CSat_3View::DrawS(CDC *pDC, int x, int y)
{
	CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
	CPen *oldPen = pDC->SelectObject(&pen);

	CBrush brush;
	brush.CreateSolidBrush(RGB(255, 255, 255));
	CBrush *oldBrush = pDC->SelectObject(&brush);

	CPoint points[]{
		CPoint(-1,1),
		CPoint(80,1),
		CPoint(80,-1),
		CPoint(-1,-1)
	};

	XFORM oldForm;
	pDC->GetWorldTransform(&oldForm);

	Translate(pDC, x, y, true);

	pDC->BeginPath();
	pDC->Polygon(points, 4);
	pDC->EndPath();
	pDC->StrokeAndFillPath();

	pDC->SetWorldTransform(&oldForm);

	pDC->SelectObject(oldPen);
	pDC->SelectObject(oldBrush);
	brush.DeleteObject();
	pen.DeleteObject();
}

void CSat_3View::DrawNeedles(CDC *pDC, int x, int y, int sati, int minuti, int sekunde)
{	
	XFORM oldForm;
	pDC->GetWorldTransform(&oldForm);
	
	float rotAngleH = (sati * (360 / 12)) - 90;
	float rotAngleM = (minuti * (360 / 60)) - 90;
	float rotAngleS = (sekunde * (360 / 60)) - 90;

	Rotate(pDC, rotAngleH, false);
	DrawH(pDC,x,y);
	pDC->SetWorldTransform(&oldForm);

	Rotate(pDC, rotAngleM, false);
	DrawM(pDC, x, y);
	pDC->SetWorldTransform(&oldForm);

	Rotate(pDC, rotAngleS, false);
	DrawS(pDC, x, y);
	pDC->SetWorldTransform(&oldForm);
}

void CSat_3View::SaveClock(int x, int y)
{
	CDC *pDC = GetDC();

	CDC *memDC = new CDC();
	memDC->CreateCompatibleDC(NULL);

	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC, 200, 200);
	memDC->SelectObject(&bmp);

	memDC->BitBlt(0, 0, 200, 200, pDC, x - 100, y - 100, SRCCOPY);

	DImage img(bmp);
	img.Save((CString)"output.bmp");

	memDC->DeleteDC();
	delete memDC;
}

BOOL CSat_3View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSat_3View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSat_3View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

#ifdef _DEBUG
void CSat_3View::AssertValid() const
{
	CView::AssertValid();
}

void CSat_3View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSat_3Doc* CSat_3View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSat_3Doc)));
	return (CSat_3Doc*)m_pDocument;
}
#endif //_DEBUG