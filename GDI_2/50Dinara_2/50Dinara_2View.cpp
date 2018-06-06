
// 50Dinara_2View.cpp : implementation of the CMy50Dinara_2View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "50Dinara_2.h"
#endif

#include "50Dinara_2Doc.h"
#include "50Dinara_2View.h"
#include "DImage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy50Dinara_2View

IMPLEMENT_DYNCREATE(CMy50Dinara_2View, CView)

BEGIN_MESSAGE_MAP(CMy50Dinara_2View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMy50Dinara_2View construction/destruction

DImage *bg;
CMy50Dinara_2View::CMy50Dinara_2View()
{
	// TODO: add construction code here
	bg = new DImage();
	bg->Load((CString)"background.jpg");
}

CMy50Dinara_2View::~CMy50Dinara_2View()
{
	delete bg;
}

BOOL CMy50Dinara_2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMy50Dinara_2View drawing

void CMy50Dinara_2View::OnDraw(CDC* pDC)
{
	CMy50Dinara_2Doc* pDoc = GetDocument();
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

	CBrush grey;
	grey.CreateSolidBrush(RGB(68, 68, 68));
	CBrush *oldBrush = memDC->SelectObject(&grey);

	memDC->Rectangle(CRect(0, 0, rect.Width(), rect.Height()));

	memDC->SelectObject(oldBrush);
	grey.DeleteObject();

	//-----------------------------------

	//pozivi funkcija
	DrawCoin(memDC, CPoint(100, 100), 100, (CString)"Republika Srbija Narodna banka", 25, (CString)"50", 48, RGB(0, 0, 0));

	//draw..

	memDC->SetWorldTransform(&form);
	memDC->SetGraphicsMode(oldMode);

	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), memDC, 0, 0, SRCCOPY);

	memDC->DeleteDC();
	delete memDC;
}

void CMy50Dinara_2View::DrawBackground(CDC *pDC, CPoint ptCenter, int radius)
{
	int x1 = ptCenter.x - radius;
	int y1 = ptCenter.y - radius;
	int x2 = ptCenter.x + radius;
	int y2 = ptCenter.y + radius;

	// Senka na ivici novcica
	CPen pen;
	pen.CreatePen(PS_SOLID, 2, RGB(0,0,0));
	CPen *oldPen = pDC->SelectObject(&pen);

	pDC->BeginPath();
	pDC->Ellipse(CRect(x1, y1, x2, y2));
	pDC->EndPath();
	pDC->StrokePath();
	
	pDC->SelectObject(oldPen);
	pen.DeleteObject();

	// Tekstrua kao pozadina novcica
	CRgn rgn;
	rgn.CreateEllipticRgn(x1, y1, x2, y2);

	pDC->SelectClipRgn(&rgn);
	
	bg->Draw(pDC, CRect(0, 0, bg->Width(), bg->Height()), CRect(x1, y1, x2, y2));	
	
	pDC->SelectClipRgn(NULL);		
}

void CMy50Dinara_2View::DrawCoin(CDC *pDC, CPoint ptCenter, int radius, CString strText, int fsizeText, CString strCoin, int fsizeCoin, COLORREF clrText)
{
	CBrush brush;
	brush.CreateSolidBrush(RGB(0, 0, 0));
	CBrush *oldBrush = pDC->SelectObject(&brush);

	CPen pen;
	pen.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	CPen *oldPen = pDC->SelectObject(&pen);

	DrawBackground(pDC, ptCenter, radius);

	// centar tekst
	CFont font;
	font.CreateFontW(fsizeCoin, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, (CString)"Arial");

	int oldAligment = pDC->SetTextAlign(TA_CENTER);
	int oldBkMode = pDC->SetBkMode(TRANSPARENT);
	COLORREF oldColor = pDC->SetTextColor(clrText);
	CFont *oldFont = pDC->SelectObject(&font);

	pDC->TextOut(ptCenter.x, ptCenter.y - (fsizeCoin / 2), strCoin);

	pDC->SetTextColor(oldColor);
	pDC->SetBkMode(oldBkMode);
	pDC->SetTextAlign(oldAligment);
	pDC->SelectObject(oldFont);
	font.DeleteObject();

	// text na ivici novcica
	CFont font1;
	font1.CreateFont(fsizeText, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, (CString)"Arial");

	int oldAligment1 = pDC->SetTextAlign(TA_CENTER);
	int oldBkMode1 = pDC->SetBkMode(TRANSPARENT);
	COLORREF oldColor1 = pDC->SetTextColor(clrText);
	CFont *oldFont1 = pDC->SelectObject(&font1);

	//tekst
	float tmpAngle = 0;
	float angle = 360 / strText.GetLength();
	for (int i = 0; i < strText.GetLength(); i++) {
		
		XFORM form;
		pDC->GetWorldTransform(&form);

		TranslateRotate(pDC, ptCenter.x, ptCenter.y, tmpAngle, radius - (fsizeText / 2));
		Rotate(pDC, 90, false);

		pDC->BeginPath();
		pDC->TextOut(0, - (fsizeText / 2), (CString) strText.GetAt(i));
		pDC->EndPath();
		pDC->StrokeAndFillPath();

		pDC->SetWorldTransform(&form);

		tmpAngle += angle;
	}

	pDC->SetTextColor(oldColor1);
	pDC->SetBkMode(oldBkMode1);
	pDC->SetTextAlign(oldAligment1);
	pDC->SelectObject(oldFont1);
	font1.DeleteObject();

	SaveBMP((CString)"Danas.bmp", pDC, ptCenter, radius);

	pDC->SelectObject(oldBrush);
	pDC->SelectObject(oldPen);
	pen.DeleteObject();
	brush.DeleteObject();
}

void CMy50Dinara_2View::SaveBMP(CString name, CDC *pDC, CPoint ptCenter, int radius)
{
	int startX = ptCenter.x - radius;
	int startY = ptCenter.y - radius;

	CRect rect;
	GetClientRect(&rect);

	CDC *memDC = new CDC();
	memDC->CreateCompatibleDC(NULL);

	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC, radius * 2, radius * 2);
	memDC->SelectObject(&bmp);

	memDC->BitBlt(0, 0, radius * 2, radius * 2, pDC, startX, startY, SRCCOPY);

	DImage img(bmp);
	img.Save(name);

	memDC->DeleteDC();
	delete memDC;
}

float CMy50Dinara_2View::toRad(float angle)
{
	return (angle * 3.14 )/ 180;
}

void CMy50Dinara_2View::TranslateRotate(CDC *pDC, float x, float y, float angle, float distance)
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

void CMy50Dinara_2View::Rotate(CDC *pDC, float angle, bool rightMultiply)
{
	XFORM form;
	form.eM11 = cos(toRad(angle));
	form.eM12 = sin(toRad(angle));
	form.eM21 = -sin(toRad(angle));
	form.eM22 = cos(toRad(angle));
	form.eDx = 0;
	form.eDy = 0;

	if (rightMultiply)
		pDC->ModifyWorldTransform(&form, MWT_RIGHTMULTIPLY);
	else
		pDC->ModifyWorldTransform(&form, MWT_LEFTMULTIPLY);
}

// CMy50Dinara_2View printing

BOOL CMy50Dinara_2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMy50Dinara_2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMy50Dinara_2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CMy50Dinara_2View diagnostics

#ifdef _DEBUG
void CMy50Dinara_2View::AssertValid() const
{
	CView::AssertValid();
}

void CMy50Dinara_2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy50Dinara_2Doc* CMy50Dinara_2View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy50Dinara_2Doc)));
	return (CMy50Dinara_2Doc*)m_pDocument;
}
#endif //_DEBUG


// CMy50Dinara_2View message handlers
