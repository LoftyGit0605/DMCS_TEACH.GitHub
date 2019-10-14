#include "GlobalDefine.h"
#ifndef BASEFORM_H_H_H
#define BASEFORM_H_H_H
#ifdef BASEFORM_H_H_H
typedef enum {
	KEYMODE_MIX = 0,	/* 0 */
	KEYMODE_SINGLE		/* 1 */
} KEYMODE;

struct RfForm
{
	unsigned long TimeInterval;						//定时器间隔时间(单位：10ms)

	void(*pInit)();	 								//初始化画面，需要把相关变量初始化，以及画面完全重绘
	void(*pDraw)();									//刷新画面事件处理，仅把会动态改变的部分重绘即可
	void(*pKeyDown)(unsigned long,KEYMODE);			//键被按下事件处理函数
	void(*pKeyUp)(unsigned long,KEYMODE);					//键被释放事件处理函数
	void(*pTimer)();								//定时器事件处理函数
	void(*pUnload)();								//退出画面事件处理函数
};


typedef enum {
	MsgButton_OkOnly = 0,	/* 0 */
	MsgButton_OkCancel,		/* 1 */
	MsgButton_YesNo,		/* 2 */
	MsgButton_YesNoOnlyZhome,/*3*/
	//MsgButton_YesNoCancel   /*3*/
} MSGBOX_BUTTON;
//
typedef enum {
	MsgRes_Ok = 0,			/* 0 */
	MsgRes_Cancel,			/* 1 */
	MsgRes_Yes,				/* 2 */
	MsgRes_No,				/* 3 */
    MsgRes_OnlyZ
} MSGBOX_RESULT;
//
typedef enum {
	RF_TASKSTA_NONE = 0,			/* 0 */
	RF_TASKSTA_RUN,			/* 1 */
} RF_TASKSTA;

struct Rf_Task
{
	RF_TASKSTA Status;	
	void(*pTask_Sub)();	 					
};

#define TASKCOUNT	1		 //最大任务数

extern struct Rf_Task TaskList[TASKCOUNT];
extern unsigned char TaskNumber;

void BaseForm_Service(void);
void BaseForm_Load(struct RfForm *pForm);
void BaseForm_Refurbish(void);

extern unsigned long mKeycode;
unsigned char AddTask(void(*pSub)());
void ClearTask(void);
void DelTask(void(*pSub)());
void Doevents(unsigned short T);
void BaseForm_GetKeyCode(unsigned long *KeyVal,unsigned long *OldKeyVal);

#define DrawInterval	5;

#define KeyBitCount		32	 	//按键位数

#define Key_None   0xFFFFFFFF
extern unsigned int KeyCode;

#endif
#endif

