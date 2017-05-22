#ifndef _NOMAL_H
#define _NOMAL_H

#define bool unsigned char
#define BOOL unsigned char

#define uchar unsigned char
#define uint unsigned short int
#define uint16 unsigned short int
#define uint32 unsigned long int


#define TRUE 1
#define FALSE 0

#define true 1
#define false 0

#define SPACE 0x20
#define CharESC
#define CharSUB

//#define CR 0x0d
#define LF 0x0a


#define BIT0  0X01
#define BIT1  0X02
#define BIT2  0X04
#define BIT3  0X08
#define BIT4  0X10
#define BIT5  0X20
#define BIT6  0X40
#define BIT7  0X80


//////////////////////




uchar CompareCharChar(uchar *chr1,uchar *chr2,uchar len);
uchar MakeValAsc8(uchar *StrHead,uchar Val,uchar *StrEnd,uchar *out);	//8λ����ת��Ϊʮ���Ƶ�ASC�룬��ǰ��׺
//uchar MakeValAsc16(uchar *StrHead,uint16 Val,uchar *StrEnd,uchar *out,uchar point);	//16λ����ת��Ϊʮ���Ƶ�ASC�룬��ǰ��׺
//uchar MakeValAsc32(uchar *StrHead,uint32 Val,uchar *StrEnd,uchar *out,uchar point);	//32λ����ת��Ϊʮ���Ƶ�ASC�룬��ǰ��׺

//uchar IsNumberAsc(uchar x);   /* �ж��Ƿ�Ϊ����0~9 */
uchar HexToAsc(uchar x);   /*  1/2hex>>1asc2   */
uchar AscToHex(uchar x); 
//uint16 NumberAscStringToInt16(uchar *p);	//���5λASC��������ַ���ת��Ϊ16λ�޷�������
//uchar MakeValHex16(uchar *StrHead,uint Val,uchar *StrEnd,uchar *out);	//16λ����ת��ΪHEX��ASC�룬��ǰ��׺
uchar PutString(uchar *ps,uchar *pd,uchar max_ps) ;
#endif