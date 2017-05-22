#ifndef _DECODE_H
#define _DECODE_H

#define MAX_DECODE_BUF_LEN	6
#define LENGTH_REMOT_PARK	4





#define TestProc_LED1_ON	;//SetLed1
#define TestProc_LED1_OFF	;//ClrLed1
#define TestProc_LED2_ON	;//SetLed2
#define TestProc_LED2_OFF	;//ClrLed2

#define LED_RECV_ON		;//SetLed2
#define LED_RECV_OFF	;//ClrLed2


#define DatTypeX	unsigned char
//#define DatTypeX	unsigned int 

//#define Fosc  8000000
//#define Fosc	  (8000000/2)

	//�Ľ��ĸ��ٱ���
	#define DECODE_TIME1	(Fosc*2/10000/256)
	#define DECODE_TIME2	(Fosc*5/10000/256)
	#define DECODE_TIME3	(Fosc*6/10000/256)
	#define DECODE_TIME4	(Fosc*12/10000/256)


extern DatTypeX DecodeLastTime;	//�ϴ�����ʱ��
extern unsigned char DecodeTimeout;	//���峬ʱ��ʱ��
extern unsigned char FlagDecodeStart;	//ǰ���ѽ���
extern unsigned char DecodeStartCount;	//ǰ��������ռ�����
extern unsigned char DecodeBitCount;	//λ������
extern unsigned char DecodeByteCount;	//�ֽڼ�����
extern unsigned char DecodeByte;
extern unsigned char DecodeString[];
extern unsigned char DecodeCompleteFlag;	//ָ��������

//extern unsigned char DecodeActBitCount;	//�Ϸ����������
//extern unsigned char DecodeLastProcessCount;	//�ϴκϷ�����Ƚϼ�����

void InitDecode(void);
void _GetPulseProcess(unsigned char flag);	//���յ����崦��
void DecodePulse(DatTypeX cap_time);

#endif

