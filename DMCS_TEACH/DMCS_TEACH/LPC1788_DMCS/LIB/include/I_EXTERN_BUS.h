#include "CpuPlatForm.h"
#if   LPC2478
#include "LPC24xx.h"
#endif
#if   LPC1788
#include "lpc177x_8x_emc.h"
#include "lpc177x_8x_clkpwr.h"
#include "lpc177x_8x_pinsel.h"
#include "LPC177x_8x.h"
#endif



void driver_SDKW_Cmd(unsigned char Cmd);
unsigned char driver_SDKR_Stu(void)	;
void driver_SDKW_Fifo(unsigned char Data);
unsigned char driver_SDKR_Fifo(void);
unsigned char driver_GetSdkTxf(void);
unsigned char driver_GetSdkRxe(void);
void driver_SetSdkMsg(void);
void driver_SetSdkAck(void);
void driver_SetSdkRst(void);
unsigned char driver_GetSdkMsg(void);

//void HardWare_Init_SDKBus(void);
void I_EXTERN_BUS_Init(void);
