/**********************  ˵   ��  ********************************
    
*************************************************************************/
#define ModBus_Interval_Min  4  //����ModBus����֡ʱ��������λ��mS��

#include "STC15F2K60S2.H"
#include "ModBus.h"
#include "Inic.c"
#include "Isr.c"
#include "ModBus.c"
#include "Func.c"
#include "rtc.c"
#include "eeprom.c"
#include"Iap.c"


void main()
{	IO_Init();		//��ʼ��LED��
	Timer0_Init();	//��ʼ����ʱ��0��1mSʱ��
	Uart1_Init();	//��ʼ������1 
	Uart2_Init();   //��ʼ������2
	IE_Init();		//��ʼ���ж�
	IIC_Init();
	InitADC();
	if(DS1302Read(DS1302_second_read)&0X80)
		 Init_DS1302();

	//SaveParameter(sec2_addr,&REG1,sizeof(REG1));
	
	Init_varible();
	load_configuration();
	
	while(1)
	{  	if( flag_1mS )	       {flag_1mS=0;          Func_1mS();  }
		if(	flag_20mS )		   {flag_20mS=0;		 Func_20mS(); }
		if( flag_100mS )       {flag_100mS=0;        Func_100mS();}
		if (flag_1S!=0)    { flag_1S = 0;     Func_1S();} 
		if (flag_1Min!=0)  { flag_1Min = 0;   Func_1Min();} 
		if (flag_1Hour!=0) { flag_1Hour = 0;  Func_1Hour();} 	  	   
	}		
}
