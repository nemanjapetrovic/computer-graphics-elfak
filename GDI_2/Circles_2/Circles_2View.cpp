
// Circles_2View.cpp : implementation of the CCircles_2View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Circles_2.h"
#endif

#include "Circles_2Doc.h"
#include "Circles_2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCircles_2View

IMPLEMENT_DYNCREATE(CCircles_2View, CView)

BEGIN_MESSAGE_MAP(CCircles_2View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CCircles_2View construction/destruction

CCircles_2View::CCircles_2View()
{
	// TODO: add construction code here

}

CCircles_2View::~CCircles_2View()
{
}

BOOL CCircles_2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CCircles_2View drawing

void CCircles_2View::OnDraw(CDC* /*pDC*/)
{
	CCircles_2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CCircles_2View printing

BOOL CCircles_2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCircles_2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCircles_2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CCircles_2View diagnostics

#ifdef _DEBUG
void CCircles_2View::AssertValid() const
{
	CView::AssertValid();
}

void CCircles_2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCircles_2Doc* CCircles_2View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCircles_2Doc)));
	return (CCircles_2Doc*)m_pDocument;
}
#endif //_DEBUG


// CCircles_2View message handlers
