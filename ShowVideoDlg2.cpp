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
// BYTE CurOpenDeviceCut=0;//Ҫ�򿪵��豸������
// BYTE VedioModel=0;
// WORD WStartH = 20;//ͼ�񴰿�ˮƽ�������
// WORD WStartV = 10;//ͼ�񴰿ڴ�ֱ�������
// WORD WSizeH = 640;//ͼ�񴰿ڿ��
// WORD WSizeV = 480;//ͼ�񴰿ڸ߶�
// BYTE DeviceNum=0;//�豸����
// 
// int	 DefAWB=160;//AWB
// int	 DefBrightness=0;//����
// int	 DefContrast=50;//�Աȶ�
// int	 DefSaturation=64;//���Ͷ�
// int	 DefHue=6;//ɫ��
// int	 DefSharp=1;//���
// int	 DefLightPwr=0;//��Դģʽ

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
	p2Videopar->DefHBlanking = 9;//������
	p2Videopar->DefVBlanking = 0x19;//������

	if(Z130A_OpenVideo(VideoCallBack2,&DevFacBuf[1]))
	{
		Z130A_ShowVideo(m_hWnd,p2Videopar->WndStarH,p2Videopar->WndStarV,p2Videopar->WndSizeH,p2Videopar->WndSizeV,&DevFacBuf[1]);//m_hWnd
		p2Videopar->VedioModel = 0;//����ȱʡ��Ƶģʽ
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
//�豸�Ȱβ崦��
void ShowVideoDlg2::OnDeviceChange(UINT nEventType, DWORD dwData)
{
	BYTE i,j;
	DeviceFacilities iDevFacBuf[10] ={0};
	switch(nEventType)
	{
	case DBT_DEVICEARRIVAL://�豸����
		if (!DevFacBuf[1].Busy)
		{
			j = Z130A_GetDeviceNum(iDevFacBuf);
			if(j>0)
			{
				for (i=0;i<j;i++)
				{
					if (CurFixedNum==iDevFacBuf[i].FixedNum) 
					{
						//�����豸����
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
		
	case DBT_DEVICEREMOVECOMPLETE://�豸�γ�
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
