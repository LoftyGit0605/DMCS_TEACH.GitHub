#ifndef 		GLOBALDEFINE_H_H
#define 		GLOBALDEFINE_H_H
#ifdef 			GLOBALDEFINE_H_H


//#define    	Tcp_IP_Data_Len 	1000

#define     Link_StartByte          0x0A

//缓冲指令
struct LayoutCmd_PC		
{
	long X;							//各轴目标点	
	long Y;							//各轴目标点	
	long Z;							//各轴目标点
	long U;							//各轴目标点
	long V;							//各轴目标点
	unsigned long LineIndex;
	unsigned long Speed;			//命令线速度
	//unsigned long SpeedRate;  //andy2015.06.09
};


 #define nLcmSizeOf		28

#define SDRAM_BASE 					(0xA0000000)			//	
#define SDRAM_BASE_USER 			(0xA0000100)
#define SDRAM_BASE_IIC_USE			SDRAM_BASE_USER+ 0x1000




//#define andyTest20160314


#define PC_Link_UDP 	
//#define PC_Link_TCPIP	


#define andy20160229
#define andy20160219
#define mxx20160220
//#define xmark
//#define xmark20160226
//extern unsigned char IsSendLineBusy;
#define andy20160503





typedef unsigned   char    bool;
//typedef unsigned   char    Bool;
typedef unsigned   char    byte;
typedef char   			   sbyte;
typedef unsigned   short   uint16_;
typedef 		   short   int16_;
typedef unsigned   short   uint16;
typedef 		   short   int16;
typedef unsigned   long    uint_;
typedef unsigned   long    uint32;
typedef            long    int_;
typedef            long    int32;
typedef            long    Int32;
typedef unsigned long long  uInt64;
typedef  long long  		Int64;










typedef enum 
{
    V1788_InIO5 = 0,        //0x01
    V1788_InIO6 = 1,        //0x02
    V1788_InIO7 = 2,       //0x04
    V1788_InIO8 = 3,       //0x08
    V1788_InIO1 = 4,       //0x010
    V1788_InIO2 = 5,       //0x020
    V1788_InIO3 = 6,       //0x040
    V1788_InIO4 = 7,       //0x080
    V1788_InIOEMC = 8,     //0x0100
    V1788_InIOALmtPos = 9, //0x0200
    V1788_InIOAOrg = 10,   //0x0400
    V1788_InIOALmtNeg = 11,//0x0800
    V1788_InIORLmtPos = 12,//0x01000
    V1788_InIOROrg = 13,//0x02000
    V1788_InIORLmtNeg = 14,//0x04000
    V1788_InIOZLmtPos = 15,//0x08000
    V1788_InIOZOrg = 16,//0x010000
    V1788_InIOZLmtNeg = 17,//0x020000
    V1788_InIOYLmtPos = 18,//0x040000
    V1788_InIOYOrg = 19,//0x080000
    V1788_InIOYLmtNeg = 20,//0x0100000
    V1788_InIOXLmtPos = 21,//0x0200000
    V1788_InIOXOrg = 22,//0x0400000
    V1788_InIOXLmtNeg = 23,//0x0800000
    V1788_InIOStart = 24,//0x01000000
    V1788_InIOWaring = 25,//0x02000000
    V1788_InIOReturn = 26,//0x04000000
    V1788_InIOStop = 27,//0x08000000
}LPC1788_IO_InIOShow;

typedef enum 
{
	V1788_OutIO1 = 0, //0x01
	V1788_OutIO2 = 1, //0x02
	V1788_OutIO3 = 2, //0x04
	V1788_OutIO4 = 3, //0x08
	V1788_OutIO13 = 4, //0x010
	V1788_OutIO14 = 5, //0x020
	V1788_OutIO15 = 6, //0x040
	V1788_OutIO16 = 7, //0x080
	V1788_OutIO9 = 8, //0x0100
	V1788_OutIO10 = 9, //0x0200
	V1788_OutIO11 = 10,//0x0400
	V1788_OutIO12 = 11, //0x0800
	V1788_OutIO5 = 12, //0x01000
	V1788_OutIO6 = 13, //0x02000
	V1788_OutIO7 = 14, //0x04000
	V1788_OutIO8 = 15,//0x08000
}LPC1788_IO_OutIOShow;

//

struct AxisLmt
{
    unsigned char PosLmtIo;
    unsigned char NegLmtIo;
    unsigned char PosLmtVal;
    unsigned char NegLmtVal;
};
struct AxisLmtStruct
{
   struct AxisLmt X;
   struct AxisLmt Y;
   struct AxisLmt Z;
   struct AxisLmt U;
   struct AxisLmt V;
};
 
typedef enum {
	WorkSta_None = 0,		/* 0 */	 //手动/待机
	WorkSta_Run,
	WorkSta_Pause,			/* 1 */	 //暂停
	WorkSta_Stop,
	WorkSta_CpuSendFile,
	WorkSta_LinkErr,
	
} WORKSTA;




#define 	true		1
#define 	false		0

#define Axis_X_PC		1
#define Axis_Y_PC		2
#define Axis_Z_PC		3
#define Axis_R_PC		4
#define Axis_A_PC		5

extern volatile unsigned long NowTime;

/*
#define  Stat_LED_PortNum  18
#define  GPOUT_0_PortNum   17
#define  GPOUT_1_PortNum   16
#define  GPOUT_2_PortNum   19
#define  GPOUT_3_PortNum   20


#define GPOUT0_OFF	GPIO_OutputValue(4, (1<<GPOUT_0_PortNum), 1)
#define GPOUT1_OFF	GPIO_OutputValue(4, (1<<GPOUT_1_PortNum), 1)
#define GPOUT2_OFF	GPIO_OutputValue(4, (1<<GPOUT_2_PortNum), 1)
#define GPOUT3_OFF	GPIO_OutputValue(4, (1<<GPOUT_3_PortNum), 1)

#define GPOUT0_ON	  GPIO_OutputValue(4, (1<<GPOUT_0_PortNum), 0)
#define GPOUT1_ON	  GPIO_OutputValue(4, (1<<GPOUT_1_PortNum), 0)
#define GPOUT2_ON	  GPIO_OutputValue(4, (1<<GPOUT_2_PortNum), 0)
#define GPOUT3_ON	  GPIO_OutputValue(4, (1<<GPOUT_3_PortNum), 0)
*/

#endif
#else
#endif

