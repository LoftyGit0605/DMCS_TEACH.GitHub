#include "ff.h"

#include <absacc.h>

#define oem2uni_Size	0x15484
#define uni2oem_Size	0x15484
#define HZ_Size			0x40000

//struct SDRAM_Dat
//{
//	unsigned char Sdk_DatT[2048];
//	unsigned char Sdk_DatR[2048];
//};
//extern struct SDRAM_Dat SrDat;

short GetHZData(unsigned long Start,unsigned short Len, unsigned char *Buf);
unsigned short Get_UniOem_Data(unsigned long Index,unsigned char Dir);
