void delay();
void DS1302Write(uchar cmd,uchar dat);
uchar DS1302Read(uchar cmd);

void Init_varible(){
	Mode=0;

	Flag_flash=0;
	is_flashing=0;
	flash_pos=0;

	flag_lt=0;
}
void IO_Init(void)		   //   ��ʶ��8��LED��
{  	P2M1 = 0x00;       //   ���ã�P2����
	P2M0 = 0xff;		   
	P0M1 = 0x00;       //   ���ã�P0����   
	P0M0 = 0xff;
}

void Timer0_Init(void)  //1000΢��@11.0592MHz
{  	AUXR |= 0x80;		//��ʱ��ʱ��1Tģʽ
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TL0 = 0xCD;		//���ö�ʱ��ֵ
	TH0 = 0xD4;		//���ö�ʱ��ֵ
	TF0 = 0;		//���TF0��־
	TR0 = 1;		//��ʱ��0��ʼ��ʱ	
	ET0=1;          //������ʱ��0�ж�
}

void Uart1_Init(void)   //115200bps@11.0592MHz
{	SCON = 0x50;		//8λ����,�ɱ䲨����
	AUXR |= 0x40;		//��ʱ��1ʱ��ΪFosc,��1T
	AUXR &= 0xFE;		//����1ѡ��ʱ��1Ϊ�����ʷ�����
	TMOD &= 0x0F;		//�趨��ʱ��1Ϊ16λ�Զ���װ��ʽ
	TL1 = 0xE8;		    //�趨��ʱ��ֵ
	TH1 = 0xFF;		    //�趨��ʱ��ֵ
	ET1 = 0;		    //��ֹ��ʱ��1�ж�
	TR1 = 1;		    //������ʱ��1
	ES=1;               //��������0�ж�
}

void Uart2_Init(void)		//9600bps@11.0592MHz	
{  	S2CON = 0x50;		//8λ����,�ɱ䲨����
	AUXR |= 0x04;		//��ʱ��2ʱ��ΪFosc,��1T
	T2L = 0xE0;	  	    //�趨��ʱ��ֵ
	T2H = 0xFE;		    //�趨��ʱ��ֵ
	AUXR |= 0x10;		//������ʱ��2
	P_SW2 |= 0x01 ;     //�л�����2�Ĺܽŵ�P4.6,P4.7
	TR485=0;			//�ý���״̬
	IE2 |=0x01;         //ʹ�ܴ���2�ж�
}

void IE_Init(void)
{	
	EA=1;			
}

void IIC_init()
{
	SCL=1;
	delay();
	SDA=1;	
	delay();
}

void Init_DS1302()
{
	uchar temp;
	DS1302Write(0X8E,0X00);//д������
	temp=DS1302Read(DS1302_second_read)&0x7f;
	DS1302Write(DS1302_second_write,temp);
	DS1302Write(0X8E,0X80);//д������1
}

void InitADC()
{
	P1ASF = 0x80;			
	ADC_RES = 0;			
	ADC_CONTR = 0X8F;		 
	CLK_DIV = 0X00;			
	EADC = 1;				
	PADC = 1;				
}

void ADC_Temp_Init()			//��ʼ��ADC
{
	//P1ASF=0xff;						//��P1����Ϊģ�⹦��A/Dʹ��
	ADC_RES=0;						//�Ĵ���ADC_RES��ADC_RESL����A/Dת�����
	ADC_RESL=0;						//��ʼ��ֵ0
	CLK_DIV=0x20;					//ADRJ=1��ADC_RES[1:0]��Ÿ�2λADC�����ADC_RESL[7:0]��ŵ�8λADC���	
	ADC_CONTR=0x8c;
}

void ADC_Light_Init()			//��ʼ��ADC
{
	//P1ASF=0xff;						//��P1����Ϊģ�⹦��A/Dʹ��
	ADC_RES=0;						//�Ĵ���ADC_RES��ADC_RESL����A/Dת�����
	ADC_RESL=0;						//��ʼ��ֵ0
	CLK_DIV=0x20;					//ADRJ=1��ADC_RES[1:0]��Ÿ�2λADC�����ADC_RESL[7:0]��ŵ�8λADC���	
	ADC_CONTR=0x8b;
}