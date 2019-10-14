#include "stdint.h"


#define BUFSIZE		0x40


unsigned long HardWare_UARTInit(  uint32_t Baudrate );
void HardWare_UARTSend(unsigned char  *BufferPtr, unsigned long Length );
unsigned char HardWare_GetData(void);
unsigned char HardWare_GetState(void);

unsigned long HardWare_UART2Init(  uint32_t Baudrate );

void HardWare_UART2Send(unsigned char  *BufferPtr, unsigned long Length );
unsigned char HardWare_Get2Data(void);
unsigned char HardWare_Get2State(void);











