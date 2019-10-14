#ifndef _I_UART_H_
#define _I_UART_H_
/*****************************************************************************
 *   I_Uart.h:  串口接口头文件
 *	 两个串口接口
 *   Copyright(C) 2006, NXP Semiconductor
 *   All rights reserved.
 *
 *   
 *   
 *
******************************************************************************/
#define BUFSIZE		0x40   //串口接收数据缓冲数组大小

volatile extern unsigned char UART0Buffer[BUFSIZE];
volatile extern unsigned long UART0Count ;
volatile extern unsigned char UART2Buffer[BUFSIZE];
volatile extern unsigned long UART2Count ;
//串口1操作函数接口

//串口1初始化,Baudrate为波特率
unsigned long HardWare_UARTInit(  unsigned long Baudrate );

//串口1发送函数
void HardWare_UARTSend(unsigned char  *BufferPtr, unsigned long Length );

unsigned char HardWare_GetData(void);
unsigned char HardWare_GetState(void);


//串口2操作函数接口

//串口2发送函数,Baudrate为波特率
unsigned long HardWare_UART2Init(  unsigned long Baudrate );

//串口2发送函数
void HardWare_UART2Send(unsigned char  *BufferPtr, unsigned long Length );

unsigned char HardWare_Get2Data(void);
unsigned char HardWare_Get2State(void);

#endif
