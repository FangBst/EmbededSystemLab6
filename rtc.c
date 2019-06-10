void DS1302WriteByte(uchar dat)
{
	uchar i;
  RTC_sclk=0;//��ʼʱ������0
	for(i=0;i<8;i++)//��ʼ����8λ����
	{
		RTC_io=dat&0x01;//ȡ���λ
		
		RTC_sclk=1;//ʱ�������ߣ����������أ����ݱ����� 
		
		RTC_sclk=0;//ʱ�������ͣ�Ϊ��һ����������׼��
		dat>>=1;//��������һλ��׼��������һλ����
	}
}

////DS1302��һ���ֽڵ�����
uchar DS1302ReadByte()
{
	uchar i,dat;
	
	for(i=0;i<8;i++)
	{
		dat>>=1;//Ҫ���ص���������һλ
		if(RTC_io==1)//��������Ϊ��ʱ��֤����λ����Ϊ1
		dat|=0x80;
		RTC_sclk=1;
		
		RTC_sclk=0;//�����½���
		
	}
	return dat;//���ض�ȡ��������
}

//����Ӧ��ַ��дһ���ֽڵ�����
uchar DS1302Read(uchar cmd)
{
	uchar dat;
	RTC_rst=0;//��ʼCE��0
	RTC_sclk=0;//��ʼʱ����0
	RTC_rst=1;//��ʼCE��1�����俪ʼ
	DS1302WriteByte(cmd);//���������֣�
	dat=DS1302ReadByte();//��ȡ�õ���ʱ��
	RTC_sclk=1;//ʱ��������
	RTC_rst=0;//��ȡ������CE��0���������ݴ���
	return dat;//���صõ���ʱ������
}

//����Ӧ��ַ��д����
void DS1302Write(uchar cmd,uchar dat)
{
	RTC_rst=0;//��ʼCE��0
	RTC_sclk=0;//��ʼʱ����0
	RTC_rst=1;//��1�����俪ʼ
	DS1302WriteByte(cmd);//���������֣�Ҫд���ʱ��ĵ�ַ
	DS1302WriteByte(dat);//д���޸ĵ�ʱ��
	RTC_sclk=1;//ʱ��������
	RTC_rst=0;//��ȡ������CE=0���������ݵĴ���
}
//DS1302��ʱ��ֵ��ȡ����
void GetDA1302()
{
	uchar realvalue;
	realvalue=DS1302Read(DS1302_second_read);
	time.second=((realvalue&0x70)>>4)*10+(realvalue&0x0f);
		realvalue=DS1302Read(DS1302_minutes_read);
	time.minute=((realvalue&0x70)>>4)*10+(realvalue&0x0f);
		realvalue=DS1302Read(DS1302_hour_read );
	time.hour=((realvalue&0x70)>>4)*10+(realvalue&0x0f);
		realvalue=DS1302Read(DS1302_date_read );
	time.day=((realvalue&0x70)>>4)*10+(realvalue&0x0f);
		realvalue=DS1302Read(DS1302_week_read);
	time.week=((realvalue&0x70)>>4)*10+(realvalue&0x0f);
		realvalue=DS1302Read(DS1302_month_read);
	time.month=((realvalue&0x70)>>4)*10+(realvalue&0x0f);
			realvalue=DS1302Read(DS1302_year_read);
	time.year=((realvalue&0x70)>>4)*10+(realvalue&0x0f);
}