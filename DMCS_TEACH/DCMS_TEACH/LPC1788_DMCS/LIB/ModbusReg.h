#ifndef _MODBUSREG_H_
#define _MODBUSREG_H_

unsigned char ModbusProcess(unsigned char Index,unsigned char *Bufadd,unsigned char BufLen);
void ModbusServe(unsigned char Index);
void ModeBusTest(void);
extern unsigned char Modbus_Address[2];
extern void (*ModbusReg_Read)(unsigned short Address,unsigned short *Dat);
extern void (*ModbusReg_Write)(unsigned short Address,unsigned short Dat);
extern void (*ModbusBit_Read)(unsigned short Address,unsigned short *Dat);
extern void (*ModbusBit_Write)(unsigned short Address,unsigned short Dat);
extern void (*ModbusReg2_Read)(unsigned short Address,unsigned short *Dat);
extern void (*ModbusReg2_Write)(unsigned short Address,unsigned short Dat);
extern void (*ModbusBit2_Read)(unsigned short Address,unsigned short *Dat);
extern void (*ModbusBit2_Write)(unsigned short Address,unsigned short Dat);

#endif
