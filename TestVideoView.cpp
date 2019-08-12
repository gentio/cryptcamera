// TestVideoView.cpp : implementation of the CTestVideoView class
//

#include "stdafx.h"
#include "TestVideo.h"

#include "TestVideoDoc.h"
#include "TestVideoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestVideoView

IMPLEMENT_DYNCREATE(CTestVideoView, CView)

BEGIN_MESSAGE_MAP(CTestVideoView, CView)
	//{{AFX_MSG_MAP(CTestVideoView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestVideoView construction/destruction

CTestVideoView::CTestVideoView()
{
	// TODO: add construction code here

}

CTestVideoView::~CTestVideoView()
{
}

BOOL CTestVideoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CTestVideoView drawing
void CTestVideoView::OnDraw(CDC* pDC)
{
	CTestVideoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CTestVideoView diagnostics

#ifdef _DEBUG
void CTestVideoView::AssertValid() const
{
	CView::AssertValid();
}

void CTestVideoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTestVideoDoc* CTestVideoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTestVideoDoc)));
	return (CTestVideoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTestVideoView message handlers


