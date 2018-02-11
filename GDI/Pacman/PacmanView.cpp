
// PacmanView.cpp : implementation of the CPacmanView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Pacman.h"
#endif

#include "PacmanDoc.h"
#include "PacmanView.h"
#include "DImage.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPacmanView

IMPLEMENT_DYNCREATE(CPacmanView, CView)

BEGIN_MESSAGE_MAP(CPacmanView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_ERASEBKGND()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CPacmanView construction/destruction

bool end = false;
int moveCase = 0;
int move_hor = 0;
int move_ver = 0;
int posx = 200;
int posy = 200;
bool open = true;
float angle = 10;

DImage* bg;

CPacmanView::CPacmanView()
{
	// TODO: add construction code here
	bg = new DImage();
	bg->Load((CString)"blue.png");
}

CPacmanView::~CPacmanView()
{
	delete bg;
}

BOOL CPacmanView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CPacmanView drawing

void CPacmanView::OnDraw(CDC* pDC)
{
	CPacmanDoc* pDoc = GetDocument();
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
	bg->Draw(memDC, CRect(0, 0, bg->Width(), bg->Height()), CRect(0, 0, rect.Width(), rect.Height()));
	
	int px1 = posx + move_hor;
	int py1 = posy + move_ver;
	int px2 = posx + move_hor + 100;
	int py2 = posy + move_ver + 100;
	CRect pac(px1, py1, px2, py2);
	DrawPacman(memDC, pac, angle);

	int gx1 = rect.Width() / 2;
	int gy1 = rect.Height() / 2;
	int gx2 = rect.Width() / 2 + 100;
	int gy2 = rect.Height() / 2 + 100;
	CRect ghost(gx1, gy1, gx2, gy2);
	DrawGhost(memDC,ghost);

	//collision
	int r_pac = pac.Width() / 2;
	int r_ghost = ghost.Width() / 2;
	int dx = pac.left - ghost.left;
	int dy = pac.top - ghost.top;
	if (sqrt(dx*dx + dy*dy) <= (r_pac + r_ghost))
	{
		end = true;
	}
	//draw..
	
	memDC->SetWorldTransform(&form);
	memDC->SetGraphicsMode(oldMode);
	
	pDC->BitBlt(0,0,rect.Width(),rect.Height(),memDC,0,0,SRCCOPY);
	
	memDC->DeleteDC();
	delete memDC;
}

void CPacmanView::DrawPacman(CDC* pDC, CRect rect, float angle)
{
	CRect globalRect;
	GetClientRect(&globalRect);
	
	XFORM form;
	pDC->GetWorldTransform(&form);
	
	switch(moveCase){
		case 1:
			Translate(pDC,-(rect.left + rect.Width()/2),-(rect.top + rect.Height()/2),true);
			Rotate(pDC,toRad(-90),true);
			Translate(pDC,(rect.left + rect.Width()/2),(rect.top + rect.Height()/2),true);
			break;
		case 2:
			//nothing to do here just reset transform
			pDC->SetWorldTransform(&form);
			break;
		case 3:
			Translate(pDC,-(rect.left + rect.Width()/2),-(rect.top + rect.Height()/2),true);
			Rotate(pDC,toRad(90),true);
			Translate(pDC,(rect.left + rect.Width()/2),(rect.top + rect.Height()/2),true);
			break;
		case 4:
			pDC->SetWorldTransform(&form);
			Translate(pDC, -(rect.left + rect.Width() / 2), -(rect.top + rect.Height() / 2), true);
			Reflect(pDC, -1, 1, true);
			Translate(pDC, rect.left + rect.Width() / 2, rect.top + rect.Height() / 2, true);
			break;		
	}
	
	CPen pen(PS_SOLID,1,RGB(0,0,0));
	CBrush brush;
	brush.CreateSolidBrush(RGB(255,242,0));
	CBrush *oldBrush = pDC->SelectObject(&brush);
	CPen *oldPen = pDC->SelectObject(&pen);
	
	int mouthSize = rect.Width()/2 * tan(toRad(angle * 2));	
	int x1 = rect.left;
	int y1 = rect.top;
	int x2 = rect.right;
	int y2 = rect.bottom;
	int x3 = rect.left + rect.Width();
	int y3 = rect.top + (rect.Height() /2 - mouthSize);
	int x4 = rect.left + rect.Width();
	int y4 = rect.top + (rect.Height() - (rect.Height() / 2 - mouthSize));
	
	pDC->Pie(x1,y1,x2,y2,x3,y3,x4,y4);

	CBrush brush2;
	brush2.CreateSolidBrush(RGB(0, 0, 0));
	pDC->SelectObject(&brush2);
	pDC->Ellipse(CRect(x1 + rect.Width() / 2 + 10, rect.top + 20, x1 + rect.Width() / 2 + 20, rect.top + 30));

	pDC->SelectObject(oldBrush);
	pDC->SelectObject(oldPen);
	brush.DeleteObject();
	pen.DeleteObject();
	
	pDC->SetWorldTransform(&form);
}

void CPacmanView::DrawGhost(CDC* pDC, CRect rect)
{
	CBrush brush;
	brush.CreateSolidBrush(RGB(68,68,68));
	CBrush *oldBrush = pDC->SelectObject(&brush);
	
	pDC->Ellipse(rect);
	
	CFont font;
	font.CreateFont(10,0,0,0,0,0,0,0,0,0,0,0,0,(CString)"Arial");
	CFont *oldFont = pDC->SelectObject(&font);
	
	COLORREF oldTextColor = pDC->SetTextColor(RGB(127,221,0));
	int oldAlign = pDC->SetTextAlign(TA_CENTER);
	int oldBkMode = pDC->SetBkMode(TRANSPARENT);
	
	pDC->TextOut(rect.left+rect.Width()/2, rect.top + rect.Height()/2 - 5,(CString)"Mrzi me da crtam duha");
	
	pDC->SetBkMode(oldBkMode);
	pDC->SetTextAlign(oldAlign);
	pDC->SetTextColor(oldTextColor);
	
	pDC->SelectObject(oldFont);	
	pDC->SelectObject(oldBrush);
	brush.DeleteObject();
	font.DeleteObject();
}

float CPacmanView::toRad(float angle)
{
	return (3.14 * angle) / 180;
}

void CPacmanView::Rotate(CDC *pDC, float angle, bool right)
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

void CPacmanView::Reflect(CDC *pDC, int x, int y, bool right)
{
	XFORM form;
	form.eM11 = x;
	form.eM12 = 0;
	form.eM21 = 0;
	form.eM22 = y;
	form.eDx = 0;
	form.eDy = 0;
	if(right)
		pDC->ModifyWorldTransform(&form,MWT_RIGHTMULTIPLY);
	else
		pDC->ModifyWorldTransform(&form,MWT_LEFTMULTIPLY);
}
	

void CPacmanView::Translate(CDC *pDC, int x, int y, bool right)
{
	XFORM form;
	form.eM11 = 1;
	form.eM12 = 0;
	form.eM21 = 0;
	form.eM22 = 1;
	form.eDx = x;
	form.eDy = y;
	if(right)
		pDC->ModifyWorldTransform(&form,MWT_RIGHTMULTIPLY);
	else
		pDC->ModifyWorldTransform(&form,MWT_LEFTMULTIPLY);
}
	
// CPacmanView printing
BOOL CPacmanView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPacmanView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPacmanView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CPacmanView diagnostics

#ifdef _DEBUG
void CPacmanView::AssertValid() const
{
	CView::AssertValid();
}

void CPacmanView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPacmanDoc* CPacmanView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPacmanDoc)));
	return (CPacmanDoc*)m_pDocument;
}
#endif //_DEBUG


// CPacmanView message handlers


BOOL CPacmanView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return TRUE;
}


void CPacmanView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	if (end) {		
		return;
	}
	if(open)
	{
		angle = 0;
		open = false;
	} 
	else
	{
		angle = 10;
		open = true;
	}
	
	if(nChar == VK_LEFT){
		moveCase = 4;
		move_hor -= 10;
	}
	
	if(nChar == VK_RIGHT){		
		moveCase = 2; 
		move_hor += 10;
	}
	
	if(nChar == VK_DOWN){		
		moveCase = 3;
		move_ver += 10;
	}
	
	if(nChar == VK_UP){
		moveCase = 1;
		move_ver -= 10;
	}
	
	Invalidate();
	
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
