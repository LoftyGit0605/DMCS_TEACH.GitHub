#ifndef _GLOBALDEFINE_H_
#define _GLOBALDEFINE_H_

#define Link_StartByte          0x0A

//缓冲指令
struct LayoutCmd_PC{
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
#define SDRAM_BASE 					(0xA0000000)
#define SDRAM_BASE_USER 			(0xA0000100)
#define SDRAM_BASE_IIC_USE			SDRAM_BASE_USER+ 0x1000

#define andy20160229
#define andy20160219
#define mxx20160220
#define andy20160503

typedef unsigned char	bool;
typedef unsigned char	byte;
typedef char         	sbyte;
typedef unsigned short	uint16_;
typedef short           int16_;
typedef unsigned short	uint16;
typedef short         	int16;
typedef unsigned long	uint_;
typedef unsigned long	uint32;
typedef long         	int_;
typedef long         	int32;
typedef long            Int32;
typedef unsigned long long uInt64;
typedef long long       Int64;

typedef enum{
    V1788_InIO5 = 0,       // 0x00000001
    V1788_InIO6 = 1,       // 0x00000002
    V1788_InIO7 = 2,       // 0x00000004
    V1788_InIO8 = 3,       // 0x00000008
    V1788_InIO1 = 4,       // 0x00000010
    V1788_InIO2 = 5,       // 0x00000020
    V1788_InIO3 = 6,       // 0x00000040
    V1788_InIO4 = 7,       // 0x00000080
    V1788_InIOEMC = 8,     // 0x00000100
    V1788_InIOALmtPos = 9, // 0x00000200
    V1788_InIOAOrg = 10,   // 0x00000400
    V1788_InIOALmtNeg = 11,// 0x00000800
    V1788_InIORLmtPos = 12,// 0x00001000
    V1788_InIOROrg = 13,   // 0x00002000
    V1788_InIORLmtNeg = 14,// 0x00004000
    V1788_InIOZLmtPos = 15,// 0x00008000
    V1788_InIOZOrg = 16,   // 0x00010000
    V1788_InIOZLmtNeg = 17,// 0x00020000
    V1788_InIOYLmtPos = 18,// 0x00040000
    V1788_InIOYOrg = 19,   // 0x00080000
    V1788_InIOYLmtNeg = 20,// 0x00100000
    V1788_InIOXLmtPos = 21,// 0x00200000
    V1788_InIOXOrg = 22,   // 0x00400000
    V1788_InIOXLmtNeg = 23,// 0x00800000
    V1788_InIOStart = 24,  // 0x01000000
    V1788_InIOWaring = 25, // 0x02000000
    V1788_InIOReturn = 26, // 0x04000000
    V1788_InIOStop = 27,   // 0x08000000
}LPC1788_IO_InIOShow;

typedef enum 
{
	V1788_OutIO1 = 0,      // 0x00001
	V1788_OutIO2 = 1,      // 0x00002
	V1788_OutIO3 = 2,      // 0x00004
	V1788_OutIO4 = 3,      // 0x00008
	V1788_OutIO13 = 4,     // 0x00010
	V1788_OutIO14 = 5,     // 0x00020
	V1788_OutIO15 = 6,     // 0x00040
	V1788_OutIO16 = 7,     // 0x00080
	V1788_OutIO9 = 8,      // 0x00100
	V1788_OutIO10 = 9,     // 0x00200
	V1788_OutIO11 = 10,    // 0x00400
	V1788_OutIO12 = 11,    // 0x00800
	V1788_OutIO5 = 12,     // 0x01000
	V1788_OutIO6 = 13,     // 0x02000
	V1788_OutIO7 = 14,     // 0x04000
	V1788_OutIO8 = 15,     // 0x08000
}LPC1788_IO_OutIOShow;

struct AxisLmt{
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
 
typedef enum{
	WorkSta_None = 0,		/* 0 */	 //手动/待机
	WorkSta_Run,
	WorkSta_Pause,			/* 1 */	 //暂停
	WorkSta_Stop,
	WorkSta_CpuSendFile,
	WorkSta_LinkErr,
} WORKSTA;


#define true		1
#define false		0
#define Axis_X_PC	1
#define Axis_Y_PC	2
#define Axis_Z_PC	3
#define Axis_R_PC	4
#define Axis_A_PC	5

extern volatile unsigned long NowTime;

#endif

