#ifndef _USERFUNC_H_
#define _USERFUNC_H_

#include "Base.h"

void InitSysParam(void);
void InitSysParamTemp(void);
void DispPowerOnTime(void);
long GetMacPosPulse(uint8_t Axis);
int8_t G00RelPosNoEnd(uint8_t Axis,float Inch,long Start,long Acc,long Speed);
void ParamSave(void);
void ParamLoad(void);
int8_t AxisRunToZero(uint8_t Axis1,uint8_t Axis2);
void DispWorkMakeTime(void);
void UserValueCrcCheck(void);
void RatePlusMinus(void);
void FastManualSpeed(void);
void TeachTableCursorInit(void);
void TeachTableCursorInfo(void);
void TeachTableRate(void);
void CurrentCommandInfo(void);
void GetTeachTableIOInfo(void);
void TeachPageButtonInfo(void);
void TeachTableParam(void);
int8_t G00Func(struct _FUNCPARAM param);
int8_t G01Func(struct _FUNCPARAM param);
void OutputFunc(struct _FUNCPARAM param);
int8_t InputFunc(struct _FUNCPARAM param);
int8_t DelayFunc(struct _FUNCPARAM param);
int8_t ArcFunc(struct _FUNCPARAM param);
int8_t UserFunc(struct _FUNCPARAM param);
int8_t TeachParamExecute(void);

#endif
