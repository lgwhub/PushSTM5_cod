
// #include "uart.h"

#ifndef __UART_H 
#define __UART_H

//#define CONFIG_UART1		0
//#define CONFIG_UART2		1
//#define CONFIG_UART3		0


#define UART1_RECV_BUF_SIZE	32
#define UART1_SEND_BUF_SIZE	32
#define UART2_RECV_BUF_SIZE	32
#define UART2_SEND_BUF_SIZE	32
#define UART3_RECV_BUF_SIZE	32
#define UART3_SEND_BUF_SIZE	32

///////////////////////////////////////
#if CONFIG_UART1
extern uchar Uart1RecvBuf[UART1_RECV_BUF_SIZE+4];	//串口1接收缓冲区
extern _loopbuf Uart1RecvStruct;
extern uchar Uart1SendBuf[UART1_SEND_BUF_SIZE+4];	//串口1发缓冲区
extern _loopbuf Uart1SendStruct;


extern uchar Uart1Sending;
void  Uart1BufInit(void);
uchar GetOneFromUart1(uchar *buf);
uint16 Uart1CharSend(uchar x);
void SendString_UART1(unsigned char *StrData,uint16 len);
void SendText_UART1(uchar *StrData);

#endif

///////////////////////////////////////
#if CONFIG_UART2

extern uchar Uart2RecvBuf[UART2_RECV_BUF_SIZE+4];	//串口2接收缓冲区
extern _loopbuf Uart2RecvStruct;
extern uchar Uart2SendBuf[UART2_SEND_BUF_SIZE+4];	//串口2发缓冲区
extern _loopbuf Uart2SendStruct;




extern uchar Uart2Sending;
void  Uart2BufInit(void);
uchar GetOneFromUart2(uchar *buf);
uint16 Uart2CharSend(uchar x);
void SendString_UART2(unsigned char *StrData,uint16 len);
void SendText_UART2(uchar *StrData);

#endif

///////////////////////////////////////
#if CONFIG_UART3
extern uchar Uart3RecvBuf[UART3_RECV_BUF_SIZE+4];	//串口1接收缓冲区
extern _loopbuf Uart3RecvStruct;
extern uchar Uart3SendBuf[UART3_SEND_BUF_SIZE+4];	//串口1发缓冲区
extern _loopbuf Uart3SendStruct;

extern uchar Uart3Sending;
void  Uart3BufInit(void);
uchar GetOneFromUart3(uchar *buf);
uint16 Uart3CharSend(uchar x);
void SendString_UART3(unsigned char *StrData,uint16 len);
void SendText_UART3(uchar *StrData);

#endif




#endif /* end __UART_H */
/*****************************************************************************
**                            End Of File
******************************************************************************/
