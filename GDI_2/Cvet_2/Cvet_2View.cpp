
// Cvet_2View.cpp : implementation of the CCvet_2View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Cvet_2.h"
#endif

#include "Cvet_2Doc.h"
#include "Cvet_2View.h"
#include "DImage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCvet_2View

IMPLEMENT_DYNCREATE(CCvet_2View, CView)

BEGIN_MESSAGE_MAP(CCvet_2View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CCvet_2View construction/destruction

CCvet_2View::CCvet_2View()
{
	// TODO: add construction code here

}

CCvet_2View::~CCvet_2View()
{
}

BOOL CCvet_2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CCvet_2View drawing

void CCvet_2View::OnDraw(CDC* pDC)
{
	CCvet_2Doc* pDoc = GetDocument();
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
	DrawRosete(memDC, 0, 0, 250, 6);
	CreateTriangleBmp((CString)"bg.jpg");
	//draw..

	memDC->SetWorldTransform(&form);
	memDC->SetGraphicsMode(oldMode);

	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), memDC, 0, 0, SRCCOPY);

	memDC->DeleteDC();
	delete memDC;
}

void CCvet_2View::Rotate(CDC *pDC, float angle, bool right)
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

void CCvet_2View::TranslateRotate(CDC *pDC, float x, float y, float angle, float distance)
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

float CCvet_2View::toRad(float angle)
{
	return (angle * 3.14) / 180;
}

void CCvet_2View::DrawRosete(CDC *pDC, int x, int y, int size, int count)
{
	CBrush orange, white, yellow;
	orange.CreateSolidBrush(RGB(255,126,65));
	white.CreateSolidBrush(RGB(255, 255, 255));
	yellow.CreateSolidBrush(RGB(255, 222, 32));
	CBrush *oldBrush = pDC->SelectObject(&orange);
	
	CPen pen(PS_SOLID, 1, RGB(0, 0, 0));
	CPen *oldPen = pDC->SelectObject(&pen);

	// veci krug
	CRect veciKrug(x - size, y - size, x + size, y + size);	
	pDC->Ellipse(veciKrug);

	// listovi
	pDC->SelectObject(&white);
	float angle = 360 / count;
	float tmpAngle = 0;
	for (int i = 0; i < count; i++) 
	{
		XFORM form;
		pDC->GetWorldTransform(&form);

		TranslateRotate(pDC, 0.0, 0.0, tmpAngle, (size / 2));
		pDC->Ellipse(CRect(x - (size / 2), y - ((size / 3) / 2), x + (size / 2), y + ((size / 3) / 2)));

		pDC->SetWorldTransform(&form);
		tmpAngle += angle;
	}

	// manji krug
	pDC->SelectObject(&yellow);
	CRect manjiKrug(x - (size / 3), y - (size / 3), x + (size / 3), y + (size / 3));
	pDC->Ellipse(manjiKrug);

	pDC->SelectObject(oldPen);
	pDC->SelectObject(oldBrush);
	orange.DeleteObject();
	pen.DeleteObject();
}

void CCvet_2View::CreateTriangleBmp(CString fileName)
{
	DImage *img = new DImage();
	img->Load(fileName);

	CRect rect;
	GetClientRect(&rect);

	CDC *pDC = GetDC();

	CDC *memDC = new CDC();
	memDC->CreateCompatibleDC(NULL);

	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC, img->Width(), img->Height());
	memDC->SelectObject(&bmp);

	// Iscrtavanje slike u pDC u obliku trougla
	pDC->BeginPath();
	pDC->MoveTo(0, img->Height());
	pDC->LineTo(img->Width(), img->Height());
	pDC->LineTo(img->Width() / 2, 0);
	pDC->LineTo(0, img->Height());
	pDC->EndPath();

	CRgn rgn;
	rgn.CreateFromPath(pDC);
	pDC->SelectClipRgn(&rgn);
	
	img->Draw(pDC, CRect(0, 0, img->Width(), img->Height()), CRect(0, 0, rect.Width(), rect.Height()));

	pDC->SelectClipRgn(NULL);
	rgn.DeleteObject();

	// Prebacivanje slike iz pDC u memDC i snimanje bitmape posle toga
	memDC->BitBlt(0, 0, rect.Width(), rect.Height(), pDC, 0, 0, SRCCOPY);

	DImage saved(bmp);
	saved.Save((CString)"Output.bmp");

	delete img;
}

BOOL CCvet_2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCvet_2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCvet_2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CCvet_2View diagnostics

#ifdef _DEBUG
void CCvet_2View::AssertValid() const
{
	CView::AssertValid();
}

void CCvet_2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCvet_2Doc* CCvet_2View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCvet_2Doc)));
	return (CCvet_2Doc*)m_pDocument;
}
#endif //_DEBUG


// CCvet_2View message handlers
