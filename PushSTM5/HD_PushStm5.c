//   HD_Line1.c     
    #include <includes.h>
    

/////////////
//void GPIO_Configuration(void)
void InitGpio(void)
{

  //关所有输出
JspOut0_OFF;  
JspOut1_OFF;
JspOut2_OFF;
//SW_PWM1_OFF;
  
JspOut0_ON;  
  
 GPIO_DeInit(GPIOD);

	//GPIO_WriteHigh(GPIOA, (GPIO_Pin_TypeDef)GPIO_PIN_ALL);

 ////////  GPIO  PA  //////////////////
//void GPIO_WriteLow(GPIO_TypeDef* GPIOx, GPIO_Pin_TypeDef PortPins)

	GPIO_Init(GPIOA,  (GPIO_Pin_TypeDef)(GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6),  GPIO_MODE_OUT_PP_LOW_FAST);
  
  ////////  GPIO  PB  ////////////////// 
 GPIO_Init(GPIOB,  (GPIO_Pin_TypeDef)(GPIO_PIN_2 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7),  GPIO_MODE_IN_PU_NO_IT);		//按钮和拨码开关
 
 GPIO_Init(GPIOC,  (GPIO_Pin_TypeDef)(GPIO_PIN_3 | GPIO_PIN_5 | GPIO_PIN_7),  GPIO_MODE_OUT_PP_LOW_FAST);	//输出
 GPIO_Init(GPIOC,  (GPIO_Pin_TypeDef)(GPIO_PIN_1),  GPIO_MODE_OUT_PP_HIGH_FAST);	//输出
 GPIO_Init(GPIOC,  (GPIO_Pin_TypeDef)(GPIO_PIN_6),  GPIO_MODE_IN_PU_NO_IT);		//输入
 
 

////////  GPIO  PD  //////////////////
 //UART2发送PD5    UART2接收PD6

GPIO_Init(GPIOD,  (GPIO_Pin_TypeDef)(GPIO_PIN_6 | GPIO_PIN_4 | GPIO_PIN_3 | GPIO_PIN_0),  GPIO_MODE_IN_PU_NO_IT);
GPIO_Init(GPIOD,  (GPIO_Pin_TypeDef)(GPIO_PIN_2 | GPIO_PIN_5 | GPIO_PIN_7),  GPIO_MODE_OUT_PP_HIGH_FAST);
////////  GPIO  PE  //////////////////
GPIO_Init(GPIOE,  (GPIO_Pin_TypeDef)(GPIO_PIN_0 | GPIO_PIN_6),  GPIO_MODE_IN_PU_NO_IT);
GPIO_Init(GPIOE,  (GPIO_Pin_TypeDef)(GPIO_PIN_5),  GPIO_MODE_OUT_PP_LOW_FAST);
////////  GPIO  PG  //////////////////
GPIO_Init(GPIOG,  (GPIO_Pin_TypeDef)(GPIO_PIN_0 | GPIO_PIN_1),  GPIO_MODE_OUT_PP_HIGH_FAST);
 
  

	
}




#if CONFIG_UART2
void  UART2_TxIntEn (void)
{
	UART2_ITConfig(UART2_IT_TXE, ENABLE);
	UART2_ITConfig(UART2_IT_TC, ENABLE);		//485
   // UART_ITConfig(UART2, UART_IT_TXE, ENABLE);
   // UART_ITConfig(UART2, UART_IT_TC, ENABLE);	//485
}
#endif








 

/////////////////////////////////////////////////




/////////////////////////////////////////////////

/////////////////////////////////////////////////


//////////////////////////////

//////////////////////////////
#if CONFIG_UART2

void InitUART2(uint32 baud_rate,UART2_Parity_TypeDef parity)
{


	//UART_Cmd(UART2,ENABLE);


		  Uart2BufInit();
		  
		      UART2_Init(baud_rate, UART2_WORDLENGTH_8D, UART2_STOPBITS_1,parity,UART2_SYNCMODE_CLOCK_DISABLE, UART2_MODE_TXRX_ENABLE);	/*UART2_PARITY_NO*/
                
    
    /* Enable UART1 Transmit interrupt*/
    
		  
		  
    UART2_TxIntEn();
    
    UART2_ITConfig(UART2_IT_RXNE_OR, ENABLE);

}


void  UART2_RxISRHandler (void)
{

    if (UART2_GetITStatus(UART2_IT_RXNE) != RESET) {
                      /* Read one byte from the receive data register         */
        AddLoopBuf(&Uart2RecvStruct,Uart2RecvBuf,UART2_RECV_BUF_SIZE,UART2_ReceiveData8()&0xFF);
        //UART2_ClearITPendingBit(UART2_IT_RXNE);          /* Clear the UART Receive interrupt                   */

    }

}


void  UART2_TxISRHandler (void)
{

		unsigned char temp;



    if (UART2_GetITStatus(UART2_IT_TXE) != RESET) {
    		if (0 == Uart2SendStruct.len)
				     			{
				     			Uart2Sending = 0;	
				     			UART2_ITConfig(UART2_IT_TXE, DISABLE);
				     			//UART2_ITConfig(UART2_IT_TC, DISABLE);
				     			}
							else{
											SetEn485_2;
											GetLoopbuf(&Uart2SendStruct,Uart2SendBuf,UART2_SEND_BUF_SIZE,&temp);
        							UART2_SendData8(temp);
        							UART2_ITConfig(UART2_IT_TXE, ENABLE);
        							UART2_ITConfig(UART2_IT_TC, ENABLE);
      						}
        //UART_ClearITPendingBit(UART2, UART_IT_TXE);           /* Clear the UART transmit interrupt                  */

    }

			//485
    if (UART2_GetITStatus(UART2_IT_TC) != RESET) {
			ClrEn485_2;
			UART2_ITConfig(UART2_IT_TC, DISABLE);
        //UART2_ClearITPendingBit(UART2_IT_TC);           /* Clear the UART transmit interrupt                  */

    }


                                          /* Tell uC/OS-II that we are leaving the ISR            */
}
#endif
//////////////////////////////

////////////////////////////
