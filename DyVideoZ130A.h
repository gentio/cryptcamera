 //////////////////////////////////////////////////////////////////////////
//#define VIDEO_EXPORTS
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the VIDEO_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// VIDEO_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef  VIDEO_EXPORTS
#define VIDEO_API __declspec(dllexport)  //dllexport导出
#else
#define VIDEO_API __declspec(dllimport)  //dllimport导入
#endif
//标准调用模式
#define  STANDARD_CALL __stdcall

//////////////////////////////////////////////////////////////////////////
//视频设备属性
struct DeviceFacilities
{
	BYTE MarkNum;//掩码，用户按顺序填充
	BYTE InconstancyNum;//USB设备随机号(计算机随机自动分配)
	BYTE FixedNum;//设备固件号，保存在电路里的，掉电不丢失。可能通过SetFacilitiesNum函数修改
	BYTE ProductModel[5]; //产品型号Z30A，用ASCII码表示；
	BOOL Busy;//设备状态=1正在占用。=0为空闲。
};					       

//////////////////////////////////////////////////////////////////////////
//功  能：视频数据的回调函数                                             
//参  数：pDataRGB为RGB格式的图像数据，Width和Height分别为视频的宽度和高度
typedef BOOL (WINAPI *VideoCallBack)(BYTE *pVideoDataRGB,BYTE *pVideoDataRAW,DWORD VideoWidth,DWORD VideoHeight);

//////////////////////////////////////////////////////////////////////////
//功  能：视频数据的回调函数声明                                             
//参  数：pDataRGB为RGB格式的图像数据，Width和Height分别为视频的宽度和高度   
BOOL WINAPI VideoCallBack1(BYTE *pVideoDataRGB,BYTE *pVideoDataRAW,DWORD VideoWidth,DWORD VideoHeight);
BOOL WINAPI VideoCallBack2(BYTE *pVideoDataRGB,BYTE *pVideoDataRAW,DWORD VideoWidth,DWORD VideoHeight);


//////////////////////////////////////////////////////////////////////////
//功  能：检测设备                                             
//参  数：pDevFac，设备属性结构体指针          
//返  回：返回有效的设备数量，如果无设备，则返回0，最大10;
extern "C" VIDEO_API BYTE  Z130A_GetDeviceNum(DeviceFacilities *pDevFac);

//////////////////////////////////////////////////////////////////////////
//功  能：设置视频分辨率模式                                             
//参  数：VideoModel视频模式：0~2 分别是1280*1024 640*512 320*256      
//返  回：操作成功返回真
extern "C" VIDEO_API BOOL  Z130A_SetVideoModel(BYTE VideoModel,DeviceFacilities *pDevFac);

//////////////////////////////////////////////////////////////////////////
//功  能：开启视频                                           
//参  数：VeoCalBak：视频回调函数          
//返  回：操作成功返回真
extern "C" VIDEO_API BOOL  Z130A_OpenVideo(VideoCallBack VeoCalBak,DeviceFacilities *pDevFac);

//////////////////////////////////////////////////////////////////////////
//功  能：显示视频                                             
//参  数：hwnd为窗口句柄，可以为NULL,此时不显示图像(可以到回调函数里取图像数据)。WndStarH和WndStarV分别是窗口行场起点坐标
//        WndWidth和WndHeight分别为视频窗口的宽和高          
//返  回：操作成功返回真
extern "C" VIDEO_API BOOL  Z130A_ShowVideo(HWND hWnd,DWORD WndStarH,DWORD WndStarV,DWORD WndWidth,
									 DWORD WndHeight,DeviceFacilities *pDevFac);



//////////////////////////////////////////////////////////////////////////
//功  能：设置AWB为手动还是自动                                             
//参  数：Enable为FALSE是自动，TRUE是手动          
//返  回：操作成功返回真
extern "C" VIDEO_API BOOL  Z130A_SetAWBEnable (BOOL Enable,DeviceFacilities *pDevFac);

//////////////////////////////////////////////////////////////////////////
//功  能：手动设置传感器视频AWB， 即白平衡。此函数在黑白相机里不起作用。                                            
//参  数：AWB:范围是2800-6500，默认为4700.          
//返  回：操作成功返回真
extern "C" VIDEO_API BOOL  Z130A_SetAWB(DWORD AWB,DeviceFacilities *pDevFac);

//////////////////////////////////////////////////////////////////////////
//功  能：设置传感器AEWAEC，即AEC/AGC自动调整时的上限和下限,只有在自动曝光的时候才起作用。                                           
//参  数：AEWAEB:范围是1-255，默认打开为58          
//返  回：操作成功返回真
extern "C" VIDEO_API BOOL  Z130A_SetAEWAEB(BYTE AEWAEB,DeviceFacilities *pDevFac);

//////////////////////////////////////////////////////////////////////////
//功  能：设置AGC为手动还是自动                                             
//参  数：Enable为FALSE是自动，TRUE是手动         
//返  回：操作成功返回真
extern "C" VIDEO_API BOOL Z130A_SetAGCEnable (BOOL Enable,DeviceFacilities *pDevFac);

//////////////////////////////////////////////////////////////////////////
//功  能：手动设置AGC                                             
//参  数：手动AGC值，范围是1-126          
//返  回：操作成功返回真
extern "C" VIDEO_API BOOL  Z130A_SetAGC(WORD AGC,DeviceFacilities *pDevFac);

//////////////////////////////////////////////////////////////////////////
//功  能：设置AEC为手动还是自动                                             
//参  数：Enable为FALSE是自动，TRUE是手动         
//返  回：操作成功返回真
extern "C" VIDEO_API BOOL  Z130A_SetAECEnable (BOOL Enable,DeviceFacilities *pDevFac);

//////////////////////////////////////////////////////////////////////////
//功  能：设置视频曝光度                                             
//参  数：范围是0-512，默认打开为传感器自动设置，手动默认为140          
//返  回：操作成功返回真
extern "C" VIDEO_API BOOL  Z130A_SetAEC(DWORD AEC,DeviceFacilities *pDevFac);

//////////////////////////////////////////////////////////////////////////
//功  能：设置视频亮度                                             
//参  数：Brightness亮度值,范围0-255，默认0          
//返  回：操作成功返回真
extern "C" VIDEO_API BOOL  Z130A_SetBrightness(int Brightness,DeviceFacilities *pDevFac);

//////////////////////////////////////////////////////////////////////////
//功  能：设置视频对比度                                             
//参  数：contrast,范围是0-255，默认50          
//返  回：操作成功返回真
extern "C" VIDEO_API BOOL  Z130A_SetContrast(int Contrast,DeviceFacilities *pDevFac);

//////////////////////////////////////////////////////////////////////////
//功  能：获取AEWAEB                                            
//参  数：          
//返  回：AEWAEB值
extern "C" VIDEO_API int  Z130A_GetAEWAEB(DeviceFacilities *pDevFac);

//////////////////////////////////////////////////////////////////////////
//功  能：获取AWB值，即白平衡值                                            
//参  数：          
//返  回：白平衡值
VIDEO_API DWORD  Z130A_GetAWB(DeviceFacilities *pDevFac);

//////////////////////////////////////////////////////////////////////////
//功  能：获取手动设置的AGC，此项在自动AGC时无效                                             
//参  数：          
//返  回：AGC值
extern "C" VIDEO_API int  Z130A_GetAGC(DeviceFacilities *pDevFac);

//////////////////////////////////////////////////////////////////////////
//功  能：获取手动设置的曝光值 ，此项在自动曝光时时无效                                            
//参  数：          
//返  回：曝光值
extern "C" VIDEO_API DWORD  Z130A_GetAEC(DeviceFacilities *pDevFac);

//////////////////////////////////////////////////////////////////////////
//功  能：获取视频亮度                                             
//参  数：          
//返  回：亮度值
extern "C" VIDEO_API DWORD  Z130A_GetBrightness(DeviceFacilities *pDevFac);

//////////////////////////////////////////////////////////////////////////
//功  能：获取视频对比度                                             
//参  数：          
//返  回：对比度
extern "C" VIDEO_API DWORD  Z130A_GetContrast(DeviceFacilities *pDevFac);

//////////////////////////////////////////////////////////////////////////
//功  能：获取bmp照片格式
//参  数：BmpPhotoName-包含路径和格式的文件名
//返  回：成功返回真，否则返回假
extern "C" VIDEO_API BOOL  Z130A_GetBmpPhoto(char *BmpPhotoName,DeviceFacilities *pDevFac);

//////////////////////////////////////////////////////////////////////////
//功  能：获取行消隐
//参  数：43–1023缺省94
//返  回：行消隐
extern "C" VIDEO_API  DWORD Z130A_GetHorizontalBlanking(DeviceFacilities *pDevFac);

//////////////////////////////////////////////////////////////////////////
//功  能：获取场消隐
//参  数：4–3000  缺省45
//返  回：场消隐
extern "C" VIDEO_API  DWORD Z130A_GetVerticalBlanking(DeviceFacilities *pDevFac);

//////////////////////////////////////////////////////////////////////////
//功  能：设置行消隐，可以增加一行的消隐时间，降低帧速，在手动增益和曝光时亮度将会增加。一般不要调用这个函数，可能会引起蝴蝶效应。
//参  数：43–1023缺省94
//返  回：成功返回真，否则返回假
extern "C" VIDEO_API  BOOL Z130A_SetHorizontalBlanking(WORD Blanking,DeviceFacilities *pDevFac);

//////////////////////////////////////////////////////////////////////////
//功  能：设置场消隐，可以增加一帧的消隐时间，降低帧速，亮度不变。
//参  数：4–3000  缺省45
//返回：成功返回真，否则返回假
extern "C" VIDEO_API  BOOL Z130A_SetVerticalBlanking(WORD Blanking,DeviceFacilities *pDevFac);


//////////////////////////////////////////////////////////////////////////
//功  能：控制设备                                             
//参  数：Ctr定义Bit7:垂直镜像 Bit6:水平镜像。         
//返  回：操作成功返回真
extern "C" VIDEO_API BOOL  Z130A_SetOther(BYTE Ctr,DeviceFacilities *pDevFac);

//////////////////////////////////////////////////////////////////////////
//设置视频图像方向 取值范围0~3，缺省值为0
//Direction ：0正常 1左转90度 2左转180度  3左转270度 
//返  回：操作成功返回真
extern "C" VIDEO_API bool Z130A_SetImageDirection  (BYTE Direction,DeviceFacilities *pDevFac);

//////////////////////////////////////////////////////////////////////////
//设置视频图像颜色 取值范围0~2，缺省值为0
//Color ：0正常 1灰色 2黑白（二值化） 
//返  回：操作成功返回真
extern "C" VIDEO_API bool Z130A_SetImageColour  (BYTE Colour,DeviceFacilities *pDevFac);

 
//////////////////////////////////////////////////////////////////////////
//功  能：设置帧率，共三种档位                                             
//参  数：Rate：帧率档位，0～2；0档帧速最高。      
//返  回：成功返回真
extern "C" VIDEO_API BOOL  Z130A_SetFrameRate(BYTE Rate,DeviceFacilities *pDevFac);


//////////////////////////////////////////////////////////////////////////
//功  能：获得硬件按健状态                                             
//参  数：          
//返  回：为真时按键按下
extern "C" VIDEO_API BOOL Z130A_GetKey(DeviceFacilities *pDevFac);

//////////////////////////////////////////////////////////////////////////
//功 能：控制GPIO口,精细的对GPIO口的每一位进行读或是写操作。
//参 数：CtrType---每位对应GPIO口的每位控制的控制类型，为0是读该位，为1是写该位
//      WriteValue---每位对应要控制GPIO口的每位的值。如果CtrType中该位为写，则如果WriteValue该位为0，则控制
//                   控制GPIO口该位输出低电平，WriteValue该位为1，则控制PD口该位输出高电平。
//      *pReadValue---每位对应GPIO口的每位，如果CtrType中该位为读，则将读到该位的状态放到*pReadValue的该位里
//返 回：成功返回真，失败返回假
//备 注：IO口做为输出时，可拉/推15mA电流。外接时一定要加限流电阻，否则一旦短路将烧坏主芯片。
extern "C" VIDEO_API BOOL  Z130A_CtrGPIO(BYTE CtrType,BYTE WriteValue,BYTE *pReadValue,DeviceFacilities *pDevFac);

//////////////////////////////////////////////////////////////////////////
//功 能：使能图像触发引脚（即PA1口），使能了以后只有硬件引脚有正脉冲触发一次才能获取一张图片。
//参 数：为1时使能，为0时禁止。
//备 注：只有在开始采集图像以后，才能正确获取到硬件触发引脚的正脉冲信号。因此，这个函数必须在
//      StartVideo()后才可以调用。正脉冲宽度应大于0.1ms。
//返  回：操作成功返回真
extern "C" VIDEO_API BOOL Z130A_CtrKeyED(bool KED,DeviceFacilities *pDevFac);


//////////////////////////////////////////////////////////////////////////
//功 能：使能50HZ灯光闪烁。
//参 数：为1时使能，为0时禁止。
//返  回：操作成功返回真
extern "C" VIDEO_API BOOL Z130A_SetPowerLineEn(BYTE Enable,DeviceFacilities *pDevFac);


//////////////////////////////////////////////////////////////////////////
//功  能：设置当件打开的设备的固件设备号                                             
//参  数：FacilitiesNum设备固件号，将写入固件电路中，掉电不丢失。          
//返  回：操作成功返回真
extern "C" VIDEO_API BOOL  Z130A_SetFacilitiesNum(BYTE FacilitiesNum,DeviceFacilities *pDevFac);

//////////////////////////////////////////////////////////////////////////
//功  能：关闭视频设备，退出，清理数据                                             
//参  数：          
//返  回：操作成功返回真
extern "C" VIDEO_API BOOL  Z130A_StopVideo(DeviceFacilities *pDevFac);

//////////////////////////////////////////////////////////////////////////
//功  能：固件版本号
//返  回：版本号
extern "C" VIDEO_API BYTE Z130A_GetFixVer(DeviceFacilities *pDevFac);

//////////////////////////////////////////////////////////////////////////
//功  能：动态链接库版本号
//返  回：版本号
extern "C" VIDEO_API WORD Z130A_GetDLLVer();

//////////////////////////////////////////////////////////////////////////
//功能：验证密码，仅限8位0~9的数字，产品出厂密码为12345678。
//参数：PassWord-8位密码
//返回：成功返回真，失败返回假
//说明：此功能是为了保护应用软件开发商的知识产权。应用软件开发者可以调用Z130A_ChangePassWord函数做一个专门用于
//      修改工业相机密码的小工具软件，用来修改相机和密码。然后在正式的应用软件里去验证这个密码，以区别工业相机
//      是否是从应用软件开发者手里购买的，从而达到应用软件授权使用的目的。
VIDEO_API BOOL Z130A_VerifyPassWord(BYTE PassWord[8],DeviceFacilities *pDevFac);

//////////////////////////////////////////////////////////////////////////
//修改密码，产品出厂密码为12345678。如果原密码不正确，将无法修改密码。
//参数：OldPassWord-8位原密码，NewPassWord-8位新密码。
//返回：成功返回真，失败返回假
VIDEO_API BYTE Z130A_ChangePassWord(BYTE OldPassWord[8],BYTE NewPassWord[8],DeviceFacilities *pDevFac);

//////////////////////////////////////////////////////////////////////////
//读出出厂日期——20160215增加
//参数：pDate存放日期,比如20160218
//返回：成功返回真，失败返回假
VIDEO_API BYTE Z130A_ReadDate(BYTE *pDate,DeviceFacilities *pDevFac);    

//////////////////////////////////////////////////////////////////////////
//本厂特殊（大影）控制（本命令及函数不对任何客户开放，仅限大影公司内部调试使用）
//参数：CtrCMD:控制命令，Code数组
//返回：成功返回真，失败返回假
VIDEO_API BOOL Z130A_DySpecialCtr(BYTE CtrCMD,BYTE *pCode,DeviceFacilities *pDevFac);                    

//////////////////////////////////////////////////////////////////////////
/*版本记录
Ver1.0:
20130524:修改库名名和接口函数名
20130818:增加行、场消隐功能，以便于无极调整帧率。
20140528:增加自动曝光功能。
20130524：
1、修改库文件名和接口函数名，增加饱和度和底片特效函数
Ver3.0:
20160217:
1、增加密码校验功能。





*/