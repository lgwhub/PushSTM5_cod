/****************************************************************************
 **         �û�ʹ�ýӿں���ֻ��������
 **         cc1100Initializtion() cc1100Scanf() cc1100Printf()
 **         ģʽ�л�ȫ���������ڲ��������
 ***************************************************************************/
#include <includes.h>

		

#if 1 


unsigned char rx_buf[32+6];
uchar VolRssi;
uchar VolLqi;
uchar RssiStatus[5];
//<�Ĵ������������>
//__flash unsigned char cc1100regcfg[39]={
//const 
unsigned char cc1100regcfg[39]={
IOCFG2,IOCFG1,IOCFG0,FIFOTHR,SYNC1,SYNC0,CC1100_PKT_LEN,PKTCTRL1,PKTCTRL0,ADDR,CHANNR,FSCTRL1,FSCTRL0,
FREQ2,FREQ1,FREQ0,MDMCFG4,MDMCFG3,MDMCFG2,MDMCFG1,MDMCFG0,DEVIATN,MCSM2,MCSM1,MCSM0,FOCCFG,BSCFG,
AGCCTRL2,AGCCTRL1,AGCCTRL0,WOREVT1,WOREVT0,WORCTRL,FREND1,FREND0,FSCAL3,FSCAL2,FSCAL1,FSCAL0};

/******************************************��������********************************************/

unsigned char BusyCC1100(void)
{
unsigned char flag;
unsigned short int tim;

flag = 1;
tim = 0;	
	while(CC1100_SO_LVL!=0)	//BUSY();
		{
			
		RstWdog();	
		tim++;
		if(tim>65530)
			{
			flag = 0;	
			break;
			}
			
			
		}
return flag;
}

/*8bitд��*/
void cc1100Write8Bit(unsigned char byte)
{
  unsigned char temp;
  
  for(temp=0;temp<8;temp++)
  {  
    
    //cc1100_SI = (byte&0x80)>>7; 
   // if((byte&0x80)!=0)
     if(( (byte&0x80)>>7 )!=0)
    	{
    	SET_CC1100_SI;
    	}
    else{
    	CLR_CC1100_SI;
	}
	
    byte = byte<<1;
    SET_CC1100_SCLK;
    CLR_CC1100_SCLK;
  }
}

/*8bit����*/
unsigned char cc1100Read8Bit(void)
{
  unsigned char temp;
  unsigned char byte = 0x00;
   
  for(temp=0;temp<8;temp++)
  {
    byte = byte<<1;
    SET_CC1100_SCLK;   
    //byte = byte|(CC1100_SO_LVL&0x01);
    
    if(CC1100_SO_LVL!=0)
    	{
    		byte = byte|0x01;
    	}
    
    
    CLR_CC1100_SCLK;
  }
  return(byte);
}

/****************************************��չ����*******************************************/

/*�����ڲ�����*/
void cc1100Strobecommand(unsigned char com)
{
    CLR_CC1100_CSN;	//SPI_ENABLE();
    BusyCC1100();	//BUSY();
    cc1100Write8Bit(com);
    SET_CC1100_CSN;	//SPI_DISABLE();
}

/*���üĴ���*/
void cc1100ConfigRegister(unsigned char add, unsigned char reg)
{
    CLR_CC1100_CSN;	//SPI_ENABLE();
    BusyCC1100();	//BUSY();
    cc1100Write8Bit(cc1100_W_CONFIG(add));
    cc1100Write8Bit(reg);
    SET_CC1100_CSN;	//SPI_DISABLE();
}

/*�趨PATAB*/
void cc1100WriteTatab(unsigned char* p,unsigned char total)
{
  unsigned char temp;
  CLR_CC1100_CSN;	//SPI_ENABLE();
  BusyCC1100();	//BUSY();
  cc1100Write8Bit(cc1100_W_PATAB(0));
  for(temp=0; temp<total; temp++)
  {
    cc1100Write8Bit(p[temp]);
  }
  SET_CC1100_CSN;	//SPI_DISABLE();
}

/*���������ݼĴ���*/
void cc1100ReadRxPayload(unsigned char* p,unsigned char total)
{
  unsigned char temp;
  CLR_CC1100_CSN;	//SPI_ENABLE();
  BusyCC1100();	//BUSY();
  cc1100Write8Bit(cc1100_R_RX_PAYLOAD(0));
  for(temp=0; temp<total; temp++)
  {
    p[temp] = cc1100Read8Bit();
  }
  SET_CC1100_CSN;	//SPI_DISABLE();
  
  //RSSI
  CLR_CC1100_CSN;	//SPI_ENABLE();
  BusyCC1100();	//BUSY();
  cc1100Write8Bit(cc1100_R_RX_PAYLOAD(0));
  for(temp=0; temp<2; temp++)
  {
    RssiStatus[temp] = cc1100Read8Bit();
  }
  SET_CC1100_CSN;	//SPI_DISABLE();
  
  VolRssi=0x80+RssiStatus[0];
	VolLqi=RssiStatus[1];

}

//RSSI
/*
VolRssi
ADDR_LQI			0X33
ADDR_RSSI		0X34

void cc1100ReadRssiStatus(uchar *p)
{
	  unsigned char i;
  CLR_CC1100_CSN;	//SPI_ENABLE();
  BusyCC1100();	//BUSY();
  cc1100Write8Bit(0x80|ADDR_RSSI);
  *p= cc1100Read8Bit();
  //for(i=0; i<3; i++)
 // {
    //p[i] = cc1100Read8Bit();
  //}
  
  SET_CC1100_CSN;	//SPI_DISABLE();
	
}
*/
/*д�������ݼĴ���*/
void cc1100WriteTxPayload(unsigned char* p,unsigned char total)
{
  unsigned char temp;
  CLR_CC1100_CSN;	//SPI_ENABLE();
  BusyCC1100();	//BUSY();
  cc1100Write8Bit(cc1100_W_TX_PAYLOAD(0));
  if(total>CC1100_PKT_LEN)total=CC1100_PKT_LEN;
  for(temp=0; temp<total; temp++)
  {
    cc1100Write8Bit(p[temp]);
  }
  SET_CC1100_CSN;	//SPI_DISABLE();
}


/****************************************���ú���*******************************************/
/*��ʼ������*/
void cc1100Initializtion(void)
{
  unsigned char temp;
  //cc1100_IO_INITIALIZTION();
  
//CC1100_SCLK_ENABLE;
//CC1100_CSN_ENABLE;
//CC1100_SI_ENABLE;
//CC1100_SO_DISABLE;
//CC1100_GDO2_DISABLE;
//CC1100_GDO0_DISABLE;

SET_CC1100_CSN;
DelayMs(2);
CLR_CC1100_CSN;
DelayMs(10);

CLR_CC1100_SCLK;
//SET_CC1100_SO;
//SET_CC1100_GDO2;
//SET_CC1100_GDO0;
SET_CC1100_CSN;
CLR_CC1100_SI;
  
  
  
  
  
  
  cc1100Strobecommand(cc1100_STROBE_SRES(0));
  
       	#if CONFIG_26MHZ_OSC_OUT
 		cc1100regcfg[2]=IOCFG0_DIV128;				//���Ծ���Ƶ��
 	#endif 		
 	
 	#if USER_NEW_OSC
		cc1100regcfg[15]=FREQ0_ADJ_260018;		//����1.000153  ��ģ�龧��ƫ��26.0018 (��ģ��Ϊ25.9978), Ƶ�ʼ�Сһ��
 	#endif
  
  for(temp=0;temp<39;temp++)
  {
    cc1100ConfigRegister(temp,cc1100regcfg[temp]);
  }
  cc1100ConfigRegister(ADDR_FSTEST,FSTEST);
  cc1100ConfigRegister(ADDR_TEST2,TEST2);
  cc1100ConfigRegister(ADDR_TEST1,TEST1);
  cc1100ConfigRegister(ADDR_TEST0,TEST0);
  //cc1100WriteTatab("\xc0\xc8\x85\x60",4);
  
    //STANDARD \xc0\xc8\x85\x51\x3a\x06\x1c\x6c
  //cc1100WriteTatab("\xc0\xc8\x85\x60",4);		//org 79
  //cc1100WriteTatab("\xc8\x85\x51\x3a\x06\x1c\x6c\x18",8);	//ok3			//71	
  //cc1100WriteTatab("\xc0\xc0\xc0\xc0\xc0\xc0\xc0\xc0",8);	//ok1		79
  cc1100WriteTatab("\xc8\xc8\xc8\xc8\xc8\xc8\xc8\xc8",8);	//ok2			71
  //cc1100WriteTatab("\x85\x51\x3a\x06\x1c\x6c\x18\x18",8);	//ok4  62
  //cc1100WriteTatab("\x85\x85\x85\x85\x85\x85\x85\x85",8);		//60 ����70������
	//cc1100WriteTatab("\x51\x51\x51\x51\x51\x51\x51\x51",8);		//55
   // cc1100WriteTatab("\x3a\x3a\x3a\x3a\x3a\x3a\x3a\x3a",8);		//50 ����50
  
  cc1100Strobecommand(cc1100_STROBE_SFSTXON(0));
  cc1100Strobecommand(cc1100_STROBE_SFRX(0));
  cc1100Strobecommand(cc1100_STROBE_SRX(0));
  
  	VolRssi=0;
	VolLqi=0;
}

/*�������ݰ�(32�ֽ�)*/
unsigned char cc1100Scanf(unsigned char* p)
{
  if(CC1100_GDO2_LVL!=0){
    return(0);}
  cc1100ReadRxPayload(p,CC1100_PKT_LEN);

  cc1100Strobecommand(cc1100_STROBE_SIDLE(0));
  cc1100Strobecommand(cc1100_STROBE_SFRX(0));
  cc1100Strobecommand(cc1100_STROBE_SRX(0));
  return(1);
}

/*�������ݰ�(32�ֽ�)*/
void cc1100Printf(unsigned char* p)
{
unsigned short int tim;
  cc1100Strobecommand(cc1100_STROBE_SIDLE(0));
  cc1100WriteTxPayload(p,CC1100_PKT_LEN);
  cc1100Strobecommand(cc1100_STROBE_STX(0));
  BusyCC1100();//�ȴ������뷢�����
  
  tim=0;
  while(CC1100_SO_LVL==0)//�ȴ����ݰ��������
  	{
  	RstWdog();
  	tim++;
  	if(tim>65530)
  		break;	
  	}
  cc1100Strobecommand(cc1100_STROBE_SRX(0));
}

/**********************************************/

/*���ͷ���
unsigned char tx_buf[32];
unsigned char rx_buf[32];
void main()
{
  cc1100Initializtion();
  tx_buf[0] = 0;
  tx_buf[1] = 1;//�ڷ���������д��������Ϣ
  while(1)
  {
    cc1100Printf(tx_buf);
    //�÷��ͺ������÷������飬����������
  }
}
*/

/*���շ���
unsigned char tx_buf[32];
unsigned char rx_buf[32];
void main()
{
  cc1100Initializtion();
  while(1)
  {
    while(cc1100Scanf(rx_buf)!=1);
    //��û�н��յ����ݰ�ʱ������ѭ����һ�����յ����ݰ�����д����ָ����32�ֽڽ�������rx_buf��
    PORTB = rx_buf[0];
    //�����յ������ݰ��ĵ�һ���ֽڴ�B�����
  }
}
*/

/*ת��������
unsigned char buf[32];
void main()
{
  cc1100Initializtion();
  while(1)
  {
    while(cc1100Scanf(buf)!=1);//�ȴ��յ����ݰ�
    cc1100Printf(buf);//���յ������ݰ�ԭ������
    //ע��:cc1100Printf() cc1100Scanf() ������������˳����ȫ���ⲻ�ÿ������߼������Ӱ��
  }
}
*/


#endif


