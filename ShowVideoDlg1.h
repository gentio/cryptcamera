#if !defined(AFX_SHOWVIDEODLG1_H__575F136F_6F6F_488D_9308_29C47E48700A__INCLUDED_)
#define AFX_SHOWVIDEODLG1_H__575F136F_6F6F_488D_9308_29C47E48700A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ShowVideoDlg1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ShowVideoDlg1 dialog

class ShowVideoDlg1 : public CDialog
{
// Construction
public:
	BYTE CurFixedNum;//当前设备的固件号
	ShowVideoDlg1(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(ShowVideoDlg1)
	enum { IDD = IDD_SHOWVIDEO_DIALOG1 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ShowVideoDlg1)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ShowVideoDlg1)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnClose();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	afx_msg void OnDeviceChange(UINT nEventType, DWORD dwData );
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHOWVIDEODLG1_H__575F136F_6F6F_488D_9308_29C47E48700A__INCLUDED_)
