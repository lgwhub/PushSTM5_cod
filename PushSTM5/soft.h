#ifndef _SOFT_H
#define _SOFT_H


/**************** ѡ������汾��*************/
/*  ����汾��  */
//#define Soft_VER  0x05
//#define FIRST_PASS 0x20


extern uchar  InputBuf;
extern uchar  KeybyteBuf;
extern uchar FlagSetCurrent1;

/* �������� */
typedef unsigned char        BOOLEN;
typedef unsigned char        INT8U;
typedef signed char          INT8S;
typedef unsigned short       INT16U;
typedef signed short         INT16S;
typedef unsigned int         INT32U;
typedef signed int           INT32S;
typedef float                FP32;
typedef double               FP64;


#define BYTE                 INT8S
#define UBYTE                INT8U    
#define WORD                 INT16S
#define UWORD                INT16U
#define LONG                 INT32S
#define ULONG                INT32U

//�㶯
#define COMMAND_C1	0X11		//��һ�µ�һ·��ת���κ�һ·תʱ����ֹͣ
#define COMMAND_CC1	0X21		//��һ�µ�һ·��ת���κ�һ·תʱ����ֹͣ
#define COMMAND_C2	0X12		//��һ�µڶ�·��ת���κ�һ·תʱ����ֹͣ
#define COMMAND_CC2	0X22		//��һ�µڶ�·��ת���κ�һ·תʱ����ֹͣ
#define COMMAND_C3	0X13
#define COMMAND_CC3	0X23

//�Զ�����
#define COMMAND_A1	0X31			//��һ�µ�һ·��ת
#define COMMAND_AA1	0X41			//��һ�µ�һ·��ת
#define COMMAND_A2	0X51			//��һ�µڶ�·��ת
#define COMMAND_AA2	0X61			//��һ�µڶ�·��ת	
#define COMMAND_A3	0X71			//��һ�µ���·��ת
#define COMMAND_AA3	0X81			//��һ�µ���·��ת		



//�綯����
#define REMOT_COMMAND_MOT3_CW		0X51
#define REMOT_COMMAND_MOT3_CCW		0X55
#define REMOT_COMMAND_MOT4_CW		0X52
#define REMOT_COMMAND_MOT4_CCW		0X56
#define REMOT_COMMAND_MOT3_MOT4_CW		0X53
#define REMOT_COMMAND_MOT3_MOT4_CCW		0X57
#define RESPONES_RUNING			0X68
#define RESPONES_COMMPLETE		0X69
//�綯��������
#define REMOT_COMMAND_SHIFT_SET_ID		0X6C
//�����綯��������
#define REMOT_COMMAND_SET_RATE3		0X6D
//�綯�����ܿ��ƿ�
#define REMOT_COMMAND_PUSH_POWER_ON		0X6F
////////////////
#define REMOT_COMMAND_POWER_ON		0X39
#define REMOT_COMMAND_POWER_OFF		0X49
#define REMOT_COMMAND_MOT1_CW		0X31
#define REMOT_COMMAND_MOT1_CCW		0X41
#define REMOT_COMMAND_MOT2_CW		0X32
#define REMOT_COMMAND_MOT2_CCW		0X42

#define REMOT_COMMAND_MOT1_CW_MOT2_CCW	0X33
#define REMOT_COMMAND_MOT2_CW_MOT1_CCW	0X43

#define REMOT_COMMAND_MOT1_MOT2_CW	0X34
#define REMOT_COMMAND_MOT1_MOT2_CCW	0X44

//ң������Դ����
#define REMOT_COMMAND_REMOT_HAND_ON	0X38
//������Ƽ��շſ�
#define REMOT_COMMAND_MOT1_MOT2_OFF	0x48
#define REMOT_COMMAND_SET_ID		0X59

//���Է�ʽ
#define REMOT_COMMAND_DEBUG		0X25
//��������
#define REMOT_COMMAND_SET_RATE1		0X21
#define REMOT_COMMAND_SET_RATE2		0X22

#define REMOT_COMMAND_PARA_INIT	0x29

#define REMOT_COMMAND_TEST1		0X5A

#define REMOT_COMMAND_SET_SUB   0X76


#define REMOT_COMMAND_TEST_UART1   0X70
#define REMOT_COMMAND_TEST_UART2   0X71
#define REMOT_COMMAND_TEST_UART3   0X72


#define REMOT_COMMAND_TEST_STATUS	 0X73
/////////////////////////////////////////////////////////////////////////
////////////////////////////////���صı����ź�/////////////////////////////////////////

#define STATUS_POWER_ON  0x74
#define STATUS_POWER_OFF  0x75
//�¶ȱ������
#define ALM_TEMPERATURE		0X62

//����ѹ�������
#define ALM_VOLTHIGH			0X64

//Ƿ��ѹ�������
#define ALM_VOLT_LOW			0X63

//�������������
#define ALM_CURRENT1			0X61

//�������������
#define ALM_CURRENT2			0X60


/**************************************************************************************************/
extern uchar bTimeBase;

#define LED_CURRENT_ON			SetLed3
#define LED_CURRENT_OFF			ClrLed3


#define LED_RUN_ON			SetLed2
#define LED_RUN_OFF			ClrLed2
#define LED_RECV_ON			;//SetLed1
#define LED_RECV_OFF		;//ClrLed1


#define LED_Al_Box		SetLed1
#define LED_Fe_Box		ClrLed1

extern unsigned char Time_LedRecv_LED;

#if CONFIG_433SG
			//LED�Զ�Ϩ��
			extern unsigned char Time_TestProc_LED1;
			extern unsigned char Time_TestProc_LED2;
			
			extern uint PulseCount;
#endif			
			extern uchar LastCommand;	//�ϴ�����
			
//			extern uchar SamCommandTime;	//�ظ�������ʱ��	
			

 			
			extern uchar SetIdTime;			//����IDʱ��





extern uchar bExCurrentForwardMax;
extern uchar bExCurrentBackwardMax;

struct	struct_save
{

		//uchar bCurrentForward;			//��������1(uint=0.2A)
		//uchar bCurrentBackward;			//��������2(uint=0.2A)
		uchar bCurrentRate;			//������������200-206-220(uint=0.2A)		
		
		#if CONFIG_433SG 
				uchar RemotName[2];
				uchar xxx[2];
		#elif CONFIG_CC1100
				uchar RemotName[3];
				uchar xxx[2];
		#endif
		
		
		uchar flag;				//�����Ѿ���ʼ�����
};

extern struct	struct_save *gpParam;
//#define Max_Param_Len		8
#define Max_Param_Len		12
//�����Ѿ���ʼ�����
#define FlagParamInitnized	0xA9
extern uchar gbParamBuf[Max_Param_Len+2];

//������EEPROM���׵�ַ
#define EEPROM_BASE_ADR	0X4010


void SendToRemot(uchar command); //������ң����

extern uint16 giCodeChecksum;

void Execute(uchar cmd);
void ParamSend(void);
void AutoSend(void);
void SendText_UART0(INT8U *StrData);
	#if CONFIG_433SG
			void RemotCodeSend(uchar *command1,uchar comlen1);
	#endif

void CheckKey(void);		//����10ms
void CheckInput(void);
void Work(void);
void Default_ParamInit(void);


void Load_Param(void);
void Write_Param(void);






#endif










