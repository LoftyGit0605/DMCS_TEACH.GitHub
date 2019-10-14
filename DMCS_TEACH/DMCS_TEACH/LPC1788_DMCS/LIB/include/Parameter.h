#ifndef PARAMETER_H_H_H
#define PARAMETER_H_H_H
#ifdef PARAMETER_H_H_H
#include "GlobalDefine.h"

#pragma pack(1)





struct Parameter
{

    float Mm_To_Pulse[6];		//脉冲转换系数 //第1个为X轴的下丝杆，第6个为X轴上丝杆
    float Pulse_To_Mm[6];		//脉冲转换系数倒数 //第1个为X轴的下丝杆，第6个为X轴上丝杆
    float TableSize[6];  //各个轴的行程  //第1个为X轴的下丝杆，第6个为X轴上丝杆
    float SpeedMax[5];  //各个轴的最大移动速度
    float SoftLmtPos[5];  //各个轴的正向最大行程
    float SoftLmtNeg[5]; //各个轴的负向最大行程

    float SpeedMin[5];
    float SpeedAcc[5];
    float SpeedHome[5];
    float DBSGSpeedBack;
    float posOrgX;
    float posOrgY;
    float posOrgZ;
    float posOrgRNeg;
    float posOrgRPos;
    float posOrgA;
    uint32 TableSizePluse;
    uint32 delActSiGanDownClose; //下丝杆关闭动作时间
    uint32 delActSiGanDownOpen; //下丝杆打开动作时间
    uint32 delActSiGanUpClose;  //上丝杆关闭动作时间
    uint32 delActSiGanUpOpen;  //上丝杆打开动作时间
    uint32 delHaveMaterTimeOut;
    uint32 delBendActTime;  //折弯IO动作时间
    uint32 delBendTimeOut;	//折弯IO检测超时时间
    uint32 delDaoWeiX;
    uint32 delDaoWeiR;
    uint32 delDaoWeiA;

    sbyte AxisMaterMode;  //0:普通模式;  1: 双丝杆
    sbyte AxisBendMode;  // 0:普通模式   1:插杆选择
    sbyte HomeDir[5];   //0: + ;;  1: -
    sbyte IOIn_BendCCWOff;
    sbyte IOIn_BendCCWOn;
    sbyte IOIn_BendCWOff;
    sbyte IOIn_BendCWOn;
    sbyte IOOut_DBSGUpOpen;  //  
    sbyte IOOut_DBSGUpClose;  //
    sbyte IOOut_DBSGDownOpen;  //
    sbyte IOOut_DBSGDownClose;  //
    sbyte IOOut_BendCCWOn;
    sbyte IOOut_BendCWOn;

};



extern sbyte IOIn_AlarmX ;   //+
extern sbyte IOIn_AlarmY ;	//-
extern sbyte IOIn_AlarmZ;  //-
extern sbyte IOIn_AlarmR; //+
extern sbyte IOIn_AlarmA; //+
extern sbyte IOIn_AlarmEMC; //+
extern sbyte IOIn_AlarmKaLiao; //+
extern sbyte IOIn_AlarmQiaoWei;//+
extern sbyte IOIn_SawB_SpeedTimeOut; //-
extern sbyte IOIn_SawBAlarm;//+
extern sbyte IOIn_HaveMater; //- :wu
extern sbyte IOIn_DaoWeiX;  //-
extern sbyte IOIn_DaoWeiR; //-
extern sbyte IOIn_DaoWeiA;  //-
extern sbyte IOIn_LmtXPos;  //-
extern sbyte IOIn_LmtXNeg;  //-
extern sbyte IOIn_LmtYPos;  //-
extern sbyte IOIn_LmtYNeg;  //-
extern sbyte IOIn_LmtZPos;  //-
extern sbyte IOIn_LmtZNeg;  //-
extern sbyte IOIn_LmtRPos;  //-
extern sbyte IOIn_LmtRNeg;  //-
extern sbyte IOIn_LmtAPos;  //-
extern sbyte IOIn_LmtANeg;   //-
extern sbyte IOIn_LmtYPos;
extern sbyte IOIn_LmtXPos_Val;  //-
extern sbyte IOIn_LmtXNeg_Val;  //-
extern sbyte IOIn_LmtYPos_Val;  //-
extern sbyte IOIn_LmtYNeg_Val;  //-
extern sbyte IOIn_LmtZPos_Val;  //-
extern sbyte IOIn_LmtZNeg_Val;  
extern sbyte IOIn_LmtRPos_Val;  //-
extern sbyte IOIn_LmtRNeg_Val;  //-
extern sbyte IOIn_LmtAPos_Val;  //-
extern sbyte IOIn_LmtANeg_Val;   //-

extern struct Parameter McuSetting;

void Init_Parameter(void);
void Save_Parameter(void);	
void CalcuMmToPulse(void);

extern sbyte GpIO_OutStu[16];
extern sbyte GpIO_InStu[28];


extern float Pulse_To_Mm_X[2];
extern float Mm_To_Pulse_X[2];
extern float OrgPos[5];

extern uint32 WorkIndex;
extern byte preCutHeadDownMode;
extern byte preCutTailDownMode;

extern bool IsCheckEMCIO ;
extern bool IsCheckKaLiao;
extern bool IsCheckAlarmX;
extern bool IsCheckAlarmY;
extern bool IsCheckAlarmZ;
extern bool IsCheckAlarmR;
extern bool IsCheckAlarmA;
extern bool IsCheckAlarmSawB;
extern bool IsCheckAlarmQaiWei;
extern bool IsCheckAxisLmtPosX;
extern bool IsCheckAxisLmtPosZ;
extern bool IsCheckAxisLmtPosR;
extern bool IsCheckAxisLmtPosA;
extern bool IsCheckAxisLmtNegX;
extern bool IsCheckAxisLmtNegY;
extern bool IsCheckAxisLmtNegZ;
extern bool IsCheckAxisLmtNegR;
extern bool IsCheckAxisLmtNegA;


extern bool IsWorkRunFile;
extern bool IsPauseReStart;
extern bool IsCheckIsHaveMater;

extern bool AlarmAxisX ;
extern bool AlarmAxisY ;
extern bool AlarmAxisZ ;
extern bool AlarmAxisA;
extern bool AlarmAxisR ;
extern bool AlarmSaw ;
extern bool AlarmQiaoWei ;
extern bool AlarmKaLiao ;
extern bool AlarmEMCStop ;
extern bool AlarmAxisLmtPosX;
extern bool AlarmAxisLmtNegX;
extern bool AlarmAxisLmtNegY;
extern bool AlarmAxisLmtPosZ;
extern bool AlarmAxisLmtNegZ;
extern bool AlarmAxisLmtPosR;
extern bool AlarmAxisLmtNegR;
extern bool AlarmAxisLmtPosA;
extern bool AlarmAxisLmtNegA;
extern bool IsHaveAlarm ;



extern bool SuccHomeX ;  //X轴是否回零成功
extern bool SuccHomeY ;  //Y轴是否回零成功
extern bool SuccHomeZ ;  //Z轴是否回零成功
extern bool SuccHomeR;  //R轴是否回零成功
extern bool SuccHomeA ;  //A轴是否回零成功

extern bool isDBSGUpCloseIOOn;
extern bool isDBSGDownCloseIOOn;

extern long mCWInfo;
extern long mCurrCMDEndStu;
extern long mCurrAlarmCheStu ;

extern byte mFCmdCheckIOPin ;
extern bool mFCmdCheckIOVal ;
extern byte mFCmdCheckIOChuli ;

extern bool IsHaveAlarm;  //系统是否已经有警告状态，有了就不在检测，必须等到PC下发清除后重新检测
extern bool IsStartTask;
extern byte TaskType ;
extern byte McStopB ;
extern byte McPauseB ;

void GetPC_LinkData(void);
long CheckIOAlarm(void);
void Doevents(unsigned short T);


extern sbyte Auto_Busy;
//extern sbyte EMCStopIOStu;
//extern WORKSTA WorkSta;			//运行状态
extern sbyte WorkStatus;		//加工状态

extern struct FCmdFileHeadStruct currFCmdHead;
extern struct FCmdData_SDRAM datFCmd;

extern sbyte MainDisMoveAxis;
extern float MainDisMovePos;
extern float MainDisMoveSpeed;
extern float MainDisMoveSpeedMin;
extern float MainDisMoveSpeedAcc;
extern byte StopFCmdFile;



extern sbyte isPCGetErrInfo;

extern unsigned long preWritedatIndex;
extern unsigned char IsCurrLinkFile;  //是否在网络传递文件
extern uint32 FCmdFileLen ;
extern uint32 FCmdFileIndexWrite;

void SetLmtMode_Default(void);

extern bool IsStopBtnClick ;
extern bool IsPauseBtnClick;
extern sbyte IsCheckSuccessHome;

extern unsigned char GPOUT0Stu;
extern unsigned char GPOUT1Stu;
extern unsigned char GPOUT2Stu;
extern unsigned char GPOUT3Stu;
extern sbyte IsCheckSoftLmt;
extern bool IsUpdateProgram;
#endif
#endif


