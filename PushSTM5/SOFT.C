
#include <includes.h>






/**************************************************************************************************/
uchar bTimeBase;

uint16 giCodeChecksum;
uchar FlagGetUartOk;

uchar ReInitCC1100Time=0;
unsigned char Time_LedRecv_LED;

#if CONFIG_433SG
		//LED�Զ�Ϩ��
		unsigned char Time_TestProc_LED1;
		unsigned char Time_TestProc_LED2;
		
		uint PulseCount=0;
		
#endif		
//		uchar SamCommandTime;	//�ظ�������ʱ��
		uchar LastCommand;	//�ϴ�����

		


		uchar SetIdTime;			//����IDʱ��


uchar FlagSetCurrent1=0;
uchar CommandLostTimeOut;	//û���յ������ʱ��,��ʱ����������������ʱ��


uchar FlagAuto;	//�Զ���㶯��ʽ���
uchar DropOffTime;//����ʱ��
#if 0
uchar TestStepCount;
uchar FlagTestStep;
#endif


struct	struct_save *gpParam;
uchar gbParamBuf[Max_Param_Len+2];

uchar TimeDebug=0;
uchar FlagInputZero=0;
uchar InputBuf=0x0f;

uchar bExCurrentForwardMax;
uchar bExCurrentForwardPer85;
//333	uchar bExCurrentForwardPer94;

uchar bExCurrentBackwardMax;
uchar bExCurrentBackwardPer85;
//333	uchar bExCurrentBackwardPer94;

uchar KeybyteOld_Buf;
uchar KeybyteBuf;
uchar KeybyteOld;
uchar KeybyteCur;
////
struct _motor_struct
{
//��һ·��ת��ǰ�źű��
//�ڶ�·��ת����źű��
//����·��ת����źű��

uchar CommandType	;//����,ת��
uchar CurrentType	;//��ǰ�Է���,ת��
uchar OverType1	;//�����ķ���,ת��
//uchar OverType2	;//�����ķ���,ת��
//uchar OverType3	;//�����ķ���,ת��
uchar FlagPower;
uchar FlagRuning;
uchar Pwm1;		//��һ·��ת��ǰ���������
uchar timer_sec100;
//uchar RunTime;	//����ʱ�䶨ʱ��,��λS
uint16	RunTime;	//����ʱ�䶨ʱ��,��λ0.1S
uchar unPushTime;
//333	uchar TimePer94;		//94%������������ʱ�䶨ʱ��,��λ10mS
uint16 iTimePer85;		//75%������������ʱ�䶨ʱ��,��λ10mS
};
struct _motor_struct  Motor;
///

//void ProcessTestStep(void);

void SendToRemot(uchar command) //������ң����
{
#if CONFIG_CC1100
uchar buf[36+14];
uchar i;	

//static uchar id;
//id++;
//buf[0]=0x31+(0x07&id);	//1~8
buf[0]=0x31;	//1~8
buf[1]=gpParam->RemotName[0];
buf[2]=gpParam->RemotName[1];
buf[3]=gpParam->RemotName[2];
buf[4]=command;
buf[5]='3';
buf[6]='3';
buf[7]=0x77;
for(i=8;i<30;i++)
{
buf[i]='4';
}
//		if(1)	//if(WirelessDebugTime>0)
//						{
//						len=8;
//						len+=MakeValAsc8("%A,T",Motor.ActiveTime,",",&buf[len]);
//						len+=MakeValAsc8("L",chCurrent1,",",&buf[len]);
//						len+=MakeValAsc8("R",chCurrent2,",",&buf[len]);
//						//��ǿ
//						len+=MakeValAsc8("E",VolRssi,",",&buf[len]);
//						len		+=	PutString("*****",&buf[len],5);
//						}

buf[30]=0x0d;
buf[31]=0x0a;
buf[32]=0x00;
		
								cc1100Printf(buf);


		#endif	
}

///////
//uchar GetOneFromUart2(uchar *buf)
//{
//	if(Uart2RecvStruct.len)
//			{
//			GetLoopbuf(&Uart2RecvStruct,Uart2RecvBuf,UART2_RECV_BUF_SIZE,buf);
//			return 1;
//			}
//	else 	return 0;
//}
/////////
//void SendText_UART2(INT8U *StrData)
//{
//	uchar i;
//	for(i=0;i<255;i++)
//	  {
//	  if(*(StrData+i)==0x00)break;
//	   Uart2CharSend(*(StrData+i));
//	  }	
//	
//}
///////

void ProcessUartCommand(uchar *buf,uchar len)
{
uchar i,sum;
	if(len<3)return;
	if(*buf!='%')return;

	switch(*(buf+1))
		{
			case 'K':
			//�ֻ����յ���������
			sum=0;
			for(i=0;i<8;i++)
					{
					sum+=*(buf+i);
					}	
			
			if((AscToHex(*(buf+8))*0x10+AscToHex(*(buf+9)))==sum)
					{
//					UartLinkTimeout=0;
//					if(*(buf+3)=='0')
//							Motor.FlagLineContral=0;
//					else 		Motor.FlagLineContral=1;
//						
//					Motor.CommBuf1=AscToHex(*(buf+4))*0x10+AscToHex(*(buf+5));
//					if(Motor.CommBuf1>(PWM_MAX_VAL-1))Motor.CommBuf1=(PWM_MAX_VAL-1);
//					Motor.CommBuf2=AscToHex(*(buf+6))*0x10+AscToHex(*(buf+7));
//					if(Motor.CommBuf2>(PWM_MAX_VAL-1))Motor.CommBuf2=(PWM_MAX_VAL-1);
						
//						switch(*(buf+2))
//										{
//										case REMOT_COMMAND_TEST_UART1:
//										SendUartCommand(REMOT_COMMAND_TEST_UART2);
//										
//										break;	
//											case REMOT_COMMAND_TEST_UART2:
//												SendUartCommand(REMOT_COMMAND_TEST_UART3);
//												
//											break;	
//											case REMOT_COMMAND_TEST_UART3:
//											
//											TimeTestUart=20;	//4��  		//��������Դ��� ���ֵ���˸��ʱ��
//											break;	
//											
//
//											
//											default:		
//
//											break;
//										}
						Execute(*(buf+2));
						
					}
			break;
//			case 'R':
//				//���෵��
//						sum=0;
//			for(i=0;i<4;i++)
//					{
//					sum+=*(buf+i);
//					}	
//			
//			if((AscToHex(*(buf+4))*0x10+AscToHex(*(buf+5)))==sum)
//						{
//////						UartLinkTimeout=0;
////						temp=	AscToHex(*(buf+2))*0x10+AscToHex(*(buf+3));
//////							if((BIT6)&temp)
//////										{
//////										Motor.FlagSubPowerOn=1;
//////										}
//////							else{
//////									Motor.FlagSubPowerOn=0;
//////									}
//////							
//////							SubStatuByte=0x3F&(temp);		//�ֻ�״̬���
//
//						}
//			break;
			default:										
			break;	
		}
		
		
}
///////////		

void CheckUart(void)
{
	uchar temp;
	static uchar len;
	static uchar buf[20+2];
	if(FlagGetUartOk==0)
		{
			if(GetOneFromUart2(&temp))
				{
					
					switch(temp)
							{
								case '%':
								len=0;
								break;
								
								case '\r':
								FlagGetUartOk=1;
								break;
								
								default:

								break;
							}
					if(len<20)
										{
										buf[len]=temp;
										len++;
										}
								else{
										len=0;
										}
				}
		}
	else{//FlagGetUartOk==1
		//EventRecvAnyTim=2;
			ProcessUartCommand(buf,len);
			buf[0]=0;
			len=0;
			FlagGetUartOk=0;
			}
}
///////

void Default_ParamInit(void)
{	//gpParam�����ṹ��ָ��

	//gpParam->bCurrentForward=90;			//�����ת�� 18A   max=256*75%=192
	//gpParam->bCurrentBackward=80;			//�����ת�� 16A
	//gpParam->bCurrentForward=124;			//�����ת�� 18A   max=256*75%=192
	//gpParam->bCurrentBackward=110;			//�����ת�� 16A
	gpParam->bCurrentForward=CURRENT_FORWARD;			//�����ת�� 18A   max=256*75%=192
	gpParam->bCurrentBackward=CURRENT_BACKWARD;			//�����ת�� 16A
	//	gpParam->bCurrentBackward=3;			//�����ת�� 0.6A
	gpParam->bCurrentRate=CURRENT_RATE;			//���3�� 5A
	
	

	
#if CONFIG_CC1100
	gpParam->RemotName[0]=0x31;
	gpParam->RemotName[1]=0x32;
	gpParam->RemotName[2]=0x33;	
	//gpParam->xxx[0]=0x0;
	//gpParam->xxx[1]=0x0;
#elif CONFIG_433SG
	gpParam->RemotName[0]=0x0;
	gpParam->RemotName[1]=0x0;
	//gpParam->xxx[0]=0x0;
	//gpParam->xxx[1]=0x0;
#endif	
	gpParam->flag=FlagParamInitnized;		//�����Ѿ���ʼ�����
	
	/////////
	
	CommandLostTimeOut=0;	//û���յ������ʱ��,��ʱ����������������ʱ��


	
	FlagAuto=0;	//�Զ���㶯��ʽ���
	Motor.FlagRuning=0;
	Motor.FlagPower=0;		//���ߵ��Դ�򿪱��
//333		Motor.TimePer94=0;
	Motor.iTimePer85=0;
	Motor.timer_sec100=0;
	Motor.RunTime=0;	//60s�Զ��ص�
	Motor.unPushTime=0;
	Motor.CommandType=0;
	Motor.CurrentType=0	;		//��ǰ�Է���,ת��
	Motor.OverType1	=0;		//�����ķ���,ת��
	//Motor.OverType2	=0;		//�����ķ���,ת��
	//Motor.OverType3	=0;		//�����ķ���,ת��
	
	Motor.Pwm1=0;		//��һ·��ת��ǰ���������

	DropOffTime=0;//����ʱ��
	

	#if 0
	TestStepCount=0;
	FlagTestStep=0;
	#endif
	
//		#if CONFIG_433SG ||CONFIG_CC1100
//		SamCommandTime=0;	//��������ʱ��
//		#endif	
		LastCommand=0;	//�ϴ�����

	
	//SetIdTime=70;  //7S
	SetIdTime=0;  //7S
	
	ClearLoopBuf(&Uart2RecvStruct,UART2_RECV_BUF_SIZE);	//������ͻ�����
	
}
	
///////////

//////////////////////////////////////////////////

/////////////
void AllJspOff(void)
{
JspOut1_OFF;
JspOut2_OFF;	

}
/////
#if 0
void ProcessTestStep(void)
{
	static uchar tim6;
	if(FlagTestStep==0)return;
		if(tim6<100)	//1s
			{
				tim6++;
			}
	else{
			tim6=0;
			if(TestStepCount<8)
					{
						TestStepCount++;
					}
			else{
				FlagTestStep=0;
					}
			
			switch(TestStepCount)
					{
						case 1:
						Motor.CommandType=COMMAND_C1;		//��ס��һ·��ת
						FlagAuto=1;	//�Զ���㶯��ʽ���
						break;
						
						case 4:
						FlagAuto=0;	//�Զ���㶯��ʽ���
						break;
						
						case 5:
						Motor.CommandType=COMMAND_CC1;		//��ס��һ·��ת
						FlagAuto=1;	//�Զ���㶯��ʽ���
						break;
						
						case 8:
						FlagAuto=0;	//�Զ���㶯��ʽ���
						break;	
						

						
						
						default:
						break;
			
					}
			}
}
#endif
/////
void ProcessJspSwitch(void)		//��ת�����л� ����
{
		//if(Motor.Pwm1==0)
			if(DropOffTime>120)//����ʱ��
						{//��ת�Ѿ�ֹͣ
						switch(Motor.CommandType)	//
								{
								case COMMAND_C1:		//��ס��һ·��ת
								case COMMAND_A1:			//��һ�µ�һ·��ת
							//	if(Motor.OverType1!=1)		//�����ķ���,ת��
										{
											Motor.OverType1=0;
											JspOut1_ON;
											JspOut2_OFF;
											Motor.FlagRuning=1;
											Motor.CurrentType=Motor.CommandType;		//��ǰ�Է���,ת��
											Motor.CommandType=0;	//ִ�к����
											//SendUartRespone();
										}
								break;
								
								case COMMAND_CC1:		//��ס��һ·��ת
								case COMMAND_AA1:			//��һ�µ�һ·��ת
							//		if(Motor.OverType1!=2)		//�����ķ���,ת��
										{
											Motor.OverType1=0;
											JspOut1_OFF;
											JspOut2_ON;
											Motor.FlagRuning=2;
											Motor.CurrentType=Motor.CommandType;		//��ǰ�Է���,ת��
											Motor.CommandType=0;	//ִ�к����
											//SendUartRespone();
										}
								break;								

			
								
								default:
								
								break;
								
							}
							
							
						}
	
}
/////

/////////
#if CONFIG_433SG || CONFIG_CC1100
void ProcessCommand(uchar command)
{
	
	switch(command)
		{	//�㶯������
			case COMMAND_C1:		//��ס��һ·��ת
			case COMMAND_CC1:		//��ס��һ·��ת
			case COMMAND_C2:
			case COMMAND_CC2:
			case COMMAND_C3:
			case COMMAND_CC3:
				
				//333	Motor.TimePer94=0;
				Motor.iTimePer85=0;
				Motor.timer_sec100=0;
				Motor.RunTime=0;	//60s�Զ��ص�
				Motor.unPushTime=0;
				
				#if CONFIG_FUNCTION_AUTO
						
//				//������Ϊ�Զ����ܣ��ſ��������ٰ��ſ���Ϊ�ֶ�����
//				if(SamCommandTime>150)
//					{
//					FlagAuto=1;//�ǵ㶯��ʽ
//					}
//				else FlagAuto=0;//�㶯��ʽ
					
				FlagAuto=1;//�ǵ㶯��ʽ
				
				
				#else	
					FlagAuto=0;//�㶯��ʽ	
				#endif
			break;

			
			default:
				
			break;
		}
}
#endif
///////


void Execute(uchar cmd)
{	
		switch(cmd)
					{
					case REMOT_COMMAND_MOT3_CW:
					
					if(Motor.FlagPower>0)
									{
									Motor.FlagPower=90; //3����
									Motor.FlagRuning=0;
									Motor.CommandType=COMMAND_C1;		//����һ·��ת
									FlagAuto=1;//�ǵ㶯��ʽ
									ProcessCommand(Motor.CommandType);		//for CC1100
									//SendUartRespone();
									}
					break;
					
					case REMOT_COMMAND_MOT3_CCW:
					if(Motor.FlagPower>0)
							{
							Motor.FlagPower=90; //3����	
							Motor.FlagRuning=0;
							Motor.CommandType=COMMAND_CC1;		//����һ·��ת
							FlagAuto=1;//�ǵ㶯��ʽ
							ProcessCommand(Motor.CommandType);		//for CC1100
							//SendUartRespone();
							}
					break;
												
					case REMOT_COMMAND_POWER_ON:
					case REMOT_COMMAND_PUSH_POWER_ON:
							Motor.FlagPower=90; //3����	
					break;
					
					case REMOT_COMMAND_POWER_OFF:
																Motor.FlagPower=0;
																Motor.FlagRuning=0;
																Motor.CommandType=0;
																Motor.CurrentType=0;													
					break;
				case REMOT_COMMAND_SET_RATE3:	//���õ���

				
																
					if(	FlagSetCurrent1==0)
								{
								if((Motor.FlagRuning)&&(InputBuf==0x0f)&&(FlagInputZero>0))
												{
													Motor.FlagPower=90; //4����
													FlagSetCurrent1=1;
													TimeDebug=120;
												}
								}
				break;
															
															//�������ڲ���
					case REMOT_COMMAND_MOT1_CW:
					case REMOT_COMMAND_MOT1_CCW:	
					case REMOT_COMMAND_MOT2_CW:
					case REMOT_COMMAND_MOT2_CCW:
					case REMOT_COMMAND_MOT1_CW_MOT2_CCW:
					case REMOT_COMMAND_MOT2_CW_MOT1_CCW:
					case REMOT_COMMAND_MOT1_MOT2_CW:
					case REMOT_COMMAND_MOT1_MOT2_CCW:

					//ң������Դ����
					case REMOT_COMMAND_REMOT_HAND_ON:
															
							Motor.FlagPower=90; //4����
															
					break;
					}
}


#if CONFIG_CC1100

void ProcessRemotCommand(uchar *p)		//for CC1100
{



uchar *nm;
uchar cmd;


/*
			buf[4]=	command;	
			buf[5]=	'6';	
			buf[6]=	'6';
			buf[7]=	0x70;
	*/
		if(*p<0x40)return;		//���ţ�1�ֽ�, ң��������Ϊ"4xH"
		if((*(p+7)!=0x70)&&(*(p+7)!=0x71))return;
			
		nm=p+1;
		cmd=*(p+4);
		//if(('6'==*(p+5))&&('6'==*(p+6))&&(*(p+7)==0x70))
//		if(*(p+7)==0x70)	
//			{//��ʽң��������
//		}

	if(SetIdTime>0)
		{
	

			//setid
			if(cmd==REMOT_COMMAND_POWER_ON)//REMOT_COMMAND_SHIFT_SET_ID)
					{
					gpParam->RemotName[0]=*(nm);
					gpParam->RemotName[1]=*(nm+1);
					gpParam->RemotName[2]=*(nm+2);


				

						Write_Param();				
			
				Motor.FlagPower=90; //3����
				SetIdTime=0;
		
				}
		}	
	else{	
			//�Ƕ���ʱ��
			if((CompareCharChar(nm,"555",3)!=0)||(CompareCharChar(nm,&gpParam->RemotName[0],3)!=0))	//Ĭ�ϵ�ַ
				{
			//ң�������ok

			
					//	SendUartCommand(cmd);
					if(LastCommand!=cmd)
								{
								Execute(cmd);

								}
				LastCommand=cmd;								
				}
		}

	
}
///////////////////

void ProcessRfRecv(void)
{
	if(cc1100Scanf(rx_buf))
									{
									//RecvAny_LED1_ON;
									ReInitCC1100Time=0;
									
									//LED_RECV_ON;
									Time_LedRecv_LED=20;
				
									ProcessRemotCommand(rx_buf);		//for CC1100
//									ResponseTime=0;
//									#if CONFIG_TEST_COMMAND_ENDCODE
//									for(i=0;i<CC1100_PKT_LEN;i++)
//							        	{
//							        	Uart2CharSend(rx_buf[i]);	
//							        	}
//									#endif
				        	}
}

#elif CONFIG_433SG
void ProcessRfRecv(void)
{
	uchar i;
	if(DecodeCompleteFlag==0)return;	//ָ��������
	
	/*
	sum=0;
	for(i=0;i<4;i++)
			{
				sum^=DecodeString[i];
			}
	if(sum==0)
		*/
	if(DecodeString[2]==DecodeString[3])	
		{
		//LED_RECV_ON;
		Time_LedRecv_LED=20;
				
				if((SetIdTime>1)||((DecodeString[0]==gpParam->RemotName[0])&&(DecodeString[1]==gpParam->RemotName[1])))
					{//����ʱ��
					CommandLostTimeOut=0;	//û���յ������ʱ��
					if(LastCommand!=DecodeString[2])	//��ָ��
							{//�ж�ʱ��
					//			SamCommandTime=0;
								LastCommand=DecodeString[2];
								Motor.CommandType=DecodeString[2];
								Motor.FlagRuning=0;
							}
			
						
					ProcessCommand(DecodeString[2]);
					if(SetIdTime>1)
											{
												//if(DecodeString[2]==0x50)
													gpParam->RemotName[0]=DecodeString[0];
													gpParam->RemotName[1]=DecodeString[1];

														
													Write_Param();
												
												SetIdTime=0;
											}
					}
					
		}

	RemotCodeSend(DecodeString,LENGTH_REMOT_PARK);	

	DecodeCompleteFlag=0;	//�����ٴν���ָ��
}
#endif
///////

void CheckInput(void)
{
static uchar old;
uchar temp;									


temp=Input4>>4;


		if(old==temp)
					{
						InputBuf=temp;//(~temp);	//ȡ��
						if(InputBuf==0)FlagInputZero=120;  //4����
					}
		else{ 	
				old=temp;	
				}
				
	//			InputBuf=0~15;   //18-30A
				
		/*
		Max=(18+0.8*InputBuf)
		Max=18*(1+InputBuf/15*2/3)
		Max=18*(1+InputBuf*2/45)=18*(45+2*InputBuf)/45=18+18*2*InputBuf/45		
		
		InputBuf=0  18A
		InputBuf=1  18.8A
		InputBuf=2  19.6A		
		
		
		InputBuf=13  28.4A
		InputBuf=14  29.2A
		InputBuf=15  30A			
		*/
		if(Motor.FlagRuning==0)
			{
			//��ת	(1+adj*2/45)*100%   adj=0-15
			bExCurrentForwardMax=(gpParam->bCurrentForward<<1)*InputBuf/30+gpParam->bCurrentForward;

			bExCurrentForwardPer85=(uchar)((uint16)(bExCurrentForwardMax)*7>>3);
			//15/16=93.75%
			
			//��ת
			bExCurrentBackwardMax=(gpParam->bCurrentBackward<<1)*InputBuf/30+gpParam->bCurrentBackward;			

			//3/4=75%
			bExCurrentBackwardPer85=(uchar)((uint16)(bExCurrentBackwardMax*7)>>3);
			//15/16=93.75%
		}
		
}
/////
void ProcessKey(uchar in,uchar old)
{
		#if CONFIG_FUNCTION_AUTO
		
		if( (in&BIT0)!=(old&BIT0) )	//�Ǳ���
			{
				if((in&BIT0)==0)
					{	//k1
							if(Motor.FlagRuning!=1)
							{
								Motor.FlagRuning=0;
							Motor.CommandType=COMMAND_C1;		//����һ·��ת
							FlagAuto=1;//�ǵ㶯��ʽ
							
							//333	Motor.TimePer94=0;
							Motor.iTimePer85=0;
							Motor.timer_sec100=0;
							Motor.RunTime=0;	//60s�Զ��ص�
							Motor.unPushTime=0;
							}
					}
				}
	
		if( (in&BIT1)!=(old&BIT1) )	//�Ǳ���
			{
				if((in&BIT1)==0)
					{	//k2
						//if(Motor.FlagRuning==0)
						if(Motor.FlagRuning!=2)	
							{
								Motor.FlagRuning=0;
							Motor.CommandType=COMMAND_CC1;		//��ת
							FlagAuto=1;//�ǵ㶯��ʽ

							//333	Motor.TimePer94=0;
							Motor.iTimePer85=0;	
							Motor.timer_sec100=0;						
							Motor.RunTime=0;	//60s�Զ��ص�
							Motor.unPushTime=0;
							}
					}
				}		
////				

////				
			#else	
			if( in !=old)
				{
					//333	Motor.TimePer94=0;
					Motor.iTimePer85=0;
					Motor.timer_sec100=0;
					Motor.RunTime=0;	//60s�Զ��ص�
					Motor.unPushTime=0;
				}
			//k1
			if((in&BIT0)==0)
				{
					Motor.CommandType=COMMAND_C1;		//����һ·��ת
					FlagAuto=0;//�㶯��ʽ	
					CommandLostTimeOut=0;
				}
			else if((in&BIT1)==0)
				{//k2
					Motor.CommandType=COMMAND_CC1;		//��ת
					FlagAuto=0;//�㶯��ʽ	
					CommandLostTimeOut=0;
				}
				
			#endif
			
			if( (in&BIT2)!=(old&BIT2) )	//�Ǳ���K3 ,Set Current
						{
							if((in&BIT2)==0)
										{
										TimeDebug=30;	
										ParamSend();	
											if(FlagSetCurrent1==0)	
												{
												
														if((Motor.FlagRuning)&&(InputBuf==0x0f)&&(FlagInputZero>0))
																{
																	FlagSetCurrent1=1;
																}

												}
										}
						}			
			
			if( (in&BIT4)!=(old&BIT4) )	//�Ǳ���K5 SetId
						{
							if((in&BIT4)==0)
										{			
											SetIdTime=70;  //7S		
										}
						}	
						
			//ProcessCommand(Motor.CommandType);
}

/////
void CheckKey(void)		//����10ms
{
		/*
				if(K1_LVL)
						KeybyteCur	|=	BIT0;
				else	KeybyteCur	&=	(~BIT0);
				if(K2_LVL)
						KeybyteCur	|=	BIT1;
				else	KeybyteCur	&=	(~BIT1);
				*/
				if(K3_LVL)
						KeybyteCur	|=	BIT2;
				else	KeybyteCur	&=	(~BIT2);
	/*
	#if Config_Al_Box				
				if(K4_LVL)
						KeybyteCur	|=	BIT3;
				else	KeybyteCur	&=	(~BIT3);					
	#endif
	*/
			
				if(K5_LVL)
						KeybyteCur	|=	BIT4;
				else	KeybyteCur	&=	(~BIT4);					

		
	
	//������������,������ͬ��Ч
	
					if(KeybyteOld==KeybyteCur)		//�ϴζ�������
								KeybyteBuf=KeybyteCur;		//���
					else  KeybyteOld=KeybyteCur;
		ProcessKey(KeybyteBuf,KeybyteOld_Buf);
			/*
			if((KeybyteOld_Buf!=KeybyteBuf)&&(0==(KeybyteBuf&BIT0)))
				{
				TestStepCount=0;
				FlagTestStep=1;
			}*/
		KeybyteOld_Buf=KeybyteBuf;
}
//////

void ProcessTimeOut(void)	//10MS�����
{
//#define COMMAND_CONTINU_TIME_300  40
#define COMMAND_CONTINU_TIME_300  30

static uchar tim1000ms;


//#if CONFIG_433SG
//	if(SamCommandTime<253)SamCommandTime++;
//#endif

//��ť�ɿ��Զ��ر�
	if(CommandLostTimeOut<253)CommandLostTimeOut++;	//û���յ������ʱ��
	if(CommandLostTimeOut>COMMAND_CONTINU_TIME_300)	//û���յ������ʱ��	//400ms
		{
			if(FlagAuto==0)
				{//�㶯��ʽ
					Motor.FlagRuning=0;
					Motor.CurrentType=0;
					}
					
//		#if CONFIG_433SG ||CONFIG_CC1100
//			SamCommandTime=0;	//age
//		#endif	
		//	LastCommand=0;		
		

		}
		
////////////////////////////////////////////	
	if(tim1000ms<200)
		{
			tim1000ms++;
		}
	else{//����2��
		tim1000ms=0;
		LastCommand=0;

					
				
		/////////////////////////////
			if(ReInitCC1100Time>20)//if(ReInitCC1100Time>30)
										{
										
										ReInitCC1100Time=0;
							
												#if CONFIG_CC1100
															cc1100Initializtion();
												#endif		
										}
				else{
						ReInitCC1100Time++;
						}
			
			if(Motor.FlagPower>0)	//
						{
							SendToRemot(REMOT_COMMAND_PUSH_POWER_ON);
							Motor.FlagPower--;//ÿ2���1
						}	
								
			if(FlagInputZero>0)	FlagInputZero--;
				
			if(TimeDebug>0)	TimeDebug--;
						
			}
///////////////////////////////////////////////////////////	
//��ʱ�Զ��ر�		
	if(Motor.timer_sec100<10)	
			{
				Motor.timer_sec100++;
			}
	else{//100MS
			Motor.timer_sec100=0;
			if(SetIdTime>0)SetIdTime--;			//����IDʱ��	
			//if(Motor.RunTime<253)	//60s�Զ��ص�	
			if(Motor.RunTime<65530)	//60s�Զ��ص�		
				{
					Motor.RunTime++;
				}

			}
			
		
			if(Motor.RunTime>MAX_RUN_TIME_sec)	//80s�Զ��ص�	
			//if((Motor.RunTime+Motor.unPushTime)>MAX_RUN_TIME_sec)	//80s�Զ��ص�		
					{
					//Motor.RunTime=0;
					Motor.FlagRuning=0;
					Motor.CommandType=0;
					Motor.CurrentType=0;
					
					}	
		
			if(FlagSetCurrent1==1)
				{
				//if(Motor.RunTime>5)
				if(Motor.RunTime>50)	
						{
						FlagSetCurrent1=2;
						}
				}
		
			if(FlagSetCurrent1==3)
				{
					FlagSetCurrent1=0;
					//FlagSetCurrent1=4;
					Motor.FlagRuning=0;
					Motor.CommandType=0;
					Motor.CurrentType=0;
					
					Write_Param();
						
				}
					
			if(Motor.unPushTime!=0)
				{
					Motor.unPushTime--;
				}
		else{
		//if(Motor.RunTime>3)	//��������������������ʱ�䣿
		//if(Motor.RunTime>1)	//��������������������ʱ�䣿	
			{	
			switch(Motor.CurrentType)		//��ǰ�Է���,ת��
				{//����=(DIGETAL-5)*20	(mA)
											case COMMAND_C1:		//��ס��һ·��ת
										case COMMAND_A1:			//��һ�µ�һ·��ת
											if(chAdc_Resoult7>bExCurrentForwardPer85)
												{
												Motor.iTimePer85++;
												}
											else{
													if(Motor.iTimePer85>0)Motor.iTimePer85--;
													}
											
											//if((chAdc_Resoult7>bExCurrentForwardMax)||(0*Motor.iTimePer85>Time10000Ms))
											if((chAdc_Resoult7>bExCurrentForwardMax)||(Motor.iTimePer85>Time10000Ms))
														{
															Motor.OverType1=1;		//�����ķ���,ת��
															Motor.FlagRuning=0;
															Motor.CommandType=0;
															Motor.CurrentType=0;
															//Motor.unPushTime=0;
															SendToRemot(RESPONES_COMMPLETE);
															SendToRemot(RESPONES_COMMPLETE);
															SendToRemot(RESPONES_COMMPLETE);
															SendToRemot(RESPONES_COMMPLETE);
															//SendUartRespone();
														}
										break;
										
										case COMMAND_CC1:		//��ס��һ·��ת
										case COMMAND_AA1:			//��һ�µ�һ·��ת
											if(chAdc_Resoult7>bExCurrentBackwardPer85)
												{
												Motor.iTimePer85++;
												}
											else{
													//333	Motor.TimePer94=0;
													if(Motor.iTimePer85>0)Motor.iTimePer85--;
													}
											
											//if((chAdc_Resoult7>bExCurrentBackwardMax)||(0*Motor.iTimePer85>Time10000Ms))
											if((chAdc_Resoult7>bExCurrentBackwardMax)||(Motor.iTimePer85>Time10000Ms))
												{
													Motor.OverType1=2;		//�����ķ���,ת��
													Motor.FlagRuning=0;
													Motor.CommandType=0;		
													Motor.CurrentType=0;
													//SendToRemot(RESPONES_COMMPLETE);
													
													#if CONFIG_UNPUSH
													//��ֹ��ƤȦѹ��̫������ת�˵��׺��Զ���תһ�㣬����
														//if(Motor.RunTime>10)	//����10�����Ч
														if(Motor.RunTime>100)	//����10�����Ч	
																		{
																			Motor.CommandType=COMMAND_C1;		//��ת
																			FlagAuto=1;//�ǵ㶯��ʽ
																			//333	Motor.TimePer94=0;
																			Motor.iTimePer85=0;							
																			//Motor.RunTime=MAX_RUN_TIME_sec-3;	//��ת�˵��׺��Զ���ת3��
																			Motor.timer_sec100=0;
																			#if Config_Al_Box
																			//if(KeybyteBuf&BIT3)	//K4_LVL
																				if(K4_LVL)
																				{//SetLed2
																					Motor.RunTime=MAX_RUN_TIME_sec-15;	//��ת�˵��׺��Զ���ת0.8��,׼���¿����Ͻ�����
																					}
																			else{//�պ�
																					//Motor.RunTime=MAX_RUN_TIME_sec-4;	//��ת�˵��׺��Զ���ת3��
																					Motor.RunTime=MAX_RUN_TIME_sec-40;	//��ת�˵��׺��Զ���ת3��
																					}	
																			#else			
																				//Motor.RunTime=MAX_RUN_TIME_sec-4;	//��ת�˵��׺��Զ���ת3��
																				Motor.RunTime=MAX_RUN_TIME_sec-40;	//��ת�˵��׺��Զ���ת3��
																			#endif
																		Motor.unPushTime=20;
																		}
																else{
																		SendToRemot(RESPONES_COMMPLETE);
																		SendToRemot(RESPONES_COMMPLETE);
																		SendToRemot(RESPONES_COMMPLETE);
																		SendToRemot(RESPONES_COMMPLETE);
																	
																		}
													#endif
													
																						
												}
										break;								
										
										default:
										
										break;
										
									}
				}
			}
}
////
void ProcessTimeSoftStart(void)	//10MS������
{	
//#define SoftStep	10
//#define SoftStep	20
#define SoftStep	15
		if(Motor.FlagRuning)
		{
			//������
			//if(Motor.Pwm1<(PWM_MAX_VAL-1))Motor.Pwm1+=1;
			if(Motor.Pwm1<(PWM_MAX_VAL-SoftStep))Motor.Pwm1+=SoftStep;
			else Motor.Pwm1=PWM_MAX_VAL;
			DropOffTime=0;	
		}
	else{

			#define CONFIG_SOFT_STOP		0
			
			#if CONFIG_SOFT_STOP
						if(Motor.Pwm1>(SoftStep*4))
							{
								Motor.Pwm1-=(SoftStep*4);	
							}
						else{
							  Motor.Pwm1=0;	//ֱ��ֹͣ
							}
				#else
				Motor.Pwm1=0;	//ֱ��ֹͣ
				#endif			
				
		if(Motor.Pwm1==0)
				{
				if(DropOffTime<253)DropOffTime++;//����ʱ��
				//if(DropOffTime>10)AllJspOff();//�̵�����
				if(DropOffTime>30)AllJspOff();//�̵�����	
				}
		 else{
		 			DropOffTime=0;
					}
		}
PwmContral1(Motor.Pwm1);	//OC1A PWM1 ����

}

/////
void SendUartRespone(void)		//%B ת���ķ�����Ϣ
{
//		uchar len;
//	uchar buf[20];
//		uchar chksum,temp;
//	uchar i;
//	uchar status;
//	
//	status=		//����
//
//RESPONES_COMMPLETE
//		RESPONES_RUNING;
//
//
//
//	len		=	PutString("%B",buf,5);								//head 3
//	buf[len]=HexToAsc(status>>4);				//
//	len		++;
//	buf[len]=HexToAsc(status);				//
//	len		++;
//	//У����  %RxxCC\r\n
//		chksum=0;
//	for(i=0;i<len;i++)
//			{
//			chksum+=buf[i];
//			}
//	buf[len]=HexToAsc(chksum>>4);
//	len		++;
//	buf[len]=HexToAsc(chksum);
//	len		++;
//	
//	//////////////////
//	#if DEBUG2
//	temp=	gpParam->flag_MainSub;
//	if(Flag_Link==1)
//	  		{
//	  			//��������
//	  			temp|=BIT7;
//	  		}
//	  		
//	if(Flag_unLink==1)
//	  		{
//	  			//��������
//	  			temp|=BIT6;
//	  		}	  		
//	  if(Motor.FlagSubPowerOn!=0)
//	  	{
//	  		temp|=BIT5;
//	  	}		
//	
//		buf[len]=HexToAsc(temp>>4);
//	len		++;
//	buf[len]=HexToAsc(temp);
//	len		++;
//	#endif
//	///////////////////
//	len  += PutString("\r\n",&buf[len],5);
//	SendText_UART2(buf);
	
}
/////
void SendParamBuf(void)
{
uchar i;
SendText_UART2("ParamBuf....");	
	
for(i=0;i<Max_Param_Len;i++)
		{
		
		Uart2CharSend(HexToAsc(gbParamBuf[i]>>4));
		Uart2CharSend(HexToAsc(gbParamBuf[i]));
		
		Uart2CharSend(0x20);
		}
SendText_UART2("\r\n");	
}
/////
void ParamSend(void)
{
	uchar len;
	//uchar i;
	uchar  buf[60];

SendParamBuf();


	len		=	PutString("&ED,",buf,5);								//head 4
	len		+=	MakeValAsc8("I1=",gpParam->bCurrentForward,",",&buf[len]);	//
	len		+=	MakeValAsc8("I2=",gpParam->bCurrentBackward,",",&buf[len]);	//
	len		+=	MakeValAsc8("k=",gpParam->bCurrentRate,",",&buf[len]);	//
	
	#if CONFIG_433SG || CONFIG_CC1100
	len		+=	PutString("ID=",&buf[len],5);
	buf[len]=HexToAsc(gpParam->RemotName[0]>>4);
	len++;
	buf[len]=HexToAsc(gpParam->RemotName[0]);
	len++;
	buf[len]=HexToAsc(gpParam->RemotName[1]>>4);
	len++;
	buf[len]=HexToAsc(gpParam->RemotName[1]);
	len++;
			#if CONFIG_CC1100
			buf[len]=HexToAsc(gpParam->RemotName[2]>>4);
			len++;
			buf[len]=HexToAsc(gpParam->RemotName[2]);
			len++;
			#endif
	buf[len]=',';
	len++;
	#endif
	
	
	len		+=	PutString("\r\n",&buf[len],5);

SendText_UART2(buf);	
////////////////////////////////////////
len		=	PutString("%C,",buf,5);	
buf[len]=HexToAsc((giCodeChecksum>>12)&0x0f);
len++;
buf[len]=HexToAsc((giCodeChecksum>>8)&0x0f);
len++;	
buf[len]=HexToAsc((giCodeChecksum>>4)&0x0f);
len++;
buf[len]=HexToAsc(giCodeChecksum&0x0f);
len++;
len		+=	PutString("\r\n",&buf[len],5);
SendText_UART2(buf);


}
/////
void AutoSend(void)
{
	uchar len;

	
	uchar buf[66];
	len		=	PutString("&EA,",buf,5);								//head 4
	buf[len]=HexToAsc(Motor.FlagRuning);		//foreward��ǰ��ת1,backward���2
	//buf[len]=HexToAsc(FlagInputZero);
	//buf[len]=HexToAsc(FlagSetCurrent1);
	len++;
	buf[len]=',';
	len++;
	
	len		+=	MakeValAsc8("I=",chAdc_Resoult7,",",&buf[len]);	//����100ma
	//len		+=	MakeValAsc8("F=",bExCurrentForwardMax,",",&buf[len]);	//adj
	//len		+=	MakeValAsc8("B=",bExCurrentBackwardMax,",",&buf[len]);	//�Ƚϵ���100ma
	len		+=	MakeValAsc8("k=",gpParam->bCurrentRate,",",&buf[len]);
	//len		+=	MakeValAsc8("9=",bExCurrentBackwardPer94,",",&buf[len]);	//�Ƚϵ���100ma
	//len		+=	MakeValAsc8("7=",bExCurrentBackwardPer85,",",&buf[len]);	//�Ƚϵ���100ma
	
	//gpParam->bCurrentForward
	len		+=	PutString("In=",&buf[len],5);
	/*
	buf[len]=HexToAsc(InputBuf>>4);
	len++;
	*/
	//InputBuf��4λ
	buf[len]=HexToAsc(InputBuf);
	len++;
	
	///

	///
	#if CONFIG_433SG
			buf[len]=',';
			len++;
			len		+=	PutString("Pu=",&buf[len],5);
			buf[len]=HexToAsc(PulseCount>>12);
			len++;
			buf[len]=HexToAsc(PulseCount>>8);
			len++;
			buf[len]=HexToAsc(PulseCount>>4);
			len++;
			buf[len]=HexToAsc(PulseCount);
			len++;	
	#endif		

	/*
	len		+=	PutString(",Key=",&buf[len],5);
	for(i=0;i<4;i++)
		{if(Key_Buf[i])
			{
			buf[len]='1';	
			}
		else{
			buf[len]='0';
			}
		len++;
		}		
	*/	


len		+=	PutString("\r\n",&buf[len],5);

SendText_UART2(buf);
		
}
#if CONFIG_433SG
void RemotCodeSend(uchar *command1,uchar comlen1)
{
	uchar len;
	uchar i;
	
	uchar buf[60];
	
	if(comlen1>16)comlen1=16;
	
	len		=	PutString("&ER,",buf,5);								//head 4


	for(i=0;i<comlen1;i++)
					{
				
					buf[len]=HexToAsc(*(command1+i)>>4);
					len++;
					buf[len]=HexToAsc(*(command1+i));
					len++;
				}
	

	/*
	len		+=	PutString(",Key=",&buf[len],5);
	for(i=0;i<4;i++)
		{if(Key_Buf[i])
			{
			buf[len]='1';	
			}
		else{
			buf[len]='0';
			}
		len++;
		}		
	*/	


len		+=	PutString("\r\n",&buf[len],5);

SendText_UART2(buf);
		
}
#endif

/////
void Work(void)
{
	static uchar tim;
	uchar tim4;
		if(bTimeBase)	//����ʱ�䵽���	10ms
				{	
				bTimeBase=0;
	
					
				AdcProcess();
				CheckKey();		//����10ms
				CheckInput();
#if CONFIG_433SG || CONFIG_CC1100
				ProcessRfRecv();
#endif				

				CheckUart();
				
				ProcessTimeSoftStart();	//10MS������
//				ProcessTestStep();
				ProcessJspSwitch();		//��ת�����л� ����
				ProcessTimeOut();	//10MS�����
				


				LedContral();
	
				//chAdc_Resoult7
				if(Motor.FlagRuning==2)
							tim4=150;		//���� 1.5s��˸
				else  tim4=30;		//���� 300ms��˸
				
				
				tim++;
				if(tim>tim4)
					{tim=0;

						if((TimeDebug>0)||(FlagSetCurrent1!=0))
								{
								AutoSend();
								}

					if((Motor.FlagRuning!=0)||(SetIdTime>0)||(Motor.FlagPower>0))
									{
									LED_RUN_ON;	//SetLed1
									}
					//if(Motor.FlagRuning!=0)
						if(Motor.CurrentType!=0)
							{
							SendToRemot(RESPONES_RUNING);	
							}
						
						
					}
				else if(tim>15)
					{
						if((Motor.FlagRuning!=0)||(SetIdTime>0)||(Motor.FlagPower==0))
										{
											LED_RUN_OFF;
										}
					}
//#if Config_Al_Box					
//
//					if(K4_LVL)
//								{
//									//SetLed2;	//���߲����ӱ�ʾ������
//									LED_Al_Box;
//								}
//				else{
//								//ClrLed2;	//�������ӱ�ʾ������
//								LED_Fe_Box;
//						}
//#endif				
				
				}
}