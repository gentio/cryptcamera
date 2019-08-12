// ShowVideoDlg2.cpp : implementation file
//

#include "stdafx.h"
#include "TestVideo.h"
#include "ShowVideoDlg2.h"
#include "DyVideoZ130A.h"
#include <dbt.h>
#include <Rpcdce.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



// VIDEOFACILITIES DevFacBuf[10];
// BYTE CurOpenDeviceCut=0;//要打开的设备计数号
// BYTE VedioModel=0;
// WORD WStartH = 20;//图像窗口水平起点坐标
// WORD WStartV = 10;//图像窗口垂直起点坐标
// WORD WSizeH = 640;//图像窗口宽度
// WORD WSizeV = 480;//图像窗口高度
// BYTE DeviceNum=0;//设备数量
// 
// int	 DefAWB=160;//AWB
// int	 DefBrightness=0;//亮度
// int	 DefContrast=50;//对比度
// int	 DefSaturation=64;//饱和度
// int	 DefHue=6;//色调
// int	 DefSharp=1;//锐度
// int	 DefLightPwr=0;//光源模式

/////////////////////////////////////////////////////////////////////////////
// ShowVideoDlg2 dialog


ShowVideoDlg2::ShowVideoDlg2(CWnd* pParent /*=NULL*/)
	: CDialog(ShowVideoDlg2::IDD, pParent)
{
	//{{AFX_DATA_INIT(ShowVideoDlg2)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void ShowVideoDlg2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ShowVideoDlg2)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ShowVideoDlg2, CDialog)
	//{{AFX_MSG_MAP(ShowVideoDlg2)
	ON_WM_SHOWWINDOW()
	ON_WM_CLOSE()
	//ON_WM_DEVICECHANGE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ShowVideoDlg2 message handlers
struct  VideoParameter *p2Videopar;

void ShowVideoDlg2::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
	p2Videopar = new VideoParameter;
	p2Videopar->WndStarH = 0;
	p2Videopar->WndStarV = 0;
	p2Videopar->WndSizeH = 640;
	p2Videopar->WndSizeV = 512;
	p2Videopar->DefAEC = 1024;
	p2Videopar->DefAGC = 20;
	p2Videopar->DefAEWAEB = 80;
	p2Videopar->DefBrightness = 0;
	p2Videopar->DefContrast = 125;
	p2Videopar->DefAWB = 4700;
	p2Videopar->DefHBlanking = 9;//行消隐
	p2Videopar->DefVBlanking = 0x19;//场消隐

	if(Z130A_OpenVideo(VideoCallBack2,&DevFacBuf[1]))
	{
		Z130A_ShowVideo(m_hWnd,p2Videopar->WndStarH,p2Videopar->WndStarV,p2Videopar->WndSizeH,p2Videopar->WndSizeV,&DevFacBuf[1]);//m_hWnd
		p2Videopar->VedioModel = 0;//设置缺省视频模式
		Z130A_SetVideoModel(p2Videopar->VedioModel,&DevFacBuf[1]);
		Z130A_SetAEWAEB(p2Videopar->DefAEWAEB,&DevFacBuf[1]);
		CurFixedNum = DevFacBuf[1].FixedNum;
	}
}

void ShowVideoDlg2::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	Z130A_StopVideo(&DevFacBuf[1]);
	CDialog::OnClose();
}


//////////////////////////////////////////////////////////////////////////
//设备热拔插处理
void ShowVideoDlg2::OnDeviceChange(UINT nEventType, DWORD dwData)
{
	BYTE i,j;
	DeviceFacilities iDevFacBuf[10] ={0};
	switch(nEventType)
	{
	case DBT_DEVICEARRIVAL://设备插入
		if (!DevFacBuf[1].Busy)
		{
			j = Z130A_GetDeviceNum(iDevFacBuf);
			if(j>0)
			{
				for (i=0;i<j;i++)
				{
					if (CurFixedNum==iDevFacBuf[i].FixedNum) 
					{
						//更新设备属性
						DevFacBuf[1].Busy = iDevFacBuf[i].Busy;
						DevFacBuf[1].InconstancyNum = iDevFacBuf[i].InconstancyNum;
						if(Z130A_OpenVideo(VideoCallBack2,&DevFacBuf[1]))
						{
							Z130A_ShowVideo(m_hWnd,p2Videopar->WndStarH,p2Videopar->WndStarV,p2Videopar->WndSizeH,p2Videopar->WndSizeV,&DevFacBuf[1]);//m_hWnd
							Z130A_SetVideoModel(p2Videopar->VedioModel,&DevFacBuf[1]);
						}
					}
				}			
			}
		}
		
		break;	
		
	case DBT_DEVICEREMOVECOMPLETE://设备拔出
		j = Z130A_GetDeviceNum(iDevFacBuf);
		if(j>0)
		{
			for (i=0;i<j;i++)
			{
				if (CurFixedNum==iDevFacBuf[i].FixedNum) 
					return ;
				else 
				{
					Z130A_StopVideo(&DevFacBuf[1]);			
				}
			}				
		}
		else 
		{
			Z130A_StopVideo(&DevFacBuf[1]);		
		}
		break;
	default:
		break;	
	}
}
