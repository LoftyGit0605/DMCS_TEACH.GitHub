/****************************************************************************
*                           Machine-hand Project 
*
* File:
*   Main.c
*
* Description:
*   This is machine-hand project of the fish-float project. 
*             
* Author:
*   Lofty
*
****************************************************************************/
#include "Base.h"

#define	APP_ADDR	0x00010000UL
#define	BOOT_ADDR	0x00000000UL

//// using to update for STM32
//int SDUpgradeStm32(void);
//int USBUpgradeStm32(void);
extern void RatePlusMinus(void);
extern void TeachTableParam(void);
//extern void TeachParamExecute(void);
extern void TeachParamExecuteA(void);
extern void TeachParamExecuteB(void);
extern void UserValueCrcCheck(void);
extern void FastManualSpeed(void);
extern void ReadWorkParam(void);
extern int8_t ServoAlarmCheck(void);
typedef	void (*pFunction)(void);
uint16_t DReg[20000] __at(0xa0100000);        // mobuds register
struct LayoutCmd_PC Line[5000] __at(SDRAM_BASE_USER+0x200000); // using for interpolation
void AppJumpToBoot(void)
{
    pFunction jump;
    SCB->VTOR = BOOT_ADDR;                    // remap vector table
    jump = (pFunction)*(( __IO uint32_t*)(BOOT_ADDR+4));
    jump();                                   // go to application
}

int WriteLocus(void);
void SysTick_Handler(void);
void systick_init(uint32_t ms);
void Reg_Read(unsigned short Address,unsigned short *Dat)
{
	if(Address >= 10000)return;
	*Dat = DReg[Address];  
}

void Reg_Write(unsigned short Address,unsigned short Dat)
{
	if(Address >= 10000)return;
	DReg[Address] = Dat; 
}

void Bit_Read(unsigned short Address,unsigned short *Dat)
{}

void Bit_Write(unsigned short Address,unsigned short Dat)
{} 

void InitModBus(void)
{
	ModbusReg_Read = &Reg_Read;
	ModbusReg_Write = &Reg_Write;
	ModbusBit_Read = &Bit_Read;
	ModbusBit_Write = &Bit_Write;
	//InitModbusReg(0);
}

int IRQHandle()
{
	static int a;
	a++;
	return 0;
}

extern FIL SD;
unsigned long sta;
long value,AxisPos[8];
FUNCPARAM FPA[100];     // work A
FUNCPARAM FPB[100];     // work B
//FUNCPARAM FPAB[100];    // work AB
uint16_t crc_temp = 0;
uint16_t crc_value = 0xffff;
uint16_t SoftLimit[10];
uint16_t lineBit,tempLineBit;
float LimitPos[5],LimitNeg[5];
unsigned short AxisDir;
unsigned long STM32Ver;
unsigned long FPGAVer;
char STM32Path[50] = "1:/UpgradeFile.STM32";
char crcPath1[50] = "1:/Teach_Bak1.RB";
char crcPath2[50] = "1:/Teach_Bak2.RB";
float ftemp1,ftemp2,ftemp3,ftemp;
int main()
{
	uint8_t i=0,flag;
	uint8_t fileLoadFlag;
	uint8_t fileSaveFlag;
	FRESULT fr;	
	UINT bw;
	
	regIRQ(&IRQHandle);
	SystemInit();	
	HW_Init();	
	I_GPIO_Init();	
	HardWare_UART2Init(115200);
	HardWare_UARTInit(57600);
	__enable_irq();
	InitLink();
	
	value = LinkConnectTest();
	if(value == 0)ClearPort(18);
	else SetPort(18);
	InitSysParamTemp();
	InitSysParam();
	
	SetLmtMode(XLMTPOS,YLMTPOS,ZLMTPOS,ALMTPOS,BLMTPOS,
	           XLMTNEG,YLMTNEG,ZLMTNEG,ALMTNEG,BLMTNEG,
		       0,0,0,0,0,0,0,0,0,0);
	Lmt_Disable(0);
	
	for(i=0;i<5;i++)SetPosDev(i+1,0);
	AxisDir = 0x0000;
	SetMotionDir(AxisDir);
	InitModBus();	
	ClearPort(18);       // LED_ON
	for(i=0;i<8;i++)AxisPos[i] = 0;
	
//	// STM32 update for moving G01
//	flag = USBUpgradeStm32();
//	if(flag == 0)
//	{
//		;//update success
//	}
//	else
//	{
//		;//update fail
//	}
	
	// open and read parameter bakup file	
	fr = f_open(&SD,crcPath1,FA_READ);
	if(fr == FR_OK)
	{
		f_read(&SD,&DReg[REGSTART],REGMAXNUM*sizeof(unsigned short),&bw);
		// CRC check and save DReg[] real time
		crc_value = UserCRC16((unsigned char *)(&DReg[REGSTART]),(REGMAXNUM-1)*sizeof(unsigned short));
		if(crc_value != DReg[REGSTART+REGMAXNUM-1])flag = 10;  // param file ERR
		f_close(&SD);
	}
	else flag = 10;             // open param file err
	
	if(flag == 10)
	{
		fr = f_open(&SD,crcPath2,FA_READ);
		if(fr == FR_OK)
		{
			f_read(&SD,&DReg[REGSTART],REGMAXNUM*sizeof(unsigned short),&bw);
			// CRC check and save DReg[] real time
			crc_value = UserCRC16((unsigned char *)(&DReg[REGSTART]),(REGMAXNUM-1)*sizeof(unsigned short));
			if(crc_value != DReg[REGSTART+REGMAXNUM-1])flag = 20;// param file ERR
			f_close(&SD);
		}
	}
	flag = 0;
	
	// teach table value init
	CurLine = 0;
	TotalLine = 0;
	tempPage = 0;
	PauseFlag = 0;
	tempLine = 0xffff;
	fileLoadFlag = 0;
	fileSaveFlag = 0;
	LastTime = NowTime;
	CommandInsertFlag = 0;
	lineBit = 0x0000 | (0x01<<0);
	tempLineBit = 0x0000;
	DReg[F_TEACHLINE01] = 1;
	
	// get STM32 and FPGA ver
	GetSTM32VerDev(&STM32Ver);
	GetFpgaVerDev(&FPGAVer);
	memcpy(&DReg[F_STM32VER],&STM32Ver,sizeof(unsigned long));
	memcpy(&DReg[F_FPGAVER],&FPGAVer,sizeof(unsigned long));
	
	// auto home when power or not
	if(DReg[F_AUTOHOME] == 1)DReg[F_RESETBTN] = 1;
	else DReg[F_RESETBTN] = 0;
	SystemStopLed();
	while(1)
	{
		ModbusServe(0);
		UpdateAxisParam();
		DispAxisPosition();
		DispInput();
		DispOutput();		
		LimitInputCheck();
		LimitPosCheck();
		ServoAlarmCheck();
		AxisManualMove();
		AxisMoveZero();
		MoveSettingInch();
		RatePlusMinus();
//		FastManualSpeed();
		TeachTableParam();
		DReg[F_SYSTEMSTATE] = 0;		
		
		if((DReg[F_TOTALCLEAR] == 1) && (PauseFlag == 0))
		{
			DReg[F_TOTALNUM] = 0;
			while(DReg[F_TOTALCLEAR] == 1)OSDelay(10);
		}
			
		// machine start execute program
		if((DReg[F_STARTBTN] == 1) || (ReadInput(STARTIN) == 0))
		{
			DReg[F_STARTBTN] = 0;
			StartFlag = 1;
		}
		else StartFlag = 0;
		
		// all axis search home point
		ExcuteMoverZeroConfig();
		
		if(((DReg[F_STOPBTN] == 1) || (ReadInput(ALARMIN) == 0)) && (PauseFlag == 0))
		{
			if(ReadInput(ALARMIN) == 0)
			{
				SystemAlarmLed();
			}
			for(i=0;i<16;i++)
			{
				WriteOutput(i,0);
				DReg[F_OUTPUT01+i] = 0;
			}
			for(i=0;i<5;i++)SAxisDec_stop(i+1);
		}
				
		// load param from file
		if((DReg[F_FILELOAD] == 1) && (PauseFlag == 0))
		{
			DReg[F_FILELOAD] = 0;
			fileLoadFlag = 1;
		}
		if(fileLoadFlag)
		{
			if(DReg[F_ACCEPTFLAG] == 1)
			{
				DReg[F_ACCEPTFLAG] = 0;
				ParamLoad();
				UserValueCrcCheck();
				DReg[F_LOADFLAG] = 1;
				fileLoadFlag = 0;
			}				
		}

		// save param into file
		if((DReg[F_FILESAVE] == 1) && (PauseFlag == 0))
		{
			DReg[F_FILESAVE] = 0;
			fileSaveFlag = 1;
		}
		if(fileSaveFlag)
		{
			if(DReg[F_ACCEPTFLAG] == 1)
			{
				DReg[F_ACCEPTFLAG] = 0;
				ParamSave();
				DReg[F_SAVEFLAG] = 1;
				fileSaveFlag = 0;
			}				
		}

		// begain execute program
		if((StartFlag == 1) && (DReg[F_AUTOMANUAL] == 1))
		{
			StartFlag = 0;
			SystemPauseLed();
			DReg[F_SYSTEMSTATE] = 1;
			if((DReg[F_CONTINUEBTN] == 1) || (DReg[F_SETNUMBER] == 0))
			{
				TeachParamExecute();
			}
			else if(DReg[F_CONTINUEBTN] == 0)
			{
				for(i=0;i<DReg[F_SETNUMBER];i++)
				{
					if(TeachParamExecute() == -1)break;
				}
			}
			DReg[F_SYSTEMSTATE] = 0;
			SystemStopLed();
			ustemp1 = NowTime;
		}
		
		// CRC check and save param real time
		if(NowTime%50 == 0)
		{
			UserValueCrcCheck();
		}
		DispPowerOnTime();
		StartFlag = 0;
	}
}

