
// 50Dinara_3View.cpp : implementation of the CMy50Dinara_3View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "50Dinara_3.h"
#endif

#include "50Dinara_3Doc.h"
#include "50Dinara_3View.h"
#include "DImage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy50Dinara_3View

IMPLEMENT_DYNCREATE(CMy50Dinara_3View, CView)

BEGIN_MESSAGE_MAP(CMy50Dinara_3View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMy50Dinara_3View construction/destruction

DImage *bg;
CMy50Dinara_3View::CMy50Dinara_3View()
{
	// TODO: add construction code here
	bg = new DImage();
	bg->Load((CString)"bg.jpg");
}

CMy50Dinara_3View::~CMy50Dinara_3View()
{
	delete bg;
}

BOOL CMy50Dinara_3View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}






void CMy50Dinara_3View::OnDraw(CDC* pDC)
{
	CMy50Dinara_3Doc* pDoc = GetDocument();
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


	///draw..
	CPoint point(250, 250);
	int radius = 100;
	DrawBackground(memDC, point, radius);
	DrawCoin(memDC, point, radius, (CString)"Republika Srbija Narodna banka", 12, (CString)"50", 100, RGB(27, 255, 94));
	///draw..

	memDC->SetWorldTransform(&form);
	memDC->SetGraphicsMode(oldMode);

	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), memDC, 0, 0, SRCCOPY);

	//Save screenshot novcica
	SaveBMP((CString)"screen.bmp", pDC, point, radius);

	memDC->DeleteDC();
	delete memDC;
}

void CMy50Dinara_3View::DrawBackground(CDC *pDC, CPoint ptCenter, int radius)
{
	CRect rect(ptCenter.x - radius, ptCenter.y - radius, ptCenter.x + radius, ptCenter.y + radius);

	CRgn rgn;
	rgn.CreateEllipticRgn(rect.left, rect.top, rect.right, rect.bottom);
	pDC->SelectClipRgn(&rgn);

	bg->Draw(pDC, CRect(0, 0, bg->Width(), bg->Height()), rect);

	pDC->SelectClipRgn(NULL);
}

void CMy50Dinara_3View::DrawCoin(CDC *pDC, CPoint ptCenter, int radius, CString strText, int fsizeText, CString strCoin, int fsizeCoin, COLORREF clrText)
{
	// crtanje ivice novcica
	CPen pen(PS_SOLID, 3, RGB(23, 58, 242));
	CPen *oldPen = pDC->SelectObject(&pen);

	//transparentna cetka
	CBrush *oldBrush = (CBrush *)pDC->SelectStockObject(NULL_BRUSH);	

	CRect rect(ptCenter.x - radius, ptCenter.y - radius, ptCenter.x + radius, ptCenter.y + radius);
	pDC->Ellipse(&rect);

	pDC->SelectObject(oldBrush);
	pDC->SelectObject(oldPen);
	pen.DeleteObject();

	//priprema olovke i brusheva
	CPen blackPen(PS_SOLID, 1, RGB(0, 0, 0));
	CPen *oldPen1 = pDC->SelectObject(&blackPen);
	
	CBrush brush;
	brush.CreateSolidBrush(clrText);
	CBrush *oldBrush1 = pDC->SelectObject(&brush);

	//ispis teksta u sredini
	CFont font1;
	font1.CreateFont(fsizeCoin, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, (CString)"Arial");
	CFont *oldFont = pDC->SelectObject(&font1);

	int oldBkMode1 = pDC->SetBkMode(TRANSPARENT);
	int oldTextAlign1 = pDC->SetTextAlign(TA_CENTER);
	COLORREF oldTextCol1 = pDC->SetTextColor(clrText);

	pDC->BeginPath();
	pDC->TextOut(ptCenter.x, (ptCenter.y - (fsizeCoin / 2)), strCoin);
	pDC->EndPath();
	pDC->StrokeAndFillPath();

	pDC->SetTextColor(oldTextCol1);
	pDC->SetTextAlign(oldTextAlign1);
	pDC->SetBkMode(oldBkMode1);
	
	//ispis teksta sa strane
	CFont font2;
	font2.CreateFont(fsizeText, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, (CString)"Arial");
	pDC->SelectObject(&font2);

	int oldBkMode2 = pDC->SetBkMode(TRANSPARENT);
	int oldTextAlign2 = pDC->SetTextAlign(TA_CENTER);
	COLORREF oldTextCol2 = pDC->SetTextColor(clrText);

	
	float angle = 360 / strText.GetLength();
	float tmpAngle = 0;
	for (int i = 0; i < strText.GetLength(); i++) 
	{		
		XFORM form;
		pDC->GetWorldTransform(&form);

		TranslateRotate(pDC, ptCenter.x, ptCenter.y, tmpAngle, radius - (fsizeText / 2));
		Rotate(pDC, 90, false);

		pDC->BeginPath();
		pDC->TextOut(0, fsizeText / 2, (CString)strText.GetAt(i));
		pDC->EndPath();
		pDC->StrokeAndFillPath();

		pDC->SetWorldTransform(&form);
		
		tmpAngle += angle;
	}

	pDC->SetTextColor(oldTextCol2);
	pDC->SetTextAlign(oldTextAlign2);
	pDC->SetBkMode(oldBkMode2);

	//ciscenje
	pDC->SelectObject(oldFont);
	pDC->SelectObject(oldPen1);
	pDC->SelectObject(oldBrush1);
	brush.DeleteObject();
	blackPen.DeleteObject();
	font1.DeleteObject();
	font2.DeleteObject();
}

void CMy50Dinara_3View::SaveBMP(CString name, CDC *pDC, CPoint ptCenter, int radius)
{
	int novcic_width = radius * 2;
	int novcic_height = radius * 2;

	CDC *memDC = new CDC();
	memDC->CreateCompatibleDC(NULL);

	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC, novcic_width, novcic_height);
	memDC->SelectObject(&bmp);

	memDC->BitBlt(0, 0, novcic_width, novcic_height, pDC, ptCenter.x - radius, ptCenter.y - radius, SRCCOPY);

	DImage *img = new DImage(bmp);
	img->Save(name);
	delete img;

	memDC->DeleteDC();
	delete memDC;
}

float CMy50Dinara_3View::toRad(float angle)
{
	return (angle * 3.14) / 180;
}

void CMy50Dinara_3View::Rotate(CDC *pDC, float angle, bool right)
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

void CMy50Dinara_3View::TranslateRotate(CDC *pDC, float x, float y, float angle, float distance)
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

BOOL CMy50Dinara_3View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMy50Dinara_3View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMy50Dinara_3View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CMy50Dinara_3View diagnostics

#ifdef _DEBUG
void CMy50Dinara_3View::AssertValid() const
{
	CView::AssertValid();
}

void CMy50Dinara_3View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy50Dinara_3Doc* CMy50Dinara_3View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy50Dinara_3Doc)));
	return (CMy50Dinara_3Doc*)m_pDocument;
}
#endif //_DEBUG


// CMy50Dinara_3View message handlers
