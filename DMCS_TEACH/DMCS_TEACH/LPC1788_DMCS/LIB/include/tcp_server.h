#ifndef  __TCP_SERVER_H
#define  __TCP_SERVER_H
#include "GlobalDefine.h"
#ifdef PC_Link_TCPIP


void Init_TCP_Server(void);

#define LWIP_CONNECTED  0X80 //���ӳɹ�
#define LWIP_NEW_DATA   0x40 //���µ�����
#define LWIP_SEND_DATA  0x20 //��������Ҫ����
#define LWIP_DEMO_BUF        254
#define Flash_program_ok  0x01
#define LWIP_TCP_SERVER 0x80  //tcp ����������
#define LWIP_TCP_CLIENT 0x40	//tcp �ͻ��˹���
#define LWIP_UDP_SERVER 0x20  //UDP ����������
#define LWIP_UDP_CLIENT 0x10  //UDP �ͻ��˹���
#define LWIP_WEBSERVER  0x08  //UDP �ͻ��˹���


#define LWIP_DEMO_DEBUG 1  //�Ƿ��ӡ������Ϣ   

#endif

#endif
