#if !defined(AFX_SHOWVIDEODLG2_H__C97AB431_1429_4E0D_9C03_82D31BCA6A3B__INCLUDED_)
#define AFX_SHOWVIDEODLG2_H__C97AB431_1429_4E0D_9C03_82D31BCA6A3B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ShowVideoDlg2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ShowVideoDlg2 dialog

class ShowVideoDlg2 : public CDialog
{
// Construction
public:
	BYTE CurFixedNum;//当前设备的固件号
	ShowVideoDlg2(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(ShowVideoDlg2)
	enum { IDD = IDD_SHOWVIDEO_DIALOG2 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ShowVideoDlg2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ShowVideoDlg2)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnClose();
	//}}AFX_MSG
	afx_msg void OnDeviceChange(UINT nEventType, DWORD dwData );
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHOWVIDEODLG2_H__C97AB431_1429_4E0D_9C03_82D31BCA6A3B__INCLUDED_)
