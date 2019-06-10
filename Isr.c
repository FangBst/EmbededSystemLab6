void Timer0_isr(void) interrupt 1
{	flag_1mS = 1;
	count_1mS++;
	if( count_1mS == 20 ) 
	     { count_1mS = 0;    
		   flag_20mS = 1;
		   count_20mS++;
		   if(count_20mS==5){
		       count_20mS=0;
			   flag_100mS=1;
			   count_100mS++;
			   if (count_100mS==10) 
				 { count_100mS=0;			 
				 	flag_1S=1;
					count_1S++;
						 if(count_1S==60) 
							{ count_1S=0;						
							  flag_1Min=1;
							  count_1Min++;
								if(count_1Min==60) 
									{ count_1Min=0;	flag_1Hour=1;
									}
							} 
				 }
         	}
	}							
}

void ADC_isr() interrupt 5
{

	if(Mode==0){
		global++;
		if(global>500)			  //���ɼ�500�κ���������ƽ��ֵ
		{
			date_h=(sum+250)/500;//��������
			nav_h=(date_h>>5)&0x07;
			nav_l=date_h&0x1F;
			global=0;
			sum=0;
		}
		sum+=ADC_RES;
		ADC_CONTR&=~0X10;		  //��ADC_FLAGλ����
		ADC_CONTR|=0X08;		 //��ADC_START���������λ
	}
	else{
		Time_ad++;
		if(Time_ad>500){
			if(flag_lt==1)
			{
				uint ii=(tsum+ttime/2)/ttime;
				tvalue=tdata[ii-1];
				tsum=0;
				ttime=0;
				Time_ad=0;
			}
			if(flag_lt==-1)
			{
				lvalue=(lsum+ltime/2)/ltime;
				lsum=0;
				ltime=0;
				Time_ad=0;
			}
		}
		else {
			if(flag_lt==1)
			{
				//��Ӧ�¶ȵ����ݴ���
				tsum+=((ADC_RES*256+ADC_RESL)/4);//��10λADֵת��Ϊ8λADֵ
				ttime++;
			}
			if(flag_lt==-1)
			{
				//����ⲿ�ֵ�����
				lsum+=(ADC_RES*256+ADC_RESL);
				ltime++;
			}
		}
		ADC_CONTR&=~0X10;  					 //ת����ɺ�ADC_FLAG����
		ADC_CONTR|=0X08;	 					 //ת����ɺ�ADC_START��1
	}
}

void Uart1_isr(void) interrupt 4 		   //�����жϺ���   
{	if (TI) 
        { TI = 0;                      // �����һ�����ݷ��꣬TI = 0; 
		  if (Uart1.Tx_count++ >= Uart1.Tx_Nmax)      // ������ݰ��������	   
			   flag_Uart1_Tx=FREE;
		  else SBUF=*Uart1.Tx_Pc++;    // ���������ݰ���һ�ֽ�	       	   					 
        }       
	if (RI) 
	    { RI=0;			       				
	    }
}

void Uart2_isr(void) interrupt 8
{   if(S2CON & 0x02)
      { S2CON &= ~0x02;	    //�巢���жϱ�־λ
	  	if(Uart2.Tx_count++ >=Uart2.Tx_Nmax){
			flag_Uart2_Tx=FREE;
			TR485=0;
		}
		else {
			S2BUF=*Uart2.Tx_Pc++;
		}  
	  }
	if(S2CON & 0x01)
      { S2CON &= ~0x01;		//������жϱ�־λ 
	    if(flag_Uart2_Rx==FREE)		      //������Խ�������֡
		{   *Uart2.Rx_Pc++=S2BUF;
			Uart2.Rx_count++;
			Uart2.Rx_interval_time=ModBus_Interval_Min;	
		}
	  }
}

