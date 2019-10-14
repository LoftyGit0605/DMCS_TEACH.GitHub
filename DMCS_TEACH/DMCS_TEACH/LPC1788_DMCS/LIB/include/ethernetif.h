#ifndef __ETHERNETIF_H
#define __ETHERNETIF_H	 


#include "lwip/opt.h"
#include "lwip/netif.h"
#include <lwip/stats.h>
#include "err.h"
#include "lpc_types.h"
#define MYMAC_1         0x1E            /* our ethernet (MAC) address        */
#define MYMAC_2         0x30            /* (MUST be unique in LAN!)          */
#define MYMAC_3         0x6c
#define MYMAC_4         0xa2
#define MYMAC_5         0x45
#define MYMAC_6         0x5e


//void ethernetif_input(struct netif *netif);
err_t ethernetif_init(struct netif *netif);
void  ethernetif_input(struct netif *netif,uint8_t * p_rx_packet,
                 uint32_t pckt_length);
// prototypes
//void           Init_EMAC(void);
//uint16_t       ReadHalfWordBE_EMAC(void);
//void           CopyToFrame_EMAC(void *Source, unsigned int Size);
//void           CopyFromFrame_EMAC(void *Dest, uint16_t Size);
//void           DummyReadFrame_EMAC(uint16_t Size);
//void           ReadFrame_EMAC(void *Dest, uint16_t Size);
//uint16_t       StartReadFrame(void);
//void           EndReadFrame(void);
//unsigned int   CheckFrameReceived(void);
//unsigned int   Rdy4Tx(void);
//void           SendFrame(void *Source, unsigned int Size);
//void           FrameReceiveCallback(uint16_t* pData, uint32_t size);
//void           ErrorReceiveCallback(int32_t errCode);
#endif

