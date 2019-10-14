#define PUBLIC_GLOBAL
#include "Base.h"

extern long AxisPos[];
extern int16_t PulseDir[5];
extern uint16_t SoftLimit[10];
extern unsigned short DReg[];
extern struct LayoutCmd_PC Line[];
extern void DispWorkMakeTime(void);
extern float LimitPos[5],LimitNeg[5];
extern int8_t ServoAlarmCheck(void);
extern void UserValueCrcCheck(void);
extern void SetManualSpeed(uint8_t Axis,long Speed[]);
/****************************************************************************************
Function :  display delay time (unit: 10ms)
Parameter:  time    :delay time
Return   :
****************************************************************************************/
int8_t OSDelay(int Time)
{
	int startTime = NowTime;
	Time = Time/10;
	while(NowTime < startTime+Time)
	{
		ModbusServe(0);
		DispAxisPosition();
		DispInput();
		DispOutput();
		UpdateAxisParam();
		if(ServoAlarmCheck() == -1)return -1;
		if(LimitPosCheck() == -1)return -1;
		if(LimitInputCheck() == -1)return -1;
		if(StartFlag)DispPowerOnTime();
		if(DReg[F_PAUSEBTN] == 1)
		{
			while(1)
			{
				ModbusServe(0);
				if((DReg[F_STOPBTN] == 1) || (ReadInput(STOPIN) == 0))return -1;
				if((DReg[F_STARTBTN] == 1) || (ReadInput(STARTIN) == 0))break;
			}
		}
		if((DReg[F_STOPBTN] == 1) || (ReadInput(STOPIN) == 0))return -1;
	}
	return 1;
}
/****************************************************************************************
Function :	machine search home
Parameter:  axis    :axis number
			mode    :home mode(0:machine home 1:program home)
Return   :   1: home success  -1: exit when homing 
****************************************************************************************/
int8_t MoveZero(uint8_t axis,uint8_t mode)
{
	long AxisPos[8],speed[3];
	long value1,value2;
	unsigned long sta;
	float OffsetHome[5];
	int dir,home;
	
	if(mode == 1)
	{
		GetPosDev(&AxisPos[0],&AxisPos[1],&AxisPos[2],&AxisPos[3],&AxisPos[4],&AxisPos[5],&AxisPos[6],&AxisPos[7]);
		speed[0] = mm(DReg[F_HOMESPEEDX+axis-1])*0.4/60.*SP.AxisGear[axis-1];
		speed[1] = mm(DReg[F_MAKEADDX+axis-1])*SP.AxisGear[axis-1];
		speed[2] = mm(DReg[F_HOMESPEEDX+axis-1])/60.*SP.AxisGear[axis-1];
		SAxisPmove(axis,-AxisPos[axis-1],speed[0],speed[1],speed[2]);
		while(1)
		{
			ModbusServe(0);
			GetMotionStatus(&sta);
			if(sta == 0)break;
			if((DReg[F_STOPBTN] == 1) || (ReadInput(STOPIN) == 0))
			{
				SAxisDec_stop(axis);
				while(1)
				{
					ModbusServe(0);
					GetMotionStatus(&sta);
					if(sta == 0)break;
					DispInput();
					DispOutput();		
					if(LimitInputCheck() == -1)return -1;
					if(ServoAlarmCheck() == -1)return -1;
					DispAxisPosition();					
					if(DispFlag)DispPowerOnTime();
				}
				return -1;
			}
			DispInput();
			DispOutput();		
			if(LimitInputCheck() == -1)return -1;
			if(ServoAlarmCheck() == -1)return -1;
			ServoAlarmCheck();
			DispAxisPosition();			
			if(DispFlag)DispPowerOnTime();
		}
		SetPosDev(axis,0);
	}
	else
	{
		if(DReg[F_HOMEDIRX+axis-1] == 1)dir = 1;
		else dir = -1;
		if(axis == 1)home = HOMEINX;
		if(axis == 2)home = HOMEINY;
		if(axis == 3)home = HOMEINZ;
		if(axis == 4)home = HOMEINA;
		if(axis == 5)home = HOMEINB;
		
		speed[0] = mm(DReg[F_HOMESPEEDX+axis-1])*0.4/60.*SP.AxisGear[axis-1];
		speed[1] = mm(DReg[F_MAKEADDX+axis-1])*SP.AxisGear[axis-1];
		speed[2] = mm(DReg[F_HOMESPEEDX+axis-1])/60.*SP.AxisGear[axis-1];
		SAxisPmove(axis,99999999*dir,speed[0],speed[1],speed[2]);
		while(1)
		{
			ModbusServe(0);
			GetGPIO_Input(&value1);
			value2 = 0x1 << home;
			if((value1 & value2) == 0)break;
			GetMotionStatus(&sta);
			if(sta == 0)break;
			if((DReg[F_STOPBTN] == 1) || (ReadInput(STOPIN) == 0))
			{
				SAxisDec_stop(axis);
				while(1)
				{
					ModbusServe(0);
					GetMotionStatus(&sta);
					if(sta == 0)break;
					DispInput();
					DispOutput();		
					if(LimitInputCheck() == -1)return -1;
					if(ServoAlarmCheck() == -1)return -1;
					ServoAlarmCheck();
					DispAxisPosition();
					if(DispFlag)DispPowerOnTime();
				}
				return -1;
			}
			DispInput();
			DispOutput();		
			if(LimitInputCheck() == -1)return -1;
			if(ServoAlarmCheck() == -1)return -1;
			ServoAlarmCheck();
			DispAxisPosition();
			if(DispFlag)DispPowerOnTime();
		}
		SAxisDec_stop(axis);
		while(1)
		{
			ModbusServe(0);
			GetMotionStatus(&sta);
			if(sta == 0)break;
			if((DReg[F_STOPBTN] == 1) || (ReadInput(STOPIN) == 0))
			{
				SAxisDec_stop(axis);
				while(1)
				{
					ModbusServe(0);
					GetMotionStatus(&sta);
					if(sta == 0)break;
					DispInput();
					DispOutput();		
					if(LimitInputCheck() == -1)return -1;
					if(ServoAlarmCheck() == -1)return -1;
					ServoAlarmCheck();
					DispAxisPosition();
					if(DispFlag)DispPowerOnTime();
				}
				return -1;
			}
			DispInput();
			DispOutput();		
			if(LimitInputCheck() == -1)return -1;
			if(ServoAlarmCheck() == -1)return -1;
			ServoAlarmCheck();
			DispAxisPosition();
			if(DispFlag)DispPowerOnTime();
		}
		
		speed[0] = mm(DReg[F_HOMESPEEDX+axis-1])*0.4*0.6/60.*SP.AxisGear[axis-1];
		speed[1] = mm(DReg[F_MAKEADDX+axis-1])*SP.AxisGear[axis-1];
		speed[2] = mm(DReg[F_HOMESPEEDX+axis-1])*0.6/60.*SP.AxisGear[axis-1];
		SAxisPmove(axis,-99999999*dir,speed[0],speed[1],speed[2]);
		while(1)
		{
			ModbusServe(0);
			GetGPIO_Input(&value1);
			value2 = 0x1 << home;
			if((value1 & value2) != 0)break;
			GetMotionStatus(&sta);
			if(sta == 0)break;
			if((DReg[F_STOPBTN] == 1) || (ReadInput(STOPIN) == 0))
			{
				SAxisDec_stop(axis);
				while(1)
				{
					ModbusServe(0);
					GetMotionStatus(&sta);
					if(sta == 0)break;
					DispInput();
					DispOutput();		
					if(LimitInputCheck() == -1)return -1;
					if(ServoAlarmCheck() == -1)return -1;
					ServoAlarmCheck();
					DispAxisPosition();
					if(DispFlag)DispPowerOnTime();
				}
				return -1;
			}
			DispInput();
			DispOutput();		
			if(LimitInputCheck() == -1)return -1;
			ServoAlarmCheck();
			DispAxisPosition();
			if(DispFlag)DispPowerOnTime();
		}
		SAxisDec_stop(axis);
		while(1)
		{
			ModbusServe(0);
			GetMotionStatus(&sta);
			if(sta == 0)break;
			if((DReg[F_STOPBTN] == 1) || (ReadInput(STOPIN) == 0))
			{
				SAxisDec_stop(axis);
				while(1)
				{
					ModbusServe(0);
					GetMotionStatus(&sta);
					if(sta == 0)break;
					DispInput();
					DispOutput();		
					if(LimitInputCheck() == -1)return -1;
					if(ServoAlarmCheck() == -1)return -1;
					ServoAlarmCheck();
					DispAxisPosition();
					if(DispFlag)DispPowerOnTime();
				}
				return -1;
			}
			DispInput();
			DispOutput();		
			if(LimitInputCheck() == -1)return -1;
			ServoAlarmCheck();
			DispAxisPosition();
			if(DispFlag)DispPowerOnTime();
		}
		
		speed[0] = mm(DReg[F_HOMESPEEDX+axis-1])*0.4*0.3/60.*SP.AxisGear[axis-1];
		speed[1] = mm(DReg[F_MAKEADDX+axis-1])*SP.AxisGear[axis-1];
		speed[2] = mm(DReg[F_HOMESPEEDX+axis-1])*0.3/60.*SP.AxisGear[axis-1];
		SAxisPmove(axis,99999999*dir,speed[0],speed[1],speed[2]);
		while(1)
		{
			ModbusServe(0);
			GetGPIO_Input(&value1);
			value2 = 0x1 << home;
			if((value1 & value2) == 0)break;
			GetMotionStatus(&sta);
			if(sta == 0)break;
			if((DReg[F_STOPBTN] == 1) || (ReadInput(STOPIN) == 0))
			{
				SAxisDec_stop(axis);
				while(1)
				{
					ModbusServe(0);
					GetMotionStatus(&sta);
					if(sta == 0)break;
					//OSDelay(2);
					DispInput();
					DispOutput();		
					if(LimitInputCheck() == -1)return -1;
					ServoAlarmCheck();
					DispAxisPosition();
					if(DispFlag)DispPowerOnTime();
				}
				return -1;
			}
			//OSDelay(2);
			DispInput();
			DispOutput();		
			if(LimitInputCheck() == -1)return -1;
			ServoAlarmCheck();
			DispAxisPosition();
			if(DispFlag)DispPowerOnTime();
		}
		SAxisDec_stop(axis);
		while(1)
		{
			ModbusServe(0);
			GetMotionStatus(&sta);
			if(sta == 0)break;
			if((DReg[F_STOPBTN] == 1) || (ReadInput(STOPIN) == 0))
			{
				SAxisDec_stop(axis);
				while(1)
				{
					ModbusServe(0);
					GetMotionStatus(&sta);
					if(sta == 0)break;
					//OSDelay(2);
					DispInput();
					DispOutput();		
					if(LimitInputCheck() == -1)return -1;
					ServoAlarmCheck();
					DispAxisPosition();
					if(DispFlag)DispPowerOnTime();
				}
				return -1;
			}
			//OSDelay(2);
			DispInput();
			DispOutput();		
			if(LimitInputCheck() == -1)return -1;
			ServoAlarmCheck();
			DispAxisPosition();
			if(DispFlag)DispPowerOnTime();
		}
		SetPosDev(axis,0);

		memcpy(&OffsetHome[0],&DReg[F_OFFSETHOMEX],sizeof(float));
		memcpy(&OffsetHome[1],&DReg[F_OFFSETHOMEY],sizeof(float));
		memcpy(&OffsetHome[2],&DReg[F_OFFSETHOMEZ],sizeof(float));
		memcpy(&OffsetHome[3],&DReg[F_OFFSETHOMEA],sizeof(float));
		memcpy(&OffsetHome[4],&DReg[F_OFFSETHOMEB],sizeof(float));
		if((int)(OffsetHome[axis-1]*1000*SP.AxisGear[axis-1]) != 0)
		{
			value1 = 0;
			speed[0] = mm(DReg[F_HOMESPEEDX+axis-1])*0.4/60.*SP.AxisGear[axis-1];
			speed[1] = mm(DReg[F_MAKEADDX+axis-1])*SP.AxisGear[axis-1];
			speed[2] = mm(DReg[F_HOMESPEEDX+axis-1])/60.*SP.AxisGear[axis-1];
			value1 = mm(OffsetHome[axis-1])*SP.AxisGear[axis-1];
			SAxisPmove(axis,value1,speed[0],speed[1],speed[2]);
			SetGPIO_Output(1,1);
			while(1)
			{
				ModbusServe(0);
				GetMotionStatus(&sta);
				if(sta == 0)break;
				if((DReg[F_STOPBTN] == 1) || (ReadInput(STOPIN) == 0))
				{
					SAxisDec_stop(axis);
					while(1)
					{
						ModbusServe(0);
						GetMotionStatus(&sta);
						if(sta == 0)break;
						//OSDelay(2);
						DispInput();
						DispOutput();		
						if(LimitInputCheck() == -1)return -1;
						ServoAlarmCheck();
						DispAxisPosition();
						if(DispFlag)DispPowerOnTime();
					}
					return -1;
				}
				//OSDelay(2);
				DispInput();
				DispOutput();		
				if(LimitInputCheck() == -1)return -1;
				ServoAlarmCheck();
				DispAxisPosition();
				if(DispFlag)DispPowerOnTime();
			}
			SAxisDec_stop(axis);
			while(1)
			{
				ModbusServe(0);
				GetMotionStatus(&sta);
				if(sta == 0)break;
				if((DReg[F_STOPBTN] == 1) || (ReadInput(STOPIN) == 0))
				{
					SAxisDec_stop(axis);
					while(1)
					{
						ModbusServe(0);
						GetMotionStatus(&sta);
						if(sta == 0)break;
						//OSDelay(2);
						DispInput();
						DispOutput();		
						if(LimitInputCheck() == -1)return -1;
						ServoAlarmCheck();
						DispAxisPosition();
						if(DispFlag)DispPowerOnTime();
					}
					return -1;
				}
				//OSDelay(2);
				DispInput();
				DispOutput();		
				if(LimitInputCheck() == -1)return -1;
				ServoAlarmCheck();
				DispAxisPosition();
				if(DispFlag)DispPowerOnTime();
			}
			SetPosDev(axis,0);
		}
	}
	return 1;
}
/****************************************************************************************
Function :	search home by config order
Parameter:  
Return   :  1: success  -1: fail 
****************************************************************************************/
int8_t ExcuteMoverZeroConfig(void)
{
	uint16_t HomeAxis[5],HomeMode[5];
	uint8_t i;
	
	if((DReg[F_RESETBTN] == 1) || (ReadInput(RESETIN) == 0))
	{
		DReg[F_RESETBTN] = 0;
		DReg[F_SYSTEMSTATE] = 3;
		for(i=0;i<5;i++)
		{
			HomeAxis[i] = 0;
			if(DReg[F_HOMETYPEX+i] != 0)DReg[F_HOMETYPEX+i] = 1;
			HomeMode[i] = DReg[F_HOMETYPEX+i];
		}
		
		if(MCTYPE == MCT300)
		{
			if(DReg[F_HOMEORDER] < 10000)DReg[F_HOMEORDER] = 31200;
			HomeAxis[0] = DReg[F_HOMEORDER]/10000;
			HomeAxis[1] = DReg[F_HOMEORDER]%10000/1000;
			HomeAxis[2] = DReg[F_HOMEORDER]%1000/100;
			for(i=0;i<3;i++)
			{
				if(MoveZero(HomeAxis[i],HomeMode[HomeAxis[i]-1]) == 1)
				{
					DReg[F_HOMEFLAGX+HomeAxis[i]-1] = 1;
				}
			}
//			if(MoveZero(3,0) == 1)DReg[F_HOMEFLAGZ] = 1;
//			if(MoveZero(1,0) == 1)DReg[F_HOMEFLAGX] = 1;
//			if(MoveZero(2,0) == 1)DReg[F_HOMEFLAGY] = 1;
//			if(MoveZero(4,0) == 1)DReg[F_HOMEFLAGA] = 1;
//			if(MoveZero(5,0) == 1)DReg[F_HOMEFLAGB] = 1;
		}
		else if(MCTYPE == MCT400)
		{
			if(DReg[F_HOMEORDER] < 10000)DReg[F_HOMEORDER] = 31240;
			HomeAxis[0] = DReg[F_HOMEORDER]/10000;
			HomeAxis[1] = DReg[F_HOMEORDER]%10000/1000;
			HomeAxis[2] = DReg[F_HOMEORDER]%1000/100;
			HomeAxis[3] = DReg[F_HOMEORDER]%100/10;
			for(i=0;i<4;i++)
			{
				if(MoveZero(HomeAxis[i],HomeMode[HomeAxis[i]-1]) == 1)
				{
					DReg[F_HOMEFLAGX+HomeAxis[i]-1] = 1;
				}
			}
//			if(MoveZero(3,0) == 1)DReg[F_HOMEFLAGZ] = 1;
//			if(MoveZero(1,0) == 1)DReg[F_HOMEFLAGX] = 1;
//			if(MoveZero(2,0) == 1)DReg[F_HOMEFLAGY] = 1;
//			if(MoveZero(4,0) == 1)DReg[F_HOMEFLAGA] = 1;
//			if(MoveZero(5,0) == 1)DReg[F_HOMEFLAGB] = 1;
		}
		else if(MCTYPE == MCT500)
		{
			if(DReg[F_HOMEORDER] < 10000)DReg[F_HOMEORDER] = 31245;
			HomeAxis[0] = DReg[F_HOMEORDER]/10000;
			HomeAxis[1] = DReg[F_HOMEORDER]%10000/1000;
			HomeAxis[2] = DReg[F_HOMEORDER]%1000/100;
			HomeAxis[3] = DReg[F_HOMEORDER]%100/10;
			HomeAxis[4] = DReg[F_HOMEORDER]%10;
			for(i=0;i<5;i++)
			{
				if(MoveZero(HomeAxis[i],HomeMode[HomeAxis[i]-1]) == 1)
				{
					DReg[F_HOMEFLAGX+HomeAxis[i]-1] = 1;
				}
			}
//			if(MoveZero(3,0) == 1)DReg[F_HOMEFLAGZ] = 1;
//			if(MoveZero(1,0) == 1)DReg[F_HOMEFLAGX] = 1;
//			if(MoveZero(2,0) == 1)DReg[F_HOMEFLAGY] = 1;
//			if(MoveZero(4,0) == 1)DReg[F_HOMEFLAGA] = 1;
//			if(MoveZero(5,0) == 1)DReg[F_HOMEFLAGB] = 1;
		}
	}
	return 1;
}
/****************************************************************************************
Function :	axes move by the setting inch in absolute or relative
Parameter:   		
Return   :
****************************************************************************************/
void MoveSettingInch(void)
{
	long i,speed[5][3];
	float ftemp;
	
	if(StartFlag == 1)return;
	for(i=0;i<5;i++)SetManualSpeed(i+1,speed[i]);	
	if(DReg[F_MOVEMODE] == 0)
	{
		if(DReg[F_BTNINCHX] == 1)
		{
			memcpy(&ftemp,&DReg[F_SETINCHX],sizeof(float));
			if(G00RelPos(1,ftemp,speed[0][0],speed[0][1],speed[0][2]) == -1)return;
			while(DReg[F_BTNINCHX] == 1)OSDelay(10);
		}
		if(DReg[F_BTNINCHY] == 1)
		{
			memcpy(&ftemp,&DReg[F_SETINCHY],sizeof(float));
			if(G00RelPos(2,ftemp,speed[1][0],speed[1][1],speed[1][2]) == -1)return;
			while(DReg[F_BTNINCHY] == 1)OSDelay(10);
		}
		if(DReg[F_BTNINCHZ] == 1)
		{
			memcpy(&ftemp,&DReg[F_SETINCHZ],sizeof(float));
			if(G00RelPos(3,ftemp,speed[2][0],speed[2][1],speed[2][2]) == -1)return;
			while(DReg[F_BTNINCHZ] == 1)OSDelay(10);
		}
		if(DReg[F_BTNINCHA] == 1)
		{
			memcpy(&ftemp,&DReg[F_SETINCHA],sizeof(float));
			if(G00RelPos(4,ftemp,speed[3][0],speed[3][1],speed[3][2]) == -1)return;
			while(DReg[F_BTNINCHA] == 1)OSDelay(10);
		}
		if(DReg[F_BTNINCHB] == 1)
		{
			memcpy(&ftemp,&DReg[F_SETINCHB],sizeof(float));
			if(G00RelPos(5,ftemp,speed[4][0],speed[4][1],speed[4][2]) == -1)return;
			while(DReg[F_BTNINCHB] == 1)OSDelay(10);
		}
	}
	else if(DReg[F_MOVEMODE] == 1)
	{
		if(DReg[F_BTNINCHX] == 1)
		{
			memcpy(&ftemp,&DReg[F_SETINCHX],sizeof(float));
			ftemp = ftemp - GetMacPosMm(1);
			if(G00RelPos(1,ftemp,speed[0][0],speed[0][1],speed[0][2]) == -1)return;
			while(DReg[F_BTNINCHX] == 1)OSDelay(10);
		}
		if(DReg[F_BTNINCHY] == 1)
		{
			memcpy(&ftemp,&DReg[F_SETINCHY],sizeof(float));
			ftemp = ftemp - GetMacPosMm(2);
			if(G00RelPos(2,ftemp,speed[1][0],speed[1][1],speed[1][2]) == -1)return;
			while(DReg[F_BTNINCHY] == 1)OSDelay(10);
		}
		if(DReg[F_BTNINCHZ] == 1)
		{
			memcpy(&ftemp,&DReg[F_SETINCHZ],sizeof(float));
			ftemp = ftemp - GetMacPosMm(3);
			if(G00RelPos(3,ftemp,speed[2][0],speed[2][1],speed[2][2]) == -1)return;
			while(DReg[F_BTNINCHZ] == 1)OSDelay(10);
		}
		if(DReg[F_BTNINCHA] == 1)
		{
			memcpy(&ftemp,&DReg[F_SETINCHA],sizeof(float));
			ftemp = ftemp - GetMacPosMm(4);
			if(G00RelPos(4,ftemp,speed[3][0],speed[3][1],speed[3][2]) == -1)return;
			while(DReg[F_BTNINCHA] == 1)OSDelay(10);
		}
		if(DReg[F_BTNINCHB] == 1)
		{
			memcpy(&ftemp,&DReg[F_SETINCHB],sizeof(float));
			ftemp = ftemp - GetMacPosMm(5);
			if(G00RelPos(5,ftemp,speed[4][0],speed[4][1],speed[4][2]) == -1)return;
			while(DReg[F_BTNINCHB] == 1)OSDelay(10);		
		}
	}
}
/****************************************************************************************
Function :	machine move in hand mode
Parameter:  axis    :axis number
			dir     :machine move direction
Return   :
****************************************************************************************/
void ManualMove(uint8_t axis,int8_t dir)
{
	long AxisPos[8],speed[3];
	unsigned long sta;
	
	UpdateAxisParam();
	GetMotionStatus(&sta);	
	GetPosDev(&AxisPos[0],&AxisPos[1],&AxisPos[2],&AxisPos[3],&AxisPos[4],&AxisPos[5],&AxisPos[6],&AxisPos[7]);
	if(sta == 0)
	{
		if(dir == 1)
		{
			speed[0] = mm(DReg[F_MANSPEED1X+axis-1])/60.*SP.AxisGear[axis-1];
			speed[2] = mm(DReg[F_MAKEADDX+axis-1])*SP.AxisGear[axis-1];
			speed[1] = mm(DReg[F_MANSPEED2X+axis-1])/60.*SP.AxisGear[axis-1];
			SAxisPmove(axis,(SP.LimitPos[axis-1]*1000*SP.AxisGear[axis-1]-AxisPos[axis-1]+100),speed[0],speed[2],speed[1]);
		}
		else if(dir == -1)
		{
			speed[0] = mm(DReg[F_MANSPEED1X+axis-1])/60.*SP.AxisGear[axis-1];
			speed[2] = mm(DReg[F_MAKEADDX+axis-1])*SP.AxisGear[axis-1];
			speed[1] = mm(DReg[F_MANSPEED2X+axis-1])/60.*SP.AxisGear[axis-1];
			SAxisPmove(axis,(SP.LimitNeg[axis-1]*1000*SP.AxisGear[axis-1]-AxisPos[axis-1]-100),speed[0],speed[2],speed[1]);
		}
	}
}
/****************************************************************************************
Function :	axis move in hand mode
Parameter:   
Return   :
****************************************************************************************/
void AxisManualMove(void)
{
	if(StartFlag != 1)
	{		
		if(DReg[F_MANUALPOSX] == 1)      //X-axis manual run to positive
		{
			if((DReg[F_LMTPOSX] == 0) && (SoftLimit[0] == 0))
			{
				ManualMove(1,1);				
			}			
		}
		else if(DReg[F_MANUALNEGX] == 1) //X-axis manual run to negative
		{
			if((DReg[F_LMTNEGX] == 0) && (SoftLimit[1] == 0))
			{
				ManualMove(1,-1);
			}
		}
		else SAxisDec_stop(1);

		if(DReg[F_MANUALPOSY] == 1)      //Y-axis manual run to positive
		{
			if((DReg[F_LMTPOSY] == 0) && (SoftLimit[2] == 0))
			{
				ManualMove(2,1);
			}
		}
		else if(DReg[F_MANUALNEGY] == 1) //Y-axis manual run to negative
		{
			if((DReg[F_LMTNEGY] == 0) && (SoftLimit[3] == 0))
			{
				ManualMove(2,-1);
			}
		}
		else SAxisDec_stop(2);

		if(DReg[F_MANUALPOSZ] == 1)      //Z-axis manual run to positive
		{
			if((DReg[F_LMTPOSZ] == 0) && (SoftLimit[4] == 0))
			{
				ManualMove(3,1);
			}
		}
		else if(DReg[F_MANUALNEGZ] == 1) //Z-axis manual run to negative
		{
			if((DReg[F_LMTNEGZ] == 0) && (SoftLimit[5] == 0))
			{
				ManualMove(3,-1);
			}
		}
		else SAxisDec_stop(3);

		if(DReg[F_MANUALPOSA] == 1)      //A-axis manual run to positive
		{
			if((DReg[F_LMTPOSA] == 0) && (SoftLimit[6] == 0))
			{
				ManualMove(4,1);
			}
		}
		else if(DReg[F_MANUALNEGA] == 1) //A-axis manual run to negative
		{
			if((DReg[F_LMTNEGA] == 0) && (SoftLimit[7] == 0))
			{
				ManualMove(4,-1);
			}
		}
		else SAxisDec_stop(4);

		if(DReg[F_MANUALPOSB] == 1)	   //B-axis manual run to positive
		{
			if((DReg[F_LMTPOSB] == 0) && (SoftLimit[8] == 0))
			{
				ManualMove(5,1);
			}
		}
		else if(DReg[F_MANUALNEGB] == 1) //B-axis manual run to negative
		{
			if((DReg[F_LMTNEGB] == 0) && (SoftLimit[9] == 0))
			{
				ManualMove(5,-1);
			}
		}
		else SAxisDec_stop(5);
	}
}
/****************************************************************************************
Function :	axis search home
Parameter:   
Return   :
****************************************************************************************/
void AxisMoveZero(void)
{
	//Y-axis search home point first
	if(DReg[F_HOMEBTNY] == 1)
	{
		DReg[F_HOMEBTNY] = 0;
		if(MoveZero(2,DReg[F_HOMETYPEY]) == 1)
		{
			DReg[F_HOMEFLAGY] = 1;
		}
	}
	
	//X-axis search home point second
	if(DReg[F_HOMEBTNX] == 1)
	{
		DReg[F_HOMEBTNX] = 0;
		if(MoveZero(1,DReg[F_HOMETYPEX]) == 1)
		{
			DReg[F_HOMEFLAGX] = 1;
		}
	}
	
	//Z-axis search home point
	if(DReg[F_HOMEBTNZ] == 1)
	{
		DReg[F_HOMEBTNZ] = 0;
		if(MoveZero(3,DReg[F_HOMETYPEZ]) == 1)
		{
			DReg[F_HOMEFLAGZ] = 1;
		}
	}
	
	//A-axis search home point
	if(DReg[F_HOMEBTNA] == 1)
	{
		if(MCTYPE == MCT300)return;
		DReg[F_HOMEBTNA] = 0;
		if(MoveZero(4,DReg[F_HOMETYPEA]) == 1)
		{
			DReg[F_HOMEFLAGA] = 1;
		}
	}
	
	//B-axis search home point
	if(DReg[F_HOMEBTNB] == 1)
	{
		if(MCTYPE == MCT300)return;
		if(MCTYPE == MCT400)return;
		DReg[F_HOMEBTNB] = 0;
		if(MoveZero(5,DReg[F_HOMETYPEB]) == 1)
		{
			DReg[F_HOMEFLAGB] = 1;
		}
	}
}
/****************************************************************************************
Function :	dignose input
Parameter:   
Return   :
****************************************************************************************/
void DispInput(void)
{
	if(ReadInput(HOMEINX) == 0)DReg[F_HOMEINX] = 1;
	else DReg[F_HOMEINX] = 0;
	if(ReadInput(HOMEINY) == 0)DReg[F_HOMEINY] = 1;
	else DReg[F_HOMEINY] = 0;
	if(ReadInput(HOMEINZ) == 0)DReg[F_HOMEINZ] = 1;
	else DReg[F_HOMEINZ] = 0;
	if(ReadInput(HOMEINA) == 0)DReg[F_HOMEINA] = 1;
	else DReg[F_HOMEINA] = 0;
	if(ReadInput(HOMEINB) == 0)DReg[F_HOMEINB] = 1;
	else DReg[F_HOMEINB] = 0;
	
	if(ReadInput(XLMTPOS) == 0)DReg[F_LMTPOSX] = 1;
	else DReg[F_LMTPOSX] = 0;
	if(ReadInput(XLMTNEG) == 0)DReg[F_LMTNEGX] = 1;
	else DReg[F_LMTNEGX] = 0;
	
	if(ReadInput(YLMTPOS) == 0)DReg[F_LMTPOSY] = 1;
	else DReg[F_LMTPOSY] = 0;
	if(ReadInput(YLMTNEG) == 0)DReg[F_LMTNEGY] = 1;
	else DReg[F_LMTNEGY] = 0;
	
	if(ReadInput(ZLMTPOS) == 0)DReg[F_LMTPOSZ] = 1;
	else DReg[F_LMTPOSZ] = 0;
	if(ReadInput(ZLMTNEG) == 0)DReg[F_LMTNEGZ] = 1;
	else DReg[F_LMTNEGZ] = 0;
	
	if(ReadInput(ALMTPOS) == 0)DReg[F_LMTPOSA] = 1;
	else DReg[F_LMTPOSA] = 0;
	if(ReadInput(ALMTPOS) == 0)DReg[F_LMTNEGA] = 1;
	else DReg[F_LMTNEGA] = 0;
	
	if(ReadInput(BLMTPOS) == 0)DReg[F_LMTPOSB] = 1;
	else DReg[F_LMTPOSB] = 0;
	if(ReadInput(BLMTNEG) == 0)DReg[F_LMTNEGB] = 1;
	else DReg[F_LMTNEGB] = 0;
	
	if(ReadInput(STARTIN) == 0)DReg[F_STARTIN] = 1;
	else DReg[F_STARTIN] = 0;
	if(ReadInput(ALARMIN) == 0)DReg[F_ALARMIN] = 1;
	else DReg[F_ALARMIN] = 0;
	if(ReadInput(RESETIN) == 0)DReg[F_RESETIN] = 1;
	else DReg[F_RESETIN] = 0;
	if(ReadInput(STOPIN) == 0)DReg[F_STOPIN] = 1;
	else DReg[F_STOPIN] = 0;
	
	if(ReadInput(INPUT01) == 0)DReg[F_INPUT01] = 1;
	else DReg[F_INPUT01] = 0;
	if(ReadInput(INPUT02) == 0)DReg[F_INPUT02] = 1;
	else DReg[F_INPUT02] = 0;
	if(ReadInput(INPUT03) == 0)DReg[F_INPUT03] = 1;
	else DReg[F_INPUT03] = 0;
	if(ReadInput(INPUT04) == 0)DReg[F_INPUT04] = 1;
	else DReg[F_INPUT04] = 0;
	if(ReadInput(INPUT05) == 0)DReg[F_INPUT05] = 1;
	else DReg[F_INPUT05] = 0;
	if(ReadInput(INPUT06) == 0)DReg[F_INPUT06] = 1;
	else DReg[F_INPUT06] = 0;
	if(ReadInput(INPUT07) == 0)DReg[F_INPUT07] = 1;
	else DReg[F_INPUT07] = 0;
	if(ReadInput(INPUT08) == 0)DReg[F_INPUT08] = 1;
	else DReg[F_INPUT08] = 0;
	if(ReadInput(INPUT09) == 0)DReg[F_INPUT09] = 1;
	else DReg[F_INPUT09] = 0;
}
/****************************************************************************************
Function :	dignose output
Parameter:   
Return   :
****************************************************************************************/
void DispOutput(void)
{
	if(DReg[F_OUTPUT01] == 1)WriteOutput(OUTPUT01,1);
	else WriteOutput(OUTPUT01,0);
	if(DReg[F_OUTPUT02] == 1)WriteOutput(OUTPUT02,1);
	else WriteOutput(OUTPUT02,0);
	if(DReg[F_OUTPUT03] == 1)WriteOutput(OUTPUT03,1);
	else WriteOutput(OUTPUT03,0);
	if(DReg[F_OUTPUT04] == 1)WriteOutput(OUTPUT04,1);
	else WriteOutput(OUTPUT04,0);
	if(DReg[F_OUTPUT05] == 1)WriteOutput(OUTPUT05,1);
	else WriteOutput(OUTPUT05,0);
	if(DReg[F_OUTPUT06] == 1)WriteOutput(OUTPUT06,1);
	else WriteOutput(OUTPUT06,0);
	if(DReg[F_OUTPUT07] == 1)WriteOutput(OUTPUT07,1);
	else WriteOutput(OUTPUT07,0);
	if(DReg[F_OUTPUT08] == 1)WriteOutput(OUTPUT08,1);
	else WriteOutput(OUTPUT08,0);
	if(DReg[F_OUTPUT09] == 1)WriteOutput(OUTPUT09,1);
	else WriteOutput(OUTPUT09,0);
	if(DReg[F_OUTPUT10] == 1)WriteOutput(OUTPUT10,1);
	else WriteOutput(OUTPUT10,0);
	if(DReg[F_OUTPUT11] == 1)WriteOutput(OUTPUT11,1);
	else WriteOutput(OUTPUT11,0);
	if(DReg[F_OUTPUT12] == 1)WriteOutput(OUTPUT12,1);
	else WriteOutput(OUTPUT12,0);
	if(DReg[F_OUTPUT13] == 1)WriteOutput(OUTPUT13,1);
	else WriteOutput(OUTPUT13,0);
	if(DReg[F_OUTPUT14] == 1)WriteOutput(OUTPUT14,1);
	else WriteOutput(OUTPUT14,0);
	if(DReg[F_OUTPUT15] == 1)WriteOutput(OUTPUT15,1);
	else WriteOutput(OUTPUT15,0);
	if(DReg[F_OUTPUT16] == 1)WriteOutput(OUTPUT16,1);
	else WriteOutput(OUTPUT16,0);
}
/****************************************************************************************
Function :  axis limit input check
Parameter:
Return   :  1:motion success  -1:exit when moving
****************************************************************************************/
int8_t LimitInputCheck(void)
{
	long val;
	int8_t flag;
	
	flag = 0;
	GetGPIO_Input(&val);
	//XYZRA limit input
	if((val&(0x1<<XLMTPOS)) == 0) // axis-X positive limit
	{
		DReg[F_LMTPOSX] = 1;
		SAxisDec_stop(1);
		flag = 1;
	}
	else DReg[F_LMTPOSX] = 0;
	
	if((val&(0x1<<XLMTNEG)) == 0) // axis-X negative limit
	{
		DReg[F_LMTNEGX] = 1;
		SAxisDec_stop(1);
		flag = 1;
	}
	else DReg[F_LMTNEGX] =0;
	
	if((val&(0x1<<YLMTPOS)) == 0) // axis-Y positive limit
	{
		DReg[F_LMTPOSY] = 1;
		SAxisDec_stop(2);
		flag = 1;
	}
	else DReg[F_LMTPOSY] = 0;
	
	if((val&(0x1<<YLMTNEG)) == 0) // axis-Y negative limit
	{
		DReg[F_LMTNEGY] = 1;
		SAxisDec_stop(2);
		flag = 1;
	}
	else DReg[F_LMTNEGY] = 0;
	
	if((val&(0x1<<ZLMTPOS)) == 0) // axis-Z positive limit
	{
		DReg[F_LMTPOSZ] = 1;
		SAxisDec_stop(3);
		flag = 1;
	}
	else DReg[F_LMTPOSZ] = 0;
	
	if((val&(0x1<<ZLMTNEG)) == 0) // axis-Z negative limit
	{
		DReg[F_LMTNEGZ] = 1;
		SAxisDec_stop(3);
		flag = 1;
	}
	else DReg[F_LMTNEGZ] = 0;
	
	if((val&(0x1<<ALMTPOS)) == 0) // axis-A positive limit(map R of the controler)
	{
		DReg[F_LMTPOSA] = 1;
		SAxisDec_stop(4);
		flag = 1;
	}
	else DReg[F_LMTPOSA] = 0;
	
	if((val&(0x1<<ALMTNEG)) == 0) // axis-A negative limit(map R of the controler)
	{
		DReg[F_LMTNEGA] = 1;
		SAxisDec_stop(4);
		flag = 1;
	}
	else DReg[F_LMTNEGA] = 0;
	
	if((val&(0x1<<BLMTPOS)) == 0) // axis-B positive limit(map A of the controler)
	{
		DReg[F_LMTPOSB] = 1;
		SAxisDec_stop(5);
		flag = 1;
	}
	else DReg[F_LMTPOSB] = 0;
	
	if((val&(0x1<<BLMTNEG)) == 0) // axis-B negative limit(map A of the controler)
	{
		DReg[F_LMTNEGB] = 1;
		SAxisDec_stop(5);
		flag = 1;
	}
	else DReg[F_LMTNEGB] = 0;
	if(flag == 1)
	{
		if(StartFlag == 1)
		{
			SAxisDec_stop(1);
			SAxisDec_stop(2);
			SAxisDec_stop(3);
			SAxisDec_stop(4);
			SAxisDec_stop(5);
		}
		return -1;
	}
	return 1;
}
/****************************************************************************************
Function :	limit soft position check
Parameter:   
Return   :
****************************************************************************************/
int8_t LimitPosCheck(void)
{
	float temp[5];
	int8_t flag;
	
	flag = 0;
	memcpy(&temp[0],&DReg[F_AXISPOSX],sizeof(float));
	memcpy(&temp[1],&DReg[F_AXISPOSY],sizeof(float));
	memcpy(&temp[2],&DReg[F_AXISPOSZ],sizeof(float));
	memcpy(&temp[3],&DReg[F_AXISPOSA],sizeof(float));
	memcpy(&temp[4],&DReg[F_AXISPOSB],sizeof(float));
	// axis-X positive limit
	if((int)(temp[0]*1000) > (int)(LimitPos[0]*1000))
	{
		SAxisDec_stop(1);
		SoftLimit[0] = 1;
		flag = 1;
	}
	else SoftLimit[0] = 0;
	
	// axis-X negative limit
	if((int)(temp[0]*1000) < (int)(LimitNeg[0]*1000))
	{
		SAxisDec_stop(1);
		SoftLimit[1] = 1;
		flag = 1;
	}
	else SoftLimit[1] = 0;
	
	// axis-Y positive limit
	if((int)(temp[1]*1000) > (int)(LimitPos[1]*1000))
	{
		SAxisDec_stop(2);
		SoftLimit[2] = 1;
		flag = 1;
	}
	else SoftLimit[2] = 0;
	
	// axis-Y negative limit
	if((int)(temp[1]*1000) < (int)(LimitNeg[1]*1000))
	{
		SAxisDec_stop(2);
		SoftLimit[3] = 1;
		flag = 1;
	}
	else SoftLimit[3] = 0;
	
	// axis-Z positive limit
	if((int)(temp[2]*1000) > (int)(LimitPos[2]*1000))
	{
		SAxisDec_stop(3);
		SoftLimit[4] = 1;
		flag = 1;
	}
	else SoftLimit[4] = 0;
	
	// axis-Z negative limit
	if((int)(temp[2]*1000) < (int)(LimitNeg[2]*1000))
	{
		SAxisDec_stop(3);
		SoftLimit[5] = 1;
		flag = 1;
	}
	else SoftLimit[5] = 0;
	
	// axis-A positive limit
	if((int)(temp[3]*1000) > (int)(LimitPos[3]*1000))
	{
		SAxisDec_stop(4);
		SoftLimit[6] = 1;
		flag = 1;
	}
	else SoftLimit[6] = 0;
	
	// axis-A negative limit
	if((int)(temp[3]*1000) < (int)(LimitNeg[3]*1000))
	{
		SAxisDec_stop(4);
		SoftLimit[7] = 1;
		flag = 1;
	}
	else SoftLimit[7] = 0;

	// axis-B positive limit
	if((int)(temp[4]*1000) > (int)(LimitPos[4]*1000))
	{
		SAxisDec_stop(5);
		SoftLimit[8] = 1;
		flag = 1;
	}
	else SoftLimit[8] = 0;
	
	// axis-B negative limit
	if((int)(temp[4]*1000) < (int)(LimitNeg[4]*1000))
	{
		SAxisDec_stop(5);
		SoftLimit[9] = 1;
		flag = 1;
	}
	else SoftLimit[9] = 0;	
	if(flag == 1)
	{
		if(StartFlag == 1)
		{
			SAxisDec_stop(1);
			SAxisDec_stop(2);
			SAxisDec_stop(3);
			SAxisDec_stop(4);
			SAxisDec_stop(5);
		}
		return -1;
	}
	
	return 1;
}
/****************************************************************************************
Function :  servo alarm
Parameter:
Return   :  1:no alarm  -1:alarm
****************************************************************************************/
int8_t ServoAlarmCheck(void)
{
	long val;
	int8_t flag;
	
	flag = 0;
	GetGPIO_Input(&val);
	// servo-X alarm and warning
	if((val&(0x1<<INPUT05)) == 0) 
	{
		DReg[F_INPUT05] = 1;
		SAxisDec_stop(1);
		//WriteOutput(ALARMOUT,1);
		//DReg[ALARMREG] = 1;
		flag = 1;
	}
	else DReg[F_INPUT05] = 0;
	
	// servo-Y alarm and warning
	if((val&(0x1<<INPUT06)) == 0) 
	{
		DReg[F_INPUT06] = 1;
		SAxisDec_stop(2);
		//WriteOutput(ALARMOUT,1);
		//DReg[ALARMREG] = 1;
		flag = 1;
	}
	else DReg[F_INPUT06] =0;
	
	// servo-Z alarm and warning
	if((val&(0x1<<INPUT07)) == 0) 
	{
		DReg[F_INPUT07] = 1;
		SAxisDec_stop(3);
		//WriteOutput(ALARMOUT,1);
		//DReg[ALARMREG] = 1;
		flag = 1;
	}
	else DReg[F_INPUT07] =0;
	
	// servo-A alarm and warning
	if((val&(0x1<<INPUT08)) == 0) 
	{
		DReg[F_INPUT08] = 1;
		SAxisDec_stop(4);
		//WriteOutput(ALARMOUT,1);
		//DReg[ALARMREG] = 1;
		flag = 1;
	}
	else DReg[F_INPUT08] =0;
	
	// servo-B alarm and warning
	if((val&(0x1<<INPUT09)) == 0) 
	{
		DReg[F_INPUT09] = 1;
		SAxisDec_stop(5);
		//WriteOutput(ALARMOUT,1);
		//DReg[ALARMREG] = 1;
		flag = 1;
	}
	else DReg[F_INPUT09] =0;
	if(flag == 1)
	{
		if(StartFlag == 1)
		{
			SAxisDec_stop(1);
			SAxisDec_stop(2);
			SAxisDec_stop(3);
			SAxisDec_stop(4);
			SAxisDec_stop(5);
		}
		return -1;
	}
	
	return 1;
}
/****************************************************************************************
Function :  set axis speed
Parameter:  Axis    :axis number
            Speed   :include start speed, acceleration speed, make speed
Return   :
****************************************************************************************/
void SetMakeSpeed(uint8_t Axis,long Speed[])
{	
	Speed[0] = (long)(DReg[F_MAKESTARTX+Axis-1]*DReg[F_AUTORATE]/100.);
	Speed[1] = (long)(DReg[F_MAKEADDX+Axis-1]*DReg[F_AUTORATE]/100.);
	Speed[2] = (long)(DReg[F_MAKESPEEDX+Axis-1]*DReg[F_AUTORATE]/100.);
}
/****************************************************************************************
Function :  set axis manual speed
Parameter:  Axis    :axis number
            Speed   :include start speed, acceleration speed, make speed
Return   :
****************************************************************************************/
void SetManualSpeed(uint8_t Axis,long Speed[])
{	
	Speed[0] = (long)(DReg[F_MANSPEED1X+Axis-1]*DReg[F_MANUALRATE]/100.);
	Speed[1] = (long)(DReg[F_MAKEADDX+Axis-1]*DReg[F_MANUALRATE]/100.);
	Speed[2] = (long)(DReg[F_MANSPEED2X+Axis-1]*DReg[F_MANUALRATE]/100.);
}
/****************************************************************************************
Function :  get the state of input
Parameter:  Input   :input port number
Return   :  0:valiad     1:invalid
****************************************************************************************/
int ReadInput(int Input)
{
	long value1,value2;
	int result;
	
	GetGPIO_Input(&value1);
	value2 = 0x1 << Input;
	if((value1 & value2) == 0)result = 0;
	else result = 1;
	
	return result;
}
/****************************************************************************************
Function :  write the output
Parameter:  Output   :output port number
Return   :  0:valiad     1:invalid
****************************************************************************************/
int8_t WriteOutput(uint8_t Output,uint8_t Value)
{
	int result;
	SetGPIO_Output(Output,Value);
	if(Value == 1)result = 0;
	else result = 1;
	return result;
}
/****************************************************************************************
Function :  axis move with waitting end
Parameter:  Axis    :axis number
            Inch    :move distance (unit: mm)
            Start   :start speed (unit: mm/min)
            Acc     :accelerate speed
            Speed   :make speed
Return   :  1:motion success  -1:exit when moving
****************************************************************************************/
int8_t G00RelPos(uint8_t Axis,float Inch,long Start,long Acc,long Speed)
{
	long pulse,speed[3];
	unsigned long sta;
	long AxisPos[8],temp;
	
//	if(MCTYPE == MCT300)
//	{
//		if((Axis == 4) || (Axis == 5))return 1;
//	}
//	else if(MCTYPE == MCT400)
//	{
//		if(Axis == 5)return 1;
//	}
	pulse = mm(Inch)*SP.AxisGear[Axis-1];
	speed[0] = mm(Start)/60.*SP.AxisGear[Axis-1];
	speed[1] = mm(Acc)*SP.AxisGear[Axis-1];
	speed[2] = mm(Speed)/60.*SP.AxisGear[Axis-1];
	GetPosDev(&AxisPos[0],&AxisPos[1],&AxisPos[2],&AxisPos[3],&AxisPos[4],&AxisPos[5],&AxisPos[6],&AxisPos[7]);
	SAxisPmove(Axis,pulse,speed[0],speed[1],speed[2]);
	temp = AxisPos[Axis-1]+pulse;
	while(1)
	{
		ModbusServe(0);
		GetMotionStatus(&sta);
		if(sta == 0)break;
		if((DReg[F_PAUSEBTN] == 1) || (ReadInput(STARTIN) == 0))
		{
			SystemPauseLed();
			SAxisDec_stop(Axis);
			while(1)
			{
				ModbusServe(0);
				if((DReg[F_STOPBTN] == 1) || (ReadInput(STOPIN) == 0))return -1;
				if((DReg[F_STARTBTN] == 1) || (ReadInput(STARTIN) == 0))
				{
					SystemRunLed();
					GetPosDev(&AxisPos[0],&AxisPos[1],&AxisPos[2],&AxisPos[3],&AxisPos[4],&AxisPos[5],&AxisPos[6],&AxisPos[7]);
					pulse = temp-AxisPos[Axis-1];
					SAxisPmove(Axis,pulse,speed[0],speed[1],speed[2]);
					break;
				}
			}
		}
		if((DReg[F_STOPBTN] == 1) || (ReadInput(STOPIN) == 0))
		{
			SystemStopLed();
			SAxisDec_stop(Axis);
			while(1)
			{
				ModbusServe(0);
				GetMotionStatus(&sta);
				if(sta == 0)break;
				DispAxisPosition();
				DispWorkMakeTime();
			}
			return -1;
		}
		if(ServoAlarmCheck() == -1)return -1;
		if(LimitPosCheck() == -1)return -1;
		if(LimitInputCheck() == -1)return -1;
		DispWorkMakeTime();
	}
	SystemStopLed();
	return 1;
}
/****************************************************************************************
Function :  axis stop move
Parameter:  
Return   :  
****************************************************************************************/
void MotionStop(void)
{
	unsigned long sta;
	
	while(1)
	{
		ModbusServe(0);
		GetMotionStatus(&sta);
		if(sta == 0)break;
		DispInput();
		DispOutput();		
		if(LimitInputCheck() == -1)return;
		if(ServoAlarmCheck() == -1)return;
		DispAxisPosition();					
		if(DispFlag)DispPowerOnTime();
	}
}
/****************************************************************************************
Function :  get machine position (unit: mm)
Parameter:  Axis    :axis number
Return   :
****************************************************************************************/
float GetMacPosMm(uint8_t Axis)
{
	long AxisPos[8];
	float ftemp;
	
	GetPosDev(&AxisPos[0],&AxisPos[1],&AxisPos[2],&AxisPos[3],&AxisPos[4],&AxisPos[5],&AxisPos[6],&AxisPos[7]);
	ftemp = AxisPos[Axis-1]*SP.AxisInch[Axis-1]/1.0/SP.AxisPulse[Axis-1];
	
	return ftemp;
}
/****************************************************************************************
Function :  display machine position on the MCGS screen by DReg[] register
Parameter:  
Return   :
****************************************************************************************/
void DispAxisPosition(void)
{
	float ftemp[5];
	
	GetPosDev(&AxisPos[0],&AxisPos[1],&AxisPos[2],&AxisPos[3],&AxisPos[4],&AxisPos[5],&AxisPos[6],&AxisPos[7]);
	
	ftemp[0] = AxisPos[0]*SP.AxisInch[0]/1.0/SP.AxisPulse[0];
	memcpy(&DReg[F_AXISPOSX],&ftemp[0],sizeof(float));
	ftemp[1] = AxisPos[1]*SP.AxisInch[1]/1.0/SP.AxisPulse[1];
	memcpy(&DReg[F_AXISPOSY],&ftemp[1],sizeof(float));
	ftemp[2] = AxisPos[2]*SP.AxisInch[2]/1.0/SP.AxisPulse[2];
	memcpy(&DReg[F_AXISPOSZ],&ftemp[2],sizeof(float));
	ftemp[3] = AxisPos[3]*SP.AxisInch[3]/1.0/SP.AxisPulse[3];
	memcpy(&DReg[F_AXISPOSA],&ftemp[3],sizeof(float));
	ftemp[4] = AxisPos[4]*SP.AxisInch[4]/1.0/SP.AxisPulse[4];
	memcpy(&DReg[F_AXISPOSB],&ftemp[4],sizeof(float));
	DispPowerOnTime();
}
/****************************************************************************************
Function :  axes move setting inch 
Parameter:  Axis    :motion of the axes, for example [1,2,0,0,5] meaning axis-X, axis-Y
                     and axis-B will move (Note: axis is stored in order)
			Inch    :moving distance, for example axis[1,2,0,0,5] move [100,200,0,0,600]
			         (unit: mm  Note: inch is stored in order)  
Return   :
****************************************************************************************/
int8_t G00RelPosAll(uint8_t Axis[],float Inch[])
{
	unsigned long sta;
	long i,speed[5][3];	
	long AxisPos[8],temp[5],Pulse[5];
	long Start[5],Acc[5],Speed[5];
	
	UpdateAxisParam();
	for(i=0;i<5;i++)
	{
//		if(MCTYPE == MCT300)
//		{
//			if((Axis[i] == 4) || (Axis[i] == 5))continue;
//		}
//		else if(MCTYPE == MCT400)
//		{
//			if(Axis[i] == 5)continue;
//		}
		if(Axis[i] == (i+1))                    // check storing axis number valid or not 
		{
			SetMakeSpeed(Axis[i],speed[i]);
			Pulse[i] = mm(Inch[i])*SP.AxisGear[i];            // inch (unit: mm)
			Start[i] = mm(speed[i][0])/60.*SP.AxisGear[i];    // speed (unit: mm/min)
			Acc[i]   = mm(speed[i][1])*SP.AxisGear[i];        // speed (unit: mm/min)
			Speed[i] = mm(speed[i][2])/60.*SP.AxisGear[i];    // speed (unit: mm/min)
		}
	}
	GetPosDev(&AxisPos[0],&AxisPos[1],&AxisPos[2],&AxisPos[3],&AxisPos[4],&AxisPos[5],&AxisPos[6],&AxisPos[7]);
	for(i=0;i<5;i++)
	{
//		if(MCTYPE == MCT300)
//		{
//			if((Axis[i] == 4) || (Axis[i] == 5))continue;
//		}
//		else if(MCTYPE == MCT400)
//		{
//			if(Axis[i] == 5)continue;
//		}
		if(Axis[i] == (i+1))                   // check storing axis number valid or not
		{
			SAxisPmove(Axis[i],Pulse[i],Start[i],Acc[i],Speed[i]);
			temp[i] = AxisPos[i]+Pulse[i];
		}
	}
	
	while(1)
	{
		ModbusServe(0);
		GetMotionStatus(&sta);
		if(sta == 0)break;
		if((DReg[F_PAUSEBTN] == 1) || (ReadInput(STARTIN) == 0))
		{
			SystemPauseLed();
			DReg[F_SYSTEMSTATE] = 2;
			for(i=0;i<5;i++)
			{
				if(Axis[i] == (i+1))           // check storing axis number valid or not
				{
					SAxisDec_stop(i+1);
				}
			}
			while(1)
			{
				ModbusServe(0);
				if((DReg[F_STOPBTN] == 1) || (ReadInput(STOPIN) == 0))
				{
					SystemStopLed();
					StopFlag = 1;
					return -1;
				}
				if((DReg[F_STARTBTN] == 1) || (ReadInput(STARTIN) == 0))
				{
					SystemRunLed();
					GetPosDev(&AxisPos[0],&AxisPos[1],&AxisPos[2],&AxisPos[3],&AxisPos[4],&AxisPos[5],&AxisPos[6],&AxisPos[7]);
					for(i=0;i<5;i++)
					{
						if(Axis[i] == (i+1))   // check storing axis number valid or not
						{
							Pulse[Axis[i]-1] = temp[Axis[i]-1]-AxisPos[Axis[i]-1];
							SAxisPmove(Axis[i],Pulse[Axis[i]-1],Start[Axis[i]-1],Acc[Axis[i]-1],Speed[Axis[i]-1]);
						}
					}
					break;
				}
				if(DReg[F_FILESAVE] == 1)
				{
					DReg[F_FILESAVE] = 0;
					ParamSave();
				}
				UserValueCrcCheck();
			}
		}
		if((DReg[F_STOPBTN] == 1) || (ReadInput(STOPIN) == 0))
		{
			SystemStopLed();
			for(i=0;i<5;i++)
			{
				if(Axis[i] == (i+1))           // check storing axis number valid or not
				{
					SAxisDec_stop(i+1);
				}
			}
			while(1)
			{
				ModbusServe(0);
				GetMotionStatus(&sta);
				if(sta == 0)break;
				DispAxisPosition();
				DispWorkMakeTime();
			}
			StopFlag = 1;
			return -1;
		}
		if(DReg[F_FILESAVE] == 1)
		{
			DReg[F_FILESAVE] = 0;
			ParamSave();
		}
		DispAxisPosition();
		DispInput();
		DispOutput();		
		if(LimitInputCheck() == -1)return -1;
		if(LimitPosCheck() == -1)return -1;
		if(ServoAlarmCheck() == -1)return -1;
		RatePlusMinus();
		DispWorkMakeTime();
		if(NowTime%50 == 0)
		{
			UserValueCrcCheck();
		}
	}
	SystemStopLed();
	return 1;
}
/****************************************************************************************
Function :	rapid speed
Parameter:   
Return   :
****************************************************************************************/
float GetMinAxisGear(uint8_t Axis[])
{
	uint16_t i;
	float MinGear;

	UpdateAxisParam();
	MinGear = SP.AxisUnit[0];
	for(i=0;i<5;i++)
	{
		if(Axis[i])
		{
			if((int16_t)(MinGear*1000) > (int16_t)(SP.AxisUnit[i]*1000))
			{
				MinGear = SP.AxisUnit[i];
			}
		}
	}
	return MinGear;
}
/****************************************************************************************
Function :  axes move setting inch by interpolation
Parameter:  Axis    :motion of the axes, for example [1,2,0,0,5] meaning axis-X, axis-Y
                     and axis-B will move (Note: axis is stored in order)
			Inch    :moving distance, for example axis[1,2,0,0,5] move [100,200,0,0,600]
			         (unit: mm  Note: inch is stored in order)  
Return   :
****************************************************************************************/
int8_t G01RelPos(uint8_t Axis[],float Inch[],unsigned long InpSpeed[4])
{
	unsigned long i,sta;
	uint8_t AxisFlag[5],reg;		
	unsigned long speed[5],pulse[5];
	float temp;	

	UpdateAxisParam();
	for(i=0;i<5;i++)
	{
		AxisFlag[i] = 0;
		pulse[i] = 0;
	}
	if(Axis[0] == 1)AxisFlag[0] = 1;
	if(Axis[1] == 2)AxisFlag[1] = 1;
	if(Axis[2] == 3)AxisFlag[2] = 1;
	if(Axis[3] == 4)AxisFlag[3] = 1;
	if(Axis[4] == 5)AxisFlag[4] = 1;
	SetMoveTogetherMode(AxisFlag[0],AxisFlag[1],AxisFlag[2],AxisFlag[3],AxisFlag[4]);
	BufStop();
	LayoutStart(0);
	speed[0] = InpSpeed[0]/60.;
	speed[1] = InpSpeed[1]/60.;
	speed[2] = InpSpeed[2]/60.;
	speed[3] = InpSpeed[3]*0.8/60.;
	if(AxisFlag[0] == 1)pulse[0] = mm(Inch[0])*SP.AxisGear[0];
	if(AxisFlag[1] == 2)pulse[1] = mm(Inch[1])*SP.AxisGear[1];
	if(AxisFlag[2] == 3)pulse[2] = mm(Inch[2])*SP.AxisGear[2];
	if(AxisFlag[3] == 4)pulse[3] = mm(Inch[3])*SP.AxisGear[3];
	if(AxisFlag[4] == 5)pulse[4] = mm(Inch[4])*SP.AxisGear[4];
	MotionConfig(speed[0],speed[0],speed[1],speed[2],speed[3]);
	LayoutStart(0);
	Line[0].LineIndex = 0;
	Line[0].Speed = speed[2]*temp;
	if(AxisFlag[0] == 1)Line[0].X = pulse[0];
	if(AxisFlag[1] == 1)Line[0].Y = pulse[1];
	if(AxisFlag[2] == 1)Line[0].Z = pulse[2];
	if(AxisFlag[3] == 1)Line[0].U = pulse[3];
	if(AxisFlag[4] == 1)Line[0].V = pulse[4];
	BatchLine(Line,0,1,&reg);
	LocusEnd(0);
	LayoutStart(1);
	while(1)
	{
		ModbusServe(0);
		GetMotionStatus(&sta);
		if(sta == 0)break;
		if((DReg[F_PAUSEBTN] == 1) || (ReadInput(STARTIN) == 0))
		{
			if(AxisFlag[0] == 1)SAxisDec_stop(1);
			if(AxisFlag[1] == 1)SAxisDec_stop(2);
			if(AxisFlag[2] == 1)SAxisDec_stop(3);
			if(AxisFlag[3] == 1)SAxisDec_stop(3);
			if(AxisFlag[4] == 1)SAxisDec_stop(4);
			while(1)
			{
				ModbusServe(0);
				if((DReg[F_STOPBTN] == 1) || (ReadInput(STOPIN) == 0))return -1;
				if((DReg[F_STARTBTN] == 1) || (ReadInput(STARTIN) == 0))
				{
					LayoutStart(0);
					Line[0].LineIndex = 0;
					Line[0].Speed = speed[2]*temp;
					if(AxisFlag[0] == 1)Line[0].X = pulse[0];
					if(AxisFlag[1] == 1)Line[0].Y = pulse[1];
					if(AxisFlag[2] == 1)Line[0].Z = pulse[2];
					if(AxisFlag[3] == 1)Line[0].U = pulse[3];
					if(AxisFlag[4] == 1)Line[0].V = pulse[4];
					BatchLine(Line,0,1,&reg);
					LocusEnd(0);
					LayoutStart(1);
					break;
				}
			}
		}
		if((DReg[F_STOPBTN] == 1) || (ReadInput(STOPIN) == 0))
		{
			if(AxisFlag[0] == 1)SAxisDec_stop(1);
			if(AxisFlag[1] == 1)SAxisDec_stop(2);
			if(AxisFlag[2] == 1)SAxisDec_stop(3);
			if(AxisFlag[3] == 1)SAxisDec_stop(3);
			if(AxisFlag[4] == 1)SAxisDec_stop(4);
			while(1)
			{
				ModbusServe(0);
				GetMotionStatus(&sta);
				if(sta == 0)break;
				DispAxisPosition();
				DispWorkMakeTime();
			}
			return -1;
		}
		OSDelay(2);
		DispAxisPosition();
		DispWorkMakeTime();
	}
	BufStop();
	return 1;
}
/****************************************************************************************

****************************************************************************************/
int8_t G00RelPosWaitInput(uint8_t Axis,float Inch,long Start,long Acc,long Speed,uint8_t ReactIn)
{
	long pulse;
	float temp1,temp2;
	unsigned long speed[3];
	unsigned long sta;
	long AxisPos[8],temp;
	
	memcpy(&temp1,&DReg[F_AXISINCHX+(Axis-1)*2],sizeof(float));
	temp2 = DReg[F_AXISPULSEX+(Axis-1)]/(temp1*1000);
	pulse = mm(Inch)*temp2;
	speed[0] = mm(Start)/60.*temp2;
	speed[1] = mm(Acc)*temp2;
	speed[2] = mm(Speed)/60.*temp2;
	GetPosDev(&AxisPos[0],&AxisPos[1],&AxisPos[2],&AxisPos[3],&AxisPos[4],&AxisPos[5],&AxisPos[6],&AxisPos[7]);
	SAxisPmove(Axis,pulse,speed[0],speed[1],speed[2]);
	temp = AxisPos[Axis-1]+pulse;
	while(1)
	{
		ModbusServe(0);
		GetMotionStatus(&sta);
		if(sta == 0)break;
		if(ReadInput(ReactIn) == 0)break;
		if((DReg[F_PAUSEBTN] == 1) || (ReadInput(STARTIN) == 0))
		{
			SAxisDec_stop(Axis);
			while(1)
			{
				ModbusServe(0);
				if((DReg[F_STOPBTN] == 1) || (ReadInput(STOPIN) == 0))return -1;
				if((DReg[F_STARTBTN] == 1) || (ReadInput(STARTIN) == 0))
				{
					GetPosDev(&AxisPos[0],&AxisPos[1],&AxisPos[2],&AxisPos[3],&AxisPos[4],&AxisPos[5],&AxisPos[6],&AxisPos[7]);
					pulse = temp-AxisPos[Axis-1];
					SAxisPmove(Axis,pulse,speed[0],speed[1],speed[2]);
					if(ReadInput(ReactIn) == 0)break;
					break;
				}
			}
		}
		if((DReg[F_STOPBTN] == 1) || (ReadInput(STOPIN) == 0))
		{
			SAxisDec_stop(Axis);
			while(1)
			{
				ModbusServe(0);
				GetMotionStatus(&sta);
				if(sta == 0)break;
				if(ReadInput(ReactIn) == 0)break;
				DispAxisPosition();
				DispWorkMakeTime();
			}
			return -1;
		}
		if(ServoAlarmCheck() == -1)return -1;
		if(LimitPosCheck() == -1)return -1;
		if(LimitInputCheck() == -1)return -1;
		DispAxisPosition();
		DispWorkMakeTime();
	}
	return 1;
}
/****************************************************************************************
Function :	get axes gear and axes equivalent, and update rotate pulse, rotate inch, 
            positive limit position and negative limit position
Parameter:   
Return   :
****************************************************************************************/
extern float LimitPos[5],LimitNeg[5];
void UpdateAxisParam(void)
{
	unsigned short dir;
	
	memcpy(&SP.AxisInch[0],&DReg[F_AXISINCHX],sizeof(float));
	memcpy(&SP.AxisInch[1],&DReg[F_AXISINCHY],sizeof(float));
	memcpy(&SP.AxisInch[2],&DReg[F_AXISINCHZ],sizeof(float));
	memcpy(&SP.AxisInch[3],&DReg[F_AXISINCHA],sizeof(float));
	memcpy(&SP.AxisInch[4],&DReg[F_AXISINCHB],sizeof(float));
	SP.AxisPulse[0] = DReg[F_AXISPULSEX];
	SP.AxisPulse[1] = DReg[F_AXISPULSEY];
	SP.AxisPulse[2] = DReg[F_AXISPULSEZ];
	SP.AxisPulse[3] = DReg[F_AXISPULSEA];
	SP.AxisPulse[4] = DReg[F_AXISPULSEB];
	
	SP.AxisGear[0] = SP.AxisPulse[0]/(SP.AxisInch[0]*1000);
	SP.AxisGear[1] = SP.AxisPulse[1]/(SP.AxisInch[1]*1000);
	SP.AxisGear[2] = SP.AxisPulse[2]/(SP.AxisInch[2]*1000);
	SP.AxisGear[3] = SP.AxisPulse[3]/(SP.AxisInch[3]*1000);
	SP.AxisGear[4] = SP.AxisPulse[4]/(SP.AxisInch[4]*1000);
	SP.AxisUnit[0] = SP.AxisInch[0]/SP.AxisPulse[0];
	SP.AxisUnit[1] = SP.AxisInch[1]/SP.AxisPulse[1];
	SP.AxisUnit[2] = SP.AxisInch[2]/SP.AxisPulse[2];
	SP.AxisUnit[3] = SP.AxisInch[3]/SP.AxisPulse[3];
	SP.AxisUnit[4] = SP.AxisInch[4]/SP.AxisPulse[4];

	memcpy(&LimitPos[0],&DReg[F_POSLMTX],sizeof(float));
	memcpy(&LimitPos[1],&DReg[F_POSLMTY],sizeof(float));
	memcpy(&LimitPos[2],&DReg[F_POSLMTZ],sizeof(float));
	memcpy(&LimitPos[3],&DReg[F_POSLMTA],sizeof(float));
	memcpy(&LimitPos[4],&DReg[F_POSLMTB],sizeof(float));
	memcpy(&LimitNeg[0],&DReg[F_NEGLMTX],sizeof(float));
	memcpy(&LimitNeg[1],&DReg[F_NEGLMTY],sizeof(float));
	memcpy(&LimitNeg[2],&DReg[F_NEGLMTZ],sizeof(float));
	memcpy(&LimitNeg[3],&DReg[F_NEGLMTA],sizeof(float));
	memcpy(&LimitNeg[4],&DReg[F_NEGLMTB],sizeof(float));
	SP.LimitPos[0] = LimitPos[0];
	SP.LimitPos[1] = LimitPos[1];
	SP.LimitPos[2] = LimitPos[2];
	SP.LimitPos[3] = LimitPos[3];
	SP.LimitPos[4] = LimitPos[4];
	SP.LimitNeg[0] = LimitNeg[0];
	SP.LimitNeg[1] = LimitNeg[1];
	SP.LimitNeg[2] = LimitNeg[2];
	SP.LimitNeg[3] = LimitNeg[3];
	SP.LimitNeg[4] = LimitNeg[4];
	if((StartFlag == 0) || (DReg[F_AUTOMANUAL] == 0))
	{
		dir = 0x0000;
		if(DReg[F_AXISDIRX] == 0)dir &= 0x80F0;
		else dir |= 0x0010;
		if(DReg[F_AXISDIRY] == 0)dir &= 0x80F0;
		else dir |= 0x0020;
		if(DReg[F_AXISDIRZ] == 0)dir &= 0x80F0;
		else dir |= 0x0040;
		if(DReg[F_AXISDIRA] == 0)dir &= 0x80F0;
		else dir |= 0x0080;
		if(DReg[F_AXISDIRB] == 0)dir &= 0x80F0;
		else dir |= 0x8000;
		SetMotionDir(dir);
	}
}

