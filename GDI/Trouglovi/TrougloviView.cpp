
// TrougloviView.cpp : implementation of the CTrougloviView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Trouglovi.h"
#endif

#include "TrougloviDoc.h"
#include "TrougloviView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTrougloviView

IMPLEMENT_DYNCREATE(CTrougloviView, CView)

BEGIN_MESSAGE_MAP(CTrougloviView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CTrougloviView construction/destruction

CTrougloviView::CTrougloviView()
{
	// TODO: add construction code here

}

CTrougloviView::~CTrougloviView()
{
}

BOOL CTrougloviView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CTrougloviView drawing

void CTrougloviView::OnDraw(CDC* pDC)
{
	CTrougloviDoc* pDoc = GetDocument();
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
	XFORM tranForm = Translate(300, 300);

	//levi dole
	XFORM rotForm1 = Rotate(90);	
	XFORM tmpForm1;
	CombineTransform(&tmpForm1,&rotForm1,&tranForm);
	memDC->SetWorldTransform(&tmpForm1);
	DrawTriangle(memDC);
	memDC->SetWorldTransform(&form);

	//levi gore
	XFORM rotForm2 = Rotate(-180);
	XFORM tmpForm2;
	CombineTransform(&tmpForm2, &rotForm2, &tranForm);
	memDC->SetWorldTransform(&tmpForm2);
	DrawTriangle(memDC);
	memDC->SetWorldTransform(&form);

	//desi gore
	XFORM rotForm3 = Rotate(-180);
	XFORM reflectForm3 = Reflect(-1, 1);
	XFORM tmpForm3,tmpForm33;
	CombineTransform(&tmpForm3, &rotForm3, &reflectForm3);
	CombineTransform(&tmpForm33, &tmpForm3, &tranForm);
	memDC->SetWorldTransform(&tmpForm33);
	DrawTriangle(memDC);
	memDC->SetWorldTransform(&form);

	//desni dole
	XFORM rotForm4 = Rotate(90);
	XFORM reflectForm4 = Reflect(-1, 1);
	XFORM tmpForm4, tmpForm44;
	CombineTransform(&tmpForm4, &rotForm4, &reflectForm4);
	CombineTransform(&tmpForm44, &tmpForm4, &tranForm);
	memDC->SetWorldTransform(&tmpForm44);
	DrawTriangle(memDC);
	memDC->SetWorldTransform(&form);
	//draw..
	
	memDC->SetWorldTransform(&form);
	memDC->SetGraphicsMode(oldMode);
	
	pDC->BitBlt(0,0,rect.Width(),rect.Height(),memDC,0,0,SRCCOPY);
	
	memDC->DeleteDC();
	delete memDC;
}

XFORM CTrougloviView::Translate(float x, float y)
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

XFORM CTrougloviView::Rotate(float a)
{
	XFORM form;
	
	form.eM11 = cos(toRad(a));
	form.eM12 = sin(toRad(a));
	form.eM21 = -sin(toRad(a));
	form.eM22 = cos(toRad(a));
	
	form.eDx = 0;
	form.eDy = 0;
	
	return form;
}

XFORM CTrougloviView::Reflect(float Sx, float Sy)
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

float CTrougloviView::toRad(float angle)
{
	return (3.14 * angle)/180;
}

void CTrougloviView::DrawTriangle(CDC* pDC)
{
	CBrush brush;
	brush.CreateSolidBrush(RGB(68,68,68));
	CBrush *oldBrush = pDC->SelectObject(&brush);
	CPen pen(PS_SOLID,1,RGB(34,177,58));
	CPen *oldPen = pDC->SelectObject(&pen);
	
	pDC->BeginPath();
	pDC->MoveTo(0,0);
	pDC->LineTo(100,0);
	pDC->LineTo(0, 200);
	pDC->LineTo(0,0);
	pDC->EndPath();
	
	pDC->StrokeAndFillPath();
	
	pDC->SelectObject(oldBrush);
	pDC->SelectObject(oldPen);
	pen.DeleteObject();
	brush.DeleteObject();
}

// CTrougloviView printing

BOOL CTrougloviView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTrougloviView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTrougloviView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CTrougloviView diagnostics

#ifdef _DEBUG
void CTrougloviView::AssertValid() const
{
	CView::AssertValid();
}

void CTrougloviView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTrougloviDoc* CTrougloviView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTrougloviDoc)));
	return (CTrougloviDoc*)m_pDocument;
}
#endif //_DEBUG


// CTrougloviView message handlers
