#ifndef _CONFIG_H
#define _CONFIG_H

////////ѡ���Ź�//////
#define EnWdog 				0



//���õ������ߵ������
#define CONFIG_CC1100		1
//���õ������ߵ������
#define CONFIG_433SG		0
#define CC1100_PKT_LEN 32

//��ֹ��ƤȦѹ��̫������ת�˵��׺��Զ���תһ�㣬����
#define CONFIG_UNPUSH		1
//ѡ��������
#define Config_Al_Box		1


//IOCFG0_DIV128;				//���Ծ���Ƶ��
#define CONFIG_26MHZ_OSC_OUT		1
		
//FREQ0_ADJ_260018;		//����1.000153  ��ģ�龧��ƫ�� 	
#define USER_NEW_OSC		1



//��������ʱ��
//#define MAX_RUN_TIME_sec	(72)
#define MAX_RUN_TIME_sec	(720)
//85%�����µ�������ʱ��
#define Time10000Ms					1000
//94%�����µ�������ʱ��
#define Time2000Ms					200

//3.3V�ο��µ�����������
//gpParam->bCurrentRate ( 200 - 220 )
//#define CURRENT_RATE	(114)
#define CURRENT_RATE	(168)
//gpParam->bCurrentRate=CURRENT_RATE;			//���3�� 5A

//�����ת�������趨ֵ�����ֵΪ127  18A   max=256*75%=192

//#define CURRENT_FORWARD	(85)
#define CURRENT_FORWARD	(75)
//�����ת���ɵ��趨ֵ�����ֵΪ127  16A
//#define CURRENT_BACKWARD 78
#define CURRENT_BACKWARD 72
//#define CURRENT_BACKWARD 75




///////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
/////////////////////����Ϊһ�㲻��Ҫ�ı������////////////////////////////////
///////////////////////////////////////////////////////////////////////////////





//������Ϊ�Զ����ܣ��ſ��������ٰ��ſ���Ϊ�ֶ�����
#define CONFIG_FUNCTION_AUTO	1
//���Ӷ������Զ������о�������
//#define CONFIG_AUTOKEY	0



#endif