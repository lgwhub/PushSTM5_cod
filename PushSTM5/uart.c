
#include <includes.h>

#if CONFIG_UART1
uchar Uart1Sending;
uchar Uart1RecvBuf[UART1_RECV_BUF_SIZE+4];	//串口1接收缓冲区
_loopbuf Uart1RecvStruct;
uchar Uart1SendBuf[UART1_SEND_BUF_SIZE+4];	//串口1发缓冲区
_loopbuf Uart1SendStruct;
#endif

#if CONFIG_UART2
uchar Uart2Sending;
uchar Uart2RecvBuf[UART2_RECV_BUF_SIZE+4];	//串口2接收缓冲区
_loopbuf Uart2RecvStruct;
uchar Uart2SendBuf[UART2_SEND_BUF_SIZE+4];	//串口2发缓冲区
_loopbuf Uart2SendStruct;
#endif

#if CONFIG_UART3
uchar Uart3Sending;
uchar Uart3RecvBuf[UART3_RECV_BUF_SIZE+4];	//串口1接收缓冲区
_loopbuf Uart3RecvStruct;
uchar Uart3SendBuf[UART3_SEND_BUF_SIZE+4];	//串口1发缓冲区
_loopbuf Uart3SendStruct;
#endif


/*****************************************************************************/

///////////////////
//*************************************
void Delay5ms(void)
{
	unsigned short int x;
	
	x=20000;
	while(x>0)
	{
		x--;
	}
	
}


#if CONFIG_UART1
/****************************************************************************
* 名称：void  Uart1Init(ulong baud, uchar parity)
* 功能：初始化串口1。设置其工作模式及波特率。
* 入口参数：baud                波特率
*   parity          0:无校验  1：奇校验  2：偶校验
****************************************************************************/
void  Uart1BufInit(void)
{  

   Uart1Sending = 0;
   ClearLoopBuf(&Uart1SendStruct,UART1_SEND_BUF_SIZE);				//清除环型缓冲区
	ClearLoopBuf(&Uart1RecvStruct,UART1_RECV_BUF_SIZE);
   

}


///////////////////


////////////
uchar GetOneFromUart1(uchar *buf)
{
	uchar flag;

	
	if(Uart1RecvStruct.len)
		{
		GetLoopbuf(&Uart1RecvStruct,Uart1RecvBuf,UART1_RECV_BUF_SIZE,buf);
		flag= 1;
		}
	else 	flag=  0;

	
	return flag;
}


uint16 Uart1CharSend(uchar x)
{
	
	uchar temp;
	uint16 fail=0;
	uint32 t;

    if(Uart1SendStruct.len>3)
	    	{//full
	    	t=10;
	    	while((Uart1SendStruct.addTail == Uart1SendStruct.outTail)&&(t>0))
	    		{
	    		Delay5ms();	//延时10毫秒		
	    		t--;
	    		}
	    	}
	    if(t==0)
	    	fail=1;
	    	
 
	AddLoopBuf(&Uart1SendStruct,Uart1SendBuf,UART1_SEND_BUF_SIZE,x);	//加入到环型缓冲区
 	

	if(Uart1Sending==0)
	             {
	              //Un485Send=FALSE;  //485允许发送
	              //U1MCR=0x03;     //DTR_232=1,RTS_232=1

	              
	              if(GetLoopbuf(&Uart1SendStruct,Uart1SendBuf,UART1_SEND_BUF_SIZE,&temp))
	              	{
	              		Uart1Sending = 1;
	              		SetEn485_1;	//SetPin_DTR1;	//uart1_485
										UART1_SendData(temp);
	              		UART1_ITConfig(UART1_IT_TXE, ENABLE);
	        			}

	             }
	return (!fail);
}








/************************************************************************/
/************************************************************************/
/*     uart1中断方式发送字符串，调用方法:				*/
/* 1.SendString_UART1("ATZ\r",sizeof("ATZ\r"));				     */
/* 2.SendString_UART1(&XYZ[0],length);					     */
/* 3.如果时间超过而没有发送完成，则返回剩余的未发送字节数，如果成功则返回0 */
/************************************************************************/
void SendString_UART1(unsigned char *StrData,uint16 len)
{
uint16 i;
	for(i=0;i<len;i++)
	  {
	  Uart1CharSend(*(StrData+i));
	  }
  
}

/*************************************************************/

void SendText_UART1(uchar *StrData)
{

	uchar i;
	for(i=0;i<255;i++)
	  {
	  if(*(StrData+i)==0x00)break;
	   Uart1CharSend(*(StrData+i));
	  }
}
#endif
///////////////////
#if CONFIG_UART2
void  Uart2BufInit(void)
{  

	
  Uart2Sending = 0;
  ClearLoopBuf(&Uart2SendStruct,UART2_SEND_BUF_SIZE);				//清除环型缓冲区
	ClearLoopBuf(&Uart2RecvStruct,UART2_RECV_BUF_SIZE);

}
///////////////////



///////////////////
uchar GetOneFromUart2(uchar *buf)
{
	uchar flag;


	
	if(Uart2RecvStruct.len)
		{
		GetLoopbuf(&Uart2RecvStruct,Uart2RecvBuf,UART2_RECV_BUF_SIZE,buf);
		flag= 1;
		}
	else 	flag=  0;
	
	
	return flag;
}
///////////////////
uint16 Uart2CharSend(uchar x)  //Uart0CharSend
{
	
	uchar temp;
	uint16 fail=0;
	uint32 t;

	
    if(Uart2SendStruct.len>3)
	    	{//full
	    	t=10;
	    	while((Uart2SendStruct.addTail == Uart2SendStruct.outTail)&&(t>0))
	    		{
	    		Delay5ms();	//延时10毫秒		
	    		t--;
	    		}
	    	}
	    if(t==0)
	    	fail=1;
		
	
 
	AddLoopBuf(&Uart2SendStruct,Uart2SendBuf,UART2_SEND_BUF_SIZE,x);	//加入到环型缓冲区
       //ucos2  	
	///
//	if(Uart2Sending)
//		{
//		if(U0LSR&BIT5)//发送保持寄存器空
//	   		{
//	   		 Uart2Sending = 0;
//	   		}
//		}
	///
	if(!Uart2Sending)
	             {


	              if(GetLoopbuf(&Uart2SendStruct,Uart2SendBuf,UART2_SEND_BUF_SIZE,&temp))
	              		{
	              		Uart2Sending = 1;	
	              			SetEn485_2;
										UART2_SendData8(temp);
	              	UART2_ITConfig(UART2_IT_TXE, ENABLE);
        							UART2_ITConfig(UART2_IT_TC, ENABLE);
	        		}
	
	             }
	 
	return (!fail);
}
///////////////////
void SendText_UART2(uchar *StrData)
{
	//	 INT8U err;
	uchar i;

		for(i=0;i<255;i++)
		  {
		  if(*(StrData+i)==0x00)break;
		   Uart2CharSend(*(StrData+i));
		  }
 
	  
}
///////////////////
void SendString_UART2(uchar *StrData,uint16 len)
{
 //  INT8U err;
	uint16 i;

	
		for(i=0;i<len;i++)
		  {
		  Uart2CharSend(*(StrData+i));
		  }

}
///////////////////


#endif
///////////////////

#if CONFIG_UART3
/****************************************************************************
* 名称：void  Uart3Init(ulong baud, uchar parity)
* 功能：初始化串口1。设置其工作模式及波特率。
* 入口参数：baud                波特率
*   parity          0:无校验  1：奇校验  2：偶校验
****************************************************************************/
void  Uart3BufInit(void)
{  

   Uart3Sending = 0;
   ClearLoopBuf(&Uart3SendStruct,UART3_SEND_BUF_SIZE);				//清除环型缓冲区
	ClearLoopBuf(&Uart3RecvStruct,UART3_RECV_BUF_SIZE);

}


///////////////////


////////////
uchar GetOneFromUart3(uchar *buf)
{
	uchar flag;

	
	if(Uart3RecvStruct.len)
		{
		GetLoopbuf(&Uart3RecvStruct,Uart3RecvBuf,UART3_RECV_BUF_SIZE,buf);
		flag= 1;
		}
	else 	flag=  0;
	

	
	return flag;
}


uint16 Uart3CharSend(uchar x)
{
	
	uchar temp;
	uint16 fail=0;
	uint32 t;

    if(Uart3SendStruct.len>3)
	    	{//full
	    	t=10;
	    	while((Uart3SendStruct.addTail == Uart3SendStruct.outTail)&&(t>0))
	    		{
	    		Delay5ms();	//延时10毫秒		
	    		t--;
	    		}
	    	}
	    if(t==0)
	    	fail=1;
	    	

	AddLoopBuf(&Uart3SendStruct,Uart3SendBuf,UART3_SEND_BUF_SIZE,x);	//加入到环型缓冲区
	
	/*
	if(Uart3Sending!=0)	//准备继续发送
		{
		if(U1LSR&BIT5)//发送保持寄存器空
	   		{
	   		Uart3Sending = 0;
	   		}
		}
		//20100915
	*/
	if(Uart3Sending==0)
	             {
	              //Un485Send=FALSE;  //485允许发送
	              //U1MCR=0x03;     //DTR_232=1,RTS_232=1

	              
	              if(GetLoopbuf(&Uart3SendStruct,Uart3SendBuf,UART3_SEND_BUF_SIZE,&temp))
	              	{
	              		Uart3Sending = 1;
	              		SetEn485_3;
										UART3_SendData(temp);
										UART3_ITConfig(UART3_IT_TXE, ENABLE);
	              		
	        			}
	
	             }
	return (!fail);
}







/************************************************************************/
/************************************************************************/
/*     uart1中断方式发送字符串，调用方法:				*/
/* 1.SendString_UART3("ATZ\r",sizeof("ATZ\r"));				     */
/* 2.SendString_UART3(&XYZ[0],length);					     */
/* 3.如果时间超过而没有发送完成，则返回剩余的未发送字节数，如果成功则返回0 */
/************************************************************************/
void SendString_UART3(unsigned char *StrData,uint16 len)
{
uint16 i;
	for(i=0;i<len;i++)
	  {
	  Uart3CharSend(*(StrData+i));
	  }
  
}

/*************************************************************/

void SendText_UART3(uchar *StrData)
{

	uchar i;
	for(i=0;i<255;i++)
	  {
	  if(*(StrData+i)==0x00)break;
	   Uart3CharSend(*(StrData+i));
	  }
}
#endif
//////////////////////////////////////////////////////////////////


/******************************************************************************
**                            End Of File
******************************************************************************/
