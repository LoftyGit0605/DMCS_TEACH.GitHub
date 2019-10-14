#include "Base.h"

extern uint16_t DReg[];
/****************************************************************************************
Function :	get puchBuffer CRC-check value
Parameter:  puchBuffer   :the message for getting CRC-check value
            usDataLen    :length of the message with getting CRC-check value
Return   :
****************************************************************************************/
//unsigned short UserCRC16(unsigned char *puchMsg,unsigned short usDataLen)
uint16_t UserCRC16(uint8_t *puchMsg,uint16_t usDataLen)
{
//	unsigned char uchCRCHi = 0xFF;     // init high-8bit of CRC
//	unsigned char uchCRCLo = 0xFF;     // init low-8bit of CRC
//	unsigned short i,uIndex;
	uint8_t  uchCRCHi = 0xFF;     // init high-8bit of CRC
	uint8_t  uchCRCLo = 0xFF;     // init low-8bit of CRC
	uint16_t i,uIndex;
	
	while(usDataLen--)
	{
		if((usDataLen % 20) == 0)ModbusServe(0); // forbid communication unlink
		if(DReg[F_STOPBTN] == 1)
		{
			DReg[F_STOPBTN] = 0;
			for(i=0;i<16;i++)WriteOutput(i,0);
			for(i=0;i<5;i++)SAxisDec_stop(i+1);
		}
		uIndex = uchCRCLo ^ *puchMsg++; // get CRC-check value
		uchCRCLo = uchCRCHi ^ auchCRCHi[uIndex];
		uchCRCHi = auchCRCLo[uIndex];
	}
	return ((uchCRCHi << 8) | uchCRCLo);
}

