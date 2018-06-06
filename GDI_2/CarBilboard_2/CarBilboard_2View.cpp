
// CarBilboard_2View.cpp : implementation of the CCarBilboard_2View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "CarBilboard_2.h"
#endif

#include "CarBilboard_2Doc.h"
#include "CarBilboard_2View.h"
#include "DImage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCarBilboard_2View

IMPLEMENT_DYNCREATE(CCarBilboard_2View, CView)

BEGIN_MESSAGE_MAP(CCarBilboard_2View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CCarBilboard_2View construction/destruction

int move;
HENHMETAFILE tocak, clio;
DImage *bg;
CCarBilboard_2View::CCarBilboard_2View()
{
	move = 0;

	tocak = GetEnhMetaFile((CString)"tocak.emf");
	clio = GetEnhMetaFile((CString)"clio.emf");

	bg = new DImage();
	bg->Load((CString)"sky.jpg");
}

CCarBilboard_2View::~CCarBilboard_2View()
{
	delete bg;
	DeleteEnhMetaFile(clio);
	DeleteEnhMetaFile(tocak);
}

BOOL CCarBilboard_2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CCarBilboard_2View drawing

void CCarBilboard_2View::OnDraw(CDC* pDC)
{
	CCarBilboard_2Doc* pDoc = GetDocument();
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
	bg->Draw(memDC, CRect(0,0,bg->Width(),bg->Height()), CRect(0, 0, rect.Width(), rect.Height()));
	DrawBilboards(memDC);
	DrawCar(memDC);	
	//draw..

	memDC->SetWorldTransform(&form);
	memDC->SetGraphicsMode(oldMode);

	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), memDC, 0, 0, SRCCOPY);

	memDC->DeleteDC();
	delete memDC;
}

void CCarBilboard_2View::DrawCar(CDC *pDC)
{
	CRect rect;
	GetClientRect(&rect);

	float centerX = rect.Width() / 2;
	float centerY = rect.Height() / 2;

	// sasija
	CRect clioRect(centerX - 322.5 + move,
				   centerY - 130,
				   centerX + 322.5 + move,
				   centerY + 130);
	pDC->PlayMetaFile(clio, clioRect);

	XFORM form;
	pDC->GetWorldTransform(&form);
	float predjeniUgao = move / (2 * 3.14);

	//levi tocak	
	TranslateAndRotate(pDC, centerX - 245 + move + 50, centerY + 56 + 50, predjeniUgao);
	CRect lTocakRect(centerX - 245 + move, 
					 centerY + 56, 
					 centerX - 145 + move, 
					 centerY + 156);
	pDC->PlayMetaFile(tocak, lTocakRect);
	pDC->SetWorldTransform(&form);

	//desni tocak
	TranslateAndRotate(pDC, centerX + 173 + move + 50, centerY + 56 + 50, predjeniUgao);
	CRect rTocakRect(centerX + 173 + move, 
					 centerY + 56, 
					 centerX + 273 + move, 
					 centerY + 156);
	pDC->PlayMetaFile(tocak, rTocakRect);
	pDC->SetWorldTransform(&form);
}

void CCarBilboard_2View::DrawBilboards(CDC *pDC)
{
	CRect rect;
	GetClientRect(&rect);

	float centerX = rect.Width() / 2;
	float centerY = rect.Height() / 2;

	CBrush bela, crna, siva;
	bela.CreateSolidBrush(RGB(255, 255, 255));
	crna.CreateSolidBrush(RGB(0, 0, 0));
	siva.CreateSolidBrush(RGB(68, 68, 68));
	CBrush *oldBrush = pDC->SelectObject(&siva);
	CPen pen;
	pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	CPen *oldPen = pDC->SelectObject(&pen);

	// sivo
	CRect sivo(centerX - 382.5, centerY - 190, centerX + 382.5, centerY + 190);
	CRect sivoSenka(centerX - 380, centerY - 185, centerX + 385, centerY + 195);
	pDC->SelectObject(&crna);
	pDC->RoundRect(sivoSenka, CPoint(10, 10));
	pDC->SelectObject(&siva);
	pDC->RoundRect(sivo, CPoint(10, 10));

	// belo	
	CRect belo(centerX - 362.5, centerY - 170, centerX + 362.5, centerY + 170);
	CRect beloSenka(centerX - 360, centerY - 165, centerX + 365, centerY + 175);
	pDC->SelectObject(&crna);
	pDC->RoundRect(beloSenka, CPoint(10, 10));
	pDC->SelectObject(&bela);
	pDC->RoundRect(belo, CPoint(10, 10));
	
	// postolje	crno
	CRect postolje(centerX - 50, centerY + 190, centerX + 50, rect.Height());
	pDC->SelectObject(&crna);
	pDC->Rectangle(postolje);

	pDC->SelectObject(oldPen);
	pDC->SelectObject(oldBrush);
	pen.DeleteObject();
	bela.DeleteObject();
	crna.DeleteObject();
	siva.DeleteObject();
}

void CCarBilboard_2View::TranslateAndRotate(CDC *pDC, float x, float y, float angle) {
	XFORM form;

	form.eM11 = cos(toRad(angle));
	form.eM12 = sin(toRad(angle));
	form.eM21 = -sin(toRad(angle));
	form.eM22 = cos(toRad(angle));

	form.eDx = (float)(x - cos(toRad(angle))*x + sin(toRad(angle))*y);
	form.eDy = (float)(y - cos(toRad(angle))*y - sin(toRad(angle))*x);

	pDC->SetWorldTransform(&form);
}

float CCarBilboard_2View::toRad(float angle) {
	return angle * 3.14 / 180;
}

// CCarBilboard_2View printing

BOOL CCarBilboard_2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCarBilboard_2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCarBilboard_2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CCarBilboard_2View diagnostics

#ifdef _DEBUG
void CCarBilboard_2View::AssertValid() const
{
	CView::AssertValid();
}

void CCarBilboard_2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCarBilboard_2Doc* CCarBilboard_2View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCarBilboard_2Doc)));
	return (CCarBilboard_2Doc*)m_pDocument;
}
#endif //_DEBUG


// CCarBilboard_2View message handlers


void CCarBilboard_2View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default

	if (nChar == VK_LEFT) {
		move -= 5;
		Invalidate();
	}

	if (nChar == VK_RIGHT) {
		move += 5;
		Invalidate();
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


BOOL CCarBilboard_2View::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return TRUE;
}
