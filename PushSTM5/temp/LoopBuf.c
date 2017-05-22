#include "nomal.h"
#include "config.h"



#include "LoopBuf.h"


uchar Uart0RecvBuf[UART0_RECV_BUF_SIZE+6];	//����0���ջ�����
_loopbuf Uart0RecvStruct;
uchar Uart0SendBuf[UART0_SEND_BUF_SIZE+6];	//����0��������
_loopbuf Uart0SendStruct;




/*****************************************************************************/

void ClearLoopBuf(_loopbuf *st,SizeDataType BufSize)	//������ͻ�����
{
st->len		=	0;		//���г���
st->addTail	=	0;       	//��������β
//st->outHead=0;      			//�������ͷ
st->outTail	=0;		//	BufSize;      //�������β
//st->outTail	=	BufSize;      //�������β
}
/************************************************************************/
uchar AddLoopBuf(_loopbuf *st,uchar *buf,SizeDataType BufSize,uchar chr)	//���뵽���ͻ�����
{
if( (st->addTail != st->outTail) || (0 == st->len) )
	{
	*(buf+st->addTail) = chr;	
	if(st->addTail<BufSize)
		{
		st->addTail++;
		}
	else{
		st->addTail=0;	//ѭ��
		}
	st->len++;
	return 1;		
	}	
else{	//��������
	return 0;
	}	
}


/************************************************************************/
uchar GetLoopbuf(_loopbuf *st,uchar *buf,SizeDataType BufSize,uchar *chr)	//�ӻ��ͻ�������ȡ
{
if( st->len > 0 )
	{
	*chr = *( buf + st->outTail );
	if(st->outTail<BufSize)
		{
		st->outTail ++;	
		}
	else{	//ѭ��
		st->outTail = 0;
		}	
	st->len--;
	if( st->outTail == st->addTail )
		{
		st->len = 0;
		}
	return 1;	//��������
	}
else return 0;	//������û������

}


