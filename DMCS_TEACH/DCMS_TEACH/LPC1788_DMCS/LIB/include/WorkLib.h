#include "GlobalDefine.h"

#ifndef WORKLIB_H_H_H
#define WORKLIB_H_H_H
#ifdef WORKLIB_H_H_H
#include "Parameter.h"








void SetAxisOrg_PC(sbyte Axis, float pos);
void SetAxisOrgAll_PC( float x,float y,float z,float r, float a);

void Init_Axis_Move_ReMain(void);
short StopMotion(void);
short PauseMotion(void);
float GetPos_Rel_Axis(sbyte axis);
float GetPos_Abs_Axis(sbyte axis);
int_ GetPosInt_Axis(sbyte axis);
short StopAxis(sbyte Axis);
short GetLmt(byte *Xv,byte *Yv,byte *Zv,byte *Rv,byte* Av);
float GetAxisOrg(sbyte Axis);
short SetAxisOrg(sbyte Axis, float pos);
float GetAxisPos_DBSG_X(sbyte AbsMode);
short GetPos_Rel(float *X,float *Y,float *Z,float *R,float *A);
short GetPos_Abs(float *X,float *Y,float *Z,float *R,float *A);
long DelayMs(uint_ ms);
long CheckMotionStu(sbyte Axis);
int_ GetGpOutIOStuSigle(sbyte pin ,bool* IoStu);
long SetOneIOAfterCheckInIO(sbyte pin, sbyte setIOVal,  int_ delActTime);
int32 AxisDBSiGanChangeUpDown(void);
int_ Abs_int(int_ val);
float Abs_double(float val);
float Abs_float(float val);
short AxisMove_Distance(unsigned char Axis,float Value,float Speed);
short AxisMove_AbsPos(unsigned char Axis,float Value,float Speed);
short AxisMove_RelPos(unsigned char Axis,float Value,float Speed);
int_ DBSGMoveSetLen_SpeedBegin_Acc(float SpeedS, float moveLen, int_ CPosX ,float speedMinS, float AccS);
short AxisMove_SpeedBegin_Acc(sbyte Axis,float Value,float Speed,sbyte PosMode,sbyte AbsMode,float SpeedBegin,float Acc);
short AxisMove_Distance_SpeedBegin_Acc(unsigned char Axis,float Value,float Speed,float SpeedBegin,float Acc);
short AxisMove_AbsPos_SpeedBegin_Acc(unsigned char Axis,float Value,float Speed,float SpeedBegin,float Acc);
short AxisMove_RelPos_SpeedBegin_Acc(unsigned char Axis,float Value,float Speed,float SpeedBegin,float Acc);
int_  CloseAllIO(void);
void WorkRunFile(void);
void GoHome_X(void);
void GoHome_Y(void);
void GoHome_Z(void);
void GoHome_R(void);
void GoHome_A(void);
extern bool isHomeFirstMoveDBSG;
extern byte nCurrDBSiGangDC;
long Work_FCmd_CheckDaoWei(void);
long CheckFourIOStu(byte* val);
long SetOneGpOut(sbyte pin, sbyte val, long activeTime);
long SetTwoGpOut(sbyte pin1, sbyte val1,sbyte pin2, sbyte val2,  long activeTime);
long MoveBendModeCCW_CW(long PosMove,long CurrPos,float Speed, float SpeedMin, float Acc);
long AxisXMoveCheckDaoWei(byte Axis, long PosMove, unsigned long SpeedMin,unsigned long Acc,unsigned long Speed);
long FCmd_CheckDaoWei_Axis(sbyte Axis);








#endif
#endif



