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

void HardWare_Init_SDKBus(void);
