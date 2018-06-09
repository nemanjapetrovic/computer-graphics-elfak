
// Trouglovi_2View.cpp : implementation of the CTrouglovi_2View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Trouglovi_2.h"
#endif

#include "Trouglovi_2Doc.h"
#include "Trouglovi_2View.h"
#include "DImage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTrouglovi_2View

IMPLEMENT_DYNCREATE(CTrouglovi_2View, CView)

BEGIN_MESSAGE_MAP(CTrouglovi_2View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CTrouglovi_2View construction/destruction

CTrouglovi_2View::CTrouglovi_2View()
{
	// TODO: add construction code here

}

CTrouglovi_2View::~CTrouglovi_2View()
{
}

BOOL CTrouglovi_2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CTrouglovi_2View drawing

void CTrouglovi_2View::OnDraw(CDC* pDC)
{
	CTrouglovi_2Doc* pDoc = GetDocument();
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
	
	//Desni trougao gore
	XFORM translate1 = Translate(300, 300);
	XFORM reflect1 = Reflect(1.0, -1.0);
	XFORM out1;
	CombineTransform(&out1,&reflect1,&translate1);
	memDC->SetWorldTransform(&out1);
	DrawTriangle(memDC);
	memDC->SetWorldTransform(&form);

	//Levi trougao gore
	XFORM translate2 = Translate(300, 300);
	XFORM reflect2 = Reflect(-1.0, 1.0);
	XFORM reflect21 = Reflect(1.0, -1.0);
	XFORM out2, out22;
	CombineTransform(&out2, &reflect2, &reflect21);
	CombineTransform(&out22, &out2, &translate2);
	memDC->SetWorldTransform(&out22);
	DrawTriangle(memDC);
	memDC->SetWorldTransform(&form);

	//Desni trougao dole
	XFORM translate3 = Translate(300, 300);	
	XFORM rotate3 = Rotate(-90);
	XFORM reflect3 = Reflect(1.0, -1.0);
	XFORM out3, out33;
	CombineTransform(&out3, &rotate3, &reflect3);
	CombineTransform(&out33, &out3, &translate3);
	memDC->SetWorldTransform(&out33);
	DrawTriangle(memDC);
	memDC->SetWorldTransform(&form);

	//Levi trougao dole
	XFORM translate4 = Translate(300, 300);
	XFORM rotate4 = Rotate(90);
	XFORM out4;
	CombineTransform(&out4, &rotate4, &translate4);
	memDC->SetWorldTransform(&out4);
	DrawTriangle(memDC);
	memDC->SetWorldTransform(&form);
	//draw..

	memDC->SetGraphicsMode(oldMode);
	memDC->SetWorldTransform(&form);

	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), memDC, 0, 0, SRCCOPY);

	// Save img
	SaveImg();

	memDC->DeleteDC();
	delete memDC;
}

void  CTrouglovi_2View::SaveImg()
{
	int width = 400;
	int height = 300;

	CDC *pDC = GetDC();

	CDC *memDC = new CDC();
	memDC->CreateCompatibleDC(NULL);

	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC, width, height);
	memDC->SelectObject(&bmp);

	memDC->BitBlt(0, 0, width, height, pDC, 100, 100, SRCCOPY);

	DImage img(bmp);
	img.Save((CString)"test.bmp");

	memDC->DeleteDC();
	delete memDC;
}

XFORM CTrouglovi_2View::Translate(float x, float y)
{
	XFORM form;
	
	form.eM11 = 1;
	form.eM12 = 0;
	form.eM21 = 0;
	form.eM22 = 1;
	
	form.eDx = x;
	form.eDy = y;
	
	return form;
}

XFORM CTrouglovi_2View::Rotate(float a)
{
	float tmpAngle = (a * 3.14) / 180;

	XFORM form;

	form.eM11 = cos(tmpAngle);
	form.eM12 = sin(tmpAngle);
	form.eM21 = -sin(tmpAngle);
	form.eM22 = cos(tmpAngle);

	form.eDx = 0;
	form.eDy = 0;

	return form;
}

XFORM CTrouglovi_2View::Reflect(float Sx, float Sy)
{
	XFORM form;
	
	form.eM11 = Sx;
	form.eM12 = 0;
	form.eM21 = 0;
	form.eM22 = Sy;

	form.eDx = 0;
	form.eDy = 0;

	return form;
}

void CTrouglovi_2View::DrawTriangle(CDC* pDC)
{
	CBrush brush;
	brush.CreateSolidBrush(RGB(68, 68, 68));
	CBrush *oldBrush = pDC->SelectObject(&brush);

	CPen pen;
	pen.CreatePen(PS_SOLID, 1, RGB(35,24,48));
	CPen *oldPen = pDC->SelectObject(&pen);


	pDC->BeginPath();
	pDC->MoveTo(0.0, 0.0);
	pDC->LineTo(0.0, 200.0);
	pDC->LineTo(100.0, 0.0);
	pDC->LineTo(0.0, 0.0);
	pDC->EndPath();
	pDC->StrokeAndFillPath();


	pDC->SelectObject(oldPen);
	pDC->SelectObject(oldBrush);

	pen.DeleteObject();
	brush.DeleteObject();	
}


// CTrouglovi_2View printing

BOOL CTrouglovi_2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTrouglovi_2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTrouglovi_2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CTrouglovi_2View diagnostics

#ifdef _DEBUG
void CTrouglovi_2View::AssertValid() const
{
	CView::AssertValid();
}

void CTrouglovi_2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTrouglovi_2Doc* CTrouglovi_2View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTrouglovi_2Doc)));
	return (CTrouglovi_2Doc*)m_pDocument;
}
#endif //_DEBUG


// CTrouglovi_2View message handlers
