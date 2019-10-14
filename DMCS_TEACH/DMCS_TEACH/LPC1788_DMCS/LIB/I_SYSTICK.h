#ifndef _ISYSTICK_H_
#define _ISYSTICK_H_

#include <stdint.h>
#include "lpc177x_8x_systick.h"

typedef int(*IRQCallBackFun)(); 
extern volatile uint32_t LWIP_TIME;
extern volatile unsigned long NowTime;   //ÿ��1��ʱ1ms
void I_SYSTICK_Init(void);               //��HW_Init�Ѿ�����
int regIRQ(IRQCallBackFun cb);

#endif
