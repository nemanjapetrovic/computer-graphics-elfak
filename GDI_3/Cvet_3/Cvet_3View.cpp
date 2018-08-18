
// Cvet_3View.cpp : implementation of the CCvet_3View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Cvet_3.h"
#endif

#include "Cvet_3Doc.h"
#include "Cvet_3View.h"
#include "DImage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCvet_3View

IMPLEMENT_DYNCREATE(CCvet_3View, CView)

BEGIN_MESSAGE_MAP(CCvet_3View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CCvet_3View construction/destruction

DImage *img;
CCvet_3View::CCvet_3View()
{	
	img = new DImage();
	img->Load((CString)"bg.jpg");
}

CCvet_3View::~CCvet_3View()
{
	delete img;
}

BOOL CCvet_3View::PreCreateWindow(CREATESTRUCT& cs)
{	
	return CView::PreCreateWindow(cs);
}

// CCvet_3View drawing

void CCvet_3View::OnDraw(CDC* pDC)
{
	CCvet_3Doc* pDoc = GetDocument();
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

	//draw...
	CreateTriangleBmp();
	DrawRosete(memDC, 250, 250, 100, 8);
	//draw...

	memDC->SetWorldTransform(&form);
	memDC->SetGraphicsMode(oldMode);

	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), memDC, 0, 0, SRCCOPY);

	memDC->DeleteDC();
	delete memDC;
}


void CCvet_3View::DrawRosete(CDC *pDC, int x, int y, int size, int count)
{
	CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
	CPen *oldPen = pDC->SelectObject(&pen);

	CBrush white, orange;
	white.CreateSolidBrush(RGB(255, 255, 255));
	orange.CreateSolidBrush(RGB(255, 127, 39));
	CBrush *oldBrush = pDC->SelectObject(&orange);

	//spoljasnja kruznica
	pDC->Ellipse(x-size, y-size, x+size, y+size);

	//elipse
	pDC->SelectObject(&white);
	int visinaElipsi = size / 3;
	float angle = 360 / count;
	float tmpAngle = 0;
	for (int i = 0; i < count; i++) {
		XFORM form;
		pDC->GetWorldTransform(&form);

		TranslateRotate(pDC, x, y, tmpAngle, size / 2);
		pDC->Ellipse(-size / 2, -visinaElipsi / 2, size / 2, visinaElipsi / 2);

		pDC->SetWorldTransform(&form);

		tmpAngle += angle;
	}

	//unutrasnja kruznica
	pDC->SelectObject(&orange);
	pDC->Ellipse(x - visinaElipsi, y - visinaElipsi, x + visinaElipsi, y + visinaElipsi);

	pDC->SelectObject(oldBrush);
	pDC->SelectObject(oldPen);
	white.DeleteObject();
	orange.DeleteObject();
	pen.DeleteObject();
}

void CCvet_3View::CreateTriangleBmp()
{
	CRect rect;
	GetClientRect(&rect);

	CDC *pDC = GetDC();

	CDC *memDC = new CDC();
	memDC->CreateCompatibleDC(NULL);

	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC, img->Width(), img->Height());
	memDC->SelectObject(&bmp);

	pDC->BeginPath();
	pDC->MoveTo(0, img->Height());
	pDC->LineTo(img->Width() / 2, 0);
	pDC->LineTo(img->Width(), img->Height());
	pDC->LineTo(0, img->Height());
	pDC->EndPath();

	CRgn rgn;
	rgn.CreateFromPath(pDC);
	pDC->SelectClipRgn(&rgn);

	img->Draw(pDC, CRect(0, 0, img->Width(), img->Height()), CRect(0, 0, rect.Width(), rect.Height()));

	pDC->SelectClipRgn(NULL);
	rgn.DeleteObject();

	memDC->BitBlt(0, 0, img->Width(), img->Height(), pDC, 0, 0, SRCCOPY);

	DImage img(bmp);
	img.Save((CString)"output.bmp");

	memDC->DeleteDC();
	delete memDC;
}

void CCvet_3View::TranslateRotate(CDC *pDC, int x, int y, float angle, float distance) 
{
	float tmpAngle = (angle * 3.14) / 180;
	XFORM form;

	form.eM11 = cos(tmpAngle);
	form.eM12 = sin(tmpAngle);
	form.eM21 = -sin(tmpAngle);
	form.eM22 = cos(tmpAngle);

	form.eDx = x + (distance * cos(tmpAngle));
	form.eDy = y + (distance * sin(tmpAngle));

	pDC->SetWorldTransform(&form);
}

// CCvet_3View printing

BOOL CCvet_3View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCvet_3View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCvet_3View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CCvet_3View diagnostics

#ifdef _DEBUG
void CCvet_3View::AssertValid() const
{
	CView::AssertValid();
}

void CCvet_3View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCvet_3Doc* CCvet_3View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCvet_3Doc)));
	return (CCvet_3Doc*)m_pDocument;
}
#endif //_DEBUG


// CCvet_3View message handlers
