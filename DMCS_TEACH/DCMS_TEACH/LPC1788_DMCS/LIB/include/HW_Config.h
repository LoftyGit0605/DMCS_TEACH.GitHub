/*********************************************************************************
*    This the default HardWare Config
*    IF YOU  WANT  TO  CHANGE THE DEFAULT CONFIG 
*    PLEASE GO TO THE HW_User_Config.h"
*    @COMPANY:
*    @DATE   :						2016-3-31
*    @AUTHOR :						MR.M
*    @REV		 :            DATE                   Description                                          				AUTHOR
*                         2016-3-31          完成当前版本的硬件配置宏定义                                     Mr.M
*                          ?                         ?                                                         ?
*
*/
#include "HW_User_Config.h"





/**********************************************************
*THIS IS THE NETWORK CONFIG 
* @IPADDRESS
* @GATEWAY
* @NETMASK
**********************************************************/
#ifndef  Ip_1
#define  Ip_1               (192)
#endif 
/*******************************************************/
#ifndef  Ip_2
#define  Ip_2       				(168)
#endif
/*******************************************************/
#ifndef  Ip_3
#define  Ip_3       				(0)
#endif
/*******************************************************/
#ifndef  Ip_4
#define  Ip_4       				(100)
#endif
/*******************************************************/
#ifndef  GateWay_1
#define  GateWay_1  				(192)
#endif
/*******************************************************/
#ifndef  GateWay_2
#define  GateWay_2  				(168)
#endif
/*******************************************************/
#ifndef  GateWay_3
#define  GateWay_3  				(0)
#endif
/*******************************************************/
#ifndef  GateWay_4
#define  GateWay_4  				(1)
#endif
/*******************************************************/
#ifndef  NetMask_1
#define  NetMask_1 					(255)
#endif
/*******************************************************/
#ifndef  NetMask_2
#define  NetMask_2					(255)
#endif
/*******************************************************/
#ifndef  NetMask_3
#define  NetMask_3					(255)
#endif
/*******************************************************/
#ifndef  NetMask_4
#define  NetMask_4					(0)
#endif
/**********************************************************
*  THIS IS THE SYSTICK CONFIG
*  @SYSTICK     MS
*/ 
#ifndef  SYS_TICK_MS
#define  SYS_TICK_MS         (5) ////
#endif
/**********************************************************
*  CORE TIMER CONFIG
* @TIMER_TIME_MS    MS
*/
//#ifndef  TIMER_TIME_MS
//#define  TIMER_TIME_MS       (0)
//#endif
/**********************************************************
*  UART CONFIG
*  @UART0
*  @UART2
*  1: @TurnOn
*  0: @TurnOff
*/
#ifndef  H_UART0
#define  H_UART0               1
#endif
/*****************************************************************/
#ifndef  H_UART2
#define  H_UART2               0
#endif
/**********************************************************
*   UART BAUDRATE CONFIG
*/
#ifndef  UART0BaudRate
#define  UART0BaudRate         38400
#endif
#ifndef  UART2BaudRate
#define  UART2BaudRate         115200
#endif
/*****************************************************************
*  NET CONFIG
*  1: @TurnOn
*  0: @TurnOff
*/
#ifndef  H_NET
#define  H_NET                 1
#endif
/*******************************************************************
*  EEPROM CONFIG
*  1: @TurnOn
*  0: @TurnOff
*/
#ifndef  H_EEPROM
#define  H_EEPROM               1
#endif
/*******************************************************************
*  SDRAM CONFIG
*  1: @TurnOn
*  0: @TurnOff
*/
#ifndef H_SDRAM
#define H_SDRAM                 1
#endif
/*********************************************************************
*   TCP CONFIG
*   1: @TurnOn
*   0: @TurnOff
*/
#ifndef  H_TCP
#define  H_TCP                   0
#endif
/*********************************************************************
*   UDP CONFIG
*   1: @TurnOn
*   0: @TurnOff
*/
#ifndef  H_UDP
#define  H_UDP                   1
#endif
/*********************************************************************
*   EXTERN BUS CONFIG
*   1: @TurnOn
*   0: @TurnOff
*/
#ifndef   H_EXTERN_BUS
#define   H_EXTERN_BUS           1
#endif 
/*********************************************************************
*   SPI  CONFIG
*   1: @TurnOn
*   0: @TurnOff
*/
#ifndef   H_SPI_0
#define   H_SPI_0                0
#endif
/*********************************************************************/
#ifndef   H_SPI_1
#define   H_SPI_1                0
#endif
/*********************************************************************/
#ifndef   H_SPI_2
#define   H_SPI_2                0
#endif
/**********************************************************
*  FILE SYSTEM CONFIG
*  1: @Turn ON
*  0: @Turn OFF
*  H_FS_SDCARD   Mount the file-system on SDCARD
*  H_FS_USBDisk  Mount the file-system on USBDisk
*/
#ifndef   H_FS_SDCARD
#define   H_FS_SDCARD              1
#endif
/*************************************************************************/
#ifndef   H_FS_USBDisk
#define   H_FS_USBDisk             1
#endif













