
//includes.h

#ifndef _INCLUDE_H
#define _INCLUDE_H

#include "nomal.h"
#define CONFIG_UART1		0
#define CONFIG_UART2		1
#define CONFIG_UART3		0

//#include "stm8s.h"
#include "stm8s_conf.h"
#include "config.h"
#include "LoopBuf.h"
#include "uart.h"
#include "HD_PushSTM5.H"
#include "main.h"

#include "soft.h"


#include "GetAverage.h"

#include "CC1100.h"

#if CONFIG_433SG
  #include "Decode.h"
#endif



#endif





