#ifndef _HD_PUSH_STM5_H
#define _HD_PUSH_STM5_H

//#define OSSCAL_AT_MEGA48_FLASH	(*(const unsigned char *)(0xfff))

#define Enable_TEST_FREQ_PIN	
#define Not_TEST_FREQ_PIN		


//out

#define JspOut0_OFF			GPIO_WriteLow(GPIOE,GPIO_PIN_5)
#define JspOut0_ON			GPIO_WriteHigh(GPIOE,GPIO_PIN_5)

#define JspOut1_OFF			GPIO_WriteLow(GPIOC,GPIO_PIN_3)
#define JspOut1_ON			GPIO_WriteHigh(GPIOC,GPIO_PIN_3)

#define JspOut2_OFF			GPIO_WriteLow(GPIOC,GPIO_PIN_5)
#define JspOut2_ON			GPIO_WriteHigh(GPIOC,GPIO_PIN_5)

//PWM_OUT


#define Input4	GPIO_ReadInputData(GPIOB)



//S2 AN1 PC6 SetId
#define K5_LVL	(GPIO_ReadInputPin(GPIOC,GPIO_PIN_6))
//S1  AN2 PD3 设置电流
#define K3_LVL	(GPIO_ReadInputPin(GPIOD,GPIO_PIN_3))

//AN3 PD4 select  //选择铁箱体跳线
#define K4_LVL	(GPIO_ReadInputPin(GPIOD,GPIO_PIN_4))

//  ADC2 PB2
#define K1_LVL  (GPIO_ReadInputPin(GPIOB,GPIO_PIN_2))

#define K2_LVL


#define ClrLed1		GPIO_WriteLow(GPIOA,GPIO_PIN_6)
#define SetLed1			GPIO_WriteHigh(GPIOA,GPIO_PIN_6)

#define ClrLed2		GPIO_WriteLow(GPIOA,GPIO_PIN_5)
#define SetLed2			GPIO_WriteHigh(GPIOA,GPIO_PIN_5)

#define ClrLed3		GPIO_WriteLow(GPIOA,GPIO_PIN_4)
#define SetLed3			GPIO_WriteHigh(GPIOA,GPIO_PIN_4)



///////////////////////////
//CC1100 IO
/*******************IO定义(根据具体情况重新定义)*******************/


//IO数据输出寄存器
#define SET_CC1100_SCLK  GPIO_WriteHigh(GPIOG,GPIO_PIN_1)
#define SET_CC1100_CSN   GPIO_WriteHigh(GPIOD,GPIO_PIN_2)
#define SET_CC1100_SI    GPIO_WriteHigh(GPIOG,GPIO_PIN_0)

#define CLR_CC1100_SCLK  GPIO_WriteLow(GPIOG,GPIO_PIN_1)
#define CLR_CC1100_CSN   GPIO_WriteLow(GPIOD,GPIO_PIN_2)
#define CLR_CC1100_SI    GPIO_WriteLow(GPIOG,GPIO_PIN_0)

//IO读管脚寄存器
#define CC1100_SO_LVL    (GPIO_ReadInputPin(GPIOE,GPIO_PIN_0))
#define CC1100_GDO2_LVL  (GPIO_ReadInputPin(GPIOD,GPIO_PIN_0))
//#define CC1100_GDO0_LVL  ()
/*******************IO初始化(根据具体情况重新定义)********************/
#define cc1100_IO_INITIALIZTION()  \
CC1100_SCLK_ENABLE;\
CC1100_CSN_ENABLE;\
CC1100_SI_ENABLE;\
CLR_CC1100_SCLK;\
SET_CC1100_SO;\
SET_CC1100_GDO2;\
SET_CC1100_GDO0;\
SET_CC1100_CSN;\
CLR_CC1100_SI




#define PWM_MAX_VAL	252
#define PWM_MIN_VAL	10

////////////////////////////////////////////////////

#define SetEn485_1    ;
#define ClrEn485_1    ;
#define SetEn485_2    ;
#define ClrEn485_2    ;
#define SetEn485_3    ;
#define ClrEn485_3    ;


void InitGpio(void);
//UART
////OS_VIEW_UART				     UART1
//TXD1  PA9


#if CONFIG_UART1
void  UART1_RxISRHandler (void);
void  UART1_TxISRHandler (void);
void InitUART1(uint32 baud_rate,uint16_t parity);
#endif

#if CONFIG_UART2

void  UART2_TxISRHandler (void);

void  UART2_RxISRHandler (void);
void InitUART2(uint32 baud_rate,UART2_Parity_TypeDef parity);


#endif

#if CONFIG_UART3
void  UART3_RxISRHandler (void);
void  UART3_TxISRHandler (void);
void InitUART3(uint32 baud_rate,uint16_t parity);
#endif


#endif
    


