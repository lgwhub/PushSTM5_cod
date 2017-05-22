/* MAIN.C file
 * 
 *Copyright (c) 2002-2005 STMicroelectronics
 */


#include <includes.h>

static void CLK_Config(void);
static void UART_Config(void);
void ADC_Config(void);
void  PwmConfig_TIM1(void);
void TIM4_Config(void);	//����TIM4ÿ1MS����һ�������ж�

unsigned char AdcBuf[2+2];
uchar chAdc_Resoult6;
uchar chAdc_Resoult7;

//void PwmContral1(uint16 x);	//PWM1 ����
//void PwmContral2(uint16 x);	//PWM2 ����


void IWDG_Config(void)
{
#if EnWdog

IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);

IWDG_SetPrescaler(IWDG_Prescaler_256);

IWDG_SetReload(0xff);		//���1s

IWDG_ReloadCounter();

IWDG_Enable();
#endif
}



void RstWdog(void)
{
#if EnWdog
IWDG_ReloadCounter();

#endif
}



void DelayMs(unsigned short int x)
{
	unsigned short int i;
	
	while(x>0)
	{
	x--;
	i=1500;
	while(i>0)
		{
			i--;
		}
		
	}
	
}


////////////////////////
void SendTestCC1100M(void) //�ϵ�ʱ��ס�����Ͳ��԰�
{

uchar buf[36+14];
uchar len;
uint16	iTimeout;;	

for(len=0;len<30;len++)
		{
		buf[len]='*';
		}


buf[0]=0x31;	//1~8
buf[1]=gpParam->RemotName[0];
buf[2]=gpParam->RemotName[1];
buf[3]=gpParam->RemotName[2];
buf[4]=REMOT_COMMAND_POWER_OFF;
buf[5]=giCodeChecksum>>8;
buf[6]=giCodeChecksum&0xff;
buf[7]=0x70;



						len=8;
						len		+=	MakeValAsc8("K",gpParam->bCurrentRate,",",&buf[len]);	//
						len+=MakeValAsc8("I",gpParam->bCurrentForward,",",&buf[len]);
						len+=MakeValAsc8("",gpParam->bCurrentBackward,",",&buf[len]);
						len+=MakeValAsc8("F",cc1100regcfg[2],",",&buf[len]);
						



buf[30]=0x0d;
buf[31]=0x0a;
buf[32]=0x00;

if(K5_LVL==0)
		{
			cc1100Initializtion();
			DelayMs(10);
		}
		

		iTimeout=0;
while((K5_LVL==0)&&(iTimeout<2000))
				{
					iTimeout++;
					cc1100Printf(buf);
					RstWdog();
				}
}
////////////////////////
uint16 GetCodeCheckSum(void)
{
	uint16 sum;
	uint16 i;
	const uchar *p;
	p=0;
	sum=0;
	for(i=0;i<8192;i++)  //mega88
			{
				sum+=*(p+i);
				
			}		

return sum;
}


void AdcProcess(void)
{//MAX_ADC_NUMBER
uint16 temp16;
uchar xxx;
//AdcBuf[i]


			

		
			
			//temp16=((Adc.sum7>>4)*33)>>8;	//(UINT=100mA)
			//temp16=((Adc.sum7>>4)*330)>>8;	//(UINT=10mA) max=1980mA
			//temp16=(Adc.sum[7]>>4);				//Big Error   Adc.sum��ΧΪ6-7
			temp16=AdcBuf[0];	//����  ����룬ȡ��λ
			if(FlagSetCurrent1==2)
					{//10A,��ʾ50
				if(temp16>25)		//�൱��RATE<256
							{
							xxx=10*5*128/(temp16);
							if  (xxx>60)	//�൱��temp16<
										{
										gpParam->bCurrentRate=(uchar)xxx;
										FlagSetCurrent1=3;
										}
							}
						}			
			
			/*
			if (temp16>(65535/330))temp16=(65535/330);
			chAdc_Resoult7 = (uchar)((temp16*330)>>8);
		*/
				if (temp16>(32768/gpParam->bCurrentRate))temp16=(32768/gpParam->bCurrentRate);
			chAdc_Resoult7 = (uchar)((temp16*gpParam->bCurrentRate)>>7);		//uint 200ma
			

}


void LedStart(void)   /* ����ʱָʾ����˸  */
{

	uchar i;

	for(i=0;i<3;i++)
	{
		
		SetLed1;
		ClrLed2;
		ClrLed3;
		
		DelayMs(50);
		ClrLed1;
		SetLed2;
		SetLed3;
		DelayMs(100);
		RstWdog();
	}


ClrLed1;
ClrLed2;
ClrLed3;

}

void InitOutLevelDefault(void)
{



}


main()
{  
	
			/* CLK configuration -----------------------------------------*/
	CLK_Config();
	
gpParam=(struct	struct_save	*)&gbParamBuf[0];		//�����ṹ��ָ��	
	
	InitOutLevelDefault();
	
	
InitAverage(AvergeBuf1);
AvergeOffset[0]=0;

InitAverage(AvergeBuf2);
AvergeOffset[1]=0;

	Default_ParamInit();	//Init_Param();
	

	IWDG_Config();
	

Load_Param();		//ȡ�趨ֵ

	
	InitGpio();
	TIM4_Config();	//����TIM4ÿ1MS����һ�������ж�
	
//BEEP_Init(BEEP_FREQUENCY_1KHZ);
//BEEP_Cmd(ENABLE);
			/* UART configuration -----------------------------------------*/
			
	ClearLoopBuf(&Uart2SendStruct,UART2_SEND_BUF_SIZE);	//������ͻ�����
	UART_Config();  
  
  PwmConfig_TIM1();
  
	ADC_Config();


	// ����CPUȫ���ж�
	enableInterrupts();   
	
	//while(1){};
	
//#if CONFIG_CC1100
cc1100Initializtion();
//#elif CONFIG_433SG
//InitDecode();
//#endif	
	
	
	
	
if(K5_LVL==0)
		{
			DelayMs(5);
			giCodeChecksum=GetCodeCheckSum();
			
			if(K5_LVL==0)
						{
						/*
						&ED,I1=048,I2=049,I3=050,ID=0000,
						&EC,I=000,In=00,Pu=0208
						&ER,3132333435
						*/
						SendText_UART2("***Push5**\r\n");
						ParamSend();
						AutoSend();
//								#if CONFIG_433SG
//										RemotCodeSend("12345",5);
//								#endif							
						SendTestCC1100M();//�ϵ�ʱ��ס�����Ͳ��԰�	
						}

		}		
RstWdog();
		


LedStart();   /* ����ʱָʾ����˸  */
JspOut0_ON;
		

RstWdog();

	while (1)
	{
		Work();
		RstWdog();	//
//		DelayMs_105(100);
//		GPIO_WriteReverse(GPIOE, GPIO_PIN_5);
//		//GPIO_WriteReverse(GPIOD, GPIO_PIN_0 | GPIO_PIN_2 | GPIO_PIN_3);
//		GPIO_WriteReverse(GPIOD, GPIO_PIN_0 );
//
//				SendText_UART2("ADC:");
//				//ȡADCֵ�����
//				for(i=0;i<10;i++)
//   			{
//   			MakeValAsc16("",AdcBuf[i],",",buf);
//   			SendText_UART2(buf);
//  			}
//  	SendText_UART2("\r\n");


//MakeValAsc16("",AdcBuf[9],"\r\n",buf);
//     			//MakeValAsc16("",ADC1_GetConversionValue(),"\r\n",buf);
//   			SendText_UART2(buf);	
  	
		//DelayMs_105(100);
		
		//cont6565++;
		//PwmContral3(cont6565);
		//PwmContral2(cont6565);
		
		//PwmContral1(cont6565);
		
	};
}


/**
  * @brief  Configure system clock to run at 16Mhz
  * @param  None
  * @retval None
  */
static void CLK_Config(void)
{
    /* Initialization of the clock */
    /* Clock divider to HSI/1 */
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);
}

/**
  * @brief  UART1 and UART3 Configuration for interrupt communication
  * @param  None
  * @retval None
  */
static void UART_Config(void)
{
  /* Deinitializes the UART1 and UART3 peripheral */
//    UART1_DeInit();
////    UART3_DeInit();
//    /* UART1 and UART3 configuration -------------------------------------------------*/
//    /* UART1 and UART3 configured as follow:
//          - BaudRate = 9600 baud  
//          - Word Length = 8 Bits
//          - One Stop Bit
//          - No parity
//          - Receive and transmit enabled
//          - UART1 Clock disabled
//     */
//    /* Configure the UART1 */
//    UART1_Init((uint32_t)9600, UART1_WORDLENGTH_8D, UART1_STOPBITS_1, UART1_PARITY_NO,
//                UART1_SYNCMODE_CLOCK_DISABLE, UART1_MODE_TXRX_ENABLE);
//    
//    /* Enable UART1 Transmit interrupt*/
//    UART1_ITConfig(UART1_IT_TXE, ENABLE);

    
 InitUART2(9600,UART2_PARITY_NO);
    
    /* Enable general interrupts */
    enableInterrupts();    
    
}
////////////////////////



////////////////////////
void ADC_Config(void)
{	
	//����ʼ��ADC
	ADC1_DeInit();
	//��ʼ��ADC,����ת��ģʽ
	//ADC1_Init(ADC1_CONVERSIONMODE_SINGLE,ADC1_CHANNEL_0,ADC1_PRESSEL_FCPU_D18,ADC1_EXTTRIG_TIM,DISABLE,ADC1_ALIGN_RIGHT, ADC1_SCHMITTTRIG_CHANNEL0, DISABLE);
	//ADC1_Init(ADC1_CONVERSIONMODE_SINGLE,ADC1_CHANNEL_0,ADC1_PRESSEL_FCPU_D18,ADC1_EXTTRIG_TIM,DISABLE,ADC1_ALIGN_RIGHT, ADC1_SCHMITTTRIG_CHANNEL0, DISABLE);	
	//ADC1_Init(ADC1_CONVERSIONMODE_SINGLE,ADC1_CHANNEL_1,ADC1_PRESSEL_FCPU_D18,ADC1_EXTTRIG_TIM,DISABLE,ADC1_ALIGN_RIGHT, ADC1_SCHMITTTRIG_CHANNEL1, DISABLE);
	
	ADC1_Init(ADC1_CONVERSIONMODE_SINGLE,ADC1_CHANNEL_0,ADC1_PRESSEL_FCPU_D18,ADC1_EXTTRIG_TIM,DISABLE,ADC1_ALIGN_LEFT, ADC1_SCHMITTTRIG_CHANNEL0, DISABLE);	
	ADC1_Init(ADC1_CONVERSIONMODE_SINGLE,ADC1_CHANNEL_1,ADC1_PRESSEL_FCPU_D18,ADC1_EXTTRIG_TIM,DISABLE,ADC1_ALIGN_LEFT, ADC1_SCHMITTTRIG_CHANNEL1, DISABLE);	

//	ADC1_Init(ADC1_CONVERSIONMODE_SINGLE,ADC1_CHANNEL_8,ADC1_PRESSEL_FCPU_D18,ADC1_EXTTRIG_TIM,DISABLE,ADC1_ALIGN_RIGHT, ADC1_SCHMITTTRIG_CHANNEL8, DISABLE);
//	ADC1_Init(ADC1_CONVERSIONMODE_SINGLE,ADC1_CHANNEL_9,ADC1_PRESSEL_FCPU_D18,ADC1_EXTTRIG_TIM,DISABLE,ADC1_ALIGN_RIGHT, ADC1_SCHMITTTRIG_CHANNEL9, DISABLE);
	
	//ADC1_Init(ADC1_CONVERSIONMODE_SINGLE,ADC1_CHANNEL_9,ADC1_PRESSEL_FCPU_D18,ADC1_EXTTRIG_TIM,DISABLE,ADC1_ALIGN_RIGHT, ADC1_SCHMITTTRIG_CHANNEL9, DISABLE);
	//ADC1_Init(ADC1_CONVERSIONMODE_CONTINUOUS,ADC1_CHANNEL_9,ADC1_PRESSEL_FCPU_D18,ADC1_EXTTRIG_TIM,DISABLE,ADC1_ALIGN_RIGHT, ADC1_SCHMITTTRIG_CHANNEL9, DISABLE);	
	
	
	ADC1_ScanModeCmd(ENABLE);
	ADC1_DataBufferCmd(ENABLE);
	ADC1_ITConfig(ADC1_IT_EOCIE,ENABLE);
	
	//��ʼת��
	//ADC1_StartConversion();

		//ȡADC��ǰֵ�����
		//putIntLine(ADC1_GetConversionValue());
}		


#define PWM_ACTIVE_LEVEL_LOW	1

void  PwmConfig_TIM1(void)
{
	unsigned short int Val1=0;
	//unsigned short int Val2=0;

	
 	TIM1_DeInit();	

	//TIM1_TimeBaseInit(0,TIM1_COUNTERMODE_UP,4095,0); 
		//TIM2_TimeBaseInit(TIM2_PRESCALER_4,PWM_MAX_VAL); 
	TIM1_TimeBaseInit(0,TIM1_COUNTERMODE_UP,PWM_MAX_VAL-2,0); 
	TIM1_PrescalerConfig(63,TIM1_PSCRELOADMODE_IMMEDIATE);		//16000/63/PWM_MAX_VAL = 1KHZ
	#if PWM_ACTIVE_LEVEL_LOW
	
		//����PWM2ģʽ,�������,��Ч��ƽ�͵�ƽ
	TIM1_OC1Init(TIM1_OCMODE_PWM2, TIM1_OUTPUTSTATE_ENABLE, TIM1_OUTPUTNSTATE_DISABLE,Val1, TIM1_OCPOLARITY_HIGH,TIM1_OCNPOLARITY_LOW,TIM1_OCIDLESTATE_SET,TIM1_OCNIDLESTATE_RESET);
	//TIM1_OC2Init(TIM1_OCMODE_PWM2, TIM1_OUTPUTSTATE_ENABLE, TIM1_OUTPUTNSTATE_ENABLE,Val2, TIM1_OCPOLARITY_LOW,TIM1_OCNPOLARITY_HIGH,TIM1_OCIDLESTATE_SET,TIM1_OCNIDLESTATE_RESET);
	//TIM1_OC3Init(TIM1_OCMODE_PWM2, TIM1_OUTPUTSTATE_ENABLE, TIM1_OUTPUTNSTATE_ENABLE,Val3, TIM1_OCPOLARITY_LOW,TIM1_OCNPOLARITY_HIGH,TIM1_OCIDLESTATE_SET,TIM1_OCNIDLESTATE_RESET);
	//TIM1_OC4Init(TIM1_OCMODE_PWM2, TIM1_OUTPUTSTATE_ENABLE,Val4, TIM1_OCPOLARITY_LOW,TIM1_OCIDLESTATE_SET);
	#else	
	//����PWM1ģʽ,�������,��Ч��ƽ�ߵ�ƽ	
	TIM1_OC1Init(TIM1_OCMODE_PWM2, TIM1_OUTPUTSTATE_ENABLE, TIM1_OUTPUTNSTATE_DISABLE,Val1, TIM1_OCPOLARITY_LOW,TIM1_OCNPOLARITY_HIGH,TIM1_OCIDLESTATE_SET,TIM1_OCNIDLESTATE_RESET);
	//TIM1_OC2Init(TIM1_OCMODE_PWM2, TIM1_OUTPUTSTATE_ENABLE, TIM1_OUTPUTNSTATE_DISABLE,Val2, TIM1_OCPOLARITY_LOW,TIM1_OCNPOLARITY_HIGH,TIM1_OCIDLESTATE_SET,TIM1_OCNIDLESTATE_RESET);
	//TIM1_OC3Init(TIM1_OCMODE_PWM2, TIM1_OUTPUTSTATE_ENABLE, TIM1_OUTPUTNSTATE_DISABLE,Val3, TIM1_OCPOLARITY_LOW,TIM1_OCNPOLARITY_HIGH,TIM1_OCIDLESTATE_SET,TIM1_OCNIDLESTATE_RESET);
	//TIM1_OC4Init(TIM1_OCMODE_PWM2, TIM1_OUTPUTSTATE_ENABLE, Val4, TIM1_OCPOLARITY_LOW,TIM1_OCIDLESTATE_SET);
	#endif
	

	TIM1_Cmd(ENABLE); 

	TIM1_CtrlPWMOutputs(ENABLE);
	
		//����ռ��
		//	TIM2_SetCompare1(a); 
	//	TIM2_SetCompare2(a); 
	//	TIM2_SetCompare3(a); 	
	//PwmContral1
 } 	
 
void PwmContral1(uchar x)	//PWM1 ����
{
	TIM1_SetCompare1(x);		//TIM1  CH1
	
}


void  PwmConfig_TIM2(void)
{
//	unsigned short int a=60;
//	unsigned short int b=60;
//TIM2_DeInit();	
////1khz
////TIM2_PrescalerConfig(TIM2_PRESCALER_64,TIM2_PSCRELOADMODE_IMMEDIATE);		//1/4MHZ
//	//��ʼ��timer2,ָ����ֵ
//	//TIM2_TimeBaseInit(TIM2_PRESCALER_1,PWM_MAX_VAL); 
//	TIM2_TimeBaseInit(TIM2_PRESCALER_64,PWM_MAX_VAL); 
//		//TIM2_TimeBaseInit(TIM2_PRESCALER_4,PWM_MAX_VAL); 
//	
//	#if PWM_ACTIVE_LEVEL_LOW
//		//����PWM2ģʽ,�������,��Ч��ƽ�͵�ƽ
//	TIM2_OC3Init(TIM2_OCMODE_PWM2, TIM2_OUTPUTSTATE_ENABLE,b, TIM2_OCPOLARITY_HIGH);
//	#else	
//	//����PWM1ģʽ,�������,��Ч��ƽ�ߵ�ƽ	
//	TIM2_OC3Init(TIM2_OCMODE_PWM1, TIM2_OUTPUTSTATE_ENABLE,a, TIM2_OCPOLARITY_HIGH); 
//	#endif
//	//OC3�Զ�����ʹ��
//	TIM2_OC3PreloadConfig(ENABLE);	
//
//
//	#if PWM_ACTIVE_LEVEL_LOW
//		//����PWM2ģʽ,�������,��Ч��ƽ�͵�ƽ
//	TIM2_OC2Init(TIM2_OCMODE_PWM2, TIM2_OUTPUTSTATE_ENABLE,b, TIM2_OCPOLARITY_HIGH);
//	#else
//		//����PWM1ģʽ,�������,��Ч��ƽ�ߵ�ƽ
//	TIM2_OC2Init(TIM2_OCMODE_PWM1, TIM2_OUTPUTSTATE_ENABLE,b, TIM2_OCPOLARITY_HIGH); 
//	#endif
//	//OC2�Զ�����ʹ��
//	TIM2_OC2PreloadConfig(ENABLE);	
//		
//		
//	#if PWM_ACTIVE_LEVEL_LOW
//		//����PWM2ģʽ,�������,��Ч��ƽ�͵�ƽ
//	TIM2_OC1Init(TIM2_OCMODE_PWM2, TIM2_OUTPUTSTATE_ENABLE,a, TIM2_OCPOLARITY_HIGH); 
//	#else
//		//����PWM1ģʽ,�������,��Ч��ƽ�ߵ�ƽ
//	TIM2_OC1Init(TIM2_OCMODE_PWM1, TIM2_OUTPUTSTATE_ENABLE,a, TIM2_OCPOLARITY_HIGH); 
//	#endif
//		//OC1�Զ�����ʹ��
//	TIM2_OC1PreloadConfig(ENABLE);
//	
//		
//	//TIM2�Զ�����ʹ��
//	TIM2_ARRPreloadConfig(ENABLE); 
////	//���ɸ����¼�
//	//TIM2_GenerateEvent(TIM2_EVENTSOURCE_UPDATE); 	//�����п�����
//	//����TIM2
//	TIM2_Cmd(ENABLE); 
//
//
//		//����ռ��
//		//	TIM2_SetCompare1(a); 
//	//	TIM2_SetCompare2(a); 
//	//	TIM2_SetCompare3(a); 	
//	
 } 	



//void PwmContral1_TIM2(uint16 x)	//PWM1 ����
//{
//
//	//if(x<5)
//	if(x<PWM_MIN_VAL)		
//			{
//			TIM2_SetCompare1(0);
//			
//			
////			#if PWM_ACTIVE_LEVEL_LOW
////					TIM2_SelectOCxM(TIM2_CHANNEL_1, TIM2_FORCEDACTION_ACTIVE);		//HIGH
////			#else
////					TIM2_SelectOCxM(TIM2_CHANNEL_1, TIM2_FORCEDACTION_INACTIVE);//LOW	
////			#endif
//
//			}
//	else if(x>(PWM_MAX_VAL-10))
//			{
//			TIM2_SetCompare1(PWM_MAX_VAL+1);
//
////			#if PWM_ACTIVE_LEVEL_LOW
////					TIM2_SelectOCxM(TIM2_CHANNEL_1, TIM2_FORCEDACTION_INACTIVE);//LOW
////			#else
////						TIM2_SelectOCxM(TIM2_CHANNEL_1, TIM2_FORCEDACTION_ACTIVE);		//HIGH
////			#endif
//			}
//	else{
//			
//			
////				#if PWM_ACTIVE_LEVEL_LOW
////						TIM2_SelectOCxM(TIM2_CHANNEL_1, TIM2_OCMODE_PWM2);
////				#else
////						TIM2_SelectOCxM(TIM2_CHANNEL_1, TIM2_OCMODE_PWM1);
////				#endif
//	
//	
//			TIM2_SetCompare1(x);
//			}
//
//}

//void PwmContral2_TIM2(uint16 x)	//PWM2 ����
//{
//
//	//if(x<5)
//	if(x<PWM_MIN_VAL)		
//			{
//			TIM2_SetCompare2(0);
//			
//			
////			#if PWM_ACTIVE_LEVEL_LOW
////					TIM2_SelectOCxM(TIM2_CHANNEL_2, TIM2_FORCEDACTION_ACTIVE);		//HIGH
////			#else
////					TIM2_SelectOCxM(TIM2_CHANNEL_2, TIM2_FORCEDACTION_INACTIVE);//LOW	
////			#endif
//
//			}
//	else if(x>(PWM_MAX_VAL-10))
//			{
//
//			TIM2_SetCompare2(PWM_MAX_VAL+1);
//
////			#if PWM_ACTIVE_LEVEL_LOW
////					TIM2_SelectOCxM(TIM2_CHANNEL_2, TIM2_FORCEDACTION_INACTIVE);//LOW
////			#else
////						TIM2_SelectOCxM(TIM2_CHANNEL_2, TIM2_FORCEDACTION_ACTIVE);		//HIGH
////			#endif
//			}
//	else{
//			
//			
////				#if PWM_ACTIVE_LEVEL_LOW
////						TIM2_SelectOCxM(TIM2_CHANNEL_2, TIM2_OCMODE_PWM2);
////				#else
////						TIM2_SelectOCxM(TIM2_CHANNEL_2, TIM2_OCMODE_PWM1);
////				#endif
//	
//	
//			TIM2_SetCompare2(x);
//			}
//
//}


void TIM4_Config(void)	//����TIM4ÿ1MS����һ�������ж�
{//����ʱ��Ϊ16M,TIM4����Ϊ128��Ƶ��16M/128=125000HZ
//���ʱ��2.048MS, (255+1)/125000=2.048MS
//1MSʱ����TIM4�ڲ�Ԥ��Ƶ��=(0.001x125000-1)=124	
	#define TIM4_PERIOD		124
	
	TIM4_TimeBaseInit(TIM4_PRESCALER_128,TIM4_PERIOD);
	TIM4_ClearFlag(TIM4_FLAG_UPDATE);	//��TIM4�����жϱ��
	TIM4_ITConfig(TIM4_IT_UPDATE,ENABLE);//ʹ�ܸ����ж�
	//enableInterrupts();
	TIM4_Cmd(ENABLE);
}

void LedContral(void)  /* ����ת��  */
{
	
				if(Time_LedRecv_LED>0)
						{
							Time_LedRecv_LED--;
							#if Config_Al_Box					
								if(K4_LVL)
										{
											//SetLed2;	//���߲����ӱ�ʾ������
											LED_Fe_Box;  //�ź�ʱ��
										}
							else{
											//ClrLed2;	//�������ӱ�ʾ������
											LED_Al_Box;  //�ź�ʱ����
									}
							#endif
										
						}
				else{
							#if Config_Al_Box					
								if(K4_LVL)
										{
											//SetLed2;	//���߲����ӱ�ʾ������
											LED_Al_Box;  //ƽ��ʱ����
										}
							else{
											//ClrLed2;	//�������ӱ�ʾ������
											LED_Fe_Box;  //ƽ��ʱ��
									}
							#endif					
							//LED_RECV_OFF;	
							}		
						
//#if CONFIG_433SG						
//				if(Time_TestProc_LED1>0)
//						{
//							Time_TestProc_LED1--;
//							if(Time_TestProc_LED1==0)
//									{
//										TestProc_LED1_OFF;	
//									}
//						}
//				if(Time_TestProc_LED2>0)
//						{
//							Time_TestProc_LED2--;
//							if(Time_TestProc_LED2==0)
//										{
//											TestProc_LED2_OFF;	
//										}
//						}
//		
//#endif
}


void Read_Param(uchar *buf)
{
uchar i;
FLASH_Unlock(FLASH_MEMTYPE_DATA);
		for(i=0;i<Max_Param_Len;i++)
				{
				buf[i]=FLASH_ReadByte(EEPROM_BASE_ADR+i);
				}
}
void Write_Param(void)
{
uchar i,Sum;
///
Sum=0;
for(i=0;i<Max_Param_Len-1;i++)
		{
		Sum+=gbParamBuf[i];
		}
gbParamBuf[Max_Param_Len-1]=~Sum;	//У������

	//����ʼ��FLASH
	FLASH_DeInit();
	//����EEPROM,�޸Ĳ����ɵ���ΪFLASH
	FLASH_Unlock(FLASH_MEMTYPE_DATA);
///
for(i=0;i<Max_Param_Len;i++)
										{

										//���ϴ�д��
										while(FLASH_GetFlagStatus(FLASH_FLAG_EOP));
										//��ʼд
										FLASH_ProgramByte(EEPROM_BASE_ADR+i,gbParamBuf[i]);//0X4010
										}
}
////
void Load_Param(void)
{
	struct	struct_save	*p;				//15869127174
	uchar buf[Max_Param_Len+2];
	uchar i,j,Sum;
	uchar FlagOk;
	
	p=(struct	struct_save	*)&buf[0];
	
	for(j=0;j<3;j++)
		{
	Read_Param(buf);
	FlagOk=0;
	if(p->flag==FlagParamInitnized)
			{//�����Ѿ���ʼ�������ȷ
			
			Sum=0;
			for(i=0;i<Max_Param_Len;i++)
				{
				Sum+=buf[i];//У����
				}
			if(Sum==0xff)//У����
				{
					FlagOk=1;
					break;
				}
			}
		}
		
	if(p->flag!=FlagParamInitnized)
		{//EEPROM������ʼ��
			//if((p->flag==0xff)||(p->flag==0))
							{
							Write_Param();
							}
			}
					
if(FlagOk)	
			{		
			for(i=0;i<Max_Param_Len;i++)
				{//��������
				gbParamBuf[i]=buf[i];
				}
			}
}




#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval : None
  */
void assert_failed(u8* file, u32 line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif











