
// Reduce_1View.cpp : implementation of the CReduce_1View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Reduce_1.h"
#endif

#include "Reduce_1Doc.h"
#include "Reduce_1View.h"
#include "DImage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CReduce_1View

IMPLEMENT_DYNCREATE(CReduce_1View, CView)

BEGIN_MESSAGE_MAP(CReduce_1View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CReduce_1View construction/destruction
DImage *img;
CReduce_1View::CReduce_1View()
{
	// TODO: add construction code here
	img = new DImage();
	img->Load((CString)"bg.jpg");
}

CReduce_1View::~CReduce_1View()
{
	delete img;
}

BOOL CReduce_1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CReduce_1View drawing

void CReduce_1View::OnDraw(CDC* pDC)
{
	CReduce_1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	CRect rect;
	GetClientRect(&rect);

	CDC *memDC = ReduceSize();
	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), memDC, 0, 0, SRCCOPY);

	memDC->DeleteDC();
	delete memDC;
}


CDC * CReduce_1View::ReduceSize()
{
	CDC *pDC = GetDC();

	CRect rect;
	GetClientRect(&rect);

	CDC *memDC = new CDC();
	memDC->CreateCompatibleDC(pDC);
	
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	memDC->SelectObject(&bmp);

	img->Draw(pDC, CRect(0, 0, img->Width(), img->Height()), CRect(0, 0, img->Width(), img->Height()));

	int w = img->Width() / 4;
	int h = img->Height() / 4;
	int k, m;
	k = 0;
	m = 0;
	for (int i = 0; i < w; i++) {
		for (int j = 0; j < h; j++) {
			COLORREF p1 = GetPixel(pDC->m_hDC, k, m);
			COLORREF p2 = GetPixel(pDC->m_hDC, k, m + 1);
			COLORREF p3 = GetPixel(pDC->m_hDC, k + 1, m);
			COLORREF p4 = GetPixel(pDC->m_hDC, k + 1, m + 1);
			
			int r = (GetRValue(p1) + GetRValue(p2) + GetRValue(p3) + GetRValue(p4)) / 4;
			int g = (GetGValue(p1) + GetGValue(p2) + GetGValue(p3) + GetGValue(p4)) / 4;
			int b = (GetBValue(p1) + GetBValue(p2) + GetBValue(p3) + GetBValue(p4)) / 4;

			memDC->SetPixel(i, j, RGB(r, g, b));
			m=m+2;
		}
		k=k+2;
	}

	return memDC;
}

void CReduce_1View::TestRotate(CDC *pDC, bool right) 
{
	float angle = (45 * 3.14) / 180;
	XFORM form;

	form.eM11 = cos(angle);
	form.eM12 = sin(angle);
	form.eM21 = -sin(angle);
	form.eM22 = cos(angle);

	form.eDx = 0;
	form.eDy = 0;

	if (right)
		pDC->ModifyWorldTransform(&form, MWT_RIGHTMULTIPLY);
	else
		pDC->ModifyWorldTransform(&form, MWT_LEFTMULTIPLY);

	img->Draw(pDC, CRect(0, 0, img->Width(), img->Height()), CRect(0, 0, img->Width(), img->Height()));
}

BOOL CReduce_1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CReduce_1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CReduce_1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

#ifdef _DEBUG
void CReduce_1View::AssertValid() const
{
	CView::AssertValid();
}

void CReduce_1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CReduce_1Doc* CReduce_1View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CReduce_1Doc)));
	return (CReduce_1Doc*)m_pDocument;
}
#endif //_DEBUG


// CReduce_1View message handlers
