#ifndef MB85RC16_H_H_H
#define MB85RC16_H_H_H
#include <stdint.h>


typedef  enum
{
		EEPROM_EER,     //  EEPROM W/R FAILED
	EEPROM_OK    //  EEPROM W/R SUCCESSFULL

}EEPROM_FLAG;
EEPROM_FLAG  EEProm_WR(uint8_t TXData[],uint16_t addr,uint32_t tx_length);
EEPROM_FLAG  EEProm_RD(uint8_t RXData[],uint16_t addr,uint32_t rx_length);
void EEProm_init(void);


unsigned char ReadDataFlash_String(unsigned char *data,unsigned short RomAddress,unsigned short  count);
unsigned char WhirteDataFlash_String(unsigned char *data,unsigned short RomAddress,unsigned short  count);
unsigned char ReadData24c02Flash_Bytes(unsigned char *data,unsigned short RomAddress,unsigned short  count);
unsigned char WhirteData24c02Flash_Bytes(unsigned char *data,unsigned short RomAddress,unsigned short  count);
unsigned char WhirteData24c02Flash_Byte(unsigned char data,unsigned short RomAddress);
unsigned char ReadData24c02Flash_Byte(unsigned char *data,unsigned short RomAddress);

unsigned char ReadData24c02Flash_Shorts(unsigned short *data,unsigned short address,unsigned short  count);
unsigned char WhirteData24c02Flash_Shorts(unsigned short *data,unsigned short address,unsigned short  count);
unsigned char ReadData24c02Flash_Longs( long *data,unsigned short address,unsigned short  count);
unsigned char WhirteData24c02Flash_Longs( long *data,unsigned short address,unsigned short  count);
unsigned char WhirteData24c02Flash_floats(float* data,unsigned short address,unsigned short  count);
unsigned char ReadData24c02Flash_floats(float *data,unsigned short address,unsigned short  count);

unsigned char WhirteData24c02Flash_Long( long data,unsigned short address);
unsigned char ReadData24c02Flash_Long( long *data,unsigned short address);
unsigned char WhirteData24c02Flash_Short(unsigned short data,unsigned short address);
unsigned char ReadData24c02Flash_Short(unsigned short *data,unsigned short address);
unsigned char WhirteData24c02Flash_ULong(unsigned long data,unsigned short address);
unsigned char ReadData24c02Flash_ULong(unsigned long *data,unsigned short address);
unsigned char WhirteData24c02Flash_float(float data,unsigned short address);
unsigned char ReadData24c02Flash_float(float *data,unsigned short address);
#endif




