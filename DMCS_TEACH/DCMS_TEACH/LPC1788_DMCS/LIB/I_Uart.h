#ifndef _I_UART_H_
#define _I_UART_H_
/*****************************************************************************
 *   I_Uart.h:  ���ڽӿ�ͷ�ļ�
 *	 �������ڽӿ�
 *   Copyright(C) 2006, NXP Semiconductor
 *   All rights reserved.
 *
 *   
 *   
 *
******************************************************************************/
#define BUFSIZE		0x40   //���ڽ������ݻ��������С

volatile extern unsigned char UART0Buffer[BUFSIZE];
volatile extern unsigned long UART0Count ;
volatile extern unsigned char UART2Buffer[BUFSIZE];
volatile extern unsigned long UART2Count ;
//����1���������ӿ�

//����1��ʼ��,BaudrateΪ������
unsigned long HardWare_UARTInit(  unsigned long Baudrate );

//����1���ͺ���
void HardWare_UARTSend(unsigned char  *BufferPtr, unsigned long Length );

unsigned char HardWare_GetData(void);
unsigned char HardWare_GetState(void);


//����2���������ӿ�

//����2���ͺ���,BaudrateΪ������
unsigned long HardWare_UART2Init(  unsigned long Baudrate );

//����2���ͺ���
void HardWare_UART2Send(unsigned char  *BufferPtr, unsigned long Length );

unsigned char HardWare_Get2Data(void);
unsigned char HardWare_Get2State(void);

#endif
