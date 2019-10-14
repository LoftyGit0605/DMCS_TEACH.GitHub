#include <stdint.h>
#include "lpc177x_8x_systick.h"

typedef int(*IRQCallBackFun)(); // 
extern volatile uint32_t LWIP_TIME;
extern volatile unsigned long NowTime ;
void I_SYSTICK_Init(void);
int regIRQ(IRQCallBackFun cb);
