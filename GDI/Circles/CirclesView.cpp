
// CirclesView.cpp : implementation of the CCirclesView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Circles.h"
#endif

#include "CirclesDoc.h"
#include "CirclesView.h"
#include "DImage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCirclesView

IMPLEMENT_DYNCREATE(CCirclesView, CView)

BEGIN_MESSAGE_MAP(CCirclesView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CCirclesView construction/destruction

CCirclesView::CCirclesView()
{
	// TODO: add construction code here

}

CCirclesView::~CCirclesView()
{
}

BOOL CCirclesView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CCirclesView drawing

void CCirclesView::OnDraw(CDC* pDC)
{
	CCirclesDoc* pDoc = GetDocument();
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
	DrawFannyCircle(memDC, 300, 30, 270, 9, RGB(255, 255, 255), RGB(255, 255, 255), (CString)"Text");
	DrawAndSavePicture(memDC, (CString)"bg.bmp", 300);
	//draw..
	
	memDC->SetWorldTransform(&form);
	memDC->SetGraphicsMode(oldMode);
	
	pDC->BitBlt(0,0,rect.Width(),rect.Height(),memDC,0,0,SRCCOPY);
	
	memDC->DeleteDC();
	delete memDC;
}

void CCirclesView::Rotate(CDC *memDC, float angle, bool right)
{
	XFORM form;
	form.eM11 = cos(toRad(angle));
	form.eM12 = sin(toRad(angle));
	form.eM21 = -sin(toRad(angle));
	form.eM22 = cos(toRad(angle));
	
	form.eDx = 0;
	form.eDy = 0;
	
	if(right)
		memDC->ModifyWorldTransform(&form,MWT_RIGHTMULTIPLY);
	else
		memDC->ModifyWorldTransform(&form,MWT_LEFTMULTIPLY);
}

void CCirclesView::Translate(CDC *memDC, int x, int y, bool right)
{
	XFORM form;
	form.eM11 = 1;
	form.eM12 = 0;
	form.eM21 = 0;
	form.eM22 = 1;
	
	form.eDx = x;
	form.eDy = y;
	
	if(right)
		memDC->ModifyWorldTransform(&form, MWT_RIGHTMULTIPLY);
	else
		memDC->ModifyWorldTransform(&form, MWT_LEFTMULTIPLY);
}

void CCirclesView::TranslateRotate(CDC *pDC, float x, float y, float angle, float distance)
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

float CCirclesView::toRad(float angle)
{
	return (3.14*angle)/180;
}
	
void CCirclesView::DrawMultiCircle(CDC *pDC, int radius, int nConc, COLORREF colFill, CString strText)
{
	float divider = 1.0f;
	float colDivider = 1.0f;
	if (nConc < 1 || nConc > 10)
	{
		exit(-1);
	}

	for (int i = 0; i < nConc; i++) 
	{
		int r = GetRValue(colFill) * colDivider;
		int g = GetGValue(colFill) * colDivider;
		int b = GetBValue(colFill) * colDivider;
		
		CBrush brush;
		brush.CreateSolidBrush(RGB(r,g,b));
		CBrush *oldBrush = pDC->SelectObject(&brush);
		CPen pen(PS_SOLID,1,RGB(0,0,0));
		CPen *oldPen = pDC->SelectObject(&pen);
		
		int startX = -radius * divider;
		int startY = -radius * divider;
		int endX = radius * divider;
		int endY = radius * divider;

		pDC->Ellipse(CRect(startX, startY, endX, endY));
		
		divider -= 0.1f;
		colDivider -= 0.05f;
		
		pDC->SelectObject(oldBrush);
		pDC->SelectObject(oldPen);
		brush.DeleteObject();
		pen.DeleteObject();
	}
	
	CFont font;
	font.CreateFont(12,0,0,0,1,0,0,0,0,0,0,0,0,(CString)"Arial");
	CFont *oldFont = pDC->SelectObject(&font);
	
	int oldTextColor = pDC->SetTextColor(RGB(0,0,0));
	int oldBkMode = pDC->SetBkMode(TRANSPARENT);
	int oldAlign = pDC->SetTextAlign(TA_CENTER);
	
	pDC->TextOut(0,-6,strText);
	
	pDC->SetTextColor(oldTextColor);
	pDC->SetBkMode(oldBkMode);
	pDC->SetTextAlign(oldAlign);
	
	pDC->SelectObject(oldFont);
	font.DeleteObject();
}

void CCirclesView::DrawFannyCircle(CDC *pDC, int radius, int nCricle, double dAlpha, int nCone, COLORREF colFillBig, COLORREF clFillSmall, CString strText)
{
	XFORM form;
	pDC->GetWorldTransform(&form);

	//big circle
	DrawMultiCircle(pDC, radius, nCone, colFillBig, strText);
	
	//small circles
	int smallRadius = radius * 0.05;
	int smallnCone = 2;
	
	float angle = 360 / nCricle;
	float tmpAngle = 0;
	for (int i = 0; i < nCricle; i++) {
		CString text;
		text.Format(_T("%d"), (i+1));
				
		TranslateRotate(pDC, 0, 0, tmpAngle, radius);
		Rotate(pDC, dAlpha, false);

		DrawMultiCircle(pDC, smallRadius, smallnCone, clFillSmall, text);

		pDC->SetWorldTransform(&form);

		tmpAngle += angle;
	}
}

void CCirclesView::DrawAndSavePicture(CDC *pDC, CString strPicture, int radius)
{
	int width = radius * 2;
	int height = radius * 2;
	width = width + (width * 0.2);
	height = height + (height * 0.2);

	CDC *memDC = new CDC();
	memDC->CreateCompatibleDC(NULL);

	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC, width, height);
	memDC->SelectObject(&bmp);

	memDC->BitBlt(0, 0, width, height, pDC, -width / 2, -height / 2, SRCCOPY);

	DImage img(bmp);
	img.Save(strPicture);

	memDC->DeleteDC();
	delete memDC;
}

// CCirclesView printing

BOOL CCirclesView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCirclesView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCirclesView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CCirclesView diagnostics

#ifdef _DEBUG
void CCirclesView::AssertValid() const
{
	CView::AssertValid();
}

void CCirclesView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCirclesDoc* CCirclesView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCirclesDoc)));
	return (CCirclesDoc*)m_pDocument;
}
#endif //_DEBUG


// CCirclesView message handlers
