#ifndef _MAIN_H
#define _MAIN_H
//    软件1MS单位延时通用子程序
//void DelayMs(unsigned int x);
void DelayMs(unsigned short int x);
void work(void);  /*  在PC上也可以运行  */

/* 启动时指示灯闪烁  */
void LedStart(void);
/* 亮灭转换  */

void RstWdog(void);

void LedContral(void);

/////////
void AdcProcess(void);

extern uchar chAdc_Resoult6;
extern uchar chAdc_Resoult7;

extern unsigned short int AdcBuf[2+2];



void PwmContral1(uchar x);	//OC1A PWM1 控制
//void PwmContral2(uchar x);	//OC1B PWM2 控制


#endif








