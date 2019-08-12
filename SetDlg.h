#if !defined(AFX_SETDLG_H__4ED98231_9E8E_4A6C_B24B_5933303FB859__INCLUDED_)
#define AFX_SETDLG_H__4ED98231_9E8E_4A6C_B24B_5933303FB859__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetDlg dialog

class CSetDlg : public CDialog
{
// Construction
public:
	int OldAWB;
	CSetDlg(CWnd* pParent = NULL);   // standard constructor
	BYTE Other;
	int nIndex;
	BYTE CurSetDevNum;
	BYTE VideoModel;
	BYTE FrameRate;
	BYTE GPIONum;//选择的IO号
	BYTE OutOrIn;//每位对应每脚是输入还是输出操作
	BYTE Wdata;//每位对应每脚输出高电平还是低电平
	BYTE ReadGPIO;//每位对应每脚读到的是高电平还是低电平	
// Dialog Data
	//{{AFX_DATA(CSetDlg)
	enum { IDD = IDD_SET_DLG };
	CSliderCtrl	m_SliderVBlanking;
	CSliderCtrl	m_SliderHBlanking;
	CComboBox	m_SetPowerLineEnCtr;
	CSliderCtrl	m_SliderAWB;
	CButton	m_CheckCtr6;
	CButton	m_Check10;
	CComboBox	m_VideoModelCtr;
	CComboBox	m_OutOrInCtr;
	CComboBox	m_GPIONumCtr;
	CComboBox	m_FrameRateCtr;
	CSliderCtrl	m_SliderAEWAEB;
	CSliderCtrl	m_SliderAEC;
	CSliderCtrl	m_SliderAGC;
	CSliderCtrl	m_SliderContrast;
	CSliderCtrl	m_SliderBrightness;
	CComboBox	m_FacilitiesNumCtr;
	CString	m_FacilitiesNumStr;
	int		m_Brightness;
	int		m_Contrast;
	int		m_AGC;
	int		m_AEC;
	int		m_AEWAEB;
	BOOL	m_Status_AGC;
	BOOL	m_Status_AEC;
	CString	m_FrameRateStr;
	CString	m_GPIONumStr;
	CString	m_OutOrInStr;
	CString	m_VideoModelStr;
	BOOL	m_bCheck8;
	BOOL	m_bCheck9;
	BOOL	m_bCheck7;
	BOOL	m_Check6;
	BOOL	m_AWBAutoEn;
	int		m_AWB;
	CString	m_SetPowerLineEnStr;
	int		m_HBlanking;
	int		m_VBlanking;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSetDlg)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnOk();
	afx_msg void OnSetBrightness(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
	afx_msg void OnSetContrast(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSetAGC(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSetAEC(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSetAEWAEB(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCheckAGC();
	afx_msg void OnCheckAEC();
	afx_msg void OnSetDef();
	afx_msg void OnSetFacilitiesNum();
	afx_msg void OnDevSelchange();
	afx_msg void OnSelchangeVideoModel();
	afx_msg void OnSelchangeFrameRate();
	afx_msg void OnSelchangeGPIO();
	afx_msg void OnSelchangeOutOrIn();
	afx_msg void OnCheck8();
	afx_msg void OnCheck9();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnCheck7();
	afx_msg void OnCheck6();
	afx_msg void OnCheck11();
	afx_msg void OnCustomdrawSliderAWB(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSetPowerLineEn();
	afx_msg void OnSetHBlanking(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSetVBlanking(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnVerifyPassWord();
	afx_msg void OnChangePassWord();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETDLG_H__4ED98231_9E8E_4A6C_B24B_5933303FB859__INCLUDED_)

