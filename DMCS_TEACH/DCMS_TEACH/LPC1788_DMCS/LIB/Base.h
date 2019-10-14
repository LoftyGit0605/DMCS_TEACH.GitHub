#ifndef _BASE_H_
#define _BASE_H_

#include <stdio.h>
#include <stdint.h>
#include <absacc.h>
#include <string.h>
#include "system_LPC177x_8x.h"
#include "GlobalDefine.h"
#include "UpgradeStm32.h"
#include "Motion.h"
#ifdef PC_Link_TCPIP
#include "tcp_server.h"
#include "Link_PC.h"
#endif
#ifdef PC_Link_UDP
#include "PC_Link_UDP.h" 
#include "udp_server.h"
#endif
#include "LPC177x_8x.h"
#include "ModbusReg.h"
#include "MyModbus.h"
#include "HW_Init.h"
#include "I_SYSTICK.h"
#include "I_Timer.h"
#include "I_USB.h"
#include "Crc.h"
#include "I_GPIO.h"
#include "I_Uart.h"
#include "ff.h"
#include "Public.h"
#include "UserCrc.h"
#include "UserFunc.h"

#endif
