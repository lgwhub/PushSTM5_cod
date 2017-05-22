
#include "nomal.h"
#include "config.h"



#if CONFIG_433SG

#include "soft.h"
#include "main.h"
#include "Hd_ElecPush5.H"
#include "Decode.h"



DatTypeX	DecodeLastTime;	//�ϴ�����ʱ��
unsigned char DecodeTimeout;	//���峬ʱ��ʱ��
unsigned char FlagDecodeStart;	//ǰ���ѽ���
unsigned char DecodeStartCount;	//ǰ��������ռ�����
unsigned char DecodeBitCount;	//λ������
unsigned char DecodeByteCount;	//�ֽڼ�����
unsigned char DecodeByte;
unsigned char DecodeString[MAX_DECODE_BUF_LEN+10];
unsigned char DecodeCompleteFlag;	//ָ��������

//unsigned char DecodeActBitCount;	//�Ϸ����������
//unsigned char DecodeLastProcessCount;	//�ϴκϷ�����Ƚϼ�����


void InitDecode(void);
void _GetPulseProcess(unsigned char flag);	//���յ����崦��
void DecodePulse(DatTypeX cap_time);

////
void InitDecode(void)
{
unsigned char i;
	DecodeLastTime=0;	//�ϴ�����ʱ��
	DecodeTimeout=0;	//���峬ʱ��ʱ��

	DecodeByte=0;
	
	DecodeBitCount=0;	//λ������
	DecodeByteCount=0;	//�ֽڼ�����
	FlagDecodeStart=0;	//ǰ���Խ���
	DecodeStartCount=0;	//ǰ��������ռ�����
	DecodeCompleteFlag=0;
	
	for(i=0;i<MAX_DECODE_BUF_LEN;i++)
		{
			DecodeString[i]=0;
		}
}
//////
void _GetPulseProcess(unsigned char flag)	//���յ����崦��
{
	if(flag==1)	//���յ�����1
		{
		if(DecodeStartCount<100)DecodeStartCount++;	//ǰ��������ռ�����
		if(FlagDecodeStart)	//ǰ���ѽ���
			{
			DecodeByte<<=1;	
			DecodeByte|=1;	//����1
			DecodeBitCount++;	//λ������
			if(DecodeBitCount>=8)
				{
				if(DecodeByteCount<MAX_DECODE_BUF_LEN)
					{	
					DecodeString[DecodeByteCount]=DecodeByte;	
					DecodeByteCount++;
					
					if(DecodeByteCount>=LENGTH_REMOT_PARK)
						{//ָ�������ɱ��
						DecodeString[DecodeByteCount]=0x0;
						DecodeCompleteFlag=1;
						DecodeByteCount=0;
						DecodeTimeout=0;
						//TestProc_LED3_OFF;	//���
						}
					}
				DecodeBitCount=0;	
				}	
				
			}
		}
	else{	//���յ�����0

		if(DecodeStartCount>10)	//16
			{
			if(FlagDecodeStart==0)	//ǰ��δ����
				{
				DecodeBitCount=0;	//λ������
				DecodeByteCount=0;	//�ֽڼ�����	
				FlagDecodeStart=1;
				}	
			//TestProc_LED3_ON;
			}
			
		if(FlagDecodeStart)	//ǰ���ѽ���
			{
			DecodeByte<<=1;	
			DecodeBitCount++;	//λ������
			if(DecodeBitCount>=8)
				{
					
				if(DecodeByteCount<MAX_DECODE_BUF_LEN)
					{	
					DecodeString[DecodeByteCount]=DecodeByte;	
					DecodeByteCount++;
					
					
					
					if(DecodeByteCount>=LENGTH_REMOT_PARK)
						{//ָ�������ɱ��
						
						DecodeString[DecodeByteCount]=0x0;
						DecodeCompleteFlag=1;
						DecodeByteCount=0;
						DecodeTimeout=0;
						//TestProc_LED3_OFF;	//���
						}
					}
				DecodeBitCount=0;	
				}
			}	
		DecodeStartCount=0;	//ǰ��������ռ�����
		}	
}

//////////////////////////
void DecodePulse(DatTypeX cap_time)
{
//ң���������ж�  timer0 int1
//unsigned int temp2;	//����
DatTypeX temp2;	//����
	if(DecodeTimeout<100)
		{
		temp2=cap_time-DecodeLastTime;	//����

		if(temp2>DECODE_TIME1)
			{
			if(temp2<DECODE_TIME2)
				{//DECODE_TIME1~DECODE_TIME2  ����
					//FlagDecodeStart=1;	//ǰ���Խ���
				//	DecodeActBitCount++;
					if(DecodeCompleteFlag==0)_GetPulseProcess(1);
					TestProc_LED2_ON;	//�յ�0
					Time_TestProc_LED2=50;
				}
			else if	(temp2>DECODE_TIME3)
				{
				if(temp2<DECODE_TIME4)
					{//DECODE_TIME3~DECODE_TIME4  ����
						//FlagDecodeStart=1;	//ǰ���Խ���
//						DecodeActBitCount++;
						if(DecodeCompleteFlag==0)_GetPulseProcess(0);
						TestProc_LED1_ON;
						Time_TestProc_LED1=50;
					}
				else{
					//�������¿�ʼ
					
					DecodeBitCount=0;
					DecodeByteCount=0;
					FlagDecodeStart=0;	//ǰ���Խ���
					DecodeStartCount=0;	//ǰ��������ռ�����
					//DecodeCompleteFlag=0;
					/* */
					}	
				}
			else{
				//�������¿�ʼ
				DecodeBitCount=0;
				DecodeByteCount=0;
				FlagDecodeStart=0;	//ǰ���Խ���
				DecodeStartCount=0;	//ǰ��������ռ�����
				//DecodeCompleteFlag=0;
				
				}
			}
		else{/*
				//�������¿�ʼ
				DecodeBitCount=0;
				DecodeByteCount=0;
				FlagDecodeStart=0;	//ǰ���Խ���
				DecodeStartCount=0;	//ǰ��������ռ�����
				//DecodeCompleteFlag=0;
				
				*/
				}
		//��λ��ǰ	

		}
	else{//��ʱ�����¿�ʼ
		DecodeBitCount=0;
		DecodeByteCount=0;
		FlagDecodeStart=0;	//ǰ���Խ���
		DecodeStartCount=0;	//ǰ��������ռ�����
		//DecodeCompleteFlag=0;
		}
DecodeLastTime=cap_time;	//�ϴ�����ʱ��
DecodeTimeout=0;

}

#endif