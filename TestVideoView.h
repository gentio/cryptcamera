// TestVideoView.h : interface of the CTestVideoView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTVIDEOVIEW_H__1FDEF08F_8B63_41C3_8984_BEE3A12C4AB8__INCLUDED_)
#define AFX_TESTVIDEOVIEW_H__1FDEF08F_8B63_41C3_8984_BEE3A12C4AB8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CTestVideoView : public CView
{
protected: // create from serialization only
	CTestVideoView();
	DECLARE_DYNCREATE(CTestVideoView)

// Attributes
public:
	CTestVideoDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestVideoView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTestVideoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTestVideoView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in TestVideoView.cpp
inline CTestVideoDoc* CTestVideoView::GetDocument()
   { return (CTestVideoDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTVIDEOVIEW_H__1FDEF08F_8B63_41C3_8984_BEE3A12C4AB8__INCLUDED_)
