
// ClioDrive_1View.cpp : implementation of the CClioDrive_1View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "ClioDrive_1.h"
#endif

#include "ClioDrive_1Doc.h"
#include "ClioDrive_1View.h"
#include "DImage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CClioDrive_1View

IMPLEMENT_DYNCREATE(CClioDrive_1View, CView)

BEGIN_MESSAGE_MAP(CClioDrive_1View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CClioDrive_1View construction/destruction
HENHMETAFILE clio;
DImage *wheel;
int carW = 450;
int carH = 450 / 2;
int wheelSize = 38;
float moveAngle = 0;
float angleGround = 10;
float move = 0;
int carCenterX, carCenterY, lwX, lwY, rwX, rwY;
CClioDrive_1View::CClioDrive_1View()
{
	// TODO: add construction code here
	carCenterX = 0;
	carCenterY = 0;

	clio = GetEnhMetaFile((CString)"clio.emf");
	wheel = new DImage();
	wheel->Load((CString)"Wheel.png");
}

CClioDrive_1View::~CClioDrive_1View()
{	
	DeleteEnhMetaFile(clio);
	delete wheel;
}

BOOL CClioDrive_1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CClioDrive_1View drawing

void CClioDrive_1View::OnDraw(CDC* pDC)
{
	CClioDrive_1Doc* pDoc = GetDocument();
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
	DrawGround(memDC, angleGround);
	
	//postavljanje clia na strmu ravan
	carCenterX += move;
	Translate(memDC, carW / 2, -carH / 2, true);
	Rotate(memDC, -angleGround, true);
	Translate(memDC, 0, rect.Height(), true);

	DrawCar(memDC, carCenterX, carCenterY, carW, carH);

	float rotAngle = ((moveAngle / (3.14 * 2)) * 180) / 3.14;
	DrawWheel(memDC, carCenterX-155, carCenterY+70, wheelSize, rotAngle);
	DrawWheel(memDC, carCenterX+135, carCenterY+70, wheelSize, rotAngle);

	move = 0;
	//draw..
	
	memDC->SetWorldTransform(&form);
	memDC->SetGraphicsMode(oldMode);

	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), memDC, 0, 0, SRCCOPY);

	memDC->DeleteDC();
	delete memDC;
}

void CClioDrive_1View::DrawGround(CDC* pDC, float angle)
{
	CRect rect;
	GetClientRect(&rect);

	CPen pen(PS_SOLID, 3, RGB(60,20,30));
	CPen *oldPen = pDC->SelectObject(&pen);
	CBrush plava, srafirana;
	plava.CreateSolidBrush(RGB(0, 128, 198));	
	srafirana.CreateHatchBrush(HS_FDIAGONAL, RGB(0, 128, 128));
	CBrush *oldBrush = pDC->SelectObject(&plava);

	pDC->Rectangle(rect);
	
	float nasp;
	float nal = rect.Width();
	nasp = tan(toRad(angle)) * nal;

	pDC->SelectObject(&srafirana);
	pDC->BeginPath();
	pDC->MoveTo(0, rect.Height());
	pDC->LineTo(rect.Width(), rect.Height() - nasp);
	pDC->LineTo(rect.Width(), rect.Height());
	pDC->LineTo(0, rect.Height());
	pDC->EndPath();
	pDC->StrokeAndFillPath();

	pDC->SelectObject(oldPen);
	pen.DeleteObject();
}

void CClioDrive_1View::DrawCar(CDC* pDC, int x, int y, int w, int h)
{
	//CRect bounds(x - w / 2, y - h / 2, x + w / 2, y + h / 2);
	CRect invertBounds(x + w / 2, y - h / 2, x - w / 2, y + h / 2);
	pDC->PlayMetaFile(clio, invertBounds);
}

void CClioDrive_1View::DrawWheel(CDC* pDC, int x, int y, int r, float angle)
{
	XFORM form;
	pDC->GetWorldTransform(&form);
	
	Translate(pDC, x, y, false);
	Rotate(pDC, angle, false);

	wheel->Draw(pDC, CRect(52, 15, 52+376, 15+376), CRect(-r,-r,r,r));

	pDC->SetWorldTransform(&form);
}

float CClioDrive_1View::toRad(float angle)
{
	return (angle * 3.14) / 180;
}

void CClioDrive_1View::Translate(CDC* pDC, float dX, float dY, bool rightMultiply)
{
	XFORM form;

	form.eM11 = 1;
	form.eM12 = 0;
	form.eM21 = 0;
	form.eM22 = 1;

	form.eDx = dX;
	form.eDy = dY;

	if (rightMultiply)
		pDC->ModifyWorldTransform(&form, MWT_RIGHTMULTIPLY);
	else
		pDC->ModifyWorldTransform(&form, MWT_LEFTMULTIPLY);
}

void CClioDrive_1View::Rotate(CDC* pDC, float angle, bool rightMultiply)
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

void CClioDrive_1View::Scale(CDC* pDC, float sX, float sY, bool rightMultiply)
{
	XFORM form;

	form.eM11 = sX;
	form.eM12 = 0;
	form.eM21 = 0;
	form.eM22 = sY;
	
	form.eDx = 0;
	form.eDy = 0;
	
	if (rightMultiply)
		pDC->ModifyWorldTransform(&form, MWT_RIGHTMULTIPLY);
	else
		pDC->ModifyWorldTransform(&form, MWT_LEFTMULTIPLY);
}

// CClioDrive_1View printing

BOOL CClioDrive_1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CClioDrive_1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CClioDrive_1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CClioDrive_1View diagnostics

#ifdef _DEBUG
void CClioDrive_1View::AssertValid() const
{
	CView::AssertValid();
}

void CClioDrive_1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CClioDrive_1Doc* CClioDrive_1View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CClioDrive_1Doc)));
	return (CClioDrive_1Doc*)m_pDocument;
}
#endif //_DEBUG


// CClioDrive_1View message handlers


void CClioDrive_1View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default

	if (nChar == VK_RIGHT) {
		move += 10;
		moveAngle += 10;
		Invalidate();
	}
	else if (nChar == VK_LEFT) {
		move -= 10;
		moveAngle -= 10;
		Invalidate();
	}
	else if (nChar == VK_UP && angleGround < 80) {
		angleGround += 10;
		Invalidate();
	}
	else if (nChar == VK_DOWN && angleGround > 10) {
		angleGround -= 10;
		Invalidate();
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
