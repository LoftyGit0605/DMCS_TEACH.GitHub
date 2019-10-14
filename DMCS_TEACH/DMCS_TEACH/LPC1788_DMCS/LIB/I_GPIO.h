#ifndef _IGPIO_H_
#define _IGPIO_H_

#define	Stat_LED_PortNum  18
#define	GPOUT_0_PortNum   17
#define	GPOUT_1_PortNum   16
#define	GPOUT_2_PortNum   19
#define	GPOUT_3_PortNum   20
#define LED_ON	ClearPort(Stat_LED_PortNum)  //LEDÁÁ
#define LED_OFF SetPort(Stat_LED_PortNum)    //LEDÃð

extern void I_GPIO_Init(void);
extern void SetPort(unsigned char Port);     //¹Ø±ÕLEDµÆ
extern void ClearPort(unsigned char Port);   //´ò¿ªLEDµÆ

#endif
