// TestVideo.h : main header file for the TESTVIDEO application
//

#if !defined(AFX_TESTVIDEO_H__B823EC0B_D963_4C06_83E0_29988F29A6E3__INCLUDED_)
#define AFX_TESTVIDEO_H__B823EC0B_D963_4C06_83E0_29988F29A6E3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestVideoApp:
// See TestVideo.cpp for the implementation of this class
//

class CTestVideoApp : public CWinApp
{
public:
	CTestVideoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestVideoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CTestVideoApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTVIDEO_H__B823EC0B_D963_4C06_83E0_29988F29A6E3__INCLUDED_)

struct  VideoParameter
{
	BYTE VedioModel;
	WORD WndStarH;//ͼ�񴰿�ˮƽ�������
	WORD WndStarV;//ͼ�񴰿ڴ�ֱ�������
	WORD WndSizeH;//ͼ�񴰿ڿ��
	WORD WndSizeV;//ͼ�񴰿ڸ߶�
	int	 DefAEWAEB;
	int  DefAGC;
	int  DefAEC;
	int  DefAWB;
	int	 DefBrightness;//����
	int	 DefContrast;//�Աȶ�
	int  DefHBlanking;//������
	int  DefVBlanking;//������

};

extern struct DeviceFacilities DevFacBuf[];
extern BYTE CurOpenDeviceCut;//Ҫ�򿪵��豸������
extern BYTE DeviceNum;//�豸����
extern CMenu *gpCMenu;
extern DWORD FpsCut;//֡�ʼ������ 
extern double gfps;//¼��֡��