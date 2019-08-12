// ShowVideoDlg1.cpp : implementation file
//

#include "stdafx.h"
#include "TestVideo.h"
#include "ShowVideoDlg1.h"
#include "DyVideoZ130A.h"
#include <dbt.h>
#include <Rpcdce.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif





/////////////////////////////////////////////////////////////////////////////
// ShowVideoDlg1 dialog


ShowVideoDlg1::ShowVideoDlg1(CWnd* pParent /*=NULL*/)
	: CDialog(ShowVideoDlg1::IDD, pParent)
{
	//{{AFX_DATA_INIT(ShowVideoDlg1)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void ShowVideoDlg1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ShowVideoDlg1)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ShowVideoDlg1, CDialog)
	//{{afx_msg_map(ShowVideoDlg1)
	ON_WM_SHOWWINDOW()
	ON_WM_CLOSE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	//ON_WM_DEVICECHANGE() //�Ȳ��
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ShowVideoDlg1 message handlers
struct  VideoParameter *p1Videopar;

void ShowVideoDlg1::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	// TODO: Add your message handler code here
	if (DevFacBuf[0].Busy)return;//�������Ƿ����ڹ�����
	p1Videopar = new VideoParameter;
	p1Videopar->WndStarH = 0;
	p1Videopar->WndStarV = 0;
	p1Videopar->WndSizeH = 640;
	p1Videopar->WndSizeV = 512;
	p1Videopar->DefAGC = 20;//0x53;
	p1Videopar->DefAEC = 1024;//1049;
	p1Videopar->DefAEWAEB = 58;
	p1Videopar->DefBrightness = 0;
	p1Videopar->DefContrast = 125;
	p1Videopar->DefAWB = 4700;
	p1Videopar->DefHBlanking = 0x09;//������
	p1Videopar->DefVBlanking = 0x19;//������
	if(Z130A_OpenVideo(VideoCallBack1,&DevFacBuf[0]))//
	{
		//hWnd����ΪNULL
		Z130A_ShowVideo(m_hWnd,p1Videopar->WndStarH,p1Videopar->WndStarV,p1Videopar->WndSizeH,p1Videopar->WndSizeV,&DevFacBuf[0]);//m_hWnd
		p1Videopar->VedioModel = 0;//����ȱʡ��Ƶģʽ
		Z130A_SetVideoModel(p1Videopar->VedioModel,&DevFacBuf[0]);
		CurFixedNum = DevFacBuf[0].FixedNum;
		Z130A_SetAEWAEB(p1Videopar->DefAEWAEB,&DevFacBuf[0]);
// 		SetTimer(1,1000,NULL);//֡�ʼ�����ʱ��
	}
}

void ShowVideoDlg1::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	Z130A_StopVideo(&DevFacBuf[0]);
	CDialog::OnClose();
}

void ShowVideoDlg1::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);	
}



void ShowVideoDlg1::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
}


//////////////////////////////////////////////////////////////////////////
//�豸�Ȱβ崦��
void ShowVideoDlg1::OnDeviceChange(UINT nEventType, DWORD dwData)
{
	BYTE i,j;
	DeviceFacilities iDevFacBuf[10] ={0};
	switch(nEventType)
	{
		case DBT_DEVICEARRIVAL://�豸����
			if (!DevFacBuf[0].Busy)
			{
				j = Z130A_GetDeviceNum(iDevFacBuf);
				if(j>0)
				{
					for (i=0;i<j;i++)
					{
						if (CurFixedNum==iDevFacBuf[i].FixedNum) 
						{
							//�����豸����
							DevFacBuf[0].Busy = iDevFacBuf[i].Busy;
							DevFacBuf[0].InconstancyNum = iDevFacBuf[i].InconstancyNum;
							if(Z130A_OpenVideo(VideoCallBack1,&DevFacBuf[0]))
							{
								Z130A_ShowVideo(m_hWnd,p1Videopar->WndStarH,p1Videopar->WndStarV,p1Videopar->WndSizeH,p1Videopar->WndSizeV,&DevFacBuf[0]);//m_hWnd
								Z130A_SetVideoModel(p1Videopar->VedioModel,&DevFacBuf[0]);
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
					if (CurFixedNum == iDevFacBuf[i].FixedNum)
						return ;
					else 
					{
						Z130A_StopVideo(&DevFacBuf[0]);
						
					}
				}			

			}
			else 
			{
				Z130A_StopVideo(&DevFacBuf[0]);
				DevFacBuf[0].Busy = FALSE;
			}
			break;
		default:
			break;
	}
}

//////////////////////////////////////////////////////////////////////////
//����֡��
void ShowVideoDlg1::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	CString CStr;
	CStr.Format(_T("��ǰ֡�٣�%d"),FpsCut);
	SetWindowText(CStr);
	FpsCut=0;
	CDialog::OnTimer(nIDEvent);
}

