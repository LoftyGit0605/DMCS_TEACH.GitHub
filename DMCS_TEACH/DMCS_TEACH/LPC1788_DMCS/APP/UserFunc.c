#include "Base.h"

FIL    SD;
extern long AxisPos[];
extern char crcPath[];
extern uint16_t crc_temp;
extern uint16_t crc_value;
extern unsigned short DReg[];
extern uint16_t lineBit,tempLineBit;
extern struct LayoutCmd_PC Line[];
extern int8_t ServoAlarmCheck(void);
/****************************************************************************************
Function :	init the register using in project
Parameter:   		
Return   :
****************************************************************************************/
void InitSysParam(void)
{
	int i;
	float temp;
	
	for(i=0;i<10000;i++)DReg[i] = 0;
	// MainScreen
	DReg[F_TOTALNUM] = 0;                    // make total number
	DReg[F_TIMEHOUR] = 0;                    // make time hour
	DReg[F_TIMEMINUTE] = 0;                  // make time minute
	DReg[F_TIMESECOND] = 0;                  // make time second
	DReg[F_MAKESELECT] = 0;                  // make mode select (0:CAD 1:Teach)
	DReg[F_SYSTEMSTATE] = 0;                 // system state information
	DReg[F_MANUALRATE] = 100;                // manual move rate (default: 100%)
	DReg[F_AUTORATE] = 100;                  // auto move rate (default: 100%)
	DReg[F_MOVEMODE] = 0;                    // move setting inch mode (0:relative 1:absolute)
	DReg[F_MAKETIME] = 0;                    // work make time (unit: sec)
	DReg[F_STARTBTN] = 0;                    // machine start button
	DReg[F_PAUSEBTN] = 0;                    // machine pause button
	DReg[F_RESETBTN] = 0;                    // machine reset button
	DReg[F_STOPBTN] = 0;                     // machine stop button	
	// ManualScreen
	for(i=0;i<5;i++)
	{
		DReg[F_HOMEBTNX+i] = 0;              // axes search home button
		DReg[F_MANUALPOSX+i] = 0;            // axes manual run to positive button
		DReg[F_MANUALNEGX+i] = 0;            // axes manual run to negative button
		DReg[F_HOMEFLAGX+i] = 0;             // axes home flag
		DReg[F_BTNINCHX+i] = 0;              // axes move setting inch button		
		memcpy(&DReg[F_SETINCHX+2*i],&SP.SetInch[i],sizeof(float));// axes move setting inch
		memcpy(&DReg[F_AXISPOSX+2*i],&SP.AxisPos[i],sizeof(float));// axes coord value
	}
	// TeachScreen
	DReg[F_G00MODE] = 0;                     // G00 mode button
	DReg[F_G01MODE] = 0;                     // G01 mode button
	DReg[F_OUTPUTMODE] = 0;                  // output mode button
	DReg[F_INPUTMODE] = 0;                   // input mode button
	DReg[F_DELAYMODE] = 0;                   // delay mode button
	DReg[F_ARCMODE] = 0;                     // arc mode button
	DReg[F_FUNCMODE] = 0;                    // func mode button
	DReg[F_FILENAME] = 5;                    // param file name
	DReg[F_FILELOAD] = 0;                    // param file load button
	DReg[F_FILESAVE] = 0;                    // param file save button
	DReg[F_CURPAGE] = 0;                     // param current page number
	DReg[F_TOTALPAGE] = 0;                   // param total page number
	DReg[F_CURLINE] = 0;                     // param current line number
	DReg[F_TOTALLINE] = 0;                   // param total line number
	DReg[F_INOUTBTN] = 0;                    // input or output select button
	DReg[F_INOUTNUM] = 0;                    // output/input port number
	DReg[F_INOUTLEVEL] = 0;                  // output/input port level
	DReg[F_CONTINUEBTN] = 0;                 // continue run or single run (0:continue 1:single)
	DReg[F_MANUALBTN] = 0;                   // select manual speed (0:middle 1:low 2:high)
	DReg[F_RUNLINE] = 0;                     // from setting line run (0:invalid 1:valid)
	DReg[F_SPINDLERATE] = 100;               // spindle rate init value
	DReg[F_SPINDLEPLUS] = 0;                 // spindle rate plus button
	DReg[F_SPINDLEMINUS] = 0;                // spindle rate minus button
	DReg[F_MAKERATE] = 100;                  // make rate init value
	DReg[F_MAKEPLUS] = 0;                    // make rate plus button
	DReg[F_MAKEMINUS] = 0;                   // make rate minus button
	DReg[F_INSERTBTN] = 0;                   // insert empty line into teach table
	DReg[F_DELETEBTN] = 0;                   // delete line from teach table
	DReg[F_HELPBTN] = 0;                     // display help information
	DReg[F_INPSPEED] = 2000;                 // defalut interpolation speed for making
	DReg[F_DELAYTIME] = 1000;                // delay time (uint: ms)
	DReg[F_ARCINSERTBTN] = 0;                // arc command insert button
	DReg[F_IOINSERTBTN] = 0;                 // IO command insert button
	DReg[F_COORDINSERTBTN] = 0;              // coord command insert button
	DReg[F_FUNCINSERTBTN] = 0;               // func command insert button
	DReg[F_DELAYINSERTBTN] = 0;              // delay command insert button
	DReg[F_TEACHCLEARBTN] = 0;               // clear all teach table param
	DReg[F_TEACHLINE01] = 1;                 // teach line cursor init
	for(i=1;i<10;i++)
	{
		DReg[F_TEACHLINE01+i] = 0;
	}
	// Param1Screen
	for(i=0;i<5;i++)
	{
		DReg[F_HOMESPEEDX+i] = SP.HomeSpeed[i];// search home speed
		DReg[F_MAKESTARTX+i] = SP.MakeStart[i];// make start speed
		DReg[F_MAKEADDX+i] = SP.MakeAcc[i];    // make acc speed
		DReg[F_MAKESPEEDX+i] = SP.MakeSpeed[i];// make final speed
		DReg[F_MANSPEED1X+i] = SP.HandStart[i];// manual start speed
		DReg[F_MANSPEED2X+i] = SP.HandSpeed[i];// manual final speed
		DReg[F_HOMEDIRX+i] = SP.HomeDir[i];    // search home direction
		DReg[F_AXISDIRX+i] = 0;                // axes pulse direction
		DReg[F_HOMETYPEX+i] = 0;               // axes search type (0:machine 1:program)		
		memcpy(&DReg[F_OFFSETHOMEX+2*i],&SP.HomeOffset[i],sizeof(float));
	}
	DReg[F_INPSTARTSPEED] = 1000;
	DReg[F_INPADDSPEED] = 650;
	DReg[F_INPENDSPEED] = 3000;
	DReg[F_INPMAXSPEED] = 10000;
	if(MCTYPE == MCT300)
	{
		DReg[F_HOMEORDER] = 31200;
	}
	else if(MCTYPE == MCT400)
	{
		DReg[F_HOMEORDER] = 31240;
	}
	else
	{
		DReg[F_HOMEORDER] = 31245;
	}
	// Param2Screen
	for(i=0;i<5;i++)
	{
		DReg[F_AXISPULSEX+i] = SP.AxisPulse[i];
		memcpy(&DReg[F_AXISINCHX+2*i],&SP.AxisInch[i],sizeof(float));
		memcpy(&DReg[F_POSLMTX+4*i],&SP.LimitPos[i],sizeof(float));
		memcpy(&DReg[F_NEGLMTX+4*i],&SP.LimitNeg[i],sizeof(float));
	}
	// TeachScreen
	temp = 0.0;
	for(i=0;i<MAXLINENUM;i++)
	{
		DReg[F_MAKEMODE000+i] = 0;
		memcpy(&DReg[F_MAKEDATA1000+2*i],&temp,sizeof(float));
		memcpy(&DReg[F_MAKEDATA2000+2*i],&temp,sizeof(float));
		memcpy(&DReg[F_MAKEDATA3000+2*i],&temp,sizeof(float));
		memcpy(&DReg[F_MAKEDATA4000+2*i],&temp,sizeof(float));
		memcpy(&DReg[F_MAKEDATA5000+2*i],&temp,sizeof(float));
		memcpy(&DReg[F_MAKEDATA6000+2*i],&temp,sizeof(float));
	}
}
/****************************************************************************************
Function :	init the temp value using in project
Parameter:   		
Return   :
****************************************************************************************/
void InitSysParamTemp(void)
{
	int i;
/*	// MainScreen
	SP.TotalNum = 0;             // make total number
	SP.MakeHour = 0;             // make time hour
	SP.MakeMinute = 0;           // make time minute
	SP.MakeSecond = 0;           // make time second
	SP.MakeSelect = 0;           // make mode select (0:CAD 1:Teach)
	SP.SystemState = 0;          // system state information
	SP.ManualRate = 100;         // manual move rate (default: 100%)
	SP.AutoRate = 100;           // auto move rate (default: 100%)
	SP.MoveMode = 0;             // move setting inch mode (0:relative 1:absolute)
	SP.MakeTime = 0;             // work make time (unit: sec)
	// TeachScreen
	SP.FileName = 0;             // param file name
	SP.CurPage = 0;              // param current page number init value
	SP.TotalPage = 0;            // param total page number init value
	SP.CurLine = 0;              // param current line number init value
	SP.TotalLine = 0;            // param total line number init value
	SP.OutputNum = 0;            // output/input port number
	SP.OutputLevel = 0;          // output/input port level
	SP.RunLine = 0;              // from setting line run (0:invalid 1:valid)
	SP.SpindleRate = 100;        // spindle rate init value
	SP.MakeRate = 100;           // make rate init value
	SP.InpSpeed = 2000;          // defalut interpolation speed for making
	SP.DelayTime =  1000;        // delay time (uint: ms)*/
	// ManualScreen
	for(i=0;i<5;i++)
	{
		SP.HomeFlag[i] = 0;      // axes home flag init value
		SP.SetInch[i] = 0.0;     // axes move setting inch init value
		SP.AxisPos[i] = 0.0;     // axes coord init value
	}
	// ParamScreen1
	SP.HomeSpeed[0] = 100;
	SP.HomeSpeed[1] = 100;
	SP.HomeSpeed[2] = 100;
	SP.HomeSpeed[3] = 100;
	SP.HomeSpeed[4] = 100;

	SP.MakeStart[0] = 500;
	SP.MakeStart[1] = 500;
	SP.MakeStart[2] = 500;
	SP.MakeStart[3] = 500;
	SP.MakeStart[4] = 500;
	
	SP.MakeAcc[0] = 750;
	SP.MakeAcc[1] = 750;
	SP.MakeAcc[2] = 750;
	SP.MakeAcc[3] = 750;
	SP.MakeAcc[4] = 750;
	
	SP.MakeSpeed[0] = 1500;
	SP.MakeSpeed[1] = 1500;
	SP.MakeSpeed[2] = 1500;
	SP.MakeSpeed[3] = 1500;
	SP.MakeSpeed[4] = 1500;

	SP.HandStart[0] = 50;
	SP.HandStart[1] = 50;
	SP.HandStart[2] = 50;
	SP.HandStart[3] = 50;
	SP.HandStart[4] = 50;
	
	SP.HandSpeed[0] = 3000;
	SP.HandSpeed[1] = 3000;
	SP.HandSpeed[2] = 3000;
	SP.HandSpeed[3] = 3000;
	SP.HandSpeed[4] = 3000;
	
	SP.HomeDir[0] = 0;
	SP.HomeDir[1] = 0;
	SP.HomeDir[2] = 0;
	SP.HomeDir[3] = 0;
	SP.HomeDir[4] = 0;

	SP.HomeOffset[0] = 0.0;
	SP.HomeOffset[1] = 0.0;
	SP.HomeOffset[2] = 0.0;
	SP.HomeOffset[3] = 0.0;
	SP.HomeOffset[4] = 0.0;
	
	SP.InpStart = 1500;
	SP.InpAcc = 750;
	SP.InpEnd = 3000;

	// ParamScreen2
	SP.AxisPulse[0] = 10000;
	SP.AxisPulse[1] = 10000;
	SP.AxisPulse[2] = 10000;
	SP.AxisPulse[3] = 10000;
	SP.AxisPulse[4] = 10000;

	SP.AxisInch[0] = 2.0;
	SP.AxisInch[1] = 2.0;
	SP.AxisInch[2] = 2.0;
	SP.AxisInch[3] = 2.0;
	SP.AxisInch[4] = 2.0;

	SP.LimitPos[0] = 9000.0;
	SP.LimitNeg[0] = -9000.0;
	SP.LimitPos[1] = 9000.0;
	SP.LimitNeg[1] = -9000.0;
	SP.LimitPos[2] = 9000.0;
	SP.LimitNeg[2] = -9000.0;
	SP.LimitPos[3] = 9000.0;
	SP.LimitNeg[3] = -9000.0;
	SP.LimitPos[4] = 9000.0;
	SP.LimitNeg[4] = -9000.0;

	SP.AxisGear[0] = SP.AxisPulse[0]/(SP.AxisInch[0]*1000);
	SP.AxisGear[1] = SP.AxisPulse[1]/(SP.AxisInch[1]*1000);
	SP.AxisGear[2] = SP.AxisPulse[2]/(SP.AxisInch[2]*1000);
	SP.AxisGear[3] = SP.AxisPulse[3]/(SP.AxisInch[3]*1000);
	SP.AxisGear[4] = SP.AxisPulse[4]/(SP.AxisInch[4]*1000);
	// IOScreen
	SP.StartIN = 24;             // start input
	SP.AlarmIN = 25;             // alarm input
	SP.ResetIN = 26;             // reset input
	SP.StopIN = 27;              // stop input
	SP.HomeIN[0] = 22;           // axis-X home input
	SP.HomeIN[1] = 19;           // axis-Y home input
	SP.HomeIN[2] = 16;           // axis-Z home input
	SP.HomeIN[3] = 13;           // axis-A home input
	SP.HomeIN[4] = 10;           // axis-B home input
	SP.LimitPosIN[0] = 21;       // axis-X positive limit input
	SP.LimitNegIN[0] = 23;       // axis-X negative limit input
	SP.LimitPosIN[1] = 18;       // axis-Y positive limit input
	SP.LimitNegIN[1] = 20;       // axis-Y negative limit input
	SP.LimitPosIN[2] = 15;       // axis-Z positive limit input
	SP.LimitNegIN[2] = 17;       // axis-Z negative limit input
	SP.LimitPosIN[3] = 12;       // axis-A positive limit input
	SP.LimitNegIN[3] = 14;       // axis-A negative limit input
	SP.LimitPosIN[4] = 9;        // axis-B positive limit input
	SP.LimitNegIN[4] = 11;       // axis-B negative limit input
	SP.GenInput[0] = 4;          // general input01 map value
	SP.GenInput[1] = 5;          // general input02 map value
	SP.GenInput[2] = 6;          // general input03 map value
	SP.GenInput[3] = 7;          // general input04 map value
	SP.GenInput[4] = 0;          // general input05 map value
	SP.GenInput[5] = 1;          // general input06 map value
	SP.GenInput[6] = 2;          // general input07 map value
	SP.GenInput[7] = 3;          // general input08 map value
	SP.GenInput[8] = 8;          // general input09 map value
/*	SP.GenOutput[0] = 0;         // general output01 map value
	SP.GenOutput[1] = 1;         // general output02 map value
	SP.GenOutput[2] = 2;         // general output03 map value
	SP.GenOutput[3] = 3;         // general output04 map value
	SP.GenOutput[4] = 12;        // general output05 map value
	SP.GenOutput[5] = 13;        // general output06 map value
	SP.GenOutput[6] = 14;        // general output07 map value
	SP.GenOutput[7] = 15;        // general output08 map value
	SP.GenOutput[8] = 8;         // general output09 map value
	SP.GenOutput[9] = 9;         // general output10 map value
	SP.GenOutput[10] = 10;       // general output11 map value
	SP.GenOutput[11] = 11;       // general output12 map value
	SP.GenOutput[12] = 4;        // general output13 map value
	SP.GenOutput[13] = 5;        // general output14 map value
	SP.GenOutput[14] = 6;        // general output15 map value
	SP.GenOutput[15] = 7;        // general output16 map value*/
	SP.GenOutput[0] = 0;         // general output01 map value
	SP.GenOutput[1] = 1;         // general output02 map value
	SP.GenOutput[2] = 2;         // general output03 map value
	SP.GenOutput[3] = 3;         // general output04 map value
	SP.GenOutput[4] = 4;         // general output05 map value
	SP.GenOutput[5] = 5;         // general output06 map value
	SP.GenOutput[6] = 6;         // general output07 map value
	SP.GenOutput[7] = 7;         // general output08 map value
	SP.GenOutput[8] = 8;         // general output09 map value
	SP.GenOutput[9] = 9;         // general output10 map value
	SP.GenOutput[10] = 10;       // general output11 map value
	SP.GenOutput[11] = 11;       // general output12 map value
	SP.GenOutput[12] = 12;       // general output13 map value
	SP.GenOutput[13] = 13;       // general output14 map value
	SP.GenOutput[14] = 14;       // general output15 map value
	SP.GenOutput[15] = 15;       // general output16 map value
}
/****************************************************************************************
Function :  dispaly power on time
Parameter:
Return   :
****************************************************************************************/
void DispPowerOnTime(void)
{
	//display system power time
	tempTime = (NowTime-LastTime)/100;    //get total second
	DReg[F_TIMEHOUR] = tempTime/3600;
	DReg[F_TIMEMINUTE] = tempTime%3600/60;
	DReg[F_TIMESECOND] = tempTime%60;
}
/****************************************************************************************
Function :  get machine position (unit: pulse)
Parameter:  Axis    :axis number
Return   :
****************************************************************************************/
long GetMacPosPulse(uint8_t Axis)
{
	long AxisPos[8];
	GetPosDev(&AxisPos[0],&AxisPos[1],&AxisPos[2],&AxisPos[3],&AxisPos[4],&AxisPos[5],&AxisPos[6],&AxisPos[7]);
	return AxisPos[Axis-1];
}
/****************************************************************************************
Function :  axis move without waitting end
Parameter:  Axis    :axis number
            Inch    :move distance (unit: mm)
            Start   :start speed (unit: mm/min)
            Acc     :accelerate speed
            Speed   :make speed
Return   :
****************************************************************************************/
int8_t G00RelPosNoEnd(uint8_t Axis,float Inch,long Start,long Acc,long Speed)
{
	float temp1,temp2;
	unsigned long speed[3];
	long pulse,AxisPos[8];
	
	memcpy(&temp1,&DReg[F_AXISINCHX+(Axis-1)*2],sizeof(float));
	temp2 = DReg[F_AXISPULSEX+(Axis-1)]/(mm(temp1));
	pulse = mm(Inch)*temp2;
	speed[0] = mm(Start)/60.*temp2;
	speed[1] = mm(Acc)*temp2;
	speed[2] = mm(Speed)/60.*temp2;
	GetPosDev(&AxisPos[0],&AxisPos[1],&AxisPos[2],&AxisPos[3],&AxisPos[4],&AxisPos[5],&AxisPos[6],&AxisPos[7]);
	SAxisPmove(Axis,pulse,speed[0],speed[1],speed[2]);
	return 1;
}
/****************************************************************************************
Function :	param save
Parameter:   
Return   :
****************************************************************************************/
extern FUNCPARAM FPA[100],FPB[100];
void ParamSave(void)
{
	char path[50];
	FRESULT fr;	
	UINT bw;
	
	memset(path,0x00,sizeof(path));
	sprintf(path,"1:/TB%d.TBD",DReg[F_FILENAME]);
	fr = f_open(&SD,path,FA_READ | FA_WRITE | FA_CREATE_ALWAYS);
	if(fr == FR_OK)
	{
		f_write(&SD,&DReg[REGSTART],REGMAXNUM*sizeof(unsigned short),&bw);
	}
	f_close(&SD);
}
/****************************************************************************************
Function :	param load
Parameter:   
Return   :
****************************************************************************************/
void ParamLoad(void)
{
	char path[50];
	FRESULT fr;	
	UINT bw;
	
	memset(path,0x00,sizeof(path));
	sprintf(path,"1:/TB%d.TBD",DReg[F_FILENAME]);
	fr = f_open(&SD,path,FA_READ);
	if(fr == FR_OK)
	{
		f_read(&SD,&DReg[REGSTART],REGMAXNUM*sizeof(unsigned short),&bw);
	}
	f_close(&SD);
}
/****************************************************************************************
Function :	read work mould param
Parameter:   
Return   :
****************************************************************************************/
void ReadWorkParam(void)
{
	uint16_t i,j,k;
	uint16_t file1,file2;
	char path[50];
	//FUNCPARAM temp;
	FRESULT fr;	
	UINT bw;
	
	// init mould AB param
	for(i=0;i<100;i++)
	{
		FPA[i].MakeMode = CM_NULL;
		FPA[i].MakeData1 = 0.0;
		FPA[i].MakeData2 = 0.0;
		FPA[i].MakeData3 = 0.0;
		FPA[i].MakeData4 = 0.0;
		FPA[i].MakeData5 = 0.0;
		FPA[i].MakeData6 = 0.0;
		FPB[i].MakeMode = CM_NULL;
		FPB[i].MakeData1 = 0.0;
		FPB[i].MakeData2 = 0.0;
		FPB[i].MakeData3 = 0.0;
		FPB[i].MakeData4 = 0.0;
		FPB[i].MakeData5 = 0.0;
		FPB[i].MakeData6 = 0.0;
	}
	file1 = DReg[F_MOULDWORKA];
	file2 = DReg[F_MOULDWORKB];
	// save system param
	memset(path,0x00,sizeof(path));
	sprintf(path,"1:/RBak.RBD");
	fr = f_open(&SD,path,FA_READ | FA_WRITE | FA_CREATE_ALWAYS);
	if(fr == FR_OK)
	{
		f_write(&SD,&DReg,REGMAXNUM,&bw);
	}
	f_close(&SD);
	
	// get mould A param
	memset(path,0x00,sizeof(path));
	sprintf(path,"1:/RB%d.RBD",file1);
	fr = f_open(&SD,path,FA_READ);
	if(fr == FR_OK)
	{
		f_read(&SD,&DReg,REGMAXNUM,&bw);
	}
	f_close(&SD);
	
	for(i=1,j=0;i<MAXLINENUM;i++)
	{		
		if(DReg[F_MAKEMODE000+i] == CM_NULL)break;
		if((DReg[F_MAKEMODE000+i] == CM_IN) && (i != 0))break;
		if((DReg[F_MAKEMODE000+i] == CM_IN) && (i == 0))continue;		
		FPA[j].MakeMode = DReg[F_MAKEMODE000+i];
		memcpy(&FPA[j].MakeData1,&DReg[F_MAKEDATA1000+2*i],sizeof(float));
		memcpy(&FPA[j].MakeData2,&DReg[F_MAKEDATA2000+2*i],sizeof(float));
		memcpy(&FPA[j].MakeData3,&DReg[F_MAKEDATA3000+2*i],sizeof(float));
		memcpy(&FPA[j].MakeData4,&DReg[F_MAKEDATA4000+2*i],sizeof(float));
		memcpy(&FPA[j].MakeData5,&DReg[F_MAKEDATA5000+2*i],sizeof(float));
		FPA[j].MakeData6 = DReg[F_MAKEDATA6000+i];
		j++;
	}
	
	memset(path,0x00,sizeof(path));
	sprintf(path,"1:/RB%d.RBD",file2);
	fr = f_open(&SD,path,FA_READ);
	if(fr == FR_OK)
	{
		f_read(&SD,&DReg,REGMAXNUM,&bw);
	}
	f_close(&SD);
	
	for(i=1;i<MAXLINENUM;i++)
	{
		if((DReg[F_MAKEMODE000+i] == CM_IN) && (i != 0))break;
	}
	k = i+1;
	
	// get mould A param
	for(i=k,j=0;i<MAXLINENUM;i++)//
	{
		if(DReg[F_MAKEMODE000+i] == CM_NULL)break;
		FPB[j].MakeMode = DReg[F_MAKEMODE000+i];
		memcpy(&FPB[j].MakeData1,&DReg[F_MAKEDATA1000+2*i],sizeof(float));
		memcpy(&FPB[j].MakeData2,&DReg[F_MAKEDATA2000+2*i],sizeof(float));
		memcpy(&FPB[j].MakeData3,&DReg[F_MAKEDATA3000+2*i],sizeof(float));
		memcpy(&FPB[j].MakeData4,&DReg[F_MAKEDATA4000+2*i],sizeof(float));
		memcpy(&FPB[j].MakeData5,&DReg[F_MAKEDATA5000+2*i],sizeof(float));
		FPB[j].MakeData6 = DReg[F_MAKEDATA6000+i];
		j++;
	}
	
	// read system param
	memset(path,0x00,sizeof(path));
	sprintf(path,"1:/RBak.RBD");
	fr = f_open(&SD,path,FA_READ);
	if(fr == FR_OK)
	{
		f_read(&SD,&DReg,REGMAXNUM,&bw);
	}
	f_close(&SD);
}
/****************************************************************************************
Function :	two axis search home
Parameter:   
Return   :
****************************************************************************************/
int8_t AxisRunToZero(uint8_t Axis1,uint8_t Axis2)
{
	long AxisPos[8],speed[8];
	unsigned long sta;

	GetPosDev(&AxisPos[0],&AxisPos[1],&AxisPos[2],&AxisPos[3],&AxisPos[4],&AxisPos[5],&AxisPos[6],&AxisPos[7]);
	speed[0] = mm(DReg[F_HOMESPEEDX+Axis1-1])*0.4/60.*SP.AxisGear[Axis1-1];
	speed[1] = mm(DReg[F_MAKEADDX+Axis1-1])*SP.AxisGear[Axis1-1];
	speed[2] = mm(DReg[F_HOMESPEEDX+Axis1-1])/60.*SP.AxisGear[Axis1-1];
	speed[3] = mm(DReg[F_HOMESPEEDX+Axis2-1])*0.4/60.*SP.AxisGear[Axis2-1];
	speed[4] = mm(DReg[F_MAKEADDX+Axis2-1])*SP.AxisGear[Axis2-1];
	speed[5] = mm(DReg[F_HOMESPEEDX+Axis2-1])/60.*SP.AxisGear[Axis2-1];
	SAxisPmove(Axis1,-AxisPos[Axis1-1],speed[0],speed[1],speed[2]);
	SAxisPmove(Axis2,-AxisPos[Axis2-1],speed[3],speed[4],speed[5]);
	while(1)
	{
		ModbusServe(0);
		GetMotionStatus(&sta);
		if(sta == 0)break;
		if(DReg[F_STOPBTN] == 1)
		{
			SAxisDec_stop(Axis1);
			SAxisDec_stop(Axis2);
			while(1)
			{
				ModbusServe(0);
				GetMotionStatus(&sta);
				if(sta == 0)break;
				DispAxisPosition();
			}
			return -1;
		}
		UpdateAxisParam();
		DispAxisPosition();
		DispInput();
		DispOutput();		
		if(LimitInputCheck() == -1)return -1;
		if(LimitPosCheck() == -1)return -1;
		if(ServoAlarmCheck() == -1)return -1;
		AxisManualMove();
		MoveSettingInch();
		RatePlusMinus();
//		FastManualSpeed();
		TeachTableParam();
	}
	SetPosDev(Axis1,0);
	SetPosDev(Axis2,0);

	return 1;
}
/****************************************************************************************
Function :  display make time
Parameter:
Return   :
****************************************************************************************/
void DispWorkMakeTime(void)
{
	float ftemp;
	
	if(StartFlag == 1)
	{
		ustemp2 = NowTime-ustemp1;
		ftemp = ustemp2/100.;
		//memcpy(&DReg[F_MAKETIME],&ftemp,sizeof(float));
	}
}
/****************************************************************************************
Function :	place fish-float into uninstall disk
Parameter:   
Return   :
****************************************************************************************/
extern char crcPath1[];
extern char crcPath2[];
extern uint16_t crc_temp;
extern uint16_t crc_value;
void UserValueCrcCheck(void)
{
	FRESULT fr;	
	UINT bw;
	
	// CRC check and save DReg[] real time
	crc_value = UserCRC16((unsigned char *)(&DReg[REGSTART]),REGMAXNUM*sizeof(unsigned short));
	if(crc_temp != crc_value)
	{
		DReg[REGSTART+REGMAXNUM-1] = crc_value;
		// backup param into file1
		fr = f_open(&SD,crcPath1,FA_CREATE_ALWAYS | FA_WRITE | FA_READ);
		if(fr == FR_OK)
		{			
			f_write(&SD,&DReg[REGSTART],REGMAXNUM*sizeof(unsigned short),&bw);			
		}
		f_close(&SD);
		
		ModbusServe(0);    // forbid communication fail
		
		// backup param into file2
		fr = f_open(&SD,crcPath2,FA_CREATE_ALWAYS | FA_WRITE | FA_READ);
		if(fr == FR_OK)
		{
			f_write(&SD,&DReg[REGSTART],REGMAXNUM*sizeof(unsigned short),&bw);
		}
		f_close(&SD);
	}
	crc_temp = crc_value;
}
/****************************************************************************************
Function :	rate plus and minus
Parameter:   
Return   :
****************************************************************************************/
void RatePlusMinus(void)
{
	// manual rate and auto rate
	if(DReg[F_MANPLUSBTN] == 1)
	{
		DReg[F_MANPLUSBTN] = 0;
		DReg[F_MANUALRATE] += 5;
		if(DReg[F_MANUALRATE] > 200)
		{
			DReg[F_MANUALRATE] = 200;
		}
		while(DReg[F_MANPLUSBTN] == 1)OSDelay(10);
	}
	if(DReg[F_MANMINUSBTN] == 1)
	{
		DReg[F_MANMINUSBTN] = 0;
		DReg[F_MANUALRATE] -= 5;
		if(DReg[F_MANUALRATE] < 5)
		{
			DReg[F_MANUALRATE] = 5;
		}
		while(DReg[F_MANMINUSBTN] == 1)OSDelay(10);
	}
	if(DReg[F_AUTOPLUSBTN] == 1)
	{
		DReg[F_AUTOPLUSBTN] = 0;
		DReg[F_AUTORATE] += 5;
		if(DReg[F_AUTORATE] > 200)
		{
			DReg[F_AUTORATE] = 200;
		}
		while(DReg[F_AUTOPLUSBTN] == 1)OSDelay(10);
	}
	if(DReg[F_AUTOMINUSBTN] == 1)
	{
		DReg[F_AUTOMINUSBTN] = 0;
		DReg[F_AUTORATE] -= 5;
		if(DReg[F_AUTORATE] < 5)
		{
			DReg[F_AUTORATE] = 5;
		}
		while(DReg[F_AUTOMINUSBTN] == 1)OSDelay(10);
	}
}
/****************************************************************************************
Function :	manual speed set: slow,general,fast
Parameter:   
Return   :
****************************************************************************************/
void FastManualSpeed(void)
{
	uint8_t i;
	
	if(DReg[F_MANUALBTN] == 0)
	{
		SP.HandSpeed[0] = 1500;
		SP.HandSpeed[1] = 1500;
		SP.HandSpeed[2] = 1500;
		SP.HandSpeed[3] = 1500;
		SP.HandSpeed[4] = 1500;
		for(i=0;i<5;i++)
		{
			DReg[F_MANSPEED2X+i] = SP.HandSpeed[i];
		}
	}
	else if(DReg[F_MANUALBTN] == 1)
	{
		SP.HandSpeed[0] = 50;
		SP.HandSpeed[1] = 50;
		SP.HandSpeed[2] = 50;
		SP.HandSpeed[3] = 50;
		SP.HandSpeed[4] = 50;
		for(i=0;i<5;i++)
		{
			DReg[F_MANSPEED2X+i] = SP.HandSpeed[i];
		}
	}
	else if(DReg[F_MANUALBTN] == 2)
	{
		SP.HandSpeed[0] = 3000;
		SP.HandSpeed[1] = 3000;
		SP.HandSpeed[2] = 3000;
		SP.HandSpeed[3] = 3000;
		SP.HandSpeed[4] = 3000;
		for(i=0;i<5;i++)
		{
			DReg[F_MANSPEED2X+i] = SP.HandSpeed[i];
		}
	}
}
/****************************************************************************************
Function :	teach table param current cursor display
Parameter:   
Return   :
****************************************************************************************/
void TeachTableCursorInit(void)
{
	int8_t i;
	for(i=0;i<LINENUM;i++)
	{
		DReg[F_TEACHLINE01+i] = 0;
	}
}
/****************************************************************************************
Function :	teach table param current cursor information
Parameter:   
Return   :
****************************************************************************************/
void TeachTableCursorInfo(void)
{
	int8_t i;
	
	if(DReg[F_TEACHLINE01] == 1)
	{
		tempLineBit = lineBit;
		lineBit = 0x0000 | (0x01<<0);
		for(i=0;i<LINENUM;i++)
		{
			if((lineBit&(0x01<<i)) == (0x01<<i) && (tempLineBit&(0x01<<i)) != (0x01<<i))
			{				
				lineBit |= (0x01<<i);
				DReg[F_TEACHLINE01+i] = 1;
			}
			else
			{
				lineBit &= (0x00<<i);
				DReg[F_TEACHLINE01+i] = 0;
			}
		}
		tempLineBit = lineBit;
	}
	if(DReg[F_TEACHLINE02] == 1)
	{
		tempLineBit = lineBit;
		lineBit = 0x0000 | (0x01<<1);
		for(i=0;i<LINENUM;i++)
		{			
			if((lineBit&(0x01<<i)) == (0x01<<i) && (tempLineBit&(0x01<<i)) != (0x01<<i))
			{				
				lineBit |= (0x01<<i);
				DReg[F_TEACHLINE01+i] = 1;
			}
			else
			{
				lineBit &= (0x00<<i);
				DReg[F_TEACHLINE01+i] = 0;
			}
		}
		tempLineBit = lineBit;
	}
	if(DReg[F_TEACHLINE03] == 1)
	{
		tempLineBit = lineBit;
		lineBit = 0x0000 | (0x01<<2);
		for(i=0;i<LINENUM;i++)
		{
			if((lineBit&(0x01<<i)) == (0x01<<i) && (tempLineBit&(0x01<<i)) != (0x01<<i))
			{				
				lineBit |= (0x01<<i);
				DReg[F_TEACHLINE01+i] = 1;
			}
			else
			{
				lineBit &= (0x00<<i);
				DReg[F_TEACHLINE01+i] = 0;
			}
		}
		tempLineBit = lineBit;
	}
	if(DReg[F_TEACHLINE04] == 1)
	{
		tempLineBit = lineBit;
		lineBit = 0x0000 | (0x01<<3);
		for(i=0;i<LINENUM;i++)
		{
			if((lineBit&(0x01<<i)) == (0x01<<i) && (tempLineBit&(0x01<<i)) != (0x01<<i))
			{				
				lineBit |= (0x01<<i);
				DReg[F_TEACHLINE01+i] = 1;
			}
			else
			{
				lineBit &= (0x00<<i);
				DReg[F_TEACHLINE01+i] = 0;
			}
		}
		tempLineBit = lineBit;
	}
	if(DReg[F_TEACHLINE05] == 1)
	{
		tempLineBit = lineBit;
		lineBit = 0x0000 | (0x01<<4);
		for(i=0;i<LINENUM;i++)
		{
			if((lineBit&(0x01<<i)) == (0x01<<i) && (tempLineBit&(0x01<<i)) != (0x01<<i))
			{				
				lineBit |= (0x01<<i);
				DReg[F_TEACHLINE01+i] = 1;
			}
			else
			{
				lineBit &= (0x00<<i);
				DReg[F_TEACHLINE01+i] = 0;
			}
		}
		tempLineBit = lineBit;
	}
	if(DReg[F_TEACHLINE06] == 1)
	{
		lineBit = 0x0000 | (0x01<<5);
		for(i=0;i<LINENUM;i++)
		{
			if((lineBit&(0x01<<i)) == (0x01<<i))
			{				
				lineBit |= (0x01<<i);
				DReg[F_TEACHLINE01+i] = 1;
			}
			else
			{
				lineBit &= (0x00<<i);
				DReg[F_TEACHLINE01+i] = 0;
			}
		}
		tempLineBit = lineBit;
	}
	if(DReg[F_TEACHLINE07] == 1)
	{
		lineBit = 0x0000 | (0x01<<6);
		for(i=0;i<LINENUM;i++)
		{
			if((lineBit&(0x01<<i)) == (0x01<<i))
			{				
				lineBit |= (0x01<<i);
				DReg[F_TEACHLINE01+i] = 1;
			}
			else
			{
				lineBit &= (0x00<<i);
				DReg[F_TEACHLINE01+i] = 0;
			}
		}
		tempLineBit = lineBit;
	}
	if(DReg[F_TEACHLINE08] == 1)
	{
		lineBit = 0x0000 | (0x01<<7);
		for(i=0;i<LINENUM;i++)
		{
			if((lineBit&(0x01<<i)) == (0x01<<i))
			{				
				lineBit |= (0x01<<i);
				DReg[F_TEACHLINE01+i] = 1;
			}
			else
			{
				lineBit &= (0x00<<i);
				DReg[F_TEACHLINE01+i] = 0;
			}
		}
		tempLineBit = lineBit;
	}
	if(DReg[F_TEACHLINE09] == 1)
	{
		lineBit = 0x0000 | (0x01<<8);
		for(i=0;i<LINENUM;i++)
		{
			if((lineBit&(0x01<<i)) == (0x01<<i))
			{				
				lineBit |= (0x01<<i);
				DReg[F_TEACHLINE01+i] = 1;
			}
			else
			{
				lineBit &= (0x00<<i);
				DReg[F_TEACHLINE01+i] = 0;
			}
		}
		tempLineBit = lineBit;
	}
	if(DReg[F_TEACHLINE10] == 1)
	{
		lineBit = 0x0000 | (0x01<<9);
		for(i=0;i<LINENUM;i++)
		{
			if((lineBit&(0x01<<i)) == (0x01<<i))
			{				
				lineBit |= (0x01<<i);
				DReg[F_TEACHLINE01+i] = 1;
			}
			else
			{
				lineBit &= (0x00<<i);
				DReg[F_TEACHLINE01+i] = 0;
			}
		}
		tempLineBit = lineBit;
	}
}
/****************************************************************************************
Function :	teach table rate
Parameter:   
Return   :
****************************************************************************************/
void TeachTableRate(void)
{
	// spindle rate and interpolate rate
	if(DReg[F_SPINDLEPLUS] == 1)
	{
		DReg[F_SPINDLEPLUS] = 0;
		DReg[F_SPINDLERATE] += 5;
		if(DReg[F_SPINDLERATE] > 200)
		{
			DReg[F_SPINDLERATE] = 200;
		}
		while(DReg[F_SPINDLEPLUS] == 1)OSDelay(10);
	}
	if(DReg[F_SPINDLEMINUS] == 1)
	{
		DReg[F_SPINDLEMINUS] = 0;
		DReg[F_SPINDLERATE] -= 5;
		if(DReg[F_SPINDLERATE] < 5)
		{
			DReg[F_SPINDLERATE] = 5;
		}
		while(DReg[F_SPINDLEMINUS] == 1)OSDelay(10);
	}
	if(DReg[F_MAKEPLUS] == 1)
	{
		DReg[F_MAKEPLUS] = 0;
		DReg[F_MAKERATE] += 5;
		if(DReg[F_MAKERATE] > 200)
		{
			DReg[F_MAKERATE] = 200;
		}
		while(DReg[F_MAKEPLUS] == 1)OSDelay(10);
	}
	if(DReg[F_MAKEMINUS] == 1)
	{
		DReg[F_MAKEMINUS] = 0;
		DReg[F_MAKERATE] -= 5;
		if(DReg[F_MAKERATE] < 5)
		{
			DReg[F_MAKERATE] = 5;
		}
		while(DReg[F_MAKEMINUS] == 1)OSDelay(10);
	}
}
/****************************************************************************************
Function :	teach table current param command mode
Parameter:   
Return   :
****************************************************************************************/
void CurrentCommandInfo(void)
{
	// spindle rate and interpolate rate
	if(DReg[F_G00MODE] == 1)     // G00 command
	{
		DReg[F_G00MODE] = 0;
		SelectMode = CM_G00;
		DReg[F_MAKEMODE000+DReg[F_CURLINE]] = 1;
		//while(DReg[F_G00MODE] == 1)OSDelay(10);
	}
	if(DReg[F_G01MODE] == 1)     // G01 command
	{
		DReg[F_G01MODE] = 0;
		SelectMode = CM_G01;
		DReg[F_MAKEMODE000+DReg[F_CURLINE]] = 2;
		//while(DReg[F_G01MODE] == 1)OSDelay(10);
	}
	if(DReg[F_OUTPUTMODE] == 1)  // Output command
	{
		DReg[F_OUTPUTMODE] = 0;
		SelectMode = CM_OUT;
		DReg[F_MAKEMODE000+DReg[F_CURLINE]] = 3;
		//while(DReg[F_OUTPUTMODE] == 1)OSDelay(10);
	}
	if(DReg[F_INPUTMODE] == 1)   // Input command
	{
		DReg[F_INPUTMODE] = 0;
		SelectMode = CM_IN;
		DReg[F_MAKEMODE000+DReg[F_CURLINE]] = 4;
		//while(DReg[F_INPUTMODE] == 1)OSDelay(10);
	}
	if(DReg[F_DELAYMODE] == 1)   // Delay command
	{
		DReg[F_DELAYMODE] = 0;
		SelectMode = CM_DELAY;
		DReg[F_MAKEMODE000+DReg[F_CURLINE]] = 5;
		//while(DReg[F_DELAYMODE] == 1)OSDelay(10);
	}
	if(DReg[F_ARCMODE] == 1)     // Arc command
	{
		DReg[F_ARCMODE] = 0;
		SelectMode = CM_ARC;
		DReg[F_MAKEMODE000+DReg[F_CURLINE]] = 6;
		//while(DReg[F_ARCMODE] == 1)OSDelay(10);
	}
	if(DReg[F_FUNCMODE] == 1)   // Func command
	{
		DReg[F_FUNCMODE] = 0;
		SelectMode = CM_FUNC;
		DReg[F_MAKEMODE000+DReg[F_CURLINE]] = 7;
		//while(DReg[F_RIVETMODE] == 1)OSDelay(10);
	}
}
/****************************************************************************************
Function :	teach table IO information
Parameter:   
Return   :
****************************************************************************************/
void GetTeachTableIOInfo(void)
{
	if(DReg[F_INOUTBTN] == 0)
	{
		if(DReg[F_INOUTNUM] >= 15)DReg[F_INOUTNUM] = 15;
		if(DReg[F_INOUTNUM] <= 0)DReg[F_INOUTNUM] = 0;
		PortNum = DReg[F_INOUTNUM];
//		switch(DReg[F_INOUTNUM])
//		{
//			case  0:PortNum = OUTPUT01;break;
//			case  1:PortNum = OUTPUT02;break;
//			case  2:PortNum = OUTPUT03;break;
//			case  3:PortNum = OUTPUT04;break;
//			case  4:PortNum = OUTPUT05;break;
//			case  5:PortNum = OUTPUT06;break;
//			case  6:PortNum = OUTPUT07;break;
//			case  7:PortNum = OUTPUT08;break;
//			case  8:PortNum = OUTPUT09;break;
//			case  9:PortNum = OUTPUT10;break;
//			case 10:PortNum = OUTPUT11;break;
//			case 11:PortNum = OUTPUT12;break;
//			case 12:PortNum = OUTPUT13;break;
//			case 13:PortNum = OUTPUT14;break;
//			case 14:PortNum = OUTPUT15;break;
//			case 15:PortNum = OUTPUT16;break;
//			default:break;
//		}
	}
	else
	{
		if(DReg[F_INOUTNUM] >= 9)DReg[F_INOUTNUM] = 9;
		if(DReg[F_INOUTNUM] <= 1)DReg[F_INOUTNUM] = 1;
		PortNum = DReg[F_INOUTNUM];
//		switch(DReg[F_INOUTNUM])
//		{
//			case  0:PortNum = INPUT01;break;
//			case  1:PortNum = INPUT02;break;
//			case  2:PortNum = INPUT03;break;
//			case  3:PortNum = INPUT04;break;
//			case  4:PortNum = INPUT05;break;
//			case  5:PortNum = INPUT06;break;
//			case  6:PortNum = INPUT07;break;
//			case  7:PortNum = INPUT08;break;
//			case  8:PortNum = INPUT09;break;
//			default:break;
//		}	
	}
	if(DReg[F_INOUTLEVEL] >= 1)DReg[F_INOUTLEVEL] = 1;
	if(DReg[F_INOUTLEVEL] <= 0)DReg[F_INOUTLEVEL] = 0;
	PortLevel = DReg[F_INOUTLEVEL];
}
/****************************************************************************************
Function :	init teach up and down button and execute
Parameter:   
Return   :
****************************************************************************************/
void TeachPageButtonInfo(void)
{
	int8_t i;

	for(i=0;i<MAXPAGENUM;i++)
	{
		if(DReg[F_TEACHDWBTN01] == 1)
		{
			DReg[F_CURPAGE]++;
			if(DReg[F_CURPAGE] >= MAXPAGENUM)
			{
				DReg[F_CURPAGE] = 0;
			}
			DReg[F_CURLINE] = DReg[F_CURPAGE]*10;
		}
		if(DReg[F_TEACHUPBTN01] == 1)
		{
			if(DReg[F_CURPAGE] == 0)
			{
				DReg[F_CURPAGE] = MAXPAGENUM-1;
			}
			else DReg[F_CURPAGE]--;
			DReg[F_CURLINE] = DReg[F_CURPAGE]*10;
		}
		if(DReg[F_CURLINE] > DReg[F_TOTALLINE])DReg[F_CURLINE] = DReg[F_TOTALLINE];
		if(DReg[F_CURPAGE] > DReg[F_TOTALPAGE])
		{
			DReg[F_CURPAGE] = DReg[F_TOTALPAGE];
		}
	}
}
/****************************************************************************************
Function :	teach table param operate
Parameter:   
Return   :
****************************************************************************************/
void TeachTableParam(void)
{
	uint16_t i,temp1;
	float ftemp[6];

	TeachTableRate();
	CurrentCommandInfo();
	GetTeachTableIOInfo();
//	TeachPageButtonInfo();	

	// coord command insert
	if((DReg[F_COORDINSERTBTN] == 1) && (SelectMode == CM_G00 || SelectMode == CM_G01))
	{
		CommandInsertFlag = 1;
		for(i=0;i<6;i++)ftemp[i] = 0.0;
		memcpy(&DReg[F_MAKEDATA1000+2*DReg[F_CURLINE]],&DReg[F_AXISPOSX],sizeof(float));
		memcpy(&DReg[F_MAKEDATA2000+2*DReg[F_CURLINE]],&DReg[F_AXISPOSY],sizeof(float));
		memcpy(&DReg[F_MAKEDATA3000+2*DReg[F_CURLINE]],&DReg[F_AXISPOSZ],sizeof(float));
		memcpy(&DReg[F_MAKEDATA4000+2*DReg[F_CURLINE]],&DReg[F_AXISPOSA],sizeof(float));
		memcpy(&DReg[F_MAKEDATA5000+2*DReg[F_CURLINE]],&DReg[F_AXISPOSB],sizeof(float));
		if(DReg[F_MAKEMODE000+DReg[F_CURLINE]] == CM_G01)
		{
			ftemp[5] = DReg[F_INPSPEED];
			memcpy(&DReg[F_MAKEDATA6000+2*DReg[F_CURLINE]],&ftemp[5],sizeof(float));
		}
		else
		{
			ftemp[5] = 0.0;
			memcpy(&DReg[F_MAKEDATA6000+2*DReg[F_CURLINE]],&ftemp[5],sizeof(float));
		}
		if(DReg[F_MAKEMODE000+DReg[F_CURLINE]+1] == CM_NULL)
		{
			DReg[F_CURLINE]++;
			DReg[F_TOTALLINE]++;
			DReg[F_CURPAGE] = DReg[F_CURLINE]/10;			
			DReg[F_TOTALPAGE] = DReg[F_TOTALLINE]/10;
		}
		SelectMode = CM_NULL;
		while(DReg[F_COORDINSERTBTN] == 1)OSDelay(10);
	}
	// IO command insert
	if((DReg[F_IOINSERTBTN] == 1) && (SelectMode == CM_OUT || SelectMode == CM_IN))
	{
		CommandInsertFlag = 1;
		for(i=0;i<5;i++)ftemp[i] = 0.0;
		memcpy(&DReg[F_MAKEDATA1000+2*DReg[F_CURLINE]],&ftemp[0],sizeof(float));
		memcpy(&DReg[F_MAKEDATA2000+2*DReg[F_CURLINE]],&ftemp[1],sizeof(float));
		memcpy(&DReg[F_MAKEDATA3000+2*DReg[F_CURLINE]],&ftemp[2],sizeof(float));
		memcpy(&DReg[F_MAKEDATA4000+2*DReg[F_CURLINE]],&ftemp[3],sizeof(float));
		memcpy(&DReg[F_MAKEDATA5000+2*DReg[F_CURLINE]],&ftemp[4],sizeof(float));
		temp1 = PortNum*10 + PortLevel;
		ftemp[5] = temp1;
		memcpy(&DReg[F_MAKEDATA6000+2*DReg[F_CURLINE]],&ftemp[5],sizeof(float));
		if(DReg[F_MAKEMODE000+DReg[F_CURLINE]+1] == CM_NULL)
		{
			DReg[F_CURLINE]++;
			DReg[F_TOTALLINE]++;
			DReg[F_CURPAGE] = DReg[F_CURLINE]/10;		
			DReg[F_TOTALPAGE] = DReg[F_TOTALLINE]/10;			
		}
		SelectMode = CM_NULL;	
		while(DReg[F_IOINSERTBTN] == 1)OSDelay(10);
	}
	// func command insert
	if((DReg[F_FUNCINSERTBTN] == 1) && (SelectMode == CM_FUNC))
	{
		CommandInsertFlag = 1;
		for(i=0;i<5;i++)ftemp[i] = 0.0;
		memcpy(&DReg[F_MAKEDATA1000+2*DReg[F_CURLINE]],&DReg[F_AXISPOSX],sizeof(float));
		memcpy(&DReg[F_MAKEDATA2000+2*DReg[F_CURLINE]],&DReg[F_AXISPOSY],sizeof(float));
		memcpy(&DReg[F_MAKEDATA3000+2*DReg[F_CURLINE]],&DReg[F_AXISPOSZ],sizeof(float));
		memcpy(&DReg[F_MAKEDATA4000+2*DReg[F_CURLINE]],&DReg[F_AXISPOSA],sizeof(float));
		memcpy(&DReg[F_MAKEDATA5000+2*DReg[F_CURLINE]],&DReg[F_AXISPOSB],sizeof(float));
		ftemp[5] = DReg[F_DELAYTIME];
		memcpy(&DReg[F_MAKEDATA6000+2*DReg[F_CURLINE]],&ftemp[5],sizeof(float));
		if(DReg[F_MAKEMODE000+DReg[F_CURLINE]+1] == CM_NULL)
		{
			DReg[F_CURLINE]++;
			DReg[F_TOTALLINE]++;
			DReg[F_CURPAGE] = DReg[F_CURLINE]/10;			
			DReg[F_TOTALPAGE] = DReg[F_TOTALLINE]/10;
		}
		SelectMode = CM_NULL;
		while(DReg[F_FUNCINSERTBTN] == 1)OSDelay(10);
	}
	// delay command insert
	if((DReg[F_DELAYINSERTBTN] == 1) && (SelectMode == CM_DELAY))
	{
		CommandInsertFlag = 1;
		for(i=0;i<5;i++)ftemp[i] = 0.0;
		memcpy(&DReg[F_MAKEDATA1000+2*DReg[F_CURLINE]],&ftemp[0],sizeof(float));
		memcpy(&DReg[F_MAKEDATA2000+2*DReg[F_CURLINE]],&ftemp[1],sizeof(float));
		memcpy(&DReg[F_MAKEDATA3000+2*DReg[F_CURLINE]],&ftemp[2],sizeof(float));
		memcpy(&DReg[F_MAKEDATA4000+2*DReg[F_CURLINE]],&ftemp[3],sizeof(float));
		memcpy(&DReg[F_MAKEDATA5000+2*DReg[F_CURLINE]],&ftemp[4],sizeof(float));
		ftemp[5] = DReg[F_DELAYTIME];
		memcpy(&DReg[F_MAKEDATA6000+2*DReg[F_CURLINE]],&ftemp[5],sizeof(float));
		if(DReg[F_MAKEMODE000+DReg[F_CURLINE]+1] == CM_NULL)
		{
			DReg[F_CURLINE]++;
			DReg[F_TOTALLINE]++;
			DReg[F_CURPAGE] = DReg[F_CURLINE]/10;			
			DReg[F_TOTALPAGE] = DReg[F_TOTALLINE]/10;			
		}
		SelectMode = CM_NULL;
		while(DReg[F_DELAYINSERTBTN] == 1)OSDelay(10);
	}
	// get current cursor when command insert
/*	if(CommandInsertFlag)
	{
		CommandInsertFlag = 0;
		if(tempLine != (DReg[F_CURLINE]%10))
		{		
			TeachTableCursorInit();
			DReg[F_TEACHLINE01+DReg[F_CURLINE]%10] = 1;
			tempLine = DReg[F_CURLINE]%10;
		}
	}*/
//	if(CommandInsertFlag)
	{
//		CommandInsertFlag = 0;
		if(tempLine != (DReg[F_CURLINE]%10))
		{
			lineBit = 0x0000 | (0x01<<(DReg[F_CURLINE]%10));
			tempLine = DReg[F_CURLINE]%10;
			for(i=0;i<LINENUM;i++)
			{
				if((lineBit&(0x01<<i)) == (0x01<<i))
				{
					DReg[F_TEACHLINE01+i] = 1;
				}
				else
				{
					DReg[F_TEACHLINE01+i] = 0;
				}				
			}
			tempLineBit = lineBit;
		}
	}
//	TeachTableCursorInfo();
	
	// insert param before current param
	if((DReg[F_INSERTBTN] == 1) && (DReg[F_ENTERBUTTON] == 1))
	{
		DReg[F_INSERTBTN] = 0;
		DReg[F_ENTERBUTTON] = 0;
		for(i=DReg[F_TOTALLINE]+1;i>=DReg[F_CURLINE];i--)
		{
			DReg[F_MAKEMODE000+i] = DReg[F_MAKEMODE000+i-1];
			memcpy(&DReg[F_MAKEDATA1000+2*i],&DReg[F_MAKEDATA1000+2*(i-1)],sizeof(float));
			memcpy(&DReg[F_MAKEDATA2000+2*i],&DReg[F_MAKEDATA2000+2*(i-1)],sizeof(float));
			memcpy(&DReg[F_MAKEDATA3000+2*i],&DReg[F_MAKEDATA3000+2*(i-1)],sizeof(float));
			memcpy(&DReg[F_MAKEDATA4000+2*i],&DReg[F_MAKEDATA4000+2*(i-1)],sizeof(float));
			memcpy(&DReg[F_MAKEDATA5000+2*i],&DReg[F_MAKEDATA5000+2*(i-1)],sizeof(float));
			memcpy(&DReg[F_MAKEDATA6000+2*i],&DReg[F_MAKEDATA6000+2*(i-1)],sizeof(float));
		}
		for(i=0;i<6;i++)ftemp[i] = 0.0;
		DReg[F_MAKEMODE000+DReg[F_CURLINE]] = CM_NULL;
		memcpy(&DReg[F_MAKEDATA1000+2*(DReg[F_CURLINE])],&ftemp[0],sizeof(float));
		memcpy(&DReg[F_MAKEDATA2000+2*(DReg[F_CURLINE])],&ftemp[1],sizeof(float));
		memcpy(&DReg[F_MAKEDATA3000+2*(DReg[F_CURLINE])],&ftemp[2],sizeof(float));
		memcpy(&DReg[F_MAKEDATA4000+2*(DReg[F_CURLINE])],&ftemp[3],sizeof(float));
		memcpy(&DReg[F_MAKEDATA5000+2*(DReg[F_CURLINE])],&ftemp[4],sizeof(float));
		memcpy(&DReg[F_MAKEDATA6000+2*(DReg[F_CURLINE])],&ftemp[5],sizeof(float));
		tempLineBit = lineBit;
		DReg[F_CURLINE]--;
		lineBit = 0x0000 | (0x01<<(DReg[F_CURLINE]%10));
		for(i=0;i<LINENUM;i++)
		{
			if((lineBit&(0x01<<i)) == (0x01<<i))
			{
				DReg[F_TEACHLINE01+i] = 1;
			}
			else
			{
				DReg[F_TEACHLINE01+i] = 0;
			}				
		}
		DReg[F_TOTALLINE]++;
		DReg[F_CURPAGE] = DReg[F_CURLINE]/10;
		DReg[F_TOTALPAGE] = DReg[F_TOTALLINE]/10;
		//while(DReg[F_INSERTBTN] == 1)OSDelay(10);
	}
	// delete current param
	if((DReg[F_DELETEBTN] == 1) && (DReg[F_ENTERBUTTON] == 1))
	{
		DReg[F_DELETEBTN] = 0;
		DReg[F_ENTERBUTTON] = 0;
		for(i=DReg[F_CURLINE];i<DReg[F_TOTALLINE]-1;i++)
		{
			DReg[F_MAKEMODE000+i] = DReg[F_MAKEMODE000+i+1];
			memcpy(&DReg[F_MAKEDATA1000+2*i],&DReg[F_MAKEDATA1000+2*(i+1)],sizeof(float));
			memcpy(&DReg[F_MAKEDATA2000+2*i],&DReg[F_MAKEDATA2000+2*(i+1)],sizeof(float));
			memcpy(&DReg[F_MAKEDATA3000+2*i],&DReg[F_MAKEDATA3000+2*(i+1)],sizeof(float));
			memcpy(&DReg[F_MAKEDATA4000+2*i],&DReg[F_MAKEDATA4000+2*(i+1)],sizeof(float));
			memcpy(&DReg[F_MAKEDATA5000+2*i],&DReg[F_MAKEDATA5000+2*(i+1)],sizeof(float));
			memcpy(&DReg[F_MAKEDATA6000+2*i],&DReg[F_MAKEDATA6000+2*(i+1)],sizeof(float));
		}
		for(i=0;i<6;i++)ftemp[i] = 0.0;
		DReg[F_MAKEMODE000+DReg[F_TOTALLINE]-1] = CM_NULL;
		memcpy(&DReg[F_MAKEDATA1000+2*(DReg[F_TOTALLINE]-1)],&ftemp[0],sizeof(float));
		memcpy(&DReg[F_MAKEDATA2000+2*(DReg[F_TOTALLINE]-1)],&ftemp[1],sizeof(float));
		memcpy(&DReg[F_MAKEDATA3000+2*(DReg[F_TOTALLINE]-1)],&ftemp[2],sizeof(float));
		memcpy(&DReg[F_MAKEDATA4000+2*(DReg[F_TOTALLINE]-1)],&ftemp[3],sizeof(float));
		memcpy(&DReg[F_MAKEDATA5000+2*(DReg[F_TOTALLINE]-1)],&ftemp[4],sizeof(float));
		memcpy(&DReg[F_MAKEDATA6000+2*(DReg[F_TOTALLINE]-1)],&ftemp[5],sizeof(float));
		if(DReg[F_CURLINE] == DReg[F_TOTALLINE])DReg[F_CURLINE]--;
		else DReg[F_CURLINE] = DReg[F_CURLINE];
		tempLineBit = lineBit;
		lineBit = 0x0000 | (0x01<<(DReg[F_CURLINE]%10));
		for(i=0;i<LINENUM;i++)
		{
			if((lineBit&(0x01<<i)) == (0x01<<i))
			{
				DReg[F_TEACHLINE01+i] = 1;
			}
			else
			{
				DReg[F_TEACHLINE01+i] = 0;
			}				
		}
		DReg[F_TOTALLINE]--;
		DReg[F_CURPAGE] = DReg[F_CURLINE]/10;
		DReg[F_TOTALPAGE] = DReg[F_TOTALLINE]/10;
		//while(DReg[F_DELETEBTN] == 1)OSDelay(10);
	}
	// teach param all clear
	if((DReg[F_TEACHCLEARBTN] == 1) && (DReg[F_ENTERBUTTON] == 1))
	{
		DReg[F_TEACHCLEARBTN] = 0;
		DReg[F_ENTERBUTTON] = 0;
		DReg[F_CURLINE] = 0;
		DReg[F_CURPAGE] = 0;
		DReg[F_TOTALLINE] = 0;
		DReg[F_TOTALPAGE] = 0;
		lineBit = 0x0000 | (0x01<<0);
		DReg[F_TEACHLINE01] = 1;		
		for(i=1;i<LINENUM;i++)
		{
			DReg[F_TEACHLINE01+i] = 0;
		}
		for(i=0;i<6;i++)ftemp[i] = 0.0;
		for(i=0;i<100;i++)
		{
			DReg[F_MAKEMODE000+i] = CM_NULL;
			memcpy(&DReg[F_MAKEDATA1000+2*i],&ftemp[0],sizeof(float));
			memcpy(&DReg[F_MAKEDATA2000+2*i],&ftemp[1],sizeof(float));
			memcpy(&DReg[F_MAKEDATA3000+2*i],&ftemp[2],sizeof(float));
			memcpy(&DReg[F_MAKEDATA4000+2*i],&ftemp[3],sizeof(float));
			memcpy(&DReg[F_MAKEDATA5000+2*i],&ftemp[4],sizeof(float));
			memcpy(&DReg[F_MAKEDATA6000+2*i],&ftemp[5],sizeof(float));
		}
		//while(DReg[F_TEACHCLEARBTN] == 1)OSDelay(10);
	}
	// teach param set line
	if(DReg[F_SETLINEBTN] == 1)
	{
		if(DReg[F_SETLINE] < 1)DReg[F_SETLINE] = 1;
		if(DReg[F_SETLINE] > DReg[F_TOTALLINE])DReg[F_SETLINE] = DReg[F_TOTALLINE];
		lineBit = 0x0000 | (0x01<<((DReg[F_SETLINE]-1)%10));
		for(i=0;i<LINENUM;i++)
		{
			if((lineBit&(0x01<<i)) == (0x01<<i))
			{
				DReg[F_TEACHLINE01+i] = 1;
			}
			else
			{
				DReg[F_TEACHLINE01+i] = 0;
			}				
		}
		tempLineBit = lineBit;
		DReg[F_CURLINE] = DReg[F_SETLINE]-1;
		DReg[F_CURPAGE] = DReg[F_CURLINE]/10;
		while(DReg[F_SETLINEBTN] == 1)OSDelay(10);
	}
}
/****************************************************************************************
Function :	G00 move
Parameter:   
Return   :
****************************************************************************************/
extern int8_t G00RelPosAll(uint8_t Axis[],float Inch[]);
int8_t G00Func(struct _FUNCPARAM param)
{
	uint8_t Axis[5];
	float Inch[5];

	Axis[0] = 1;
	Axis[1] = 2;
	Axis[2] = 3;
	Axis[3] = 4;
	Axis[4] = 5;
	Inch[0] = param.MakeData1 - GetMacPosMm(1);
	Inch[1] = param.MakeData2 - GetMacPosMm(2);
	Inch[2] = param.MakeData3 - GetMacPosMm(3);
	Inch[3] = param.MakeData4 - GetMacPosMm(4);
	Inch[4] = param.MakeData5 - GetMacPosMm(5);
	if(G00RelPosAll(Axis,Inch) == -1)return -1;
	return 1;
}
int LineDataSend(struct LayoutCmd_PC *cmd,unsigned int total)
{
	int start,count;
	unsigned char reg;
	long result;
	
	start = 0;
	count = total;
	while(1)
	{
		if(count > MAX_INS_SEND)
		{
			result = BatchLine(cmd,start,MAX_INS_SEND,&reg);
		}
		else
		{
			result = BatchLine(cmd,start,count,&reg);
		}
		start += reg;
		count -= reg;
		if(ReadInput(STOPIN) == 0)
		{
			SAxisDec_stop(1);
			SAxisDec_stop(2);
			SAxisDec_stop(3);
			SAxisDec_stop(4);
			SAxisDec_stop(5);
		}
		if(count == 0)break;
	}
	return 0;
}
/****************************************************************************************
Function :	G01 move
Parameter:   
Return   :
****************************************************************************************/
extern float GetMinAxisGear(uint8_t Axis[]);
int8_t G01Func(struct _FUNCPARAM param)
{
	float scale[5],MinUint;
	unsigned long speed[5],sta;	
	uint8_t Axis[5],reg;
	long i,result;

	UpdateAxisParam();
	for(i=0;i<5;i++)Axis[i] = i+1;
	MinUint = GetMinAxisGear(Axis);  // 获取最小脉冲当量
	for(i=0;i<5;i++)
	{
		if(Axis[i] == i+1)scale[i] = SP.AxisUnit[i]/MinUint;  // 各轴脉冲当量除以最小脉冲当量
		else scale[i] = 1.0;
	}
	SetAxisScale(scale);
	SetMoveTogetherMode(1,1,1,1,1);
	BufStop();
	LayoutStart(0);
	BufClr();
	result = BufStart();
	speed[0] = DReg[F_INPSTARTSPEED]*0.6/60./MinUint;
	speed[1] = DReg[F_INPADDSPEED]/MinUint;
	speed[2] = param.MakeData6/60./MinUint;
	speed[3] = DReg[F_INPSTARTSPEED]*0.8/60./MinUint;

	result = MotionConfig(speed[0],speed[0],speed[1],speed[2],speed[3]);
//	GetPosDev(&AxisPos[0],&AxisPos[1],&AxisPos[2],&AxisPos[3],&AxisPos[4],&AxisPos[5],&AxisPos[6],&AxisPos[7]);
//	for(i=0;i<5;i++)stPos[0] = GetMacPosMm(i+1);
	SetSmoothLevel(8);
	Line[0].LineIndex = 0;
	Line[0].Speed = speed[2];
	Line[0].X = param.MakeData1/MinUint;   //360
	Line[0].Y = param.MakeData2/MinUint;   
	Line[0].Z = param.MakeData3/MinUint;
	Line[0].U = param.MakeData4/MinUint;
	Line[0].V = param.MakeData5/MinUint;
	BatchLine(Line,0,1,&reg);
	LayoutStart(1);
	LocusEnd(0);
	sta = 0xffff;
	while(sta != 0)
	{
		ModbusServe(0);		
		GetMotionStatus(&sta);
		if(sta == 0)break;		
		if((DReg[F_PAUSEBTN] == 1) || (ReadInput(STARTIN) == 0))
		{
			SAxisDec_stop(1);
			SAxisDec_stop(2);
			SAxisDec_stop(3);
			SAxisDec_stop(4);
			SAxisDec_stop(5);
			BufStop();
			PauseFlag = 1;
			return -2;
		}
		if((DReg[F_STOPBTN] == 1) || (ReadInput(STOPIN) == 0))
		{
			SAxisDec_stop(1);
			SAxisDec_stop(2);
			SAxisDec_stop(3);
			SAxisDec_stop(4);
			SAxisDec_stop(5);
			BufStop();
			while(1)
			{
				ModbusServe(0);
				DispAxisPosition();
				GetMotionStatus(&sta);
				if(sta == 0)break;
			}
			return -1;
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
	BufStop();
	//GetPosDev(&AxisPos[0],&AxisPos[1],&AxisPos[2],&AxisPos[3],&AxisPos[4],&AxisPos[5],&AxisPos[6],&AxisPos[7]);
	return 1;
}
/****************************************************************************************
Function :	output function
Parameter:   
Return   :
****************************************************************************************/	
void OutputFunc(struct _FUNCPARAM param)
{
	int8_t PortNum,PortLevel,temp;
	temp = ((uint8_t)param.MakeData6)/10;
	switch(temp)
	{
		case  0:PortNum = OUTPUT01;break;
		case  1:PortNum = OUTPUT02;break;
		case  2:PortNum = OUTPUT03;break;
		case  3:PortNum = OUTPUT04;break;
		case  4:PortNum = OUTPUT05;break;
		case  5:PortNum = OUTPUT06;break;
		case  6:PortNum = OUTPUT07;break;
		case  7:PortNum = OUTPUT08;break;
		case  8:PortNum = OUTPUT09;break;
		case  9:PortNum = OUTPUT10;break;
		case 10:PortNum = OUTPUT11;break;
		case 11:PortNum = OUTPUT12;break;
		case 12:PortNum = OUTPUT13;break;
		case 13:PortNum = OUTPUT14;break;
		case 14:PortNum = OUTPUT15;break;
		case 15:PortNum = OUTPUT16;break;
		default:break;
	}
	PortLevel = ((uint8_t)param.MakeData6)%2;
	WriteOutput(PortNum,PortLevel);
	DReg[F_OUTPUT01+temp] = PortLevel;
}
/****************************************************************************************
Function :	input detect function
Parameter:   
Return   :
****************************************************************************************/
int8_t InputFunc(struct _FUNCPARAM param)
{
	int32_t PortNum,PortLevel,temp;
	temp = ((uint16_t)param.MakeData6)/10;
	switch(temp)
	{
		case  1:PortNum = INPUT01;break;
		case  2:PortNum = INPUT02;break;
		case  3:PortNum = INPUT03;break;
		case  4:PortNum = INPUT04;break;
		case  5:PortNum = INPUT05;break;
		case  6:PortNum = INPUT06;break;
		case  7:PortNum = INPUT07;break;
		case  8:PortNum = INPUT08;break;
		case  9:PortNum = INPUT09;break;
		default:break;
	}
	PortLevel = ((uint16_t)param.MakeData6)%2;
	while(ReadInput(PortNum) != PortLevel)
	{
		if((DReg[F_STOPBTN] == 1) || (DReg[F_RESETBTN] == 1))
		{
			return -1;
		}
		OSDelay(2);
	}
	if(PortLevel == 0)DReg[F_INPUT01+temp-1] = 1;
	else DReg[F_INPUT01+temp-1] = 0;
	return 1;
}
/****************************************************************************************
Function :	delay function
Parameter:   
Return   :
****************************************************************************************/
int8_t DelayFunc(struct _FUNCPARAM param)
{
	if(OSDelay(param.MakeData6) == -1)return -1;
	return 1;
}
/****************************************************************************************
Function :	delay function
Parameter:   
Return   :
****************************************************************************************/	
int8_t ArcFunc(struct _FUNCPARAM param)
{
	return 1;
}
/****************************************************************************************
Function :	delay function
Parameter:   
Return   :
****************************************************************************************/	
int8_t UserFunc2(struct _FUNCPARAM param)
{
	uint8_t Axis[5];
	float   Inch[5];
	
	if(MouldAFlag == 1)
	{
		Axis[0] = 1;
		Axis[1] = 2;
		Axis[2] = 3;
		Axis[3] = 0;
		Axis[4] = 0;
		Inch[0] = param.MakeData1 - GetMacPosMm(1);
		Inch[1] = param.MakeData2 - GetMacPosMm(2);
		Inch[2] = param.MakeData3 - GetMacPosMm(3);
		Inch[3] = 0;
	}
	else if(MouldBFlag == 1)
	{
		Axis[0] = 1;
		Axis[1] = 0;
		Axis[2] = 3;
		Axis[3] = 4;
		Axis[4] = 0;
		Inch[0] = param.MakeData1 - GetMacPosMm(1);
		Inch[1] = 0;
		Inch[2] = param.MakeData3 - GetMacPosMm(3);
		Inch[3] = param.MakeData4 - GetMacPosMm(4);
	}
	else
	{
		Axis[0] = 1;
		Axis[1] = 2;
		Axis[2] = 3;
		Axis[3] = 4;
		Axis[4] = 0;
		Inch[0] = param.MakeData1 - GetMacPosMm(1);
		Inch[1] = param.MakeData2 - GetMacPosMm(2);
		Inch[2] = param.MakeData3 - GetMacPosMm(3);
		Inch[3] = param.MakeData4 - GetMacPosMm(4);	
	}
	Inch[4] = 0;
	if(G00RelPosAll(Axis,Inch) == -1)return -1;
	return 1;
}
/****************************************************************************************
Function :	delay function
Parameter:   
Return   :
****************************************************************************************/
extern void SetMakeSpeed(uint8_t Axis,long Speed[]);
int8_t UserFunc(struct _FUNCPARAM param)
{
	float offset[2],ftemp[5];
	uint16_t i,j,k,disk_total,total;
	uint16_t delay_time0;
	uint16_t delay_time1;
	uint16_t delay_time2;
	long speed[5][3];		

	// (Note: need to make parameter)	
	float    axis_x_fetch_init_point;
	float    axis_y_fetch_init_point;
	float    disk_work_row_inch;
	float    disk_work_col_inch;

	memcpy(&axis_x_fetch_init_point,&DReg[F_FETCHINITPOSX],sizeof(float));
	memcpy(&axis_y_fetch_init_point,&DReg[F_FETCHINITPOSY],sizeof(float));
	memcpy(&disk_work_row_inch,&DReg[F_DISKROWINCH],sizeof(float));
	memcpy(&disk_work_col_inch,&DReg[F_DISKCOLINCH],sizeof(float));
	delay_time0 = DReg[F_DELAYTIME0];
	delay_time1 = DReg[F_DELAYTIME1];
	delay_time2 = DReg[F_DELAYTIME2];
	
	// init all axes move speed
	for(i=0;i<5;i++)SetMakeSpeed(i+1,speed[i]);
		
	// (*********************************************************************************************)
	// (******************************* fetch work from install-disk ********************************)
	
	total = DReg[F_DISKROWNUM] * DReg[F_DISKCOLNUM];	
	for(;;)
	{
		DReg[F_CURTAKENUM] = 0;
		// Note: col -> row
//		for(i=0;i<DReg[F_DISKCOLNUM];i++)
//		{
//			for(j=0;j<DReg[F_DISKROWNUM];i++)
//			{
//				if((j%4 == 2) || (j%4 == 3))continue;
//				offset[0] = (4*(j/4) + j%2) * disk_work_row_inch;
//				offset[1] = i * disk_work_col_inch;				
//			}
//		}
		
		// Note: row -> col
		for(i=0;i<DReg[F_DISKROWNUM];i++)
		{
			if(i%4 == 0)
			{
				for(j=0;j<DReg[F_DISKCOLNUM];j++)
				{
					offset[0] = (4*(i/4) + i%2) * disk_work_row_inch;
					offset[1] = j * disk_work_col_inch;
					
					// axis-X run to install-disk prepare position to fetch work
					ftemp[0] = axis_x_fetch_init_point + offset[0] - GetMacPosMm(1);
					if(G00RelPos(1,ftemp[0],speed[0][0],speed[0][1],speed[0][2]) == -1)goto JUMP00;
					
					// axis-Y run to install-disk prepare position to fetch work
					ftemp[0] = axis_y_fetch_init_point + offset[1] - GetMacPosMm(2);
					if(G00RelPos(2,ftemp[0],speed[1][0],speed[1][1],speed[1][2]) == -1)goto JUMP00;
					
					while(1)
					{
						ModbusServe(0);
						if(ReadInput(INPUT01) == 0)break;				
						DispAxisPosition();
						UpdateAxisParam();
						DispInput();
						DispOutput();
						if(ServoAlarmCheck() == -1)goto JUMP00;
						if(LimitPosCheck() == -1)goto JUMP00;
						if(LimitInputCheck() == -1)goto JUMP00;
						if(StartFlag)DispPowerOnTime();
						if((DReg[F_STOPBTN] == 1) || (ReadInput(STOPIN) == 0))goto JUMP00;
					}
					//OSDelay(1000);
					// fetched work form disk number plus
					DReg[F_CURTAKENUM]++;
					DReg[F_TOTALNUM]++;
				}
			}
			else if(i%4 == 1)
			{
				for(j=0;j<DReg[F_DISKCOLNUM];j++)
				{
					offset[0] = (4*(i/4) + i%2) * disk_work_row_inch;
					offset[1] = ((DReg[F_DISKCOLNUM]-1) - j) * disk_work_col_inch;
					
					// axis-X run to install-disk prepare position to fetch work
					ftemp[0] = axis_x_fetch_init_point + offset[0] - GetMacPosMm(1);
					if(G00RelPos(1,ftemp[0],speed[0][0],speed[0][1],speed[0][2]) == -1)goto JUMP00;
					
					// axis-Y run to install-disk prepare position to fetch work
					ftemp[0] = axis_y_fetch_init_point + offset[1] - GetMacPosMm(2);
					if(G00RelPos(2,ftemp[0],speed[1][0],speed[1][1],speed[1][2]) == -1)goto JUMP00;
					
					while(1)
					{
						ModbusServe(0);
						if(ReadInput(INPUT01) == 0)break;				
						DispAxisPosition();
						UpdateAxisParam();
						DispInput();
						DispOutput();
						if(ServoAlarmCheck() == -1)goto JUMP00;
						if(LimitPosCheck() == -1)goto JUMP00;
						if(LimitInputCheck() == -1)goto JUMP00;
						if(StartFlag)DispPowerOnTime();
						if((DReg[F_STOPBTN] == 1) || (ReadInput(STOPIN) == 0))goto JUMP00;
					}
					//OSDelay(1000);
					// fetched work form disk number plus
					DReg[F_CURTAKENUM]++;
					DReg[F_TOTALNUM]++;
				}
			}
			else
			{
				// fetched work form disk number plus
				DReg[F_CURTAKENUM]++;
				DReg[F_TOTALNUM]++;
				continue;
			}				
		}	
	}
	// CRC-check for saving parameter real time
	UserValueCrcCheck();
	return 1;
	
JUMP00:
	// CRC-check for saving parameter real time
	UserValueCrcCheck();
	return -1;
}	
int8_t UserFunc1(struct _FUNCPARAM param)
{
	float offset[2],ftemp[5];
	uint16_t disk_total,total;
	uint16_t delay_time0;
	uint16_t delay_time1;
	uint16_t delay_time2;
	long i,speed[5][3];		

	// (Note: need to make parameter)	
	float    axis_x_fetch_init_point;
	float    axis_y_fetch_init_point;
//	float    axis_y_avoid_point;
	float    disk_work_row_inch;
	float    disk_work_col_inch;

	memcpy(&axis_x_fetch_init_point,&DReg[F_FETCHINITPOSX],sizeof(float));
	memcpy(&axis_y_fetch_init_point,&DReg[F_FETCHINITPOSY],sizeof(float));
//	memcpy(&axis_y_avoid_point,&DReg[F_AVOIDPOSY],sizeof(float));
	memcpy(&disk_work_row_inch,&DReg[F_DISKROWINCH],sizeof(float));
	memcpy(&disk_work_col_inch,&DReg[F_DISKCOLINCH],sizeof(float));
	delay_time0 = DReg[F_DELAYTIME0];
	delay_time1 = DReg[F_DELAYTIME1];
	delay_time2 = DReg[F_DELAYTIME2];
	
	// init all axes move speed
	for(i=0;i<5;i++)SetMakeSpeed(i+1,speed[i]);
		
	// (*********************************************************************************************)
	// (******************************* fetch work from install-disk ********************************)
	// get current work offset position in install-disk
	if(DReg[F_DISKWORKNUM] != 0)disk_total = DReg[F_DISKWORKNUM];
	else disk_total = DReg[F_DISKROWNUM] * DReg[F_DISKCOLNUM];
	total = DReg[F_DISKROWNUM] * DReg[F_DISKCOLNUM];
	
	DReg[F_CURTAKENUM] = 0;
   for(i=0;;i++)
	{
		if((i%4 == 0) || (i%4 == 1))
		{
			i = i;
		}
		else if((i%4 == 2) || (i%4 == 3))
		{
			DReg[F_CURTAKENUM]++;
			DReg[F_TOTALNUM]++;
			continue;
		}
			
		offset[AXIS_X] = ((int)((DReg[F_CURTAKENUM] % total) % DReg[F_DISKROWNUM])) * disk_work_row_inch;
		offset[AXIS_Y] = ((int)((DReg[F_CURTAKENUM] % total) / DReg[F_DISKROWNUM])) * disk_work_col_inch;

		// axis-X run to install-disk prepare position to fetch work
		ftemp[0] = axis_x_fetch_init_point + offset[AXIS_X] - GetMacPosMm(1);
		if(G00RelPos(1,ftemp[0],speed[0][0],speed[0][1],speed[0][2]) == -1)goto JUMP00;
		
		if(DReg[F_DELAYENABLE] == 1)
		{
			if(OSDelay(delay_time0) == -1)goto JUMP00;
		}
		
		if(DReg[F_DELAYENABLE] == 1)
		{
			if(OSDelay(delay_time2) == -1)goto JUMP00;
		}
		else
		{
			if(DReg[F_SIGNALEN] == 1)
			{
				WriteOutput(OUTPUT01,1);
			}
		}

		// axis-Y run to install-disk prepare position to fetch work
		ftemp[0] = axis_y_fetch_init_point + offset[AXIS_Y] - GetMacPosMm(2);
		if(G00RelPos(2,ftemp[0],speed[1][0],speed[1][1],speed[1][2]) == -1)goto JUMP00;	
				
		if(DReg[F_DELAYENABLE] == 1)
		{
			if(OSDelay(delay_time1) == -1)goto JUMP00;
		}
		else
		{
			if(DReg[F_SIGNALEN] == 1)
			{
				WriteOutput(OUTPUT01,0);
			}
			while(1)
			{
				ModbusServe(0);
				if(ReadInput(INPUT01) == 0)break;				
				DispAxisPosition();
				UpdateAxisParam();
				DispInput();
				DispOutput();
				if(ServoAlarmCheck() == -1)goto JUMP00;
				if(LimitPosCheck() == -1)goto JUMP00;
				if(LimitInputCheck() == -1)goto JUMP00;
				if(StartFlag)DispPowerOnTime();
				if((DReg[F_STOPBTN] == 1) || (ReadInput(STOPIN) == 0))goto JUMP00;
			}
		}
		
		if(DReg[F_DELAYENABLE] == 1)
		{
			if(OSDelay(delay_time2) == -1)goto JUMP00;
		}
		
		// fetched work form disk number plus
		DReg[F_CURTAKENUM]++;
		DReg[F_TOTALNUM]++;		
	}
	// CRC-check for saving parameter real time
	UserValueCrcCheck();
	return 1;
	
JUMP00:
	// CRC-check for saving parameter real time
	UserValueCrcCheck();
	OSDelay(20);
	return -1;
}
/****************************************************************************************
Function :	teach param execute
Parameter:   
Return   :
****************************************************************************************/	
int8_t TeachParamExecute(void)
{
	int16_t i=0;
	struct _FUNCPARAM FP;

	if(PauseLineIndex < DReg[F_RUNLINE])PauseLineIndex = DReg[F_RUNLINE];
	for(i=DReg[F_RUNLINE];;i++)       // run from settting line
	{
		if(PauseFlag == 1)
		{
			if(i < PauseLineIndex)continue;
			PauseFlag = 0;
		}		
		PauseLineIndex = i;
		if(DReg[F_MAKEMODE000+i] == 0)break;
		memcpy(&FP.MakeData1,&DReg[F_MAKEDATA1000+2*i],sizeof(float));
		memcpy(&FP.MakeData2,&DReg[F_MAKEDATA2000+2*i],sizeof(float));
		memcpy(&FP.MakeData3,&DReg[F_MAKEDATA3000+2*i],sizeof(float));
		memcpy(&FP.MakeData4,&DReg[F_MAKEDATA4000+2*i],sizeof(float));
		memcpy(&FP.MakeData5,&DReg[F_MAKEDATA5000+2*i],sizeof(float));
		memcpy(&FP.MakeData6,&DReg[F_MAKEDATA6000+2*i],sizeof(float));
		if(DReg[F_MAKEMODE000+i] == CM_G00)
		{
			if(G00Func(FP) == -1)return -1;
		}
		else if(DReg[F_MAKEMODE000+i] == CM_G01)
		{
			if(G01Func(FP) != 1)return -1;
		}
		else if(DReg[F_MAKEMODE000+i] == CM_OUT)
		{
			OutputFunc(FP);
		}
		else if(DReg[F_MAKEMODE000+i] == CM_IN)
		{
			if(InputFunc(FP) == -1)return -1;
		}
		else if(DReg[F_MAKEMODE000+i] == CM_DELAY)
		{
			if(DelayFunc(FP) == -1)return -1;
		}
		else if(DReg[F_MAKEMODE000+i] == CM_ARC)
		{}
		else if(DReg[F_MAKEMODE000+i] == CM_FUNC)
		{
			if(UserFunc(FP) == -1)return -1;
		}
//		if(DReg[F_CONTINUEBTN] == 1)
//		{
//			while(DReg[F_STARTBTN] != 1)
//			{
//				DispPowerOnTime();
//				OSDelay(10);
//			}
//		}
	}
	DReg[F_TOTALNUM] += 1;
	return 1;
}
/****************************************************************************************
Function :	teach param execute
Parameter:   
Return   :
****************************************************************************************/	
void TeachParamExecuteA(void)
{
	int16_t i=0;
	struct _FUNCPARAM FP;

	MouldAFlag = 1;
	WriteOutput(OUTPUT05,1);
	for(i=0;;i++)       // run from settting line
	{
/*		if(DReg[F_MAKEMODE00+i] == 0)break;
		memcpy(&FP.MakeData1,&DReg[F_MAKEDATA100+2*i],sizeof(float));
		memcpy(&FP.MakeData2,&DReg[F_MAKEDATA200+2*i],sizeof(float));
		memcpy(&FP.MakeData3,&DReg[F_MAKEDATA300+2*i],sizeof(float));
		memcpy(&FP.MakeData4,&DReg[F_MAKEDATA400+2*i],sizeof(float));
		memcpy(&FP.MakeData5,&DReg[F_MAKEDATA500+2*i],sizeof(float));
		FP.MakeData6 = DReg[F_MAKEDATA600+i];*/
		if(FPA[i].MakeMode == CM_NULL)break;
		FP.MakeMode = FPA[i].MakeMode;
		FP.MakeData1 = FPA[i].MakeData1;
		FP.MakeData2 = FPA[i].MakeData2;
		FP.MakeData3 = FPA[i].MakeData3;
		FP.MakeData4 = FPA[i].MakeData4;
		FP.MakeData5 = FPA[i].MakeData5;
		FP.MakeData6 = FPA[i].MakeData6;
		if(FP.MakeMode == CM_G00)
		{
			if(G00Func(FP) == -1)break;
		}
		else if(FP.MakeMode == CM_G01)
		{}
		else if(FP.MakeMode == CM_OUT)
		{
			OutputFunc(FP);
		}
		else if(FP.MakeMode == CM_IN)
		{
			InputFunc(FP);
		}
		else if(FP.MakeMode == CM_DELAY)
		{
			WriteOutput(OUTPUT07,1);
			DelayFunc(FP);
			WriteOutput(OUTPUT07,0);
		}
		else if(FP.MakeMode == CM_FUNC)
		{
			UserFunc(FP);
			WriteOutput(OUTPUT06,1);
			OSDelay(FP.MakeData6);
			WriteOutput(OUTPUT06,0);
		}
		if(DReg[F_CONTINUEBTN] == 1)
		{
			while(DReg[F_STARTBTN] != 1)
			{
				DispPowerOnTime();
				OSDelay(10);
			}
		}
	}
	WriteOutput(OUTPUT05,0);
	MouldAFlag = 0;
}
/****************************************************************************************
Function :	teach param execute
Parameter:   
Return   :
****************************************************************************************/	
void TeachParamExecuteB(void)
{
	int16_t i=0;
	struct _FUNCPARAM FP;
	
	MouldBFlag = 1;
	WriteOutput(OUTPUT05,1);
	for(i=0;;i++)       // run from settting line
	{
/*		if(DReg[F_MAKEMODE00+i] == 0)break;
		memcpy(&FP.MakeData1,&DReg[F_MAKEDATA100+2*i],sizeof(float));
		memcpy(&FP.MakeData2,&DReg[F_MAKEDATA200+2*i],sizeof(float));
		memcpy(&FP.MakeData3,&DReg[F_MAKEDATA300+2*i],sizeof(float));
		memcpy(&FP.MakeData4,&DReg[F_MAKEDATA400+2*i],sizeof(float));
		memcpy(&FP.MakeData5,&DReg[F_MAKEDATA500+2*i],sizeof(float));
		FP.MakeData6 = DReg[F_MAKEDATA600+i];*/
		if(FPB[i].MakeMode == CM_NULL)break;
		FP.MakeMode = FPB[i].MakeMode;
		FP.MakeData1 = FPB[i].MakeData1;
		FP.MakeData2 = FPB[i].MakeData2;
		FP.MakeData3 = FPB[i].MakeData3;
		FP.MakeData4 = FPB[i].MakeData4;
		FP.MakeData5 = FPB[i].MakeData5;
		FP.MakeData6 = FPB[i].MakeData6;
		if(FP.MakeMode == CM_G00)
		{
			G00Func(FP);
		}
		else if(FP.MakeMode == CM_G01)
		{}
		else if(FP.MakeMode == CM_OUT)
		{
			OutputFunc(FP);
		}
		else if(FP.MakeMode == CM_IN)
		{
			InputFunc(FP);
		}
		else if(FP.MakeMode == CM_DELAY)
		{
			WriteOutput(OUTPUT08,1);
			DelayFunc(FP);
			WriteOutput(OUTPUT08,0);
		}
		else if(FP.MakeMode == CM_FUNC)
		{
			UserFunc(FP);
			WriteOutput(OUTPUT06,1);
			OSDelay(FP.MakeData6);
			WriteOutput(OUTPUT06,0);
		}
		if(DReg[F_CONTINUEBTN] == 1)
		{
			while(DReg[F_STARTBTN] != 1)
			{
				DispPowerOnTime();
				OSDelay(10);
			}
		}
	}
	WriteOutput(OUTPUT05,0);
	MouldBFlag = 0;
}
/****************************************************************************************
Function :	system run led
Parameter:   
Return   :
****************************************************************************************/	
void SystemRunLed(void)
{
/*	WriteOutput(OUTPUT01,1);
	WriteOutput(OUTPUT02,0);
	WriteOutput(OUTPUT03,0);
	DReg[F_OUTPUT01] = 1;
	DReg[F_OUTPUT02] = 0;
	DReg[F_OUTPUT03] = 0;
	*/
}
/****************************************************************************************
Function :	system stop led
Parameter:   
Return   :
****************************************************************************************/	
void SystemStopLed(void)
{
/*	WriteOutput(OUTPUT01,0);
	WriteOutput(OUTPUT02,1);
	WriteOutput(OUTPUT03,0);
	DReg[F_OUTPUT01] = 0;
	DReg[F_OUTPUT02] = 1;
	DReg[F_OUTPUT03] = 0;
	*/
}
/****************************************************************************************
Function :	system pause led
Parameter:   
Return   :
****************************************************************************************/	
void SystemPauseLed(void)
{
/*	WriteOutput(OUTPUT01,1);
	WriteOutput(OUTPUT02,1);
	WriteOutput(OUTPUT03,0);
	DReg[F_OUTPUT01] = 1;
	DReg[F_OUTPUT02] = 1;
	DReg[F_OUTPUT03] = 0;
	*/
}
/****************************************************************************************
Function :	system alarm led
Parameter:   
Return   :
****************************************************************************************/	
void SystemAlarmLed(void)
{
/*	WriteOutput(OUTPUT01,0);
	WriteOutput(OUTPUT02,0);
	WriteOutput(OUTPUT03,1);
	DReg[F_OUTPUT01] = 0;
	DReg[F_OUTPUT02] = 0;
	DReg[F_OUTPUT03] = 1;
	*/
}
