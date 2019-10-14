#include <stdint.h>
#include "LPC177x_8x.h"
#include "lpc177x_8x_emac.h"
#include "lpc177x_8x_pinsel.h"
#include "lpc177x_8x_clkpwr.h"
#include "phylan.h"

#define MYMAC_1         0x1E            /* our ethernet (MAC) address        */
#define MYMAC_2         0x30            /* (MUST be unique in LAN!)          */
#define MYMAC_3         0x6c
#define MYMAC_4         0xa2
#define MYMAC_5         0x45
#define MYMAC_6         0x5e

void 			I_ENET_Init(void);
void 			I_ENETClearCount(void);
void  		I_ENETSendData(void *Source, uint32_t Size);
char  		I_ENETReadyRead(void);
uint8_t * I_ENetGetReadbuff(void);
uint32_t  I_ENETGetReadLength(void);




