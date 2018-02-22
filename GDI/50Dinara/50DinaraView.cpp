
// 50DinaraView.cpp : implementation of the CMy50DinaraView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "50Dinara.h"
#endif

#include "50DinaraDoc.h"
#include "50DinaraView.h"
#include "DImage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy50DinaraView

IMPLEMENT_DYNCREATE(CMy50DinaraView, CView)

BEGIN_MESSAGE_MAP(CMy50DinaraView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMy50DinaraView construction/destruction

DImage *bg;
CMy50DinaraView::CMy50DinaraView()
{
	// TODO: add construction code here
	bg = new DImage();
	bg->Load((CString)"background.jpg");
}

CMy50DinaraView::~CMy50DinaraView()
{
	delete bg;
}

BOOL CMy50DinaraView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMy50DinaraView drawing

void CMy50DinaraView::OnDraw(CDC* pDC)
{
	CMy50DinaraDoc* pDoc = GetDocument();
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
	CBrush white;
	white.CreateSolidBrush(RGB(255, 255, 255));
	CBrush *oldBrush = memDC->SelectObject(&white);
	memDC->Rectangle(rect);
	memDC->SelectObject(oldBrush);
	white.DeleteObject();

	CPoint ptCenter(250, 250);
	int radius = 100;	
	DrawCoin(memDC,ptCenter,radius,(CString)"Narodna banka Republike Srbije",25,(CString)"50",40,RGB(0,0,0));
	SaveBMP((CString)"test.bmp", memDC, ptCenter, radius);
	//draw..
	
	memDC->SetWorldTransform(&form);
	memDC->SetGraphicsMode(oldMode);
	
	pDC->BitBlt(0,0,rect.Width(),rect.Height(),memDC,0,0,SRCCOPY);
	
	memDC->DeleteDC();
	delete memDC;
}

void CMy50DinaraView::DrawBackground(CDC *pDC, CPoint ptCenter, int radius)
{
	int x1 = ptCenter.x - radius;
	int y1 = ptCenter.y - radius;
	int x2 = ptCenter.x + radius;
	int y2 = ptCenter.y + radius;

	CRgn rgn;
	rgn.CreateEllipticRgn(x1, y1, x2, y2);		
	pDC->SelectClipRgn(&rgn);
	
	bg->Draw(pDC, CRect(0, 0, bg->Width(), bg->Height()), CRect(x1, y1, x2, y2));

	pDC->SelectClipRgn(NULL);
	rgn.DeleteObject();
}

void CMy50DinaraView::DrawCoin(CDC *pDC, CPoint ptCenter, int radius, CString strText, int fsizeText, CString strCoin, int fsizeCoin, COLORREF clrText)
{
	int width = radius * 2;
	int height = radius * 2;
	int startPosx = ptCenter.x - radius;
	int startPosy = ptCenter.y - radius;
	int endPosx = ptCenter.x + radius;
	int endPosy = ptCenter.y + radius;
	
	CPen pen(PS_SOLID,3,RGB(0,0,0));
	CPen *oldPen = pDC->SelectObject(&pen);
	
	pDC->Ellipse(startPosx, startPosy, endPosx, endPosy);
	
	pDC->SelectObject(oldPen);
	pen.DeleteObject();
	
	DrawBackground(pDC, ptCenter, radius);

	// centralni tekst
	CFont font1;
	font1.CreateFont(fsizeCoin, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, (CString)"Arial");
	CFont *oldFont = pDC->SelectObject(&font1);
	int oldFontColor = pDC->SetTextColor(clrText);
	int oldTextAlign = pDC->SetTextAlign(TA_CENTER);
	int oldBkMode = pDC->SetBkMode(TRANSPARENT);

	pDC->TextOut(ptCenter.x, ptCenter.y - fsizeCoin/2, strCoin);

	pDC->SetTextColor(oldFontColor);
	pDC->SetTextAlign(oldTextAlign);
	pDC->SetBkMode(oldBkMode);
	pDC->SelectObject(oldFont);
	font1.DeleteObject();
	
	// text po ivici
	CFont font2;
	font2.CreateFont(fsizeText, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, (CString)"Arial");
	CFont *oldFont2 = pDC->SelectObject(&font2);
	int oldFontColor2 = pDC->SetTextColor(clrText);
	int oldTextAlign2 = pDC->SetTextAlign(TA_CENTER);
	int oldBkMode2 = pDC->SetBkMode(TRANSPARENT);	

	float angle = 360 / (strText.GetLength() - 1);
	float tmpAngle = 0;
	for (int i = 0; i < strText.GetLength(); i++)
	{
		XFORM form;
		pDC->GetWorldTransform(&form);		
		
		TranslateRotate(pDC, ptCenter.x, ptCenter.y, tmpAngle, radius - fsizeText / 2);
		Rotate(pDC, 90, false);

		pDC->BeginPath();
		pDC->TextOut(ptCenter.x, ptCenter.y - fsizeText / 2, (CString)strText.GetAt(i));
		pDC->EndPath();
		pDC->StrokePath();

		tmpAngle += angle;

		pDC->SetWorldTransform(&form);
	}	

	pDC->SetTextColor(oldFontColor2);
	pDC->SetTextAlign(oldTextAlign2);
	pDC->SetBkMode(oldBkMode2);
	pDC->SelectObject(oldFont2);
	font2.DeleteObject();
}

void CMy50DinaraView::SaveBMP(CString name, CDC *pDC, CPoint ptCenter, int radius)
{
	int width = radius * 2;
	int height = radius * 2;
	int startPosx = ptCenter.x - radius;
	int startPosy = ptCenter.y - radius;
	
	CDC *memDC = new CDC();
	memDC->CreateCompatibleDC(NULL);
	
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC,width,height);
	memDC->SelectObject(&bmp);
	
	memDC->BitBlt(0,0,width,height,pDC,startPosx,startPosy,SRCCOPY);
	
	DImage img(bmp);
	img.Save(name);
	
	memDC->DeleteDC();
	delete memDC;
}

float CMy50DinaraView::toRad(float angle)
{
	return (3.14*angle)/180;
}

void CMy50DinaraView::Translate(CDC *pDC, float x, float y, bool right)
{
	XFORM form;
	form.eM11 = 1;
	form.eM12 = 0;
	form.eM21 = 0;
	form.eM22 = 1;
	form.eDx = x;
	form.eDy = y;
	if (right) {
		pDC->ModifyWorldTransform(&form, MWT_RIGHTMULTIPLY);
	}
	else
	{
		pDC->ModifyWorldTransform(&form, MWT_LEFTMULTIPLY);
	}
}

void CMy50DinaraView::TranslateRotate(CDC *pDC,float x, float y, float angle,float distance)
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

void CMy50DinaraView::Rotate(CDC *pDC, float angle,bool right)
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

// CMy50DinaraView printing

BOOL CMy50DinaraView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMy50DinaraView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMy50DinaraView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CMy50DinaraView diagnostics

#ifdef _DEBUG
void CMy50DinaraView::AssertValid() const
{
	CView::AssertValid();
}

void CMy50DinaraView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy50DinaraDoc* CMy50DinaraView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy50DinaraDoc)));
	return (CMy50DinaraDoc*)m_pDocument;
}
#endif //_DEBUG


// CMy50DinaraView message handlers
