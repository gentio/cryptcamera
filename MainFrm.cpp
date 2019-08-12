// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "TestVideo.h"
#include "DyVideoZ130A.h"
#include "MainFrm.h"
#include "ShowVideoDlg1.h"
#include "ShowVideoDlg2.h"
#include "SetDlg.h"
#include <highgui.h>
#include <cv.h>
#include <cxcore.h>
#include <process.h> 
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>

//new
#include <iostream>
#include <vector>
#include <algorithm> // std::move_backward
#include <random> // std::default_random_engine
#include <chrono> // std::chrono::system_clock
//
using namespace cv;
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////////
//ȫ�ֱ���
ShowVideoDlg1 *ShVidlg1;
ShowVideoDlg2 *ShVidlg2;
CSetDlg *SetDlg;
CvVideoWriter* writer;// = cvCreateVideoWriter("Test.avi" ,CV_FOURCC('X','V','I','D'),fps,size);
IplImage* cvImage;
//IplImage* cvShow;// = cvCreateImage(size,8,3);
BOOL StarCapFlag;
BOOL StarCapFlag2;
BOOL StarCapFlag3;
BOOL CapGetOneImage;//=1Ϊһ֡ͼ��
Mat pic;
BYTE gBuffer[4147200];
BYTE gBufferLast[4147200];
BYTE gBufferDif[4147200];
int gBufferCp[4147200];//1280*1080*3
//BYTE gBufferRAW[1382400];//1280*1080
DWORD gWidth=752,gHeight=480;
DWORD gImageLen;
//DWORD gImageLenRAW;
HANDLE gHThread1;
double gfps=10;//¼��֡��
DWORD FpsCut=0;//֡�ʼ������


//////////////////////////////////////////////////////////////////////////
//ȫ�ֺ���
unsigned  __stdcall AviCapThread1(LPVOID lpParameter);

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_DEVIEC_1, OnDeviec1)
	ON_COMMAND(ID_DEVIEC_2, OnDeviec2)
	ON_COMMAND(ID_SET, OnSet)
	ON_COMMAND(ID_GETBMP_PHOTO, OnGetbmpPhoto)
	ON_WM_CLOSE()
	ON_WM_SHOWWINDOW()
	ON_COMMAND(ID_START_CAPTURE, OnStartCapture)
	ON_COMMAND(ID_STOP_CAPTURE, OnStopCapture)
	ON_COMMAND(ID_32785, OnStartCapture2)//new row
	ON_COMMAND(ID_START_CAPTURE3, OnStartCapture3)
	//ON_COMMAND(ID_TEST_RAW2RGB24, OnTestRaw2rgb24)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

//////////////////////////////////////////////////////////////////////////
//��Ƶ���ݻص�����
BOOL WINAPI VideoCallBack1(BYTE *pVideoDataRGB,BYTE *pVideoDataRAW,DWORD Width, DWORD Height)
{
	//AfxMessageBox("����ص�����");
	gWidth=Width;
	gHeight=Height;
	gImageLen =Width*Height*3;//RGB��ʽͼ�����ݳ���
	CopyMemory(gBuffer,pVideoDataRGB,gImageLen);
	DWORD ii;
	for (ii = 0; ii < gImageLen; ii++)
	{
		 gBufferCp[ii] = gBuffer[ii] - gBufferLast[ii];
		 if (gBufferCp[ii] > 20)
		 {
			 gBufferDif[ii] = 255;
		 }
		 else if (gBufferCp[ii] < -20)
		 {
			 gBufferDif[ii] = 0;
		 }
		 else
		 {
			 gBufferDif[ii] = 127;
		 }

	}
	CopyMemory(gBufferLast, gBuffer, gImageLen);
	//1280*1080*3 gBufferDif[4147200]
	
	//gImageLenRAW =Width*Height;//RAW��ʽͼ�����ݳ���
	//CopyMemory(gBufferRAW,pVideoDataRAW,gImageLenRAW);
	
	CapGetOneImage = TRUE;
	FpsCut++;
	return TRUE;
}


BOOL WINAPI VideoCallBack2(BYTE *pVideoDataRGB,BYTE *pVideoDataRAW,DWORD Width, DWORD Height)
{
	//AfxMessageBox("����ص�����");
	return TRUE;
}


//////////////////////////////////////////////////////////////////////////
//��RAW��ʽͼ��ת��ΪRGB��ʽ�������档
//BOOL  RAW2RGB24(char *BmpPhotoName,DWORD ImageLen)
//{
	//DWORD Count; //x�����꣬y������
	//DWORD i,j,x;
	//i=j=x=0;
	//BYTE *pDataRAW = new BYTE[3932160];
	//BYTE *pDataRGB=new BYTE[3932160];
	//BITMAPFILEHEADER bfh;
	//memset( &bfh, 0, sizeof( bfh ) );
	//bfh.bfType = 'MB';
	//DWORD dwWritten = 0;
	//BITMAPINFOHEADER bih;
	//memset( &bih, 0, sizeof( bih ) );
	//bih.biSize = sizeof( bih );
	//HANDLE hf = CreateFile(BmpPhotoName, GENERIC_WRITE, FILE_SHARE_READ, NULL,CREATE_ALWAYS, NULL, NULL );
	//if( hf == INVALID_HANDLE_VALUE )
	//{
		//delete []pDataRAW;
		//delete []pDataRGB;
		//return FALSE;
	//}
	//i=j=x=0;
	//�ڰ�ͼ������RAWתΪRGB24
	//for (j=0;j<ImageLen;j++)
	//{
		//for (i=0;i<3;i++)pDataRGB[x++] = gBufferRAW[j];
	//}

	//bfh.bfSize = sizeof( bfh ) + ImageLen*3 + sizeof( BITMAPINFOHEADER );
	//bfh.bfOffBits = sizeof( BITMAPINFOHEADER ) + sizeof( BITMAPFILEHEADER );

	//WriteFile( hf, &bfh, sizeof( bfh ), &dwWritten, NULL );

	//bih.biWidth = gWidth;
	//bih.biHeight = gHeight;
	//bih.biPlanes = 1;
	//bih.biBitCount = 24;

	//dwWritten = 0;
	//WriteFile( hf, &bih, sizeof( bih ), &dwWritten, NULL );

	//dwWritten = 0;
	//WriteFile( hf, pDataRGB,ImageLen*3, &dwWritten, NULL );
	//CloseHandle( hf );
	//delete []pDataRAW;
	//delete []pDataRGB;
		
	//return TRUE;
//}


//void CMainFrame::OnTestRaw2rgb24() 
//{
	// TODO: Add your command handler code here
	//RAW2RGB24("TESTRAW.bmp",gImageLenRAW);
//}



int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


void CMainFrame::OnDeviec1() 

{
	CString CStr;
	// TODO: Add your command handler code here
	HICON m_hIcon;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);//IDR_ICONΪͼ����Դ��
	if (DeviceNum)
	{
		if (!DevFacBuf[0].Busy)
		{
			ShVidlg1 = new ShowVideoDlg1;
			ShVidlg1->Create(IDD_SHOWVIDEO_DIALOG1,this);//������ģ̬�Ի���
			ShVidlg1->ShowWindow(SW_SHOW);
			ShVidlg1->SetWindowPos(NULL,5,50,640+16,512+38,SWP_SHOWWINDOW);
			ShVidlg1->SetIcon(m_hIcon, TRUE);
			CStr.Format(_T("�豸�̼���%d"),DevFacBuf[0].FixedNum);
			ShVidlg1->SetWindowText(CStr);
		}
		else MessageBox("1���豸�Ѵ򿪣�");
	}
	else MessageBox("1���豸δ���ӣ�");
	
}

void CMainFrame::OnDeviec2() 
{
	CString CStr;
	// TODO: Add your command handler code here
	HICON m_hIcon;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);//IDR_ICONΪͼ����Դ��
	if (DeviceNum>1)
	{
		if (!DevFacBuf[1].Busy)
		{
			ShVidlg2 = new ShowVideoDlg2;
			ShVidlg2->Create(IDD_SHOWVIDEO_DIALOG2,this);
			ShVidlg2->ShowWindow(SW_SHOW);
			ShVidlg2->SetWindowPos(NULL,500,100,640+16,512+38,SWP_SHOWWINDOW);
			ShVidlg1->SetIcon(m_hIcon, TRUE);
			CStr.Format(_T("�豸�̼���%d"),DevFacBuf[1].FixedNum);
			ShVidlg2->SetWindowText(CStr);
		}
		else MessageBox("1���豸�Ѵ򿪣�");
	}
	else MessageBox("2���豸δ���ӣ�");
}

void CMainFrame::OnSet() 
{
	// TODO: Add your command handler code here
	SetDlg = new CSetDlg;
	SetDlg->Create(IDD_SET_DLG,this);
	SetDlg->SetWindowPos(NULL,150,200,580,425,SWP_SHOWWINDOW);
	SetDlg->ShowWindow(SW_SHOW);
}

void CMainFrame::OnGetbmpPhoto() 
{
	// TODO: Add your command handler code here
	//����SDK��API��������ͼ��
	if(!Z130A_GetBmpPhoto("Test.bmp",&DevFacBuf[0]))
		AfxMessageBox("��ȡͼƬʧ��");
	else 
		AfxMessageBox("��ȡͼƬ�ɹ�,Test.bmp");	
}

void CMainFrame::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
// 	if(DevFacBuf[0].Busy)StopVideo(&DevFacBuf[0]);
// 	if(DevFacBuf[1].Busy)StopVideo(&DevFacBuf[1]);
	ShVidlg1->CloseWindow();
	ShVidlg2->CloseWindow();
	CFrameWnd::OnClose();
}

void CMainFrame::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CString CStr;
	DWORD DevID[2];
	DevID[0]=ID_DEVIEC_1;
	DevID[1]=ID_DEVIEC_2;
	CFrameWnd::OnShowWindow(bShow, nStatus);
	// TODO: Add your message handler code here
	DeviceNum = Z130A_GetDeviceNum(DevFacBuf);
	for (BYTE i=0;i<DeviceNum;i++)
	{
		DevFacBuf[i].MarkNum=i;
		CStr.Format(_T("�̼��ţ� %d"),DevFacBuf[i].FixedNum);
		GetMenu()->GetSubMenu(1)->AppendMenu(MF_POPUP,DevID[i],CStr);
	}
}

void CMainFrame::OnStartCapture() 
{
	StarCapFlag = 1;
	// TODO: Add your command handler code here
	// TODO: Add your command handler code here
	//CString mStrFileName =_T(" ");
	//CFileDialog mFilDlg(false,NULL ,  NULL,   OFN_FILEMUSTEXIST | OFN_READONLY | OFN_PATHMUSTEXIST,  
		//TEXT("��Ƶ�ļ� (*.avi)|*.avi|�����ļ�(*.*)|*.*||"),  NULL);
	//if(mFilDlg.DoModal() == IDOK)
	//{
		//mStrFileName = mFilDlg.GetPathName();
		//if (-1==mStrFileName.Find(_T(".avi")))mStrFileName+=_T(".avi");//����û������ļ����Ƿ��и�ʽ
		//UpdateData(FALSE);
	//}
	//else return;
	CvSize size = cvSize(gWidth, gHeight);
	//¼����Ƶ���밲װ��Ӧ����Ƶ������,������������Ϊ -1��������ʱ�ᵯ��һ��������ѡ���.
	/*
	CV_FOURCC('P', 'I', 'M', '1') = MPEG-1 codec 
	CV_FOURCC('M', 'J', 'P', 'G') = motion-jpeg codec
	CV_FOURCC('M', 'P', '4', '2') = MPEG-4.2 codec 
	CV_FOURCC('D', 'I', 'V', '3') = MPEG-4.3 codec 
	CV_FOURCC('D', 'I', 'V', 'X') = MPEG-4 codec 
	CV_FOURCC('U', '2', '6', '3') = H263 codec 
	CV_FOURCC('I', '2', '6', '3') = H263I codec 
	CV_FOURCC('F', 'L', 'V', '1') = FLV1 codec
	*/
// 	writer = cvCreateVideoWriter(mStrFileName,CV_FOURCC('X','V','I','D'),gfps,size);//'X','V','I','D'
	//writer = cvCreateVideoWriter(mStrFileName,-1,gfps,size);//'X','V','I','D'

	cvImage = cvCreateImage(size,8,3);
	unsigned int dwThreadID1;
	gHThread1 = (HANDLE)_beginthreadex(NULL,0,AviCapThread1,NULL,0,&dwThreadID1);
	CloseHandle(gHThread1);
	
}


void CMainFrame::OnStartCapture2()
{
	StarCapFlag2 = 1;//=====================
//ͬ�� ������
	CvSize size = cvSize(gWidth, gHeight);

	cvImage = cvCreateImage(size, 8, 3);
	unsigned int dwThreadID1;
	gHThread1 = (HANDLE)_beginthreadex(NULL, 0, AviCapThread1, NULL, 0, &dwThreadID1);
	CloseHandle(gHThread1);

}
void CMainFrame::OnStartCapture3()
{
	StarCapFlag3 = 1;//=====================
					 //ͬ�� ������
	CvSize size = cvSize(gWidth, gHeight);

	cvImage = cvCreateImage(size, 8, 3);
	unsigned int dwThreadID1;
	gHThread1 = (HANDLE)_beginthreadex(NULL, 0, AviCapThread1, NULL, 0, &dwThreadID1);
	CloseHandle(gHThread1);

}


void CMainFrame::OnStopCapture() 
{
	// TODO: Add your command handler code here
	StarCapFlag = 0;
	StarCapFlag2 = 0;
	StarCapFlag3 = 0;
}
//�����˳��
std::vector<int> randchange(std::vector<int> v)
{
	// obtain a time-based seed:
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(v.begin(), v.end(), std::default_random_engine(seed));

	return v;
}

unsigned  __stdcall AviCapThread1(LPVOID lpParameter)
{
	DWORD x, y, x11,y11;
	std::vector<int> x1;
	for (x = 0; x < (gWidth - 1) * 3; x += 3)
	{
		x1.push_back(x);
	}
	x1 = randchange(x1);//���ã�����~�Ͱ�һ����ÿһ֡��һ����ÿһ��Ҳһ��

	std::vector<int> y1;//������=================
	for (y = 0; y<gHeight - 1; y++)
	{
		y1.push_back(y);
	}
	y1 = randchange(y1);//���ã�����~�Ͱ�һ����ÿһ֡��һ����ÿһ��Ҳһ��

	cvNamedWindow("dif", 0);
	//DWORD x,y,x11;
	int ii;
	while (StarCapFlag)
	{
		
		if (CapGetOneImage)
		{
			CapGetOneImage = FALSE;
			//ͼ�����¾���
			

			for (y=0;y<gHeight-1;y++)
			{
				
				for (x=0;x<(gWidth-1)*3;x+=3)
				{
					//�޸�x  ʹÿһ������,x1
					//for (auto& it : x1) {
					//	x11 =  it;
						//x11 = 2253 - x;
					x11 = x1[x/3];

						//x11 = x1[ii];
						//ii++;
						cvImage->imageData[gWidth*y * 3 + x] = gBuffer[gWidth*(gHeight - y) * 3 + x11];
						cvImage->imageData[gWidth*y * 3 + x + 1] = gBuffer[gWidth*(gHeight - y) * 3 + x11 + 1];
						cvImage->imageData[gWidth*y * 3 + x + 2] = gBuffer[gWidth*(gHeight - y) * 3 + x11 + 2];
						//origin
						//cvImage->imageData[gWidth*y * 3 + x] = gBufferDif[gWidth*(gHeight - y) * 3 + x];
						//cvImage->imageData[gWidth*y * 3 + x + 1] = gBufferDif[gWidth*(gHeight - y) * 3 + x + 1];
						//cvImage->imageData[gWidth*y * 3 + x + 2] = gBufferDif[gWidth*(gHeight - y) * 3 + x + 2];
				//	}
				}
			}
			cvShowImage("dif",cvImage);
			//cvWriteFrame(writer, cvImage);
			waitKey(10);
			
		}
		else
		{
			Sleep(2);
		}
		if (!cvGetWindowHandle("dif"))
		{

			StarCapFlag = FALSE;
			break;
		}
			
	}
	while (StarCapFlag2)//������====================
	{
		if (CapGetOneImage)
		{
			CapGetOneImage = FALSE;
			//ͼ�����¾���


			for (y = 0; y<gHeight - 1; y++)
			{

				for (x = 0; x<(gWidth - 1) * 3; x += 3)
				{
					y11 = y1[y];

					//x11 = x1[ii];
					//ii++;
					cvImage->imageData[gWidth*y * 3 + x] = gBuffer[gWidth*(gHeight - y11) * 3 + x];
					cvImage->imageData[gWidth*y * 3 + x + 1] = gBuffer[gWidth*(gHeight - y11) * 3 + x + 1];
					cvImage->imageData[gWidth*y * 3 + x + 2] = gBuffer[gWidth*(gHeight - y11) * 3 + x + 2];
					//origin
					//cvImage->imageData[gWidth*y * 3 + x] = gBufferDif[gWidth*(gHeight - y) * 3 + x];
					//cvImage->imageData[gWidth*y * 3 + x + 1] = gBufferDif[gWidth*(gHeight - y) * 3 + x + 1];
					//cvImage->imageData[gWidth*y * 3 + x + 2] = gBufferDif[gWidth*(gHeight - y) * 3 + x + 2];
					//	}
				}
			}
			cvShowImage("dif", cvImage);
			//cvWriteFrame(writer, cvImage);
			waitKey(10);
		}
		else
		{
			Sleep(2);
		}
		if (!cvGetWindowHandle("dif")) {

			StarCapFlag2 = FALSE;
			break;
		}
	}
	while (StarCapFlag3)//������====================
	{
		if (CapGetOneImage)
		{
			CapGetOneImage = FALSE;
			//ͼ�����¾���


			for (y = 0; y<gHeight - 1; y++)
			{

				for (x = 0; x<(gWidth - 1) * 3; x += 3)
				{
					x11 = x1[x / 3];
					y11 = y1[y];

					//x11 = x1[ii];
					//ii++;
					cvImage->imageData[gWidth*y * 3 + x] = gBuffer[gWidth*(gHeight - y11) * 3 + x11];
					cvImage->imageData[gWidth*y * 3 + x + 1] = gBuffer[gWidth*(gHeight - y11) * 3 + x11 + 1];
					cvImage->imageData[gWidth*y * 3 + x + 2] = gBuffer[gWidth*(gHeight - y11) * 3 + x11 + 2];
					//origin
					//cvImage->imageData[gWidth*y * 3 + x] = gBufferDif[gWidth*(gHeight - y) * 3 + x];
					//cvImage->imageData[gWidth*y * 3 + x + 1] = gBufferDif[gWidth*(gHeight - y) * 3 + x + 1];
					//cvImage->imageData[gWidth*y * 3 + x + 2] = gBufferDif[gWidth*(gHeight - y) * 3 + x + 2];
					//	}
				}
			}
			cvShowImage("dif", cvImage);
			//cvWriteFrame(writer, cvImage);
			waitKey(10);
		}
		else
		{
			Sleep(2);
		}
		if (!cvGetWindowHandle("dif")) {

			StarCapFlag3 = FALSE;
			break;
		}
	}

	//cvReleaseVideoWriter(&writer);
	cvReleaseImage(&cvImage);
	//cvReleaseImage(&cvShow);
	TerminateThread(AviCapThread1,0);
	return 0;
}


