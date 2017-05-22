// #include "LoopBuf.h"

#ifndef __LOOP_BUF_H
#define __LOOP_BUF_H
//#define UART0_RECV_BUF_SIZE	(128)
//#define UART0_SEND_BUF_SIZE	(64)
//#define UART1_RECV_BUF_SIZE	(16)
//#define UART1_SEND_BUF_SIZE	16
//////////////////
#define	SizeDataType	unsigned short int
typedef struct
{
SizeDataType 		len;		//���г���
SizeDataType		addTail;	//��������β
//uint16 	outHead;	//�������ͷ
SizeDataType 		outTail;	//�������β
}_loopbuf;


/////
void SetLoopBuf_Non(uchar *buf,_loopbuf *st,SizeDataType BufSize);
void ClearLoopBuf(_loopbuf *st,SizeDataType BufSize);				//������ͻ�����
bool AddLoopBuf(_loopbuf *st,uchar *buf,SizeDataType BufSize,uchar chr);	//���뵽���ͻ�����
unsigned char GetLoopbuf(_loopbuf *st,uchar *buf,SizeDataType BufSize,uchar *chr);	//�ӻ��ͻ�������ȡ



//extern uchar Uart0RecvBuf[UART0_RECV_BUF_SIZE+4];	//����0���ջ�����
//extern _loopbuf Uart0RecvStruct;
//extern uchar Uart0SendBuf[UART0_SEND_BUF_SIZE+4];	//����0���ջ�����
//extern _loopbuf Uart0SendStruct;
//
//extern uchar Uart1RecvBuf[UART1_RECV_BUF_SIZE+4];	//����1���ջ�����
//extern _loopbuf Uart1RecvStruct;
//extern uchar Uart1SendBuf[UART1_SEND_BUF_SIZE+4];	//����1���ջ�����
//extern _loopbuf Uart1SendStruct;
////


#endif
