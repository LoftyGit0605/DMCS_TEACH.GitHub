#define AxisCount 8
#include "GlobalDefine.h"
//缓冲指令
/*
struct LayoutCmd		
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
*/

// #define nLcmSizeOf		28
/////////////////////////////////


/////////////////////////////////

typedef struct LayoutCmd_PC LayoutCmd;

//初始化相关

void InitLink(void);   //初始化连接
long LinkConnectTest(void);   //链接测试，返回0测试成功

long SAxisPmove(unsigned char Axis, long Pulse,unsigned long StartV,unsigned long Acc,unsigned long Speed);
long SAxisDec_stop(unsigned char Axis);//轴停止
long GetGPIO_Input(long *Dat);      //获取输入
long GetGPIO_Output(long *Dat);			//获取输出
//
long GetMotionStatus(unsigned long *Sta);     //获取轴运动状态
long GetPosDev(long *X, long *Y, long *Z, long *U, long *V, long *W, long *A, long *B);     //获取轴位置
//正在做插补运动的行号
//查询当前加工轨迹实际位置
//行号是在写入轨迹时自己编码的
//轨迹运动

long GetWorkIndex(unsigned long *Dat);     //获取行号


//硬件IO限位使能控制
//=0 使能
//=1 失能
long Lmt_Disable(unsigned char Onoff);			//限位失能
//开始轨迹规划
//=1 开始启动
//=0 停止轨迹规划，下面轨迹就停止规划
//主要用于 开始写一部分数据給运动规划单元，然后在开始，防止运动频繁加减速

long LayoutStart(unsigned char Onoff);			//规划启动，写1启动规划，写0停止规划
//最后一行行号,表示轨迹在这一行结束

long LocusEnd(unsigned long Index );
/*
功      能:	输出位控制
参      数:	unsigned char BitIndex 指输出端口号(0 ~ 15)
			unsigned char BitValue 只输出端口的电平(0 ~ 1)
*/
long SetGPIO_Output(unsigned char BitIndex, unsigned char BitValue);  //设置输出
//XLmtIo +限位IO
//XLmtBIo -限位IO
//XLmtLog 限位有效电平
//XLmtBLog 限位有效电平
long SetLmtMode(unsigned char XLmtIo,unsigned char YLmtIo,unsigned char ZLmtIo,unsigned char ULmtIo,unsigned char VLmtIo,
				unsigned char XLmtBIo,unsigned char YLmtBIo,unsigned char ZLmtBIo,unsigned char ULmtBIo,unsigned char VLmtBIo,
				unsigned char XLmtLog,unsigned char YLmtLog,unsigned char ZLmtLog,unsigned char ULmtLog,unsigned char VLmtLog,
				unsigned char XLmtBLog,unsigned char YLmtBLog,unsigned char ZLmtBLog,unsigned char ULmtBLog,unsigned char VLmtBLog);
						 
						 
//设置电机方向
long SetMotionDir(unsigned short Value);  // 设置轴方向
//主要用处清零当前位置，设置脉冲位置
long SetPosDev(short Axis, long Pos);    //设置轴位置
//紧急停止
long sudden_stop(unsigned char Axis);		
						 
//设置连续轨迹开始点 当前点
//开始轨迹前读取当前位置，听过该函数设置连续轨迹开始点
long BufOrg(long X, long Y, long Z, long U, long V);
//轨迹参数配置 起跳速度  最小速度  加速度  最大速度  转弯速度
long MotionConfig(unsigned long StartV,unsigned long MinSpeed,unsigned long Acc,unsigned long Speed,unsigned long AngleSpeed);
//开始轨迹,先设置开始然后写入轨迹
long BufStart(void);
//清楚轨迹数据
long BufClr(void);
//轨迹减速停止
long BufStop(void);
//轨迹目标位置发送 轨迹目标位置坐数组  数据开始下标 发送条数  返回成功写了多少条
//LayoutCmd_PC 实际数据是每个轴多少个脉冲（位置除以脉冲当量几个轴的最小值）
long BatchLine(struct LayoutCmd_PC *Cmd,unsigned short BeginIndex, unsigned char Count,unsigned char *ResV);
//long BatchAxisScale_Remote(, float *Val);
//设置脉冲当量比例，
//导程 丝杆转一圈实际走的距离 单位一般是mm A
//丝杆转一圈需要的脉冲个数 B
//脉冲当量 A/B
//根据机器情况每个轴是不一样的 机械情况
//实际计算出每个轴的脉冲当量，一最小脉冲当量作为分母，其他个轴脉冲当量作为分子，计算出脉冲当量比例
//运动程序计算脉冲数使用的
long SetAxisScale( float *Val);

long SetSmoothLevel(unsigned char Level);  //最大64级
//配置联动模式(1:联动 0:不联动)
long SetMoveTogetherMode(unsigned char X,unsigned char Y,unsigned char Z,unsigned char U,unsigned char V);
long GetSTM32VerDev(unsigned long *Ver);    //获取stm32版本号
long GetFpgaVerDev(unsigned long *Ver);     //FPGA版本号

//不用
long SynAxisConfig(unsigned long StartV,unsigned long Acc,unsigned long Speed,unsigned long LoopMax);
long SetAxisMap(unsigned char *MapDat);     //无用函数,底下无响应
long SetSynGpoutMask( unsigned short Mask); //无用函数,底下无响应

//long FPGAPortTest_Remote(long addr,long *Dat);
//long BatchSpeedSet_Remote(unsigned long Speed);
long GetTimeOut(void);          //无用
void SetTimeOut(long Value);    //无用 
short GetReSend(void);          //无用
void SetReSend(short Value);    //无用
long GetErrPack(void);          //无用
void SetErrPack(long Value);    //无用
long GetTimePack(void);         //无用
void SetTimePack(long Value);   //无用