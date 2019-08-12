// SetDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestVideo.h"
#include "SetDlg.h"
#include "DyVideoZ130A.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetDlg dialog


CSetDlg::CSetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetDlg)
	m_FacilitiesNumStr = _T("");
	m_Brightness = 0;
	m_Contrast = 0;
	m_AGC = 0;
	m_AEC = 0;
	m_AEWAEB = 0;
	m_Status_AGC = TRUE;
	m_Status_AEC = TRUE;
	m_FrameRateStr = _T("");
	m_GPIONumStr = _T("");
	m_OutOrInStr = _T("");
	m_VideoModelStr = _T("");
	m_bCheck8 = FALSE;
	m_bCheck9 = FALSE;
	m_bCheck7 = FALSE;
	m_Check6 = FALSE;
	m_AWBAutoEn = TRUE;
	m_AWB = 4700;
	m_SetPowerLineEnStr = _T("");
	Other = 0;
	GPIONum = 0;
	OutOrIn = 0;
	Wdata = 0;
	m_HBlanking = 0;
	m_VBlanking = 0;
	//}}AFX_DATA_INIT
}


void CSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetDlg)
	DDX_Control(pDX, IDC_SLIDER8, m_SliderVBlanking);
	DDX_Control(pDX, IDC_SLIDER7, m_SliderHBlanking);
	DDX_Control(pDX, IDC_COMBO6, m_SetPowerLineEnCtr);
	DDX_Control(pDX, IDC_SLIDER6, m_SliderAWB);
	DDX_Control(pDX, IDC_CHECK6, m_CheckCtr6);
	DDX_Control(pDX, IDC_CHECK10, m_Check10);
	DDX_Control(pDX, IDC_COMBO2, m_VideoModelCtr);
	DDX_Control(pDX, IDC_COMBO5, m_OutOrInCtr);
	DDX_Control(pDX, IDC_COMBO4, m_GPIONumCtr);
	DDX_Control(pDX, IDC_COMBO3, m_FrameRateCtr);
	DDX_Control(pDX, IDC_SLIDER3, m_SliderAEWAEB);
	DDX_Control(pDX, IDC_SLIDER5, m_SliderAEC);
	DDX_Control(pDX, IDC_SLIDER4, m_SliderAGC);
	DDX_Control(pDX, IDC_SLIDER2, m_SliderContrast);
	DDX_Control(pDX, IDC_SLIDER1, m_SliderBrightness);
	DDX_Control(pDX, IDC_COMBO1, m_FacilitiesNumCtr);
	DDX_CBString(pDX, IDC_COMBO1, m_FacilitiesNumStr);
	DDX_Text(pDX, IDC_EDIT1, m_Brightness);
	DDX_Text(pDX, IDC_EDIT2, m_Contrast);
	DDX_Text(pDX, IDC_EDIT4, m_AGC);
	DDX_Text(pDX, IDC_EDIT5, m_AEC);
	DDX_Text(pDX, IDC_EDIT3, m_AEWAEB);
	DDX_Check(pDX, IDC_CHECK4, m_Status_AGC);
	DDX_Check(pDX, IDC_CHECK5, m_Status_AEC);
	DDX_CBString(pDX, IDC_COMBO3, m_FrameRateStr);
	DDX_CBString(pDX, IDC_COMBO4, m_GPIONumStr);
	DDX_CBString(pDX, IDC_COMBO5, m_OutOrInStr);
	DDX_CBString(pDX, IDC_COMBO2, m_VideoModelStr);
	DDX_Check(pDX, IDC_CHECK8, m_bCheck8);
	DDX_Check(pDX, IDC_CHECK9, m_bCheck9);
	DDX_Check(pDX, IDC_CHECK7, m_bCheck7);
	DDX_Check(pDX, IDC_CHECK6, m_Check6);
	DDX_Check(pDX, IDC_CHECK11, m_AWBAutoEn);
	DDX_Text(pDX, IDC_EDIT6, m_AWB);
	DDX_CBString(pDX, IDC_COMBO6, m_SetPowerLineEnStr);
	DDX_Text(pDX, IDC_EDIT7, m_HBlanking);
	DDX_Text(pDX, IDC_EDIT8, m_VBlanking);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetDlg, CDialog)
	//{{AFX_MSG_MAP(CSetDlg)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_BUTTON7, OnOk)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, OnSetBrightness)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER2, OnSetContrast)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER4, OnSetAGC)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER5, OnSetAEC)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER3, OnSetAEWAEB)
	ON_BN_CLICKED(IDC_CHECK4, OnCheckAGC)
	ON_BN_CLICKED(IDC_CHECK5, OnCheckAEC)
	ON_BN_CLICKED(IDC_BUTTON6, OnSetDef)
	ON_BN_CLICKED(IDC_BUTTON1, OnSetFacilitiesNum)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnDevSelchange)
	ON_CBN_SELCHANGE(IDC_COMBO2, OnSelchangeVideoModel)
	ON_CBN_SELCHANGE(IDC_COMBO3, OnSelchangeFrameRate)
	ON_CBN_SELCHANGE(IDC_COMBO4, OnSelchangeGPIO)
	ON_CBN_SELCHANGE(IDC_COMBO5, OnSelchangeOutOrIn)
	ON_BN_CLICKED(IDC_CHECK8, OnCheck8)
	ON_BN_CLICKED(IDC_CHECK9, OnCheck9)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CHECK7, OnCheck7)
	ON_BN_CLICKED(IDC_CHECK6, OnCheck6)
	ON_BN_CLICKED(IDC_CHECK11, OnCheck11)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER6, OnCustomdrawSliderAWB)
	ON_CBN_SELCHANGE(IDC_COMBO6, OnSetPowerLineEn)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER7, OnSetHBlanking)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER8, OnSetVBlanking)
	ON_BN_CLICKED(IDC_BUTTON2, OnVerifyPassWord)
	ON_BN_CLICKED(IDC_BUTTON3, OnChangePassWord)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetDlg message handlers

void CSetDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);	
	// TODO: Add your message handler code here
}

void CSetDlg::OnOk() 
{
	// TODO: Add your control notification handler code here
	this->CloseWindow();	
	this->DestroyWindow();
}

void CSetDlg::OnSetBrightness(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
// 	m_Brightness=m_SliderBrightness.GetPos();
// 	Z130A_SetBrightness(m_Brightness,&DevFacBuf[CurSetDevNum]);//CurSetDevNum
	UpdateData(FALSE);		
	*pResult = 0;
}




BOOL CSetDlg::OnInitDialog() 
{
	CString CStr;
	HICON m_hIcon;
	BYTE RDate[8]= {0};
	char chRDate[9] = {0};
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);//IDR_ICON为图标资源名
	SetIcon(m_hIcon, TRUE);
	CDialog::OnInitDialog();
	//查找已经打开的设备
	for(BYTE i=0;i<10;i++)
	{
		if(DevFacBuf[i].Busy)
		{
			m_FacilitiesNumStr.Format("%d",DevFacBuf[i].FixedNum);
			m_FacilitiesNumCtr.AddString(m_FacilitiesNumStr);
		}
	}
	for(BYTE i=0;i<10;i++)
	{
		if(DevFacBuf[i].Busy)CurSetDevNum = i;
	}
	if (DevFacBuf[CurSetDevNum].Busy)
	{
		m_FacilitiesNumStr.Format("%d",DevFacBuf[CurSetDevNum].FixedNum);
		m_FacilitiesNumCtr.SelectString(0,m_FacilitiesNumStr);
		m_SliderBrightness.SetRange(0,255);	
		m_SliderContrast.SetRange(0,255);	
		m_SliderAEWAEB.SetRange(1,255);	
		m_SliderAGC.SetRange(1,53);	
		m_SliderAEC.SetRange(1,16383);
		m_SliderAWB.SetRange(2800,6500);
		m_SliderHBlanking.SetRange(9,2047);
		m_SliderVBlanking.SetRange(19,2047);
		m_Brightness=Z130A_GetBrightness(&DevFacBuf[CurSetDevNum]);
		m_Contrast=Z130A_GetContrast(&DevFacBuf[CurSetDevNum]);
		m_AEWAEB=Z130A_GetAEWAEB(&DevFacBuf[CurSetDevNum]);
		m_AGC=Z130A_GetAGC(&DevFacBuf[CurSetDevNum]);
		m_AEC=Z130A_GetAEC(&DevFacBuf[CurSetDevNum]);
		m_AWB = Z130A_GetAWB(&DevFacBuf[CurSetDevNum]);
		m_HBlanking = Z130A_GetHorizontalBlanking(&DevFacBuf[CurSetDevNum]);
		m_VBlanking = Z130A_GetVerticalBlanking(&DevFacBuf[CurSetDevNum]);
		m_SliderBrightness.SetPos(m_Brightness);
		m_SliderContrast.SetPos(m_Contrast);
		m_SliderAEWAEB.SetPos(m_AEWAEB);
		m_SliderAGC.SetPos(m_AGC);
		m_SliderAEC.SetPos(m_AEC);
		m_SliderAWB.SetPos(m_AWB);
		m_SliderHBlanking.SetPos(m_HBlanking);
		m_SliderVBlanking.SetPos(m_VBlanking);


		m_VideoModelCtr.InsertString(0,"1280*1024");
		m_VideoModelCtr.InsertString(1,"640*512");
		m_VideoModelCtr.InsertString(2,"320*256");
		m_VideoModelCtr.SetCurSel(0);
		
		m_FrameRateCtr.InsertString(0,"0");
		m_FrameRateCtr.InsertString(1,"1");
		m_FrameRateCtr.InsertString(2,"2");
		m_FrameRateCtr.SetCurSel(0);
		
		m_GPIONumCtr.InsertString(0,"0");
		m_GPIONumCtr.InsertString(1,"1");
		m_GPIONumCtr.InsertString(2,"2");
		m_GPIONumCtr.InsertString(3,"3");
		m_GPIONumCtr.InsertString(4,"4");
		m_GPIONumCtr.InsertString(5,"5");
		m_GPIONumCtr.InsertString(6,"6");
		m_GPIONumCtr.InsertString(7,"7");
		m_GPIONumCtr.SetCurSel(0);
		
		m_OutOrInCtr.InsertString(0,"读");
		m_OutOrInCtr.InsertString(1,"写");
		m_OutOrInCtr.SetCurSel(0);

		m_SetPowerLineEnCtr.InsertString(0,"关");
		m_SetPowerLineEnCtr.InsertString(1,"开");
		m_SetPowerLineEnCtr.SetCurSel(0);

		CStr.Format(_T("设置设备参数：固件号%d"),DevFacBuf[CurSetDevNum].FixedNum);
		this->SetWindowText(CStr);

		//读出相机出厂日期
		Z130A_ReadDate(RDate,&DevFacBuf[CurSetDevNum]);//正常
		//显示出厂日期
		for (BYTE i = 0; i < 8; i++)itoa(RDate[i],&chRDate[i],16);
		GetDlgItem(IDC_CAMERADATE)->SetWindowText(chRDate);

	}


	SetTimer(1,300,NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSetDlg::OnSetContrast(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
// 	m_Contrast=m_SliderContrast.GetPos();
// 	Z130A_SetContrast(m_Contrast,&DevFacBuf[CurSetDevNum]);//CurSetDevNum
	UpdateData(FALSE);			
	*pResult = 0;
}

void CSetDlg::OnSetAGC(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_AGC=m_SliderAGC.GetPos();
	Z130A_SetAGC(m_AGC,&DevFacBuf[CurSetDevNum]);//CurSetDevNum
	UpdateData(FALSE);			
	
	*pResult = 0;
}

void CSetDlg::OnSetAEWAEB(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_AEWAEB=m_SliderAEWAEB.GetPos();
	Z130A_SetAEWAEB(m_AEWAEB,&DevFacBuf[CurSetDevNum]);//CurSetDevNum
	UpdateData(FALSE);			
	*pResult = 0;
}

void CSetDlg::OnSetAEC(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_AEC=m_SliderAEC.GetPos();

	if (!m_Status_AEC)//如果手动曝光则不设置AEC
	{
		Z130A_SetAEC(m_AEC,&DevFacBuf[CurSetDevNum]);//CurSetDevNum
	}
	UpdateData(FALSE);			
	
	*pResult = 0;
}


void CSetDlg::OnCheckAGC() 
{
	// TODO: Add your control notification handler code here
// 	m_Status_AGC=!m_Status_AGC;
// 	UpdateData(TRUE);
// 	if(m_Status_AGC)
// 	{
// 		Z130A_SetAGCEnable(FALSE,&DevFacBuf[CurSetDevNum]);//自动
// 	}
// 	else 
// 	{
// 		Z130A_SetAGCEnable(TRUE,&DevFacBuf[CurSetDevNum]);//手动
// 		m_AGC = Z130A_GetAGC(&DevFacBuf[CurSetDevNum]);
// 		m_SliderAGC.SetPos(m_AGC);
// 	}
// 	UpdateData(FALSE);
	
}

void CSetDlg::OnCheckAEC() 
{
	// TODO: Add your control notification handler code here
	m_Status_AEC=!m_Status_AEC;
	UpdateData(TRUE);
	if(m_Status_AEC)
	{
		Z130A_SetAECEnable(FALSE,&DevFacBuf[CurSetDevNum]);//自动
	}
	else 
	{
		Z130A_SetAECEnable(TRUE,&DevFacBuf[CurSetDevNum]);//手动
		m_AEC = Z130A_GetAEC(&DevFacBuf[CurSetDevNum]);
		m_SliderAEC.SetPos(m_AEC);
	}
	UpdateData(FALSE);
	
}

void CSetDlg::OnSetDef() 
{
	// TODO: Add your control notification handler code here
	m_Brightness=p1Videopar->DefBrightness;
	m_SliderBrightness.SetPos(m_Brightness);
	m_Contrast=p1Videopar->DefContrast;
	m_SliderContrast.SetPos(m_Contrast);
	m_AEWAEB=p1Videopar->DefAEWAEB;
	m_SliderAEWAEB.SetPos(m_AEWAEB);
	m_AGC=p1Videopar->DefAGC;
	m_SliderAGC.SetPos(m_AGC);
	m_AEC=p1Videopar->DefAEC;
	m_SliderAEC.SetPos(m_AEC);
	m_AWB=p1Videopar->DefAWB;
	m_SliderAWB.SetPos(m_AWB);
	m_HBlanking=p1Videopar->DefHBlanking;
	m_SliderHBlanking.SetPos(m_HBlanking);
	m_VBlanking=p1Videopar->DefVBlanking;
	m_SliderVBlanking.SetPos(m_VBlanking);

}



void CSetDlg::OnSetFacilitiesNum() 
{
	// TODO: Add your control notification handler code here
	CString ctr;
	int Num = 0;
	((CComboBox*)GetDlgItem(IDC_COMBO1))->GetWindowText(ctr);
	const char* pNum = (LPCTSTR)ctr;
	sscanf(pNum, "%d ",&Num); 
	DevFacBuf[CurOpenDeviceCut].FixedNum=Num;//更新程序初始化时保存的当前设备的固件号
	if(Z130A_SetFacilitiesNum((BYTE)Num,&DevFacBuf[CurSetDevNum]))MessageBox("设置成功！");
		else MessageBox("设置失败！");
	m_FacilitiesNumCtr.DeleteString(nIndex);
	m_FacilitiesNumCtr.InsertString(nIndex,(LPCTSTR)ctr);//将行插入到指定位置
	UpdateData(true);
	UpdateData(false);
	
}



void CSetDlg::OnDevSelchange() 
{
	// TODO: Add your control notification handler code here
	CString CStr;
	BYTE i;
	BYTE RDate[8]= {0};
	char chRDate[9] = {0};
	int Num = 0;//查找的固件号
	nIndex = ((CComboBox*)GetDlgItem(IDC_COMBO1))->GetCurSel();//当前选中的行。
	((CComboBox*)GetDlgItem(IDC_COMBO1))->GetLBText(nIndex,CStr);
	const char* pNum = (LPCTSTR)CStr;
	sscanf(pNum, "%d ",&Num); 
	
	while (Num!=DevFacBuf[i].FixedNum)i++;
	CurSetDevNum =  i;
	CStr.Format(_T("设置设备参数：固件号%d"),DevFacBuf[CurSetDevNum].FixedNum);
	this->SetWindowText(CStr);
	//读出相机出厂日期
	Z130A_ReadDate(RDate,&DevFacBuf[CurSetDevNum]);//正常
	//显示出厂日期
	for (i = 0; i < 8; i++)itoa(RDate[i],&chRDate[i],16);
	GetDlgItem(IDC_CAMERADATE)->SetWindowText(chRDate);
	
}

void CSetDlg::OnSelchangeVideoModel() 
{
	// TODO: Add your control notification handler code here
	VideoModel = m_VideoModelCtr.GetCurSel();	
	Z130A_SetVideoModel(VideoModel,&DevFacBuf[CurSetDevNum]);
	switch(VideoModel)
	{
	case 0:gfps=15;
		break;
	case 1:gfps=50;
		break;
	case 2:gfps=150;
	    break;
	default:
	    break;
	}
}

void CSetDlg::OnSelchangeFrameRate() 
{
	// TODO: Add your control notification handler code here
// 	FrameRate = m_FrameRateCtr.GetCurSel();
// 	SetFrameRate(FrameRate,&DevFacBuf[CurSetDevNum]);
}

void CSetDlg::OnSelchangeGPIO() 
{
	// TODO: Add your control notification handler code here
	GPIONum = m_GPIONumCtr.GetCurSel();
}

void CSetDlg::OnSelchangeOutOrIn() 
{
	// TODO: Add your control notification handler code here
	BYTE i,j=0xff;;
	i= m_OutOrInCtr.GetCurSel();
	if (i)
	{
		switch(GPIONum)
		{
		case 0:
			if (m_Check6)Wdata = 0x01;else Wdata &=~0x01;
			OutOrIn |= 0x01;
			break;
		case 1:
			if (m_Check6)Wdata = 0x02;else Wdata &=~0x02;
			OutOrIn |= 0x02;
			break;
		case 2:
			if (m_Check6)Wdata = 0x04;else Wdata &=~0x04;
			OutOrIn |= 0x04;
			break;
		case 3:
			if (m_Check6)Wdata = 0x08;else Wdata &=~0x08;
			OutOrIn |= 0x08;
			break;
		case 4:
			if (m_Check6)Wdata = 0x10;else Wdata &=~0x10;
			OutOrIn |= 0x10;
			break;
		case 5:
			if (m_Check6)Wdata = 0x20;else Wdata &=~0x20;
			OutOrIn |= 0x20;
			break;
		case 6:
			if (m_Check6)Wdata = 0x40;else Wdata &=~0x40;
			OutOrIn |= 0x40;
			break;
		case 7:
			if (m_Check6)Wdata = 0x80;else Wdata &=~0x80;
			OutOrIn |= 0x80;
			break;
		default:
			break;
		}
		Z130A_CtrGPIO(OutOrIn,Wdata,&ReadGPIO,&DevFacBuf[CurSetDevNum]);
	}
	else
	{
		switch(GPIONum)
		{
		case 0:
			OutOrIn &= ~0x01;
			j = 0x01; 
			break;
		case 1:
			OutOrIn &= ~0x02;
			j = 0x02; 
			break;
		case 2:
			OutOrIn &= ~0x04;
			j = 0x04; 
			break;
		case 3:
			OutOrIn &= ~0x08;
			j = 0x08; 
			break;
		case 4:
			OutOrIn &= ~0x10;
			j = 0x10; 
			break;
		case 5:
			OutOrIn &= ~0x20;
			j = 0x20; 
			break;
		case 6:
			OutOrIn &= ~0x40;
			j = 0x40; 
			break;
		case 7:
			OutOrIn &= ~0x80;
			j = 0x80; 
			break;
		default:
			break;
		}
		Z130A_CtrGPIO(OutOrIn,Wdata,&ReadGPIO,&DevFacBuf[CurSetDevNum]);
		if (ReadGPIO&j)m_CheckCtr6.SetCheck(true);
			else m_CheckCtr6.SetCheck(false);
	}
}


void CSetDlg::OnCheck8() 
{
	// TODO: Add your control notification handler code here
	m_bCheck8 = !m_bCheck8;
	if (m_bCheck8)
	{
		Other |= 0x40;	
	}
	else
	{
		Other &= ~0x40;
	}
	Z130A_SetOther(Other,&DevFacBuf[CurSetDevNum]);
}

void CSetDlg::OnCheck9() 
{
	// TODO: Add your control notification handler code here
	m_bCheck9 = !m_bCheck9;
	if (m_bCheck9)
	{
		Other |= 0x80;	
	}
	else
	{
		Other &= ~0x80;
	}
	Z130A_SetOther(Other,&DevFacBuf[CurSetDevNum]);	
}


void CSetDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
// 	if(GetKey(&DevFacBuf[CurSetDevNum]))m_Check10.SetCheck(TRUE);
// 		else m_Check10.SetCheck(FALSE);
	CDialog::OnTimer(nIDEvent);
}

void CSetDlg::OnCheck7() 
{
	// TODO: Add your control notification handler code here
	m_bCheck7 = !m_bCheck7;
	if (m_bCheck7)
	{
		Z130A_CtrKeyED(1,&DevFacBuf[CurSetDevNum]);	
	}
	else
	{
		Z130A_CtrKeyED(0,&DevFacBuf[CurSetDevNum]);
	}
	
}

void CSetDlg::OnCheck6() 
{
	// TODO: Add your control notification handler code here
	m_Check6 = !m_Check6;

}

void CSetDlg::OnCheck11() 
{
	// TODO: Add your control notification handler code here
// 	m_AWBAutoEn = !m_AWBAutoEn;
// 	UpdateData(TRUE);
// 	if(m_AWBAutoEn)
// 	{
// 		Z130A_SetAWBEnable(FALSE,&DevFacBuf[CurSetDevNum]);//自动
// 	}
// 	else 
// 	{
// 		Z130A_SetAWBEnable(TRUE,&DevFacBuf[CurSetDevNum]);//手动
// 		m_AWB = Z130A_GetAWB(&DevFacBuf[CurSetDevNum]);
// 		m_SliderAWB.SetPos(m_AWB);
// 	}
// 	UpdateData(FALSE);

}

void CSetDlg::OnCustomdrawSliderAWB(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	UpdateData(FALSE);			
	*pResult = 0;
}

void CSetDlg::OnSetPowerLineEn() 
{
	// TODO: Add your control notification handler code here
}

void CSetDlg::OnSetHBlanking(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_HBlanking=m_SliderHBlanking.GetPos();
	Z130A_SetHorizontalBlanking(m_HBlanking,&DevFacBuf[CurSetDevNum]);
	UpdateData(FALSE);			
	
	*pResult = 0;
}

void CSetDlg::OnSetVBlanking(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_VBlanking=m_SliderVBlanking.GetPos();
	Z130A_SetVerticalBlanking(m_VBlanking,&DevFacBuf[CurSetDevNum]);	
	UpdateData(FALSE);			
	*pResult = 0;
}

void CSetDlg::OnVerifyPassWord() 
{
	// TODO: Add your control notification handler code here
	// BYTE password[8] = {1,8,3,4,3,6,7,8};
	BYTE password[8] = {1,2,3,4,5,6,7,8};
	if (Z130A_VerifyPassWord(password,&DevFacBuf[CurSetDevNum]))MessageBox("密码正确！","验证密码",MB_OK);
	else MessageBox("密码不正确！","验证密码",MB_OK);
	
}

void CSetDlg::OnChangePassWord() 
{
	// TODO: Add your control notification handler code here
	BYTE Oldpassword[8] = {1,8,3,4,3,6,7,8};
	BYTE Newpassword[8] = {1,2,3,4,5,6,7,8};
	
	// 	BYTE Oldpassword[8] = {1,2,3,4,5,6,7,8};
	// 	BYTE Newpassword[8] = {1,8,3,4,3,6,7,8};
	
	if (Z130A_ChangePassWord(Oldpassword,Newpassword,&DevFacBuf[CurSetDevNum]))MessageBox("密码修改成功！","密码修改",MB_OK);
	else MessageBox("密码修改失败！","密码修改",MB_OK);
	
	
	
	
	
}
