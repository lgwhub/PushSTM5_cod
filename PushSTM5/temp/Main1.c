

#if CONFIG_433SG
  #include "Decode.h"
		void Init_ext_Int1(void);
	#endif




/////////////////
void Init_Timer0(void)
{
	TCNT0	=	0;		//������
	//TCCR0B	=	0X03;	//ICNC1��׽��������  /64
	//8bit ��ʱ��
	//TCCR0B	=	0X05;	//ICNC1��׽��������  /1024
	TCCR0B	=	0X04;	//ICNC1��׽��������  /256  //ң����������Ҫ
	//TIMSK0	|=	(1<<OCIE0A)+(1<<OCIE0B)+(1<<TOIE0);
	TIMSK0	|=	(1<<OCIE0B)+(1<<TOIE0);
}



///
#if IAR_SYSTEM
#pragma vector=INT1_vect	
__interrupt void ext_int1_isr(void)
#else
#pragma interrupt_handler ext_int1_isr:iv_INT1	//2
void ext_int1_isr(void)	
#endif
{
//EIMSK	&=	(~BIT1);	//MEGA88	
#if CONFIG_433SG
		uchar temp;	//��ǰʱ��
		temp=TCNT0;	//timer0
		DecodePulse(temp);
		PulseCount++;	
#endif		

}
///




//////////
#if IAR_SYSTEM
#pragma vector=TIMER0_OVF_vect
__interrupt void time0_ovf_isr(void)
#else
#pragma interrupt_handler time0_ovf_isr:iv_TIMER0_OVF	//14
void time0_ovf_isr(void)
#endif
{
#if CONFIG_433SG
		DecodeTimeout++;
#endif		

}
//////////


