
// SatView.cpp : implementation of the CSatView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Sat.h"
#endif

#include "SatDoc.h"
#include "SatView.h"
#include "DImage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSatView

IMPLEMENT_DYNCREATE(CSatView, CView)

BEGIN_MESSAGE_MAP(CSatView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CSatView construction/destruction

CSatView::CSatView()
{
	// TODO: add construction code here

}

CSatView::~CSatView()
{
}

BOOL CSatView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CSatView drawing

void CSatView::OnDraw(CDC* pDC)
{
	CSatDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	
	CRect rect;
	GetClientRect(&rect);
	
	CDC *memDC = new CDC();
	memDC->CreateCompatibleDC(pDC);
	
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());
	memDC->SelectObject(&bmp);
	
	int oldMode = memDC->SetGraphicsMode(GM_ADVANCED);
	XFORM form;
	memDC->GetWorldTransform(&form);
	
	//draw..
	int radius = 100;
	DrawClock(memDC,5,20,23,radius);	
	//draw..
	
	memDC->SetWorldTransform(&form);
	memDC->SetGraphicsMode(oldMode);
	
	pDC->BitBlt(0,0,rect.Width(),rect.Height(),memDC,0,0,SRCCOPY);
	
	//save..
	SaveClock((CString)"test.bmp", radius);
	//save..

	memDC->DeleteDC();
	delete memDC;
}

void CSatView::Translate(CDC *pDC, int x, int y, bool right)
{
	XFORM form;
	
	form.eM11 = 1;
	form.eM12 = 0;
	form.eM21 = 0;
	form.eM22 = 1;
	
	form.eDx = x;
	form.eDy = y;
	
	if(right)
		pDC->ModifyWorldTransform(&form,MWT_RIGHTMULTIPLY);
	else
		pDC->ModifyWorldTransform(&form,MWT_LEFTMULTIPLY);
}

void CSatView::TranslateRotate(CDC *pDC, int x, int y, float angle, int distance)
{
	XFORM form;
	
	form.eM11 = cos(toRad(angle));
	form.eM12 = sin(toRad(angle));
	form.eM21 = -sin(toRad(angle));
	form.eM22 = cos(toRad(angle));
	
	form.eDx = x + (distance * cos(toRad(angle)));
	form.eDy = y + (distance * sin(toRad(angle)));
	
	SetWorldTransform(pDC->m_hDC, &form);
}

void CSatView::Rotate(CDC *pDC, float angle, bool right)
{
	XFORM form;
	
	form.eM11 = cos(toRad(angle));
	form.eM12 = sin(toRad(angle));
	form.eM21 = -sin(toRad(angle));
	form.eM22 = cos(toRad(angle));
	
	form.eDx = 0;
	form.eDy = 0;
	
	if(right)
		pDC->ModifyWorldTransform(&form,MWT_RIGHTMULTIPLY);
	else
		pDC->ModifyWorldTransform(&form,MWT_LEFTMULTIPLY);
}

float CSatView::toRad(float angle)
{
	return (3.14 * angle) / 180;
}

void CSatView::DrawMarks(CDC *pDC, int distance, int width, int height)
{
	XFORM form;
	pDC->GetWorldTransform(&form);
	
	CBrush brush;
	brush.CreateSolidBrush(RGB(255,255,255));
	CPen pen(PS_SOLID,1,RGB(0,0,0));
	
	CBrush *oldBrush = pDC->SelectObject(&brush);
	CPen *oldPen = pDC->SelectObject(&pen);
	
	float angle = 360 / 12;
	float tmpAngle = 0;
	
	for(int i = 0 ; i < 12 ; i++)
	{
		TranslateRotate(pDC, 0, 0, tmpAngle, distance);
		
		pDC->Rectangle(CRect(-width/2,-height/2,width/2,height/2));
			
		pDC->SetWorldTransform(&form);
		
		tmpAngle += angle;
	}
	
	pDC->SelectObject(oldBrush);
	pDC->SelectObject(oldPen);
	
	brush.DeleteObject();
	pen.DeleteObject();
}

void CSatView::DrawNum(CDC *pDC, int distance)
{
	XFORM form;
	pDC->GetWorldTransform(&form);
	
	CBrush brush;
	brush.CreateSolidBrush(RGB(255,255,255));
	CPen pen(PS_SOLID, 1, RGB(0,0,0));
	CBrush *oldBrush = pDC->SelectObject(&brush);
	CPen *oldPen = pDC->SelectObject(&pen);
	
	CFont font;
	font.CreateFont(16,0,0,0,0,0,0,0,0,0,0,0,0,(CString)"Arial");
	CFont *oldFont = pDC->SelectObject(&font);
	
	COLORREF oldTextCol = pDC->SetTextColor(RGB(255,255,255));
	int oldBkMode = pDC->SetBkMode(TRANSPARENT);
	int oldTextAlign = pDC->SetTextAlign(TA_CENTER);
	
	float angle = 360 / 12;
	float tmpAngle = -60;
	
	for(int i = 0 ; i < 12 ; i++)
	{
		CString str;
		str.Format(_T("%d"), (i+1));
		
		TranslateRotate(pDC, 0, 0, tmpAngle, distance);
		
		pDC->Ellipse(CRect(-2, -2, 2, 2));

		Rotate(pDC, -tmpAngle, false);

		pDC->TextOut(0,-8,str);
		
		pDC->SetWorldTransform(&form);
		
		tmpAngle += angle;
	}
	
	pDC->SetTextColor(oldTextCol);
	pDC->SetBkMode(oldBkMode);
	pDC->SetTextAlign(oldTextAlign);
	
	pDC->SelectObject(oldBrush);
	pDC->SelectObject(oldPen);
	brush.DeleteObject();
	pen.DeleteObject();
}

void CSatView::SaveClock(CString name, int radius)
{
	int width = radius*2;
	int height = radius*2;
	
	CDC *pDC = GetDC();
	
	CDC *memDC = new CDC();
	memDC->CreateCompatibleDC(NULL);
	
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC,width,height);
	memDC->SelectObject(&bmp);
	
	memDC->BitBlt(0,0,width,height,pDC,-width/2,-height/2,SRCCOPY);
	
	DImage img(bmp);
	img.Save(name);
	
	memDC->DeleteDC();
	delete memDC;
}

void CSatView::DrawS(CDC *pDC)
{
	CBrush brush;
	brush.CreateSolidBrush(RGB(255,255,255));
	CPen pen(PS_SOLID, 1, RGB(0,0,0));
	CBrush *oldBrush = pDC->SelectObject(&brush);
	CPen *oldPen = pDC->SelectObject(&pen);
	
	int x1 = -1;
	int y1 = -1;
	int x2 = 80;
	int y2 = 1;
	pDC->Rectangle(CRect(x1,y1,x2,y2));
	
	pDC->SelectObject(oldBrush);
	pDC->SelectObject(oldPen);
	brush.DeleteObject();
	pen.DeleteObject();
}

void CSatView::DrawM(CDC *pDC)
{
	CBrush brush;
	brush.CreateSolidBrush(RGB(255,255,255));
	CPen pen(PS_SOLID, 1, RGB(0,0,0));
	CBrush *oldBrush = pDC->SelectObject(&brush);
	CPen *oldPen = pDC->SelectObject(&pen);
	
	pDC->BeginPath();
	pDC->MoveTo(-5,0);
	pDC->LineTo(0,5);
	pDC->LineTo(70,0);
	pDC->LineTo(0,-5);
	pDC->LineTo(-5,0);
	pDC->EndPath();
	pDC->StrokeAndFillPath();	
	
	pDC->SelectObject(oldBrush);
	pDC->SelectObject(oldPen);
	brush.DeleteObject();
	pen.DeleteObject();
}

void CSatView::DrawH(CDC *pDC)
{
	CBrush brush;
	brush.CreateSolidBrush(RGB(255,255,255));
	CPen pen(PS_SOLID, 1, RGB(0,0,0));
	CBrush *oldBrush = pDC->SelectObject(&brush);
	CPen *oldPen = pDC->SelectObject(&pen);
	
	pDC->BeginPath();
	pDC->MoveTo(-5,0);
	pDC->LineTo(0,5);
	pDC->LineTo(50,0);
	pDC->LineTo(0,-5);
	pDC->LineTo(-5,0);
	pDC->EndPath();
	pDC->StrokeAndFillPath();	
	
	pDC->SelectObject(oldBrush);
	pDC->SelectObject(oldPen);
	brush.DeleteObject();
	pen.DeleteObject();
}

void CSatView::DrawNeedles(CDC *pDC,int sati,int minuti,int sekunde)
{
	XFORM form;
	pDC->GetWorldTransform(&form);
	
	float angleH = ((360 / 12) * sati) - 90;
	float angleM = ((360 / 60) * minuti) - 90;
	float angleS = ((360 / 60) * sekunde) - 90;
	
	Rotate(pDC, angleH, false);
	DrawH(pDC);
	pDC->SetWorldTransform(&form);
	
	Rotate(pDC, angleM, false);
	DrawM(pDC);
	pDC->SetWorldTransform(&form);
	
	Rotate(pDC, angleS, false);
	DrawS(pDC);
	pDC->SetWorldTransform(&form);	
}

void CSatView::DrawClock(CDC *pDC, int sati,int minuti,int sekunde, int clockSize)
{
	DrawMarks(pDC, clockSize - 20, 9, 5); 
	DrawNum(pDC, clockSize);	
	DrawNeedles(pDC, sati, minuti, sekunde);
}

// CSatView printing

BOOL CSatView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSatView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSatView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CSatView diagnostics

#ifdef _DEBUG
void CSatView::AssertValid() const
{
	CView::AssertValid();
}

void CSatView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSatDoc* CSatView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSatDoc)));
	return (CSatDoc*)m_pDocument;
}
#endif //_DEBUG


// CSatView message handlers
