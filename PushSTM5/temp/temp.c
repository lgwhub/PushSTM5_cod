//////////////////////////////////////////////////
void ProcessRemotCommand(uchar *p)
{

uchar i;

uchar *nm;
uchar cmd;


/*
			buf[4]=	command;	
			buf[5]=	'6';	
			buf[6]=	'6';
			buf[7]=	0x70;
	*/
		if(*p<0x40)return;		//包号，1字节, 遥控器发送为"4xH"
		if((*(p+7)!=0x70)&&(*(p+7)!=0x71))return;
			
		nm=p+1;
		cmd=*(p+4);
		//if(('6'==*(p+5))&&('6'==*(p+6))&&(*(p+7)==0x70))
//		if(*(p+7)==0x70)	
//			{//老式遥控器兼容
//		}



	if(TimeSetId>0)
		{
		
		
			//setid
			if(cmd==REMOT_COMMAND_POWER_ON)
					{
					gpParam->RemotName[0]=*(nm);
					gpParam->RemotName[1]=*(nm+1);
					gpParam->RemotName[2]=*(nm+2);
//					if(WirelessDebugTime>0)
//						ResponseType=REMOT_COMMAND_DEBUG;
//					else 	ResponseType=REMOT_COMMAND_SET_ID;	//0X59

				
				for(i=0;i<Max_Param_Len;i++)
					{
					EEPROM_Write(EEPROM_BASE_ADR+i,gbParamBuf[i]);
					}
			
				TimeSetId=0;
		
				}
		}	
	else{	
			//非对码时间
			if((CompareCharChar(nm,"555",3)!=0)||(CompareCharChar(nm,&gpParam->RemotName[0],3)!=0))	//默认地址
				{
			//遥控器序号ok
					//	SendUartCommand(cmd);
						ProcessCommand(cmd);
				}
		}

	
}
///////////////////