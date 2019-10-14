#ifndef _ISYSTICK_H_
#define _ISYSTICK_H_

#include <stdint.h>
#include "lpc177x_8x_systick.h"

typedef int(*IRQCallBackFun)(); 
extern volatile uint32_t LWIP_TIME;
extern volatile unsigned long NowTime;   //每加1延时1ms
void I_SYSTICK_Init(void);               //在HW_Init已经调用
int regIRQ(IRQCallBackFun cb);

#endif
