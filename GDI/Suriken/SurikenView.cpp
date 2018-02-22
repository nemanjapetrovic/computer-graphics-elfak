
// SurikenView.cpp : implementation of the CSurikenView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Suriken.h"
#endif

#include "SurikenDoc.h"
#include "SurikenView.h"
#include "DImage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



// CSurikenView

IMPLEMENT_DYNCREATE(CSurikenView, CView)

BEGIN_MESSAGE_MAP(CSurikenView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_ERASEBKGND()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CSurikenView construction/destruction

int start_pos_x = 100;
int start_pos_y = 200;
int stablo_x = 0;
float angle = 0;
bool disabled = false;

DImage *bark,*sky;
CSurikenView::CSurikenView()
{
	// TODO: add construction code here
	
	bark = new DImage();
	bark->Load((CString)"bark.jpg");
	sky = new DImage();
	sky->Load((CString)"sky.jpg");
}

CSurikenView::~CSurikenView()
{
	delete bark;
	delete sky;
}

BOOL CSurikenView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CSurikenView drawing

void CSurikenView::OnDraw(CDC* pDC)
{
	CSurikenDoc* pDoc = GetDocument();
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
	sky->Draw(memDC,CRect(0,0,sky->Width(),sky->Height()),CRect(0,0,rect.Width(),rect.Height()));
	bark->Draw(memDC,CRect(0,0,bark->Width(),bark->Height()),CRect(rect.Width()-bark->Width(),0,rect.Width(),rect.Height()));
	stablo_x = rect.Width() - bark->Width();
	
	//########## FIX ##############
	Rotate(memDC,toRad(angle),false);
	Translate(memDC,start_pos_x,start_pos_y,true);
	DrawStar(memDC,320);
	//draw..
	
	memDC->SetWorldTransform(&form);
	memDC->SetGraphicsMode(oldMode);
	
	pDC->BitBlt(0,0,rect.Width(),rect.Height(),memDC,0,0,SRCCOPY);
	
	memDC->DeleteDC();
	delete memDC;
}

void CSurikenView::DrawBlade(CDC* pDC, int size)
{
	CPen pen;
	pen.CreatePen(PS_SOLID,1,RGB(68,68,68));
	CBrush svetloSivo,tamnoSivo;
	svetloSivo.CreateSolidBrush(RGB(195,195,195));
	tamnoSivo.CreateSolidBrush(RGB(58,58,58));
	
	CPen* oldpen = pDC->SelectObject(&pen);
	CBrush* oldbrush = pDC->SelectObject(&svetloSivo);
	
	pDC->BeginPath();
	pDC->MoveTo(0,0);
	pDC->LineTo(size, -size);
	pDC->LineTo(4*size,0);
	pDC->LineTo(0,0);
	pDC->EndPath();
	
	pDC->StrokeAndFillPath();
	
	pDC->SelectObject(&tamnoSivo);
	
	pDC->BeginPath();
	pDC->MoveTo(0,0);
	pDC->LineTo(size,size);
	pDC->LineTo(4*size,0);
	pDC->LineTo(0,0);
	pDC->EndPath();
	
	pDC->StrokeAndFillPath();
	
	pDC->SelectObject(oldpen);
	pDC->SelectObject(oldbrush);
	svetloSivo.DeleteObject();
	tamnoSivo.DeleteObject();
	pen.DeleteObject();

	CFont font;
	font.CreateFont(0.7*size, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, (CString)"Monotype Corsiva");
	CFont *oldFont = pDC->SelectObject(&font);
	
	COLORREF oldTextColor = pDC->SetTextColor(RGB(255,255,255));
	int oldTextAlign = pDC->SetTextAlign(TA_CENTER);
	int oldBkMode = pDC->SetBkMode(TRANSPARENT);
	
	pDC->TextOut(2*size, - (0.7*size)/2, (CString)"Shuricane");
	
	pDC->SetTextColor(RGB(90,90,90));
	pDC->TextOut(2*size, - (0.66*size)/2, (CString)"Shuricane");
	
	pDC->SetTextColor(oldTextColor);
	pDC->SetTextAlign(oldTextAlign);
	pDC->SetBkMode(oldBkMode);
	pDC->SelectObject(oldFont);
	font.DeleteObject();
}

void CSurikenView::Translate(CDC *pDC, float x, float y, bool right)
{
	XFORM form;
	form.eM11 = 1;
	form.eM12 = 0;
	form.eM21 = 0;
	form.eM22 = 1;
	form.eDx = x;
	form.eDy = y;
	if(right){
		pDC->ModifyWorldTransform(&form,MWT_RIGHTMULTIPLY);
	}
	else {
		pDC->ModifyWorldTransform(&form,MWT_LEFTMULTIPLY);
	}
}

void CSurikenView::Rotate(CDC *pDC, float angle, bool right)
{
	XFORM form;
	form.eM11 = cos(angle);
	form.eM12 = sin(angle);
	form.eM21 = -sin(angle);
	form.eM22 = cos(angle);
	form.eDx = 0;
	form.eDy = 0;
	if(right)
		pDC->ModifyWorldTransform(&form,MWT_RIGHTMULTIPLY);
	else
		pDC->ModifyWorldTransform(&form,MWT_LEFTMULTIPLY);
}

float CSurikenView::toRad(float angle)
{
	return (angle*3.14)/180;
}

void CSurikenView::DrawStar(CDC* pDC, int size)
{
	for(int i = 0 ; i < 4 ;i ++){
		float angle = i * 90;
		Rotate(pDC, toRad(angle), false);
		DrawBlade(pDC, size / 8);
	}
}
	
// CSurikenView printing

BOOL CSurikenView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSurikenView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSurikenView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CSurikenView diagnostics

#ifdef _DEBUG
void CSurikenView::AssertValid() const
{
	CView::AssertValid();
}

void CSurikenView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSurikenDoc* CSurikenView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSurikenDoc)));
	return (CSurikenDoc*)m_pDocument;
}
#endif //_DEBUG


// CSurikenView message handlers


BOOL CSurikenView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return TRUE;
}


void CSurikenView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default

	if(nChar == 'W' && !disabled)
	{
		if((start_pos_x + 320/2) - stablo_x >= (320 * 0.10)){
			disabled = true;
		}
		else{
			start_pos_x += 20;
			angle += 10;			
			Invalidate();
		}
	}
	
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
