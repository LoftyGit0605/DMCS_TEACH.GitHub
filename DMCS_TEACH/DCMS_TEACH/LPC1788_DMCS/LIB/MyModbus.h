#ifndef _MYMODBUS_H_
#define _MYMODBUS_H_

//void ModbusServe(void);
typedef enum{
	Key_None_MBus=0,
	Key_Start=1,
	Key_Pause=2,
	Key_Stop=3,
	Key_Sure=4,
	Key_Cancel=5,
	Key_XaddDown=6,
	Key_XaddUp=7,
	Key_XdecDown=8,
	Key_XdecUp=9,
	Key_YaddDown=10,
	Key_YaddUp=11,
	Key_YdecDown=12,
	Key_YdecUp=13,
	Key_ZaddDown=14,
	Key_ZaddUp=15,
	Key_ZdecDown=16,
	Key_ZdecUp=17,
	Key_RaddDown=18,
	Key_RaddUp=19,
	Key_RdecDown=20,
	Key_RdecUp=21,
	Key_GoHome=22,
	Key_GoHomeXY=23,
	Key_GoHomeY=24,
	Key_GoHomeZ=25,
	Key_GoHomeR=26,
	Key_GoOrg=27,
	Key_GoOrgXY=28,
	Key_GoOrgR=29,
	Key_GoOrgZ=30,
	Key_SetOrgIndex=31,
	Key_JogSpeedMode=32,
	Key_JogLenMode=33,
	Key_JogLenVal=34,
	Key_SaveParam=35,
	Key_CancelParam=36,
	Key_MessBoxOK=37,
	Key_MessBoxYes=38,
	Key_MessBoxNo=39,
	Key_MessBoxCancel=40,
	Key_SysParamSet=41,
	Key_FormParamSet=42,
	Key_CancelParam1=43,
	Key_SetOutIO00_On=44,
	Key_SetOutIO01_On=45,
	Key_SetOutIO02_On=46,
	Key_SetOutIO03_On=47,
	Key_SetOutIO04_On=48,
	Key_SetOutIO05_On=49,
	Key_SetOutIO06_On=50,
	Key_SetOutIO07_On=51,
	Key_SetOutIO08_On=52,
	Key_SetOutIO09_On=53,
	Key_SetOutIO10_On=54,
	Key_SetOutIO11_On=55,
	Key_SetOutIO12_On=56,
	Key_SetOutIO13_On=57,
	Key_SetOutIO14_On=58,
	Key_SetOutIO15_On=59,
	Key_FormIOTest=60,
	Key_SetOutIO00_Off=61,
	Key_SetOutIO01_Off=62,
	Key_SetOutIO02_Off=63,
	Key_SetOutIO03_Off=64,
	Key_SetOutIO04_Off=65,
	Key_SetOutIO05_Off=66,
	Key_SetOutIO06_Off=67,
	Key_SetOutIO07_Off=68,
	Key_SetOutIO08_Off=69,
	Key_SetOutIO09_Off=70,
	Key_SetOutIO10_Off=71,
	Key_SetOutIO11_Off=72,
	Key_SetOutIO12_Off=73,
	Key_SetOutIO13_Off=74,
	Key_SetOutIO14_Off=75,
	Key_SetOutIO15_Off=76,
	Key_FileSelSure=77,
	Key_FileSelCancel=78,
	Key_FileSelPrePage=79,
	Key_FileSelNextPage=80,
	Key_FormFileOperate=81,
	Key_FileSelDelete=82,
	Key_FileSelIndex=83,
	Key_BrokenSelIndex=84,
	Key_BrokenSure=85,
	Key_BrokenCancel=86,
	Key_MessBoxRegOver=87,
	Key_MessBoxRegTime=88,
	Key_MessBoxRegCancel=89,
	Key_FormMachSizeTest=90,
	Key_FormMachSizeStart=91,
	Key_FormMachSizeStop=92,
	Key_FormMachSizeAdjust=93,
	Key_FormMachSizeCancel=94,
	Key_EnterMainForm=95,
	Key_LineWorkSure=96,
	Key_LineWorkCancel=97,
	Key_RepeatWorkSure=98,
	Key_RepeatWorkCancel=99,
	Key_FormEnterRegNum=100,
	Key_FormEnterAdjust=101,
	Key_SetOrigin =102,
	Key_SetRedLightOpen=103,
	Key_SetRedLightClose=104,
	Key_DaoOpen=105,
	Key_DaoClose=106,
	Key_PenOpen=107,
	Key_PenClose=108,
	Key_YaLunOpen=109,
	Key_YaLunClose=110,
	Key_VaPumn1Open=111,
	Key_VaPumn1Close=112,
	Key_VaPumn2Open=113,
	Key_VaPumn2Close=114,
	Key_TestXYSetZero=115,
	Key_TestPenTest=116,
	Key_TestPenAdjust=117,
	Key_TestYaLunTest=118,
	Key_TestYaLunAdjust=119,
	Key_TestRedLightTest=120,
	Key_TestRedLightAdjust=121,
	Key_SetDefaultOrgPos=122,
	Key_SaveParamToSD=123,
	Key_SaveParamToUSB=124,
	Key_ReadParamSD=125,
	Key_ReadParamUSB=126,
	Key_EnterSaveParamForm=127,
	Key_IOTestCancel=128,
	Key_RepeatWork=129,
	Key_EnterFormBrokenSel=130,
	Key_EnterPassword=131,
	Key_SureCompParam=132,
	Key_CancelCompParam=133,
	Key_GoHomeTipStop=134,
	Key_ManGoLeftBottom=135,
	Key_ManGoLeftUp=136,
	Key_ManGoRightBottom=137,
	Key_ManGoRightUp=138,
	Key_ManGoZUp=139,
	Key_ManGoRZero=140,
	Key_DeleteAllFile=141,
	Key_DeletePageFile=142,
	Key_DaoChengXYTest=143,		
}KeyCodeType;

typedef enum {
//总地址65535 0xffff
//按钮地址从3开始到200
	btnStart=3,  //开始按钮
	btnPause=4,
	btnStop=5,
	btnSure=6,
	btnCancel=7,
	btnOpen=8,
	btnRepeat=9,
	btnSaveParam=10,
	btnCancelParam=11,
	btnBrokenWork=12,  //断点加工
	btnLineNumWork=13, //行号加工
	btnMessBoxOk=14,	//对话框OK按钮
	btnMessBoxYes=15,	//对话框YES按钮
	btnMessBoxNo=16,	//对话框NO按钮
	btnMessBoxCancel=17, //对话框取消按钮
	btnSysParamSet=18,  //系统参数设置
	btnCancelParam1=19, //
	btnXadd=20,
	btnXdec=21,
	btnYadd=22,
	btnYdec=23,
	btnZadd=24,
	btnZdec=25,
	btnRadd=26,
	btnRdec=27,
	btnGoHome=28,
	btnGoOrigon=29,
	btnGoXYHome=30,
	btnGoZHome=31,
	btnGoRHome=32,
	btnPen1=33,
	btnSetOrgion=34,
	btnJogSpeedMode=35,//高低速
	btnJogLenMode=36,//移动模式,0:连续,1:点动;2:距离
	btnPen2=37,
	btnXiFu=38,
	btnSetOrgIndex=39,//坐标系索引切换
	btnEnterParamForm=40, //
	btnEnterMainForm=41,
	btnEnterAdjustForm=42,//
	btnEnterRegForm=43,//
	btnEnterIOTestForm=44,
	btnFileSelSure=45,
	btnFileSelCancel=46,
	btnFileSelPrePage=47,
	btnFileSelNextPage=48,
	btnFileSelDelete=49,
	btnOutIO0=50,
	btnOutIO1=51,
	btnOutIO2=52,
	btnOutIO3=53,
	btnOutIO4=54,
	btnOutIO5=55,
	btnOutIO6=56,
	btnOutIO7=57,
	btnOutIO8=58,
	btnOutIO9=59,
	btnOutIO10=60,
	btnOutIO11=61,
	btnOutIO12=62,
	btnOutIO13=63,
	btnOutIO14=64,
	btnOutIO15=65,
	btnFileSelIndex=66,
	btnBrokenIndex=67,
	btnBrokenSure=68,
	btnBrokenCancel=69,
	btnMessBoxRegOver=70,
	btnMessBoxRegTime=71,
	btnMessBoxRegCancel=72,
	btnEnterMachSizeTestForm=73,
	btnMachSizeTestStart=74,
	btnMachSizeTestStop=75,
	btnMachSizeTestAdjust=76,
	btnMachSizeTestCancel=77,
	btnLineWorkSure=78,
	btnLineWorkCancel=79,
	btnRepeatWorkSure=80,
	btnRepeatWorkCancel=81,
	btnDaoOpenClose=82,
	btnPenOpenClose=83,
	btnYaLunOpenClose=84,
	btnVaPumn1OpenClose=85,
	btnVaPumn2OpenClose=86,
	btnVaPumnOPenMode=87,
	btnTestXYSetZero=88,
	btnPenTest=89,
	btnPenAdjust=90,
	btnYaLunTest=91,
	btnYaLunAdjust=92,
	btnRedLightTest=93,
	btnRedLightAdjust=94,
	btnSetDefaultOrgPos=95,
	btnSaveParamToSD=96,
	btnSaveParamToUSB=97,
	btnReadParamToSD=98,
	btnReadParamToUSB=99,
	btnEnterSaveReadParam=100,
	btnIOTestCancel=101,
	btnEnterPassWord=102,
	btnSureEnterCompParam=103,
	btnCancelCompParam=104,
	btnGoHomeTipStop=105,
	btnGoLeftBottom=107,
	btnGoLeftUp=108,
	btnGoRightBottom=109,
	btnGoRightUp=110,
	btnGoZUp=111,
	btnGoRZero=112,
	btnDeleteAllFile=113,
	btnDeleteCurrPageFile=114,
	btnDaoChengXYTest=115,
///////////////////////////////////////////////////////////////
	btnStart_E=203,  //开始按钮
	btnPause_E=204,
	btnStop_E=205,
	btnSure_E=206,
	btnCancel_E=207,
	
	btnXadd_E=220,
	btnXdec_E=221,
	btnYadd_E=222,
	btnYdec_E=223,
	btnZadd_E=224,
	btnZdec_E=225,
	btnRadd_E=226,
	btnRaec_E=227,
	btnGoHome_E=228,
	btnGoOrigon_E=229,
	btnGoXYHome_E=230,
	btnGoZHome_E=231,
	btnGoRHome_E=232,
	btnPen1_E=233,
///////////////////////////////////////////////
//显示
	coorMachX=800, //机械坐标
	coorMachY=802,
	coorMachZ=804,
	coorMachR=806,
	coorWorkX=808, //工件坐标
	coorWorkY=810,
	coorWorkZ=812,
	coorWorkR=814,
	lmtStuX=816, //限位  0:没限位  1:+限位,2:负限位
	lmtStuY=817,
	lmtStuZ=818,
	lmtStuR=819,
	disMoveLen=821,

	stuInIOEMCStop=823,
	stuInIOPause=824,
	stuInIOOrgX=825,
	stuInIOOrgY=826,
	stuInIOOrgZ=827,
	stuInIOOrgR=828,
	stuInIOXLmtPos=829,
	stuInIOXLmtNeg=830,
	stuInIOYLmtPos=831,
	stuInIOYLmtNeg=832,
	filePenNum=833, 
	fileWorkSpeed=834,
	fileWorkName=836,  //文件加工名，20个地址，40个字节
	fileWorkTotal=858,
	fileWorkCurrIndex=860,
	fileTimeHour=862,
	fileTimeMin=864,
	fileTimeSec=865,
	fileFinishRate=866,
	//////////////////////
	//当期显示状态    
	//enum   SystemStuShowStr
	strSystemStuShow =867,
	currOrgIndex=868,
	MachSizeTestSetXval=869,
	MachSizeTestSetYval=871,
	MachSizeTestRealXval=873,
	MachSizeTestRealYval=875,
	RepeatWorkTimes=876,
	RepeatWorkDelayMs=877,
	LineWorkCmdCount=879,
	LineWorkCmdBegin=881,
	LineWorkCmdEnd=883,
	
	PenTestOffSetX =885,
	PenTestOffSetY=887,
	PenTestRealX=889,
	PenTestRealY=891,
	YaLunTestOffSetX=893,
	YaLunTestOffSetY=895,
	YaLunTestRealX=897,
	YaLunTestRealY=899,
	OffsetTestStrShow=901,
	RepeatWorkStopPosX=905,
	RepeatWorkStopPosY=907,

	//IO状态显示
	show_V2_InIO5=1000,
	show_V2_InIO6=1001,
	show_V2_InIO7=1002,
	show_V2_InIO8=1003,
	show_V2_InIO1=1004,
	show_V2_InIO2=1005,
	show_V2_InIO3=1006,
	show_V2_InIO4=1007,
	show_V2_InIOEMC=1008,
	show_V2_InIOALmtPos=1009,
	show_V2_InIOAOrg=1010,
	show_V2_InIOALmtNeg=1011,
	show_V2_InIORLmtPos=1012,
	show_V2_InIOROrg=1013,
	show_V2_InIORLmtNeg=1014,
	show_V2_InIOZLmtPos=1015,
	show_V2_InIOZOrg=1016,
	show_V2_InIOZLmtNeg=1017,
	show_V2_InIOYLmtPos=1018,
	show_V2_InIOYOrg=1019,
	show_V2_InIOYLmtNeg=1020,
	show_V2_InIOXLmtPos=1021,
	show_V2_InIOXOrg=1022,
	show_V2_InIOXLmtNeg=1023,
	show_V2_InIOStart=1024,
	show_V2_InIOWaring=1025,
	show_V2_InIOReturn=1026,
	show_V2_InIOStop=1027,
	show_V2_OutIO1=1030,
	show_V2_OutIO2=1031,
	show_V2_OutIO3=1032,
	show_V2_OutIO4=1033,
	show_V2_OutIO13=1034,
	show_V2_OutIO14=1035,
	show_V2_OutIO15=1036,
	show_V2_OutIO16=1037,
	show_V2_OutIO9=1038,
	show_V2_OutIO10=1039,
	show_V2_OutIO11=1040,
	show_V2_OutIO12=1041,
	show_V2_OutIO5=1042,
	show_V2_OutIO6=1043,
	show_V2_OutIO7=1044,
	show_V2_OutIO8=1045,
/////////////////////////
//参数
	param_SgdcX=2000,
	param_SgdcY=2002,
	param_SgdcZ=2004,
	param_SgdcR=2006,
	param_PulseX=2008,
	param_PulseY=2009,
	param_PulseZ=2010,
	param_PulseR=2011,
	param_HomeDirX=2012,
	param_HomeDirY=2013,
	param_HomeDirZ=2014,
	param_HomeDirR=2015,
	param_HomeSpeedX=2016,
	param_HomeSpeedY=2018,
	param_HomeSpeedZ=2020,
	param_HomeSpeedR=2022,
	param_SpeedMinX=2024,
	param_SpeedMaxX=2026,
	param_SpeedMinY=2028,
	param_SpeedMaxY=2030,
	param_SpeedMinZ=2032,
	param_SpeedMaxZ=2034,
	param_SpeedMinR=2036,
	param_SpeedMaxR=2038,
	param_AxisAccX=2040,
	param_AxisAccY=2042,
	param_AxisAccZ=2044,
	param_AxisAccR=2046,
	param_MoveSpeedX=2048,
	param_MoveSpeedY=2050,
	param_MoveSpeedZ=2052,
	param_MoveSpeedR=2054,
	param_JogSpeedLX=2056,
	param_JogSpeedLY=2058,
	param_JogSpeedLZ=2060,
	param_JogSpeedLR=2062,
	param_JogSpeedHX=2064,
	param_JogSpeedHY=2066,
	param_JogSpeedHZ=2068,
	param_JogSpeedHR=2070,
	param_JogStepLX=2072,
	param_JogStepLY=2074,
	param_JogStepLZ=2076,
	param_JogStepLR=2078,
	param_JogStepHX=2080,
	param_JogStepHY=2082,
	param_JogStepHZ=2084,
	param_JogStepHR=2086,
	param_AngleSpeed=2088,
	param_TrackAcc=2090,
	param_WorkSpeed=2092,
	param_TableSizeX=2094,
	param_TableSizeY=2096,
	param_TableSizeZ=2098,
	param_TableSizeR=2100,
	param_AutoGoHome=2104,
	param_SpeedGuage=2146,
	param_PausePosSel=2147,
	param_PausePosX=2148,
	param_PausePosY=2150,
	param_PausePosZ=2152,
	param_PausePosR=2154,
	param_StopPosSel=2156,
	param_StopPosX=2158,
	param_StopPosY=2160,
	param_StopPosZ=2162,
	param_StopPosR=2164,
	param_AxisAlarmStop=2166,
	param_LangageSelect=2167,
	param_LogoSelect=2168,
	param_inIOEMCStop=2169,
	param_inIOPause=2170,
	param_inIOXLmtPos=2171,
	param_inIOXLmtNeg=2172,
	param_inIOYLmtPos=2173,
	param_inIOYLmtNeg=2174,
	param_inIOXOrg=2175,
	param_inIOYOrg=2176,
	param_inIOZOrg=2177,
	param_inIOROrg=2178,
	param_outIOToolsDao=2179,
	param_outIOToolsPen=2180,
	param_outIORedPen=2181,
	param_outIOVacuumPumn=2182,
	param_outIOAdsorb1=2183,
	param_outIOAdsorb2=2184,
	param_outIOAdsorb3=2185,
	param_outIOAdsorb4=2186,
	param_outIOAdsorb5=2187,
	param_outIOAdsorb6=2188,
	param_outIOAdsorb7=2189,
	param_outIOAdsorb8=2190,
	param_MotionDirX=2191,
	param_MotionDirY=2192,
	param_MotionDirZ=2193,
	param_MotionDirR=2194,
	param_SoftLmtEnableX=2195,
	param_SoftLmtEnableY=2196,
	param_SoftLmtEnableZ=2197,
	param_SoftLmtEnableR=2198,
	param_MaxBtwAng=2199,
    param_AdsordMode=2201,
    param_AdsordSubXY=2202,
    param_PumnOpenMode=2203,
    param_ZDownSpeed=2204,
    param_ZDownVal=2206,
    param_ZUpVal=2208,
    param_RedLightOffX=2210,
    param_RedLightOffY=2212,
    param_PenOffX=2214,
    param_PenOffY=2216,
    param_YaLunOffX=2218,
    param_YaLunOffY=2220,
    param_YaLunRAxisRate=2222,
    param_RGoHomeErr=2224,
    param_DelayPumnOpen=2226,
    param_DelayToolOpen=2227,
    param_DelayPenDown=2228,
    param_DelayPenUp=2229,
    param_DelayYaLunDown=2230,
    param_DelayYaLunUp=2231,
    param_PulseXLong=2233,
	param_PulseYLong=2235,
	param_PulseZLong=2237,
	param_PulseRLong=2239,
	param_AngleSpeedDao=2241,
	param_TrackAccDao=2243,
	param_WorkSpeedDao=2245,
	param_AngleSpeedPen=2247,
	param_TrackAccPen=2249,
	param_WorkSpeedPen=2251,
	param_AngleSpeedYaLun=2253,
	param_TrackAccYaLun=2255,
	param_WorkSpeedYaLun=2257,
	param_AngleSpeedMove=2259,
	param_TrackAccMove=2261,
	param_WorkSpeedMove=2263,
	param_DownToolErrEnable=2265,
	param_UpToolErrEnable=2266,
	param_DownToolErrLen=2267,
	param_UpToolErrLen=2269,
	param_EndCutLineEnable=2271,
	param_EndCutLineLen=2272,
	param_HalfZDownVal=2274,
	param_PenDownHoldTime=2276,
	param_SpeedStartVDao=2300,
	param_SpeedStartVPen=2302,
	param_SpeedStartVYaLun=2304,
	param_SpeedStartVMove=2306,	
///////////////////////////////////////////////////////////////////////////////////////////
	broken_FileStrShow=3000,
	broken_fileIndex=3001,
	broken_file0Back=3002,
	broken_file1Back=3003,
	broken_file2Back=3004,
	broken_file3Back=3005,
	broken_file4Back=3006,
	broken_file5Back=3007,
	broken_file6Back=3008,
	broken_file7Back=3009,
	broken_file8Back=3010,
	broken_file9Back=3011,
	broken_file0=3020,
	broken_file0Lenth=3049,
	broken_file1=3050,
	broken_file1Lenth=3079,
	broken_file2=3080,
	broken_file2Lenth=3109,
	broken_file3=3110,
	broken_file3Lenth=3139,
	broken_file4=3140,
	broken_file4Lenth=3169,
	broken_file5=3170,
	broken_file5Lenth=3199,
	broken_file6=3200,
	broken_file6Lenth=3229,
	broken_file7=3230,
	broken_file7Lenth=3259,
	broken_file8=3260,
	broken_file8Lenth=3289,
	broken_file9=3290,
	broken_file9Lenth=3319,
///////////////////////////////////////////////////////////////////////
//  弹出对话框  30，YesNo, 31 OKOnly,32 OKCancel, 
//33 断点保存 34,软件注册(未到期)  35,软件已到期注册, 
	MessgeBoxFormIndex=3200,
	//显示内容定义  MessBoxShowInfo
	PasswordVal=3202, 
	MessgeBoxShowStrNone=3204,
	MessgeBoxShowStrYesNo=3205,
	MessgeBoxShowStrOkOnly=3206,
	MessgeBoxShowStrOkCancel=3207,
	MessgeBoxShowStrRegOver=3208,
	MessgeBoxShowStrRegTime=3209,
	MessgeBoxShowStrPassword=3210,
	MessgeBoxShowSaveBroken=3211,
	MessgeBoxShowGoHomeStr=3212,
/////////////////////////////////////////////////////////////////////
	file_Count=4000,
	file_PageCount=4002,
	file_PageIndex=4003,
	file_SelIndex=4004,
	file_SelBack0=4005,
	file_SelBack1=4006,
	file_SelBack2=4007,
	file_SelBack3=4008,
	file_SelBack4=4009,
	file_SelBack5=4010,
	file_SelBack6=4011,
	file_SelBack7=4012,
	file_SelBack8=4013,
	file_SelBack9=4014,

	file_Name0=4100,
	file_Name0Lenth=4199,
	file_Name1=4200,
	file_Name1Lenth=4299,
	file_Name2=4300,
	file_Name2Lenth=4399,
	file_Name3=4400,
	file_Name3Lenth=4499,
	file_Name4=4500,
	file_Name4Lenth=4599,
	file_Name5=4600,
	file_Name5Lenth=4699,
	file_Name6=4700,
	file_Name6Lenth=4799,
	file_Name7=4800,
	file_Name7Lenth=4899,
	file_Name8=4900,
	file_Name8Lenth=4999,
	file_Name9=5000,
	file_Name9Lenth=5199,
	//5100
	//触摸屏当前日期记录
	RecordCurrTimeSec=6000,
	RecordCurrTimeMin=6001,
	RecordCurrTimeHour=6002,
	RecordCurrTimeDay=6003,
	RecordCurrTimeMonth=6004,
	RecordCurrTimeYear=6005,
	//到期时间显示
	ShowEndTimeDay=6006,
	ShowEndTimeMonth=6007,
	showEndTimeYear=6008,
	//机器码
	MachineCode1=6020,
	MachineCode2=6022,
	MachineCode3=6024,
	MachineCode4=6026,
	//注册码
	RegNumCode1=6030,
	RegNumCode2=6033,
	RegNumCode3=6036,
	//调试信息打印
	debugInfoStr1=6100,
	debugInfoStr2=6130,
	debugInfoStr3=6160,
	debugInfoStr4=6190,
	//test
	testCurrTimeSec=8000,
	testCurrTimeMin=8001,
	testCurrTimeHour=8002,
	testCurrTimeDay=8003,
	testCurrTimeMonth=8004,
	testCurrTimeYear=8005,	
}Address_WeinView;

typedef enum{
	mess_FormNone=0,
	mess_FormYesNo=30,
	mess_FormOkOnly=31,
	mess_FormOKCancel=32,
	mess_FormBrokenSave=33,
	mess_FormRegOver=34,
	mess_FormRegTime=35,
	mess_FormPassword=36,
	mess_FormDebugInfo=37,
	mess_FormRepeatWork=38,
	mess_FormGoHomeTip=39,	
} MessBoxFormWeinView;

typedef enum {
	mess_AutoGoHome=0,//是否自动回零
	//mess_SaveBroken=1,//是否保存断点?
	mess_IsPowerOffWork=1,//是否掉电加工?
	mess_FileDelete=2,//是否删除选择的文件?
	mess_FileDeleteAll=3, //是否删除全部文件?
	mess_FileDeletePage=4, //是否删除当前页的文件?	
}MessBoxShowInfoYesNo;

typedef enum {
	mess_GoHomeStrAll=0,//系统正在全部回零，请等待...
	mess_GoHomeStrXY=1,//系统正在XY回零，请等待...
	mess_GoHomeStrTZ=2,//系统正在TZ回零，请等待...
	mess_GoHomeStrOrg=3, //系统正在回原点，请等待...
	mess_GoLeftButtom=4, // 系统正在回左下角,请等待...
	mess_GoLeftUp=5,   //系统正在回左上角,请等待...
	mess_GoRightButtom=6, //系统正在回右下角，请等待...
	mess_GoRightUp=7, //系统正在回右上角，请等待...
	mess_GoZUp=8, //系统正在拉起Z轴，请等待...
	mess_GoRZero=9, //系统正在T轴回零，请等待...	
}MessBoxShowGoHomeTipStr;

typedef enum{
	mess_SaveBroken=0,//是否保存断点?	
}MessBoxShowSaveBroken;

typedef enum {
	mess_OpenFileErr1=0, //文件打开失败,无法加工!
	mess_OpenFileErr2=1, //文件格式错误!"
	mess_OpenFileErr3=2,//文件读取失败,无法加工
	mess_PasswordErr1=3,//密码输入错误，请重新输入
	mess_DocLmtErr_Val_Xmax=4,//文件Xmax大于机床Xmax
	mess_DocLmtErr_Val_Xmin=5,//文件Xmin小于机床Xmin
	mess_DocLmtErr_Val_Ymax=6,//文件Ymax大于机床Ymax
	mess_DocLmtErr_Val_Ymin=7,//文件Ymin小于机床Ymin
	mess_DocLmtErr_Val_XTravel=8,//文件超过X轴行程
	mess_DocLmtErr_Val_YTravel=9,//文件超过Y轴行程
	mess_FileDeleteSuccess=10,//文件删除成功
	mess_FileDeleteFaild=11, //文件删除失败
	mess_BrokenSaveErr1=12, //断点号太大,断点无法保存!
	mess_BrokenSaveErr2=13, //断点文件打开错误,断点无法保存!
	mess_BrokenSaveErr3=14, //断点文件写入错误,断点无法保存!
	mess_BrokenReadErr1=15, //断点号太大,断点无法打开!
	mess_BrokenReadErr2=16, //断点文件打开错误,断点无法读取!
	mess_BrokenReadErr3=17, //断点文件读取错误,断点无法读取
	mess_GoHomeNoLmtX=18,	//X轴限位无法触发，回零失败
	mess_GoHomeNoLmtY=19,	//Y轴限位无法触发，回零失败
	mess_GoHomeNoLmtZ=20,	//Z轴限位无法触发，回零失败
	mess_GoHomeNoLmtR=21,	//R轴限位无法触发，回零失败
	mess_GoHomeConLmtX=22, 	//X轴限位无法退出，回零失败
	mess_GoHomeConLmtY=23, 	//Y轴限位无法退出，回零失败
	mess_GoHomeConLmtZ=24, 	//Z轴限位无法退出，回零失败
	mess_GoHomeConLmtR=25, 	//R轴限位无法退出，回零失败
	mess_NoGoHomeWork=26,//没有回零，不能加工文件!
	mess_NoGoHomeGoOrg=27,//没有回零或者定义原点,不能回原点
	mess_AxisAlarmX=28,		//X轴报警,请断电检查!
	mess_AxisAlarmY=29,		//Y轴报警,请断电检查!
	mess_AxisAlarmZ=30,		//Z轴报警,请断电检查!
	mess_AxisAlarmR=31,		//R轴报警,请断电检查!
	mess_WorkFileError=32,  //文件数据错,退出加工!
	mess_NotSetOrgWork=33,	//没有设置原点，不能加工
	mess_NotOpenFileWork=34,  //没有打开文件，不能加工!
	mess_BackUpParamOK=35, 	//参数备份成功
	mess_BackUpParamFalse=36, //参数备份失败
	mess_ReadParamOk=37,	//导入参数成功
	mess_ReadParamFalse=38,	//导入参数失败
	mess_GoHomeSuccess=39,//回零成功,
	mess_GoHomeFalse=40, //回零失败
	mess_GoOrgSuccess=41, //回原点成功
	mess_GoOrgFalse=42,	//回原点失败
	mess_ReadPowerRunFalse=43, //读取掉电文件失败
	mess_NoGoHomeToManMove=44, //没有回零，不能移动
	mess_WeiLunTimeMinCurrTime=45, //触摸屏时间小于板卡时间,请修改	
}MessBoxShowInfoOkOnly;

typedef enum{
	mess_PasswordStr=0, //请输入正确密码后进入高级参数
}MessBoxShowInfoPassWord;

typedef enum{
	mess_SysEndTime0=0, //软件已到期，需要注册才能使用
	mess_RegNumSuccessOver=1, //注册成功
	mess_RegNumFalseOver=2,	//注册失败
	mess_RegNumNoEndTimeOver=3,//系统已完全解除限制!
}MessBoxShowInfoRegOver;

typedef enum{	
	mess_SysEndTime1=0,//软件还剩0天到期，是否需要注册?
	mess_SysEndTime2=1,
	mess_SysEndTime3=2,
	mess_SysEndTime4=3,
	mess_SysEndTime5=4,
	mess_SysEndTime6=5,
	mess_SysEndTime7=6,
	mess_SysEndTime8=7,//软件还剩7天到期，是否需要注册?
	mess_SysSetRegNum=8,//系统使用时间注册
	mess_RegNumSuccessTime=9, //注册成功
	mess_RegNumFalseTime=10,	//注册失败
	mess_RegNumNoEndTimeTime=11,//系统已完全解除限制!
}MessBoxShowInfoRegTime;

typedef enum{
	strMain_SysNone=0, //系统空闲
	strMain_Working=1, //系统加工中
	strMain_Pause=2, //系统暂停...
	strMain_Stop=3, //系统停止...
	strMain_NotGoHome=4, //系统没有回零,不能加工!
	strMain_NoSetOrg=5, //系统没有设置原点，不能加工
	strMain_PauseStop=6, //系统暂停后停止
	strMain_EMCIOStop=7, //外部急停按下，系统暂停
	strMain_PasueIOStop=8, //外部暂停有信号，系统暂停
	strMain_AxisAlarmStop=9, //驱动器报警，系统停止
	strMain_NotOpenFileWork=10, //没有打开文件，不能加工!
	strMain_DocLmtErr_Val_Xmax=11,//文件Xmax大于机床Xmax
	strMain_DocLmtErr_Val_Xmin=12,//文件Xmin小于机床Xmin
	strMain_DocLmtErr_Val_Ymax=13,//文件Ymax大于机床Ymax
	strMain_DocLmtErr_Val_Ymin=14,//文件Ymin小于机床Ymin
	strMain_DocLmtErr_Val_XTravel=15,//文件超过X轴行程
	strMain_DocLmtErr_Val_YTravel=16,//文件超过Y轴行程
	strMain_DocLmtErr_Val_Work=17,  //文件可以加工
	strMain_WorkSucces=18,   //文件加工成功...
	strMain_GoHomeTipAll=19,//系统正在全部回零，请等待...
	strMain_GoHomeTipXY=20,//系统正在XY回零，请等待...
	strMain_GoHomeTipTZ=21,//系统正在TZ回零，请等待...
	strMain_GoHomeTipOrg=22,//系统正在回原点，请等待...
	strMain_GoLeftButtom=23, // 系统正在回左下角,请等待...
	strMain_GoLeftUp=24,   //系统正在回左上角,请等待...
	strMain_GoRightButtom=25, //系统正在回右下角，请等待...
	strMain_GoRightUp=26, //系统正在回右上角，请等待...
	strMain_GoZUp=27, //系统正在拉起Z轴，请等待...
	strMain_GoRZero=28, //系统正在T轴回零，请等待...
	strMain_CpuSendFile=29, //上位机正在发送文件....
	strMain_CpuSendFileSucces=30, //上位机发送文件成功.
	strMain_CpuSendFileFalse=31, //上位机发送文件失败
}MainFormStuShowStr;

void Reg_Read(unsigned short Address,unsigned short *Dat);
void Reg_Write(unsigned short Address,unsigned short Dat);
void Bit_Read(unsigned short Address,unsigned short *Dat);
void Bit_Write(unsigned short Address,unsigned short Dat);
void UpParamToModBuf(void);
void SetParamFormModBuf(void);
#define ModBufLen 65535 

extern unsigned short myModbusBuf[ModBufLen];
void InitZeroToModbusBuf(void);
extern unsigned char IsCurrTimeMaxPingTime;
extern unsigned char IsFirstCheckPingTime;

#endif



