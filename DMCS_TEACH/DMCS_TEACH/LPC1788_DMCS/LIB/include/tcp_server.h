#ifndef  __TCP_SERVER_H
#define  __TCP_SERVER_H
#include "GlobalDefine.h"
#ifdef PC_Link_TCPIP


void Init_TCP_Server(void);

#define LWIP_CONNECTED  0X80 //连接成功
#define LWIP_NEW_DATA   0x40 //有新的数据
#define LWIP_SEND_DATA  0x20 //有数据需要发送
#define LWIP_DEMO_BUF        254
#define Flash_program_ok  0x01
#define LWIP_TCP_SERVER 0x80  //tcp 服务器功能
#define LWIP_TCP_CLIENT 0x40	//tcp 客户端功能
#define LWIP_UDP_SERVER 0x20  //UDP 服务器功能
#define LWIP_UDP_CLIENT 0x10  //UDP 客户端功能
#define LWIP_WEBSERVER  0x08  //UDP 客户端功能


#define LWIP_DEMO_DEBUG 1  //是否打印调试信息   

#endif

#endif
