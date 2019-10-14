
#include <stdint.h>

#include "lpc177x_8x_i2c.h"
#include "lpc177x_8x_clkpwr.h"
#include "lpc177x_8x_pinsel.h"


typedef  enum
{
	EEPROM_OK ,    //  EEPROM W/R SUCCESSFULL
	EEPROM_EER     //  EEPROM W/R FAILED
}EEPROM_FLAG;
void I_EEPROM_Init(void);
EEPROM_FLAG ReadDataFlash_String(unsigned char *data,unsigned short RomAddress,unsigned short  count);
EEPROM_FLAG WhirteDataFlash_String(unsigned char *data,unsigned short RomAddress,unsigned short  count);
EEPROM_FLAG ReadData24c02Flash_Bytes(unsigned char *data,unsigned short RomAddress,unsigned short  count);
EEPROM_FLAG WhirteData24c02Flash_Bytes(unsigned char *data,unsigned short RomAddress,unsigned short  count);
EEPROM_FLAG WhirteData24c02Flash_Byte(unsigned char data,unsigned short RomAddress);
EEPROM_FLAG ReadData24c02Flash_Byte(unsigned char *data,unsigned short RomAddress);

EEPROM_FLAG ReadData24c02Flash_Shorts(unsigned short *data,unsigned short address,unsigned short  count);
EEPROM_FLAG WhirteData24c02Flash_Shorts(unsigned short *data,unsigned short address,unsigned short  count);
EEPROM_FLAG ReadData24c02Flash_Longs( long *data,unsigned short address,unsigned short  count);
EEPROM_FLAG WhirteData24c02Flash_Longs( long *data,unsigned short address,unsigned short  count);
EEPROM_FLAG WhirteData24c02Flash_floats(float* data,unsigned short address,unsigned short  count);
EEPROM_FLAG ReadData24c02Flash_floats(float *data,unsigned short address,unsigned short  count);

EEPROM_FLAG WhirteData24c02Flash_Long( long data,unsigned short address);
EEPROM_FLAG ReadData24c02Flash_Long( long *data,unsigned short address);
EEPROM_FLAG WhirteData24c02Flash_Short(unsigned short data,unsigned short address);
EEPROM_FLAG ReadData24c02Flash_Short(unsigned short *data,unsigned short address);
EEPROM_FLAG WhirteData24c02Flash_ULong(unsigned long data,unsigned short address);
EEPROM_FLAG ReadData24c02Flash_ULong(unsigned long *data,unsigned short address);
EEPROM_FLAG WhirteData24c02Flash_float(float data,unsigned short address);
EEPROM_FLAG ReadData24c02Flash_float(float *data,unsigned short address);



