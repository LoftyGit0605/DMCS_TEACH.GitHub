unsigned char ReadDataFlash_String(unsigned char *data,unsigned char RomAddress,unsigned short  number);
unsigned char WhirteDataFlash_String(unsigned char *data,unsigned char RomAddress,unsigned short  number);
unsigned char ReadData24c02Flash_Bytes(unsigned char *data,unsigned char RomAddress,unsigned short  number);
unsigned char WhirteData24c02Flash_Bytes(unsigned char *data,unsigned char RomAddress,unsigned short  number);
unsigned char WhirteData24c02Flash_Byte(unsigned char data,unsigned char RomAddress);
unsigned char ReadData24c02Flash_Byte(unsigned char *data,unsigned char RomAddress);

unsigned char ReadData24c02Flash_Shorts(unsigned short *data,unsigned char address,unsigned char  number);
unsigned char WhirteData24c02Flash_Shorts(unsigned short *data,unsigned char address,unsigned char  number);
unsigned char ReadData24c02Flash_Longs( long *data,unsigned char address,unsigned char  number);
unsigned char WhirteData24c02Flash_Longs( long *data,unsigned char address,unsigned char  number);
unsigned char WhirteData24c02Flash_Long( long data,unsigned char address);
unsigned char ReadData24c02Flash_Long( long *data,unsigned char address);
unsigned char WhirteData24c02Flash_Short(unsigned short data,unsigned char address);
unsigned char ReadData24c02Flash_Short(unsigned short *data,unsigned char address);
unsigned char WhirteData24c02Flash_ULong(unsigned long data,unsigned char address);
unsigned char ReadData24c02Flash_ULong(unsigned long *data,unsigned char address);
unsigned char WhirteData24c02Flash_float(float data,unsigned char address);
unsigned char ReadData24c02Flash_float(float *data,unsigned char address);
