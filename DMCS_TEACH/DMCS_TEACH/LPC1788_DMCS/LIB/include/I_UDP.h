//#ifndef __UDP_SERVER_H
//#define __UDP_SERVER_H
//#include "GlobalDefine.h"

struct Myip_addr {
  unsigned long addr;
};
typedef struct Myip_addr ip_addr_tt;
typedef int(*CallBackFun)(ip_addr_tt*, unsigned short, char*,unsigned short*); // 
int regCB(CallBackFun cb);  //??????

void Init_UDP_Server(void);//初始化UDP服务器
//void* mymemcpy(void* dest, void* source, size_t count);

//void UDP_TX_DATA(struct udp_pcb* upcb,unsigned char* data_buff,uint16_t data_len);
void Net_sendto(ip_addr_tt addr,unsigned short port, char * buf,unsigned long Lenth);
extern char Link_PC_ReBuf[1000];

//#endif


