// TestVideoDoc.cpp : implementation of the CTestVideoDoc class
//

#include "stdafx.h"
#include "TestVideo.h"

#include "TestVideoDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestVideoDoc

IMPLEMENT_DYNCREATE(CTestVideoDoc, CDocument)

BEGIN_MESSAGE_MAP(CTestVideoDoc, CDocument)
	//{{AFX_MSG_MAP(CTestVideoDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestVideoDoc construction/destruction

CTestVideoDoc::CTestVideoDoc()
{
	// TODO: add one-time construction code here

}

CTestVideoDoc::~CTestVideoDoc()
{
}

BOOL CTestVideoDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CTestVideoDoc serialization

void CTestVideoDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CTestVideoDoc diagnostics

#ifdef _DEBUG
void CTestVideoDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTestVideoDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTestVideoDoc commands
