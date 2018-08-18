
// Pahuljica_1View.cpp : implementation of the CPahuljica_1View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Pahuljica_1.h"
#endif

#include "Pahuljica_1Doc.h"
#include "Pahuljica_1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPahuljica_1View

IMPLEMENT_DYNCREATE(CPahuljica_1View, CView)

BEGIN_MESSAGE_MAP(CPahuljica_1View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CPahuljica_1View construction/destruction

CPahuljica_1View::CPahuljica_1View()
{
	// TODO: add construction code here

}

CPahuljica_1View::~CPahuljica_1View()
{
}

BOOL CPahuljica_1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CPahuljica_1View drawing

void CPahuljica_1View::OnDraw(CDC* pDC)
{
	CPahuljica_1Doc* pDoc = GetDocument();
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
	DrawSnowflakeCrystal(memDC, 250, 250, 100, 20, 45, RGB(255, 255, 255), RGB(68, 68, 68));
	float pattern[]{
		100,
		20,
		50,
		0,
		100,
		20,
		50,
		45
	};
	DrawSnowflakeArm(memDC, 300, 300, 45, pattern, 2, RGB(255, 255, 255), RGB(68, 68, 68));
	//draw...

	memDC->SetWorldTransform(&form);
	memDC->SetGraphicsMode(oldMode);

	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), memDC, 0, 0, SRCCOPY);

	memDC->DeleteDC();
	delete memDC;	
}

void CPahuljica_1View::SetTransform(CDC *pDC, float cx, float cy, float alpha, XFORM *oldForm)
{
	pDC->GetWorldTransform(oldForm);
	
	float tmpAngle = (alpha * 3.14) / 180;
	XFORM rotForm;

	rotForm.eM11 = cos(tmpAngle);
	rotForm.eM12 = sin(tmpAngle);
	rotForm.eM21 = -sin(tmpAngle);
	rotForm.eM22 = cos(tmpAngle);
	rotForm.eDx = 0;
	rotForm.eDy = 0;
	
	XFORM translateForm;

	translateForm.eM11 = 1;
	translateForm.eM12 = 0;
	translateForm.eM21 = 0;
	translateForm.eM22 = 1;
	translateForm.eDx = cx;
	translateForm.eDy = cy;

	XFORM com;

	CombineTransform(&com, &rotForm, &translateForm);
	
	pDC->SetWorldTransform(&com);
}

void CPahuljica_1View::DrawSnowflakeCrystal(CDC *pDC, float cx, float cy, float h, float w, float alpha, COLORREF borderColor, COLORREF fillColor)
{
	CPen pen(PS_SOLID, 1, borderColor);
	CPen *oldPen = pDC->SelectObject(&pen);

	CBrush brush;
	brush.CreateSolidBrush(fillColor);
	CBrush *oldBrush = pDC->SelectObject(&brush);

	int nasp = tan((alpha * 3.14) / 180) * (w / 2);
	CPoint points[]{
		CPoint(0,-h/2-nasp),
		CPoint(w/2,-h/2),
		CPoint(w/2,h/2),
		CPoint(0,h/2+nasp),
		CPoint(-w/2,h/2),
		CPoint(-w/2,-h/2)
	};

	XFORM oldForm;
	SetTransform(pDC, cx, cy, alpha, &oldForm);

	pDC->BeginPath();
	pDC->Polygon(points, 6);
	pDC->EndPath();
	pDC->StrokeAndFillPath();

	pDC->SetWorldTransform(&oldForm);

	pDC->SelectObject(oldPen);
	pDC->SelectObject(oldBrush);
	brush.DeleteObject();
	pen.DeleteObject();
}

void CPahuljica_1View::DrawSnowflakeArm(CDC *pDC, float cx, float cy, float angle, float * pattern, int n, COLORREF borderColor, COLORREF fillColor)
{
	float tmpX = cx;
	int k = -1;
	for (int i = 0; i < n; i++) {
		k++;
		float h = pattern[k];
		k++;
		float w = pattern[k];
		k++;
		float offset = pattern[k];
		k++;
		float tmpAngle = pattern[k];

		tmpX += offset;

		XFORM oldForm;
		SetTransform(pDC, tmpX, cy, tmpAngle, &oldForm);

		DrawSnowflakeCrystal(pDC, tmpX, cy, h, w, angle, borderColor, fillColor);

		pDC->SetWorldTransform(&oldForm);
	}
}

void CPahuljica_1View::DrawSnowflake(CDC *pDC, float cx, float cy, float * pattern, int n, COLORREF borderColor, COLORREF fillColor)
{
	//mrzi me
}

// CPahuljica_1View printing

BOOL CPahuljica_1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPahuljica_1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPahuljica_1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CPahuljica_1View diagnostics

#ifdef _DEBUG
void CPahuljica_1View::AssertValid() const
{
	CView::AssertValid();
}

void CPahuljica_1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPahuljica_1Doc* CPahuljica_1View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPahuljica_1Doc)));
	return (CPahuljica_1Doc*)m_pDocument;
}
#endif //_DEBUG


// CPahuljica_1View message handlers
