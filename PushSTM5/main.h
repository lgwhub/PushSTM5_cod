#ifndef _MAIN_H
#define _MAIN_H
//    ���1MS��λ��ʱͨ���ӳ���
//void DelayMs(unsigned int x);
void DelayMs(unsigned short int x);
void work(void);  /*  ��PC��Ҳ��������  */

/* ����ʱָʾ����˸  */
void LedStart(void);
/* ����ת��  */

void RstWdog(void);

void LedContral(void);

/////////
void AdcProcess(void);

extern uchar chAdc_Resoult6;
extern uchar chAdc_Resoult7;

extern unsigned short int AdcBuf[2+2];



void PwmContral1(uchar x);	//OC1A PWM1 ����
//void PwmContral2(uchar x);	//OC1B PWM2 ����


#endif








