
// TestPrimerView.cpp : implementation of the CTestPrimerView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "TestPrimer.h"
#endif

#include "TestPrimerDoc.h"
#include "TestPrimerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestPrimerView

IMPLEMENT_DYNCREATE(CTestPrimerView, CView)

BEGIN_MESSAGE_MAP(CTestPrimerView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CTestPrimerView construction/destruction

CTestPrimerView::CTestPrimerView()
{
	// TODO: add construction code here

}

CTestPrimerView::~CTestPrimerView()
{
}

BOOL CTestPrimerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CTestPrimerView drawing

void CTestPrimerView::OnDraw(CDC* pDC)
{
	CTestPrimerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	CBrush brush;
	brush.CreateSolidBrush(RGB(0,0,0));
	pDC->SelectObject(brush);

	pDC->Rectangle(CRect(-50, -50, 50, 50));

	int oldMode = pDC->SetGraphicsMode(GM_ADVANCED);
	XFORM oldForm;
	pDC->GetWorldTransform(&oldForm);
			
	// Ako hocu
	// => zarotiram za ugao
	// => pomerim na neko mesto
	Rotate(pDC, 20, false);
	Translate(pDC, 300, 150, true);
	pDC->Rectangle(CRect(-50,-50,50,50));
	pDC->SetWorldTransform(&oldForm);

	// Ako hocu
	// => pomerim negde
	// => zarotiram za ugao
	// => pomerim na sledece mesto
	Translate(pDC, 300, 300, false);
	Rotate(pDC, 20, false);
	Translate(pDC, 300, 0, true);
	pDC->Rectangle(CRect(-50,-50,50,50));
	pDC->SetWorldTransform(&oldForm);

	// Ako hocu
	// => rotiraj objekat u pocetnoj tacki (x1,y1) crtanja za ugao 	

	// Ako hocu
	// => rotiraj u odnosu na neku tacku sa pomerajem u neko mesto
	Translate(pDC, 100, 200, true);
	pDC->Rectangle(CRect(-5, -5, 5, 5));
	pDC->SetWorldTransform(&oldForm);

	float angle = 360 / 20 ;
	float tmpAngle = 0;
	for (int i = 0; i < 20; i++) {		
		Rotate(pDC, tmpAngle, false);
		Translate(pDC, 100, 200, true);

		pDC->Rectangle(CRect(50, 0, 55, 5));

		pDC->SetWorldTransform(&oldForm);
		tmpAngle += angle;
	}
	pDC->SetWorldTransform(&oldForm);

	// Ako hocu
	// => rotiraj u odnosu na neku tacku sa pomerajem u neko mesto
	// => rotiraj nakon pomeraja
	CFont font;
	font.CreateFont(20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, (CString)"Arial");
	CFont *oldFont = pDC->SelectObject(&font);

	int fontColor = pDC->SetTextColor(RGB(0, 0, 0));
	int oldAlign = pDC->SetTextAlign(TA_CENTER);
	int bkMode = pDC->SetBkMode(TRANSPARENT);

	CString data("nemanja");
	float angle2 = 360 / 7;
	float tmpAngle2 = 0;
	for (int i = 0; i < 7; i++) {				
		Translate(pDC, 500, 100, true);
		TranslateRotate(pDC, 500, 100, tmpAngle2, 50);
		Rotate(pDC, -tmpAngle2, false);
		//0 -> normalno crtanje
		//90 -> gleda ka centru
		//270 -> gleda ka spoljasnjosti
		//-tmpAngle2 -> pravo na dole

		pDC->TextOut(0, 0, (CString)data[i]);
		
		pDC->SetWorldTransform(&oldForm);
		tmpAngle2 += angle2;
	}

	pDC->SetBkMode(bkMode);
	pDC->SetTextAlign(oldAlign);
	pDC->SetTextColor(fontColor);
	pDC->SelectObject(oldFont);
	font.DeleteObject();	

	pDC->SetWorldTransform(&oldForm);
	pDC->SetGraphicsMode(oldMode);
}

void CTestPrimerView::TranslateRotate(CDC* pDC, float dX, float dY, float angle, float distance)
{
	XFORM form;
	form.eM11 = cos(toRad(angle));
	form.eM12 = sin(toRad(angle));
	form.eM21 = -sin(toRad(angle));
	form.eM22 = cos(toRad(angle));
	
	form.eDx = dX + (distance * cos(toRad(angle)));
	form.eDy = dY + (distance * sin(toRad(angle)));

	SetWorldTransform(pDC->m_hDC, &form);
}

void CTestPrimerView::Translate(CDC* pDC, float dX, float dY, bool rightMultiply)
{
	XFORM xform;
	xform.eM11 = 1;
	xform.eM12 = 0;
	xform.eM21 = 0;
	xform.eM22 = 1;
	xform.eDx = dX;
	xform.eDy = dY;
	if (rightMultiply)
	{
		pDC->ModifyWorldTransform(&xform, MWT_RIGHTMULTIPLY);
	}
	else
	{
		pDC->ModifyWorldTransform(&xform, MWT_LEFTMULTIPLY);
	}
}

void CTestPrimerView::Rotate(CDC* pDC, float angle, bool rightMultiply)
{
	XFORM xform;
	xform.eM11 = cos(toRad(angle));
	xform.eM12 = sin(toRad(angle));
	xform.eM21 = -sin(toRad(angle));
	xform.eM22 = cos(toRad(angle));
	xform.eDx = 0;
	xform.eDy = 0;

	if (rightMultiply)
	{
		pDC->ModifyWorldTransform(&xform, MWT_RIGHTMULTIPLY);
	}
	else
	{
		pDC->ModifyWorldTransform(&xform, MWT_LEFTMULTIPLY);
	}
}

float CTestPrimerView::toRad(float angle) 
{
	return (3.14*angle) / 180;
}
// CTestPrimerView printing

BOOL CTestPrimerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTestPrimerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTestPrimerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CTestPrimerView diagnostics

#ifdef _DEBUG
void CTestPrimerView::AssertValid() const
{
	CView::AssertValid();
}

void CTestPrimerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTestPrimerDoc* CTestPrimerView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTestPrimerDoc)));
	return (CTestPrimerDoc*)m_pDocument;
}
#endif //_DEBUG


// CTestPrimerView message handlers
