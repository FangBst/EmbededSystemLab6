void delay() 		//��ʱ4us
{
	;;
}

void start()	 	//���������ź�
{
 	SDA=1;
	delay();
	SCL=1;
	delay();
	SDA=0;
	delay(); 	
}
void stop()		 	//ֹͣ�ź�
{
 	SDA=0;
	delay();
	SCL=1;
	delay();
	SDA=1;
	delay();
}

void ack(){
	SDA=0;
	delay();
	SCL=1;
	delay();
	SCL=0;
}

void noack(){
	SDA=1;
	delay();
	SCL=1;
	delay();
	SCL=0;
}

void respons()	 	//�ӻ�Ӧ���ź�
{
	uchar i=0;
	SCL=1;
	delay();
	while(SDA==1&&(i<255)){  //��ʾ����һ��ʱ����û���յ���������Ӧ����
		i++;}				//������Ĭ�ϴ��ڼ��Ѿ��յ����ݶ����ٵȴ�Ӧ���źš� 
	SCL=0;
	delay();
}
void writebyte(uchar date) //��24C16дһ���ֽ�����
{
	uchar i,temp;
	temp=date;
	for(i=0;i<8;i++)
	{
		temp=temp<<1;
		SCL=0;
		delay();
		SDA=CY;
		delay();
		SCL=1;
		delay();
	}
	SCL=0;
	delay();
	SDA=1;
	delay();	
}

uchar readbyte()  			//��24C16��һ���ֽ�����
{
	uchar i,k;
	SCL=0;
	delay();
	SDA=1;
	delay();
	for(i=0;i<8;i++)
	{
		SCL=1;
		delay();
		k=(k<<1)|SDA;
		delay();
		SCL=0;
		delay();
	}
	delay();
	return k;	
}
void write_add(uchar addr,uchar date)
{
	start();
	writebyte(0xa0);							
	respons();
	writebyte(addr);
	respons();
	writebyte(date);
	respons();
	stop();							
}

uchar read_add(uchar addr) //��24C16��addr��ַ����һ���ֽ�����
{
	uchar date;
	start();
	writebyte(0xa0);
	respons();
	writebyte(addr);
	respons();	
	start();
	writebyte(0xa1);
	respons();
	date=readbyte();
	//response();
	stop();
	return date;
}

void read_adds(uchar addr,uchar *date,uchar num)
{
	uchar i;
	uchar *p;
	p=date;
	start();
	writebyte(0xa0);
	respons();
	writebyte(addr);
	respons();	
	start();
	writebyte(0xa1);
	respons();
	for (i=0;i<num;i++){
		*p=readbyte();
		if(i==num-1)  noack();
		else 	ack();
		p++;
	}
	stop();
}

void write_adds(uchar addr,uchar *date,uchar num)
{
	start();
	writebyte(0xa0);							
	respons();
	writebyte(addr);
	respons();
	for(;num>0;num--){
		writebyte(*date);
		respons();
		date++;	
	}
	stop();							
}
