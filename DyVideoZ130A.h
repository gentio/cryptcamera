 //////////////////////////////////////////////////////////////////////////
//#define VIDEO_EXPORTS
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the VIDEO_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// VIDEO_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef  VIDEO_EXPORTS
#define VIDEO_API __declspec(dllexport)  //dllexport����
#else
#define VIDEO_API __declspec(dllimport)  //dllimport����
#endif
//��׼����ģʽ
#define  STANDARD_CALL __stdcall

//////////////////////////////////////////////////////////////////////////
//��Ƶ�豸����
struct DeviceFacilities
{
	BYTE MarkNum;//���룬�û���˳�����
	BYTE InconstancyNum;//USB�豸�����(���������Զ�����)
	BYTE FixedNum;//�豸�̼��ţ������ڵ�·��ģ����粻��ʧ������ͨ��SetFacilitiesNum�����޸�
	BYTE ProductModel[5]; //��Ʒ�ͺ�Z30A����ASCII���ʾ��
	BOOL Busy;//�豸״̬=1����ռ�á�=0Ϊ���С�
};					       

//////////////////////////////////////////////////////////////////////////
//��  �ܣ���Ƶ���ݵĻص�����                                             
//��  ����pDataRGBΪRGB��ʽ��ͼ�����ݣ�Width��Height�ֱ�Ϊ��Ƶ�Ŀ�Ⱥ͸߶�
typedef BOOL (WINAPI *VideoCallBack)(BYTE *pVideoDataRGB,BYTE *pVideoDataRAW,DWORD VideoWidth,DWORD VideoHeight);

//////////////////////////////////////////////////////////////////////////
//��  �ܣ���Ƶ���ݵĻص���������                                             
//��  ����pDataRGBΪRGB��ʽ��ͼ�����ݣ�Width��Height�ֱ�Ϊ��Ƶ�Ŀ�Ⱥ͸߶�   
BOOL WINAPI VideoCallBack1(BYTE *pVideoDataRGB,BYTE *pVideoDataRAW,DWORD VideoWidth,DWORD VideoHeight);
BOOL WINAPI VideoCallBack2(BYTE *pVideoDataRGB,BYTE *pVideoDataRAW,DWORD VideoWidth,DWORD VideoHeight);


//////////////////////////////////////////////////////////////////////////
//��  �ܣ�����豸                                             
//��  ����pDevFac���豸���Խṹ��ָ��          
//��  �أ�������Ч���豸������������豸���򷵻�0�����10;
extern "C" VIDEO_API BYTE  Z130A_GetDeviceNum(DeviceFacilities *pDevFac);

//////////////////////////////////////////////////////////////////////////
//��  �ܣ�������Ƶ�ֱ���ģʽ                                             
//��  ����VideoModel��Ƶģʽ��0~2 �ֱ���1280*1024 640*512 320*256      
//��  �أ������ɹ�������
extern "C" VIDEO_API BOOL  Z130A_SetVideoModel(BYTE VideoModel,DeviceFacilities *pDevFac);

//////////////////////////////////////////////////////////////////////////
//��  �ܣ�������Ƶ                                           
//��  ����VeoCalBak����Ƶ�ص�����          
//��  �أ������ɹ�������
extern "C" VIDEO_API BOOL  Z130A_OpenVideo(VideoCallBack VeoCalBak,DeviceFacilities *pDevFac);

//////////////////////////////////////////////////////////////////////////
//��  �ܣ���ʾ��Ƶ                                             
//��  ����hwndΪ���ھ��������ΪNULL,��ʱ����ʾͼ��(���Ե��ص�������ȡͼ������)��WndStarH��WndStarV�ֱ��Ǵ����г��������
//        WndWidth��WndHeight�ֱ�Ϊ��Ƶ���ڵĿ�͸�          
//��  �أ������ɹ�������
extern "C" VIDEO_API BOOL  Z130A_ShowVideo(HWND hWnd,DWORD WndStarH,DWORD WndStarV,DWORD WndWidth,
									 DWORD WndHeight,DeviceFacilities *pDevFac);



//////////////////////////////////////////////////////////////////////////
//��  �ܣ�����AWBΪ�ֶ������Զ�                                             
//��  ����EnableΪFALSE���Զ���TRUE���ֶ�          
//��  �أ������ɹ�������
extern "C" VIDEO_API BOOL  Z130A_SetAWBEnable (BOOL Enable,DeviceFacilities *pDevFac);

//////////////////////////////////////////////////////////////////////////
//��  �ܣ��ֶ����ô�������ƵAWB�� ����ƽ�⡣�˺����ںڰ�����ﲻ�����á�                                            
//��  ����AWB:��Χ��2800-6500��Ĭ��Ϊ4700.          
//��  �أ������ɹ�������
extern "C" VIDEO_API BOOL  Z130A_SetAWB(DWORD AWB,DeviceFacilities *pDevFac);

//////////////////////////////////////////////////////////////////////////
//��  �ܣ����ô�����AEWAEC����AEC/AGC�Զ�����ʱ�����޺�����,ֻ�����Զ��ع��ʱ��������á�                                           
//��  ����AEWAEB:��Χ��1-255��Ĭ�ϴ�Ϊ58          
//��  �أ������ɹ�������
extern "C" VIDEO_API BOOL  Z130A_SetAEWAEB(BYTE AEWAEB,DeviceFacilities *pDevFac);

//////////////////////////////////////////////////////////////////////////
//��  �ܣ�����AGCΪ�ֶ������Զ�                                             
//��  ����EnableΪFALSE���Զ���TRUE���ֶ�         
//��  �أ������ɹ�������
extern "C" VIDEO_API BOOL Z130A_SetAGCEnable (BOOL Enable,DeviceFacilities *pDevFac);

//////////////////////////////////////////////////////////////////////////
//��  �ܣ��ֶ�����AGC                                             
//��  �����ֶ�AGCֵ����Χ��1-126          
//��  �أ������ɹ�������
extern "C" VIDEO_API BOOL  Z130A_SetAGC(WORD AGC,DeviceFacilities *pDevFac);

//////////////////////////////////////////////////////////////////////////
//��  �ܣ�����AECΪ�ֶ������Զ�                                             
//��  ����EnableΪFALSE���Զ���TRUE���ֶ�         
//��  �أ������ɹ�������
extern "C" VIDEO_API BOOL  Z130A_SetAECEnable (BOOL Enable,DeviceFacilities *pDevFac);

//////////////////////////////////////////////////////////////////////////
//��  �ܣ�������Ƶ�ع��                                             
//��  ������Χ��0-512��Ĭ�ϴ�Ϊ�������Զ����ã��ֶ�Ĭ��Ϊ140          
//��  �أ������ɹ�������
extern "C" VIDEO_API BOOL  Z130A_SetAEC(DWORD AEC,DeviceFacilities *pDevFac);

//////////////////////////////////////////////////////////////////////////
//��  �ܣ�������Ƶ����                                             
//��  ����Brightness����ֵ,��Χ0-255��Ĭ��0          
//��  �أ������ɹ�������
extern "C" VIDEO_API BOOL  Z130A_SetBrightness(int Brightness,DeviceFacilities *pDevFac);

//////////////////////////////////////////////////////////////////////////
//��  �ܣ�������Ƶ�Աȶ�                                             
//��  ����contrast,��Χ��0-255��Ĭ��50          
//��  �أ������ɹ�������
extern "C" VIDEO_API BOOL  Z130A_SetContrast(int Contrast,DeviceFacilities *pDevFac);

//////////////////////////////////////////////////////////////////////////
//��  �ܣ���ȡAEWAEB                                            
//��  ����          
//��  �أ�AEWAEBֵ
extern "C" VIDEO_API int  Z130A_GetAEWAEB(DeviceFacilities *pDevFac);

//////////////////////////////////////////////////////////////////////////
//��  �ܣ���ȡAWBֵ������ƽ��ֵ                                            
//��  ����          
//��  �أ���ƽ��ֵ
VIDEO_API DWORD  Z130A_GetAWB(DeviceFacilities *pDevFac);

//////////////////////////////////////////////////////////////////////////
//��  �ܣ���ȡ�ֶ����õ�AGC���������Զ�AGCʱ��Ч                                             
//��  ����          
//��  �أ�AGCֵ
extern "C" VIDEO_API int  Z130A_GetAGC(DeviceFacilities *pDevFac);

//////////////////////////////////////////////////////////////////////////
//��  �ܣ���ȡ�ֶ����õ��ع�ֵ ���������Զ��ع�ʱʱ��Ч                                            
//��  ����          
//��  �أ��ع�ֵ
extern "C" VIDEO_API DWORD  Z130A_GetAEC(DeviceFacilities *pDevFac);

//////////////////////////////////////////////////////////////////////////
//��  �ܣ���ȡ��Ƶ����                                             
//��  ����          
//��  �أ�����ֵ
extern "C" VIDEO_API DWORD  Z130A_GetBrightness(DeviceFacilities *pDevFac);

//////////////////////////////////////////////////////////////////////////
//��  �ܣ���ȡ��Ƶ�Աȶ�                                             
//��  ����          
//��  �أ��Աȶ�
extern "C" VIDEO_API DWORD  Z130A_GetContrast(DeviceFacilities *pDevFac);

//////////////////////////////////////////////////////////////////////////
//��  �ܣ���ȡbmp��Ƭ��ʽ
//��  ����BmpPhotoName-����·���͸�ʽ���ļ���
//��  �أ��ɹ������棬���򷵻ؼ�
extern "C" VIDEO_API BOOL  Z130A_GetBmpPhoto(char *BmpPhotoName,DeviceFacilities *pDevFac);

//////////////////////////////////////////////////////////////////////////
//��  �ܣ���ȡ������
//��  ����43�C1023ȱʡ94
//��  �أ�������
extern "C" VIDEO_API  DWORD Z130A_GetHorizontalBlanking(DeviceFacilities *pDevFac);

//////////////////////////////////////////////////////////////////////////
//��  �ܣ���ȡ������
//��  ����4�C3000  ȱʡ45
//��  �أ�������
extern "C" VIDEO_API  DWORD Z130A_GetVerticalBlanking(DeviceFacilities *pDevFac);

//////////////////////////////////////////////////////////////////////////
//��  �ܣ���������������������һ�е�����ʱ�䣬����֡�٣����ֶ�������ع�ʱ���Ƚ������ӡ�һ�㲻Ҫ����������������ܻ��������ЧӦ��
//��  ����43�C1023ȱʡ94
//��  �أ��ɹ������棬���򷵻ؼ�
extern "C" VIDEO_API  BOOL Z130A_SetHorizontalBlanking(WORD Blanking,DeviceFacilities *pDevFac);

//////////////////////////////////////////////////////////////////////////
//��  �ܣ����ó���������������һ֡������ʱ�䣬����֡�٣����Ȳ��䡣
//��  ����4�C3000  ȱʡ45
//���أ��ɹ������棬���򷵻ؼ�
extern "C" VIDEO_API  BOOL Z130A_SetVerticalBlanking(WORD Blanking,DeviceFacilities *pDevFac);


//////////////////////////////////////////////////////////////////////////
//��  �ܣ������豸                                             
//��  ����Ctr����Bit7:��ֱ���� Bit6:ˮƽ����         
//��  �أ������ɹ�������
extern "C" VIDEO_API BOOL  Z130A_SetOther(BYTE Ctr,DeviceFacilities *pDevFac);

//////////////////////////////////////////////////////////////////////////
//������Ƶͼ���� ȡֵ��Χ0~3��ȱʡֵΪ0
//Direction ��0���� 1��ת90�� 2��ת180��  3��ת270�� 
//��  �أ������ɹ�������
extern "C" VIDEO_API bool Z130A_SetImageDirection  (BYTE Direction,DeviceFacilities *pDevFac);

//////////////////////////////////////////////////////////////////////////
//������Ƶͼ����ɫ ȡֵ��Χ0~2��ȱʡֵΪ0
//Color ��0���� 1��ɫ 2�ڰף���ֵ���� 
//��  �أ������ɹ�������
extern "C" VIDEO_API bool Z130A_SetImageColour  (BYTE Colour,DeviceFacilities *pDevFac);

 
//////////////////////////////////////////////////////////////////////////
//��  �ܣ�����֡�ʣ������ֵ�λ                                             
//��  ����Rate��֡�ʵ�λ��0��2��0��֡����ߡ�      
//��  �أ��ɹ�������
extern "C" VIDEO_API BOOL  Z130A_SetFrameRate(BYTE Rate,DeviceFacilities *pDevFac);


//////////////////////////////////////////////////////////////////////////
//��  �ܣ����Ӳ������״̬                                             
//��  ����          
//��  �أ�Ϊ��ʱ��������
extern "C" VIDEO_API BOOL Z130A_GetKey(DeviceFacilities *pDevFac);

//////////////////////////////////////////////////////////////////////////
//�� �ܣ�����GPIO��,��ϸ�Ķ�GPIO�ڵ�ÿһλ���ж�����д������
//�� ����CtrType---ÿλ��ӦGPIO�ڵ�ÿλ���ƵĿ������ͣ�Ϊ0�Ƕ���λ��Ϊ1��д��λ
//      WriteValue---ÿλ��ӦҪ����GPIO�ڵ�ÿλ��ֵ�����CtrType�и�λΪд�������WriteValue��λΪ0�������
//                   ����GPIO�ڸ�λ����͵�ƽ��WriteValue��λΪ1�������PD�ڸ�λ����ߵ�ƽ��
//      *pReadValue---ÿλ��ӦGPIO�ڵ�ÿλ�����CtrType�и�λΪ�����򽫶�����λ��״̬�ŵ�*pReadValue�ĸ�λ��
//�� �أ��ɹ������棬ʧ�ܷ��ؼ�
//�� ע��IO����Ϊ���ʱ������/��15mA���������ʱһ��Ҫ���������裬����һ����·���ջ���оƬ��
extern "C" VIDEO_API BOOL  Z130A_CtrGPIO(BYTE CtrType,BYTE WriteValue,BYTE *pReadValue,DeviceFacilities *pDevFac);

//////////////////////////////////////////////////////////////////////////
//�� �ܣ�ʹ��ͼ�񴥷����ţ���PA1�ڣ���ʹ�����Ժ�ֻ��Ӳ�������������崥��һ�β��ܻ�ȡһ��ͼƬ��
//�� ����Ϊ1ʱʹ�ܣ�Ϊ0ʱ��ֹ��
//�� ע��ֻ���ڿ�ʼ�ɼ�ͼ���Ժ󣬲�����ȷ��ȡ��Ӳ���������ŵ��������źš���ˣ��������������
//      StartVideo()��ſ��Ե��á���������Ӧ����0.1ms��
//��  �أ������ɹ�������
extern "C" VIDEO_API BOOL Z130A_CtrKeyED(bool KED,DeviceFacilities *pDevFac);


//////////////////////////////////////////////////////////////////////////
//�� �ܣ�ʹ��50HZ�ƹ���˸��
//�� ����Ϊ1ʱʹ�ܣ�Ϊ0ʱ��ֹ��
//��  �أ������ɹ�������
extern "C" VIDEO_API BOOL Z130A_SetPowerLineEn(BYTE Enable,DeviceFacilities *pDevFac);


//////////////////////////////////////////////////////////////////////////
//��  �ܣ����õ����򿪵��豸�Ĺ̼��豸��                                             
//��  ����FacilitiesNum�豸�̼��ţ���д��̼���·�У����粻��ʧ��          
//��  �أ������ɹ�������
extern "C" VIDEO_API BOOL  Z130A_SetFacilitiesNum(BYTE FacilitiesNum,DeviceFacilities *pDevFac);

//////////////////////////////////////////////////////////////////////////
//��  �ܣ��ر���Ƶ�豸���˳�����������                                             
//��  ����          
//��  �أ������ɹ�������
extern "C" VIDEO_API BOOL  Z130A_StopVideo(DeviceFacilities *pDevFac);

//////////////////////////////////////////////////////////////////////////
//��  �ܣ��̼��汾��
//��  �أ��汾��
extern "C" VIDEO_API BYTE Z130A_GetFixVer(DeviceFacilities *pDevFac);

//////////////////////////////////////////////////////////////////////////
//��  �ܣ���̬���ӿ�汾��
//��  �أ��汾��
extern "C" VIDEO_API WORD Z130A_GetDLLVer();

//////////////////////////////////////////////////////////////////////////
//���ܣ���֤���룬����8λ0~9�����֣���Ʒ��������Ϊ12345678��
//������PassWord-8λ����
//���أ��ɹ������棬ʧ�ܷ��ؼ�
//˵�����˹�����Ϊ�˱���Ӧ����������̵�֪ʶ��Ȩ��Ӧ����������߿��Ե���Z130A_ChangePassWord������һ��ר������
//      �޸Ĺ�ҵ��������С��������������޸���������롣Ȼ������ʽ��Ӧ�������ȥ��֤������룬������ҵ���
//      �Ƿ��Ǵ�Ӧ��������������ﹺ��ģ��Ӷ��ﵽӦ�������Ȩʹ�õ�Ŀ�ġ�
VIDEO_API BOOL Z130A_VerifyPassWord(BYTE PassWord[8],DeviceFacilities *pDevFac);

//////////////////////////////////////////////////////////////////////////
//�޸����룬��Ʒ��������Ϊ12345678�����ԭ���벻��ȷ�����޷��޸����롣
//������OldPassWord-8λԭ���룬NewPassWord-8λ�����롣
//���أ��ɹ������棬ʧ�ܷ��ؼ�
VIDEO_API BYTE Z130A_ChangePassWord(BYTE OldPassWord[8],BYTE NewPassWord[8],DeviceFacilities *pDevFac);

//////////////////////////////////////////////////////////////////////////
//�����������ڡ���20160215����
//������pDate�������,����20160218
//���أ��ɹ������棬ʧ�ܷ��ؼ�
VIDEO_API BYTE Z130A_ReadDate(BYTE *pDate,DeviceFacilities *pDevFac);    

//////////////////////////////////////////////////////////////////////////
//�������⣨��Ӱ�����ƣ���������������κοͻ����ţ����޴�Ӱ��˾�ڲ�����ʹ�ã�
//������CtrCMD:�������Code����
//���أ��ɹ������棬ʧ�ܷ��ؼ�
VIDEO_API BOOL Z130A_DySpecialCtr(BYTE CtrCMD,BYTE *pCode,DeviceFacilities *pDevFac);                    

//////////////////////////////////////////////////////////////////////////
/*�汾��¼
Ver1.0:
20130524:�޸Ŀ������ͽӿں�����
20130818:�����С����������ܣ��Ա����޼�����֡�ʡ�
20140528:�����Զ��ع⹦�ܡ�
20130524��
1���޸Ŀ��ļ����ͽӿں����������ӱ��ͶȺ͵�Ƭ��Ч����
Ver3.0:
20160217:
1����������У�鹦�ܡ�





*/