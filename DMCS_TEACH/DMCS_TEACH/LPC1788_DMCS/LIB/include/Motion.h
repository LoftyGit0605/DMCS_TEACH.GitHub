#define AxisCount 8
#include "GlobalDefine.h"
//����ָ��
/*
struct LayoutCmd		
{
	long X;							//����Ŀ���	
	long Y;							//����Ŀ���	
	long Z;							//����Ŀ���
	long U;							//����Ŀ���
	long V;							//����Ŀ���
	unsigned long LineIndex;
	unsigned long Speed;			//�������ٶ�
	//unsigned long SpeedRate;  //andy2015.06.09
};
*/

// #define nLcmSizeOf		28
/////////////////////////////////


/////////////////////////////////

typedef struct LayoutCmd_PC LayoutCmd;

//��ʼ�����

void InitLink(void);   //��ʼ������
long LinkConnectTest(void);   //���Ӳ��ԣ�����0���Գɹ�

long SAxisPmove(unsigned char Axis, long Pulse,unsigned long StartV,unsigned long Acc,unsigned long Speed);
long SAxisDec_stop(unsigned char Axis);//��ֹͣ
long GetGPIO_Input(long *Dat);      //��ȡ����
long GetGPIO_Output(long *Dat);			//��ȡ���
//
long GetMotionStatus(unsigned long *Sta);     //��ȡ���˶�״̬
long GetPosDev(long *X, long *Y, long *Z, long *U, long *V, long *W, long *A, long *B);     //��ȡ��λ��
//�������岹�˶����к�
//��ѯ��ǰ�ӹ��켣ʵ��λ��
//�к�����д��켣ʱ�Լ������
//�켣�˶�

long GetWorkIndex(unsigned long *Dat);     //��ȡ�к�


//Ӳ��IO��λʹ�ܿ���
//=0 ʹ��
//=1 ʧ��
long Lmt_Disable(unsigned char Onoff);			//��λʧ��
//��ʼ�켣�滮
//=1 ��ʼ����
//=0 ֹͣ�켣�滮������켣��ֹͣ�滮
//��Ҫ���� ��ʼдһ�������ݽo�˶��滮��Ԫ��Ȼ���ڿ�ʼ����ֹ�˶�Ƶ���Ӽ���

long LayoutStart(unsigned char Onoff);			//�滮������д1�����滮��д0ֹͣ�滮
//���һ���к�,��ʾ�켣����һ�н���

long LocusEnd(unsigned long Index );
/*
��      ��:	���λ����
��      ��:	unsigned char BitIndex ָ����˿ں�(0 ~ 15)
			unsigned char BitValue ֻ����˿ڵĵ�ƽ(0 ~ 1)
*/
long SetGPIO_Output(unsigned char BitIndex, unsigned char BitValue);  //�������
//XLmtIo +��λIO
//XLmtBIo -��λIO
//XLmtLog ��λ��Ч��ƽ
//XLmtBLog ��λ��Ч��ƽ
long SetLmtMode(unsigned char XLmtIo,unsigned char YLmtIo,unsigned char ZLmtIo,unsigned char ULmtIo,unsigned char VLmtIo,
				unsigned char XLmtBIo,unsigned char YLmtBIo,unsigned char ZLmtBIo,unsigned char ULmtBIo,unsigned char VLmtBIo,
				unsigned char XLmtLog,unsigned char YLmtLog,unsigned char ZLmtLog,unsigned char ULmtLog,unsigned char VLmtLog,
				unsigned char XLmtBLog,unsigned char YLmtBLog,unsigned char ZLmtBLog,unsigned char ULmtBLog,unsigned char VLmtBLog);
						 
						 
//���õ������
long SetMotionDir(unsigned short Value);  // �����᷽��
//��Ҫ�ô����㵱ǰλ�ã���������λ��
long SetPosDev(short Axis, long Pos);    //������λ��
//����ֹͣ
long sudden_stop(unsigned char Axis);		
						 
//���������켣��ʼ�� ��ǰ��
//��ʼ�켣ǰ��ȡ��ǰλ�ã������ú������������켣��ʼ��
long BufOrg(long X, long Y, long Z, long U, long V);
//�켣�������� �����ٶ�  ��С�ٶ�  ���ٶ�  ����ٶ�  ת���ٶ�
long MotionConfig(unsigned long StartV,unsigned long MinSpeed,unsigned long Acc,unsigned long Speed,unsigned long AngleSpeed);
//��ʼ�켣,�����ÿ�ʼȻ��д��켣
long BufStart(void);
//����켣����
long BufClr(void);
//�켣����ֹͣ
long BufStop(void);
//�켣Ŀ��λ�÷��� �켣Ŀ��λ��������  ���ݿ�ʼ�±� ��������  ���سɹ�д�˶�����
//LayoutCmd_PC ʵ��������ÿ������ٸ����壨λ�ó������嵱�����������Сֵ��
long BatchLine(struct LayoutCmd_PC *Cmd,unsigned short BeginIndex, unsigned char Count,unsigned char *ResV);
//long BatchAxisScale_Remote(, float *Val);
//�������嵱��������
//���� ˿��תһȦʵ���ߵľ��� ��λһ����mm A
//˿��תһȦ��Ҫ��������� B
//���嵱�� A/B
//���ݻ������ÿ�����ǲ�һ���� ��е���
//ʵ�ʼ����ÿ��������嵱����һ��С���嵱����Ϊ��ĸ�������������嵱����Ϊ���ӣ���������嵱������
//�˶��������������ʹ�õ�
long SetAxisScale( float *Val);

long SetSmoothLevel(unsigned char Level);  //���64��
//��������ģʽ(1:���� 0:������)
long SetMoveTogetherMode(unsigned char X,unsigned char Y,unsigned char Z,unsigned char U,unsigned char V);
long GetSTM32VerDev(unsigned long *Ver);    //��ȡstm32�汾��
long GetFpgaVerDev(unsigned long *Ver);     //FPGA�汾��

//����
long SynAxisConfig(unsigned long StartV,unsigned long Acc,unsigned long Speed,unsigned long LoopMax);
long SetAxisMap(unsigned char *MapDat);     //���ú���,��������Ӧ
long SetSynGpoutMask( unsigned short Mask); //���ú���,��������Ӧ

//long FPGAPortTest_Remote(long addr,long *Dat);
//long BatchSpeedSet_Remote(unsigned long Speed);
long GetTimeOut(void);          //����
void SetTimeOut(long Value);    //���� 
short GetReSend(void);          //����
void SetReSend(short Value);    //����
long GetErrPack(void);          //����
void SetErrPack(long Value);    //����
long GetTimePack(void);         //����
void SetTimePack(long Value);   //����