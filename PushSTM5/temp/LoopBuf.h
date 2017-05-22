#ifndef __LOOP_BUF_H
#define __LOOP_BUF_H
#define UART0_RECV_BUF_SIZE	20
#define UART0_SEND_BUF_SIZE	32
//#define	SizeDataType	unsigned short int
#define	SizeDataType	unsigned char

typedef struct
{
SizeDataType 		len;		//���г���
SizeDataType		addTail;	//��������β
//uint16 	outHead;	//�������ͷ
SizeDataType 		outTail;	//�������β
}_loopbuf;


/////
void ClearLoopBuf(_loopbuf *st,SizeDataType BufSize);				//������ͻ�����
unsigned char AddLoopBuf(_loopbuf *st,uchar *buf,SizeDataType BufSize,uchar chr);	//���뵽���ͻ�����
unsigned char GetLoopbuf(_loopbuf *st,uchar *buf,SizeDataType BufSize,uchar *chr);	//�ӻ��ͻ�������ȡ



extern uchar Uart0RecvBuf[UART0_RECV_BUF_SIZE+6];	//����0���ջ�����
extern _loopbuf Uart0RecvStruct;
extern uchar Uart0SendBuf[UART0_SEND_BUF_SIZE+6];	//����0���ջ�����
extern _loopbuf Uart0SendStruct;

////
uchar Uart0CharSend(uchar x);

void SendText_UART0(uchar *StrData);
uchar GetOneFromUart0(uchar *buf);

#endif
