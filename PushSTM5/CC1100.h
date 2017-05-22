/****************************************************************************
 **
 **     ERC-cc1100�����շ�ģ�����������h�ĵ�
 **
 ***************************************************************************/


#ifndef cc1100_driver_h
#define cc1100_driver_h

extern unsigned char rx_buf[32+6];

extern unsigned char cc1100regcfg[39];

/*******************�������������ʽ(��ʽ��1��ʾ�ɱ����)*********************/
#define cc1100_COMMEND_PROCESS(com_type,format,com) \
((com_type&(~format))|(com&format))
//����д���üĴ�����ʼ��ַ
#define cc1100_W_CONFIG(factor) \
cc1100_COMMEND_PROCESS(0x40,0x3f,factor)
//���ö����üĴ�����ʼ��ַ
#define cc1100_R_CONFIG(factor) \
cc1100_COMMEND_PROCESS(0xc0,0x3f,factor)
//дPATAB ��������
#define cc1100_W_PATAB(factor) \
cc1100_COMMEND_PROCESS(0x7e,0x00,factor)
//��PATAB ��������
#define cc1100_R_PATAB(factor) \
cc1100_COMMEND_PROCESS(0xfe,0x00,factor)
//д�������� ��������
#define cc1100_W_TX_PAYLOAD(factor) \
cc1100_COMMEND_PROCESS(0x7f,0x00,factor)
//���������� ��������
#define cc1100_R_RX_PAYLOAD(factor) \
cc1100_COMMEND_PROCESS(0xff,0x00,factor)

/*Strobe commands*/
//оƬ�ڲ���λ����
#define cc1100_STROBE_SRES(factor) \
cc1100_COMMEND_PROCESS(0x30,0x00,factor)
//������У׼Ƶ�ʺϳ�������
#define cc1100_STROBE_SFSTXON(factor) \
cc1100_COMMEND_PROCESS(0x31,0x00,factor)
//������������ģʽ����
#define cc1100_STROBE_SRX(factor) \
cc1100_COMMEND_PROCESS(0x34,0x00,factor)
//������������ģʽ����
#define cc1100_STROBE_STX(factor) \
cc1100_COMMEND_PROCESS(0x35,0x00,factor)
//�������ģʽ����
#define cc1100_STROBE_SIDLE(factor) \
cc1100_COMMEND_PROCESS(0x36,0x00,factor)
//��ϴRX FIFO����
#define cc1100_STROBE_SFRX(factor) \
cc1100_COMMEND_PROCESS(0x3a,0x00,factor)
//��ϴTX FIFO����
#define cc1100_STROBE_SFTX(factor) \
cc1100_COMMEND_PROCESS(0x3b,0x00,factor)

//--------------------------------------------------------------
//<RF-Configuration-Register ������Ϣ>
#define IOCFG2        0x47       
#define IOCFG1        0x46       
#define IOCFG0        0x29       
	#define IOCFG0_DIV4        0x34
	#define IOCFG0_DIV128        0x3E
	#define IOCFG0_DIV192        0x3F      
#define FIFOTHR       0x07       
#define SYNC1         0xd3       
#define SYNC0         0x91       
//#define PKTLEN        0x20		//������  
//#define CC1100_PKT_LEN	32	//������
#define PKTCTRL1      0x0c//0x0d       //���ݰ�����
#define PKTCTRL0      0x44       
#define ADDR          0x00//0xcc       // ��ַ�趨��Ĭ��δʹ�ܣ�
//#define CHANNR        0x61//0x00       // Ƶ��ͨ���趨
#define CHANNR        0x78//0x00       // Ƶ��ͨ���趨
#define FSCTRL1       0x08       
#define FSCTRL0       0x00       
#define FREQ2         0x0f       
#define FREQ1         0xc4       
#define FREQ0         0xec

	 //����1.000083622  ģ�龧��Ϊ26.0000 (��ģ��Ϊ25.9978), Ƶ�ʼ�Сһ��
	#define FREQ0_ADJ_260000         0x95        
	//����1.000153  ��ģ�龧��ƫ��26.0018 (��ģ��Ϊ25.9978), Ƶ�ʼ�Сһ��
	#define FREQ0_ADJ_260018        0x4d  
	//Freq=Fxosc*FREQ[23:0]/65536
                  
#define MDMCFG4       0x7b       
#define MDMCFG3       0x83       
#define MDMCFG2       0x73       
#define MDMCFG1       0xa2       
#define MDMCFG0       0xf8       
#define DEVIATN       0x00       
#define MCSM2         0x07       
#define MCSM1         0x3f       
#define MCSM0         0x18       
#define FOCCFG        0x1d       
#define BSCFG         0x1c       
#define AGCCTRL2      0xc7    
#define AGCCTRL1      0x00     
#define AGCCTRL0      0xb2      
#define WOREVT1       0x87    
#define WOREVT0       0x6b   
#define WORCTRL       0x71      
#define FREND1        0xb6      
#define FREND0        0x10       
#define FSCAL3        0xea    
#define FSCAL2        0x2a      
#define FSCAL1        0x00       
#define FSCAL0        0x1f     

#define FSTEST        0x59    

#define TEST2         0x81      
#define TEST1         0x35       
#define TEST0         0x0b    

//-----------------------------------------------------------
//<�Ĵ�����ַ��Ϣ�������������޸�>
#define ADDR_IOCFG2      0x00         
#define ADDR_IOCFG1      0x01         
#define ADDR_IOCFG0      0x02         
#define ADDR_FIFOTHR     0x03         
#define ADDR_SYNC1       0x04         
#define ADDR_SYNC0       0x05         
#define ADDR_PKTLEN      0x06         
#define ADDR_PKTCTRL1    0x07         
#define ADDR_PKTCTRL0    0x08         
#define ADDR_ADDR        0x09         
#define ADDR_CHANNR      0x0a         
#define ADDR_FSCTRL1     0x0b         
#define ADDR_FSCTRL0     0x0c         
#define ADDR_FREQ2       0x0d         
#define ADDR_FREQ1       0x0e         
#define ADDR_FREQ0       0x0f         
#define ADDR_MDMCFG4     0x10         
#define ADDR_MDMCFG3     0x11         
#define ADDR_MDMCFG2     0x12        
#define ADDR_MDMCFG1     0x13        
#define ADDR_MDMCFG0     0x14       
#define ADDR_DEVIATN     0x15       
#define ADDR_MCSM2       0x16        
#define ADDR_MCSM1       0x17         
#define ADDR_MCSM0       0x18        
#define ADDR_FOCCFG      0x19         
#define ADDR_BSCFG       0x1a        
#define ADDR_AGCCTRL2    0x1b        
#define ADDR_AGCCTRL1    0x1c         
#define ADDR_AGCCTRL0    0x1d        
#define ADDR_WOREVT1     0x1e        
#define ADDR_WOREVT0     0x1f         
#define ADDR_WORCTRL     0x20       
#define ADDR_FREND1      0x21       
#define ADDR_FREND0      0x22        
#define ADDR_FSCAL3      0x23        
#define ADDR_FSCAL2      0x24         
#define ADDR_FSCAL1      0x25         
#define ADDR_FSCAL0      0x26         

#define ADDR_FSTEST      0x29         

#define ADDR_TEST2       0x2c        
#define ADDR_TEST1       0x2d         
#define ADDR_TEST0       0x2e  
 ///////////
#define ADDR_FREQEST			0X32
#define ADDR_LQI			0X33
#define ADDR_RSSI		0X34
//------------------------------------------------------------




/*******************��������*********************/
void cc1100Write8Bit(unsigned char byte);
unsigned char cc1100Read8Bit(void);
void cc1100Strobecommand(unsigned char com);
void cc1100ConfigRegister(unsigned char add, unsigned char reg);
void cc1100WriteTatab(unsigned char* p,unsigned char total);
void cc1100ReadRxPayload(unsigned char* p,unsigned char total);
void cc1100WriteTxPayload(unsigned char* p,unsigned char total);
void cc1100Initializtion(void);
unsigned char cc1100Scanf(unsigned char* p);
void cc1100Printf(unsigned char* p);

void cc1100ReadRssiStatus(uchar *p);

#endif  //cc1100_driver_h
