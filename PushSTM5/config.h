#ifndef _CONFIG_H
#define _CONFIG_H

////////选择看门狗//////
#define EnWdog 				0



//配置单向无线电接收器
#define CONFIG_CC1100		1
//配置单向无线电接收器
#define CONFIG_433SG		0
#define CC1100_PKT_LEN 32

//防止橡皮圈压得太紧，反转退到底后自动正转一点，放松
#define CONFIG_UNPUSH		1
//选择铝箱体
#define Config_Al_Box		1


//IOCFG0_DIV128;				//测试晶体频率
#define CONFIG_26MHZ_OSC_OUT		1
		
//FREQ0_ADJ_260018;		//除以1.000153  新模块晶振偏高 	
#define USER_NEW_OSC		1



//电机最长运行时间
//#define MAX_RUN_TIME_sec	(72)
#define MAX_RUN_TIME_sec	(720)
//85%电流下电机最长运行时间
#define Time10000Ms					1000
//94%电流下电机最长运行时间
#define Time2000Ms					200

//3.3V参考下电流测量比例
//gpParam->bCurrentRate ( 200 - 220 )
//#define CURRENT_RATE	(114)
#define CURRENT_RATE	(168)
//gpParam->bCurrentRate=CURRENT_RATE;			//电机3的 5A

//电机正转顶紧的设定值，最大值为127  18A   max=256*75%=192

//#define CURRENT_FORWARD	(85)
#define CURRENT_FORWARD	(75)
//电机反转放松的设定值，最大值为127  16A
//#define CURRENT_BACKWARD 78
#define CURRENT_BACKWARD 72
//#define CURRENT_BACKWARD 75




///////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
/////////////////////以下为一般不需要改变的配置////////////////////////////////
///////////////////////////////////////////////////////////////////////////////





//长按成为自动功能，放开继续，再按放开成为手动功能
#define CONFIG_FUNCTION_AUTO	1
//增加独立的自动键，感觉不方便
//#define CONFIG_AUTOKEY	0



#endif