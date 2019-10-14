#ifndef _ITIMER_H_
#define _ITIMER_H_

/*****************************************************************************
 *   I_Uart.h:  定时器接口头文件
 *	 定时器函数接口
 *   Copyright(C) 2006, NXP Semiconductor
 *   All rights reserved.
 *
 *   
 *   
 *
******************************************************************************/

//#define  TIMER_TIME_MS       (10)  //定时器每次中断计数间隔时间，单位毫秒

void I_Timer_Init(unsigned long TIMER_TIME_MS);  //定时初始化

#endif
