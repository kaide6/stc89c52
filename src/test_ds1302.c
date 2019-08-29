/**************************************************************************************
*		              DS1302ʱ��ʵ��												  *
ʵ���������س�����������ʾʱ������
ע�����
***************************************************************************************/

#include "reg52.h"			 //���ļ��ж����˵�Ƭ����һЩ���⹦�ܼĴ���
#include"ds1302.h"

typedef unsigned int u16;	  //���������ͽ�����������
typedef unsigned char u8;

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;


char num=0;
u8 DisplayData[8];
u8 code ds_smgduan[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};

/*******************************************************************************
* �� �� ��         : delay
* ��������		   : ��ʱ������i=1ʱ����Լ��ʱ10us
*******************************************************************************/
void delay(u16 i);

/*******************************************************************************
* �� �� ��         : datapros()
* ��������		   : ʱ���ȡ����ת������
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/

void datapros()
{
   	Ds1302ReadTime();
	DisplayData[0] = ds_smgduan[TIME[2]/16];				//ʱ
	DisplayData[1] = ds_smgduan[TIME[2]&0x0f];
	DisplayData[2] = 0x40;
	DisplayData[3] = ds_smgduan[TIME[1]/16];				//��
	DisplayData[4] = ds_smgduan[TIME[1]&0x0f];
	DisplayData[5] = 0x40;
	DisplayData[6] = ds_smgduan[TIME[0]/16];				//��
	DisplayData[7] = ds_smgduan[TIME[0]&0x0f];
}


void calendar()
{
   	Ds1302ReadTime();
	DisplayData[0] = ds_smgduan[TIME[6]/16];				//��
	DisplayData[1] = ds_smgduan[TIME[6]&0x0f];
	DisplayData[2] = 0x40;
	DisplayData[3] = ds_smgduan[TIME[4]/16];				//��
	DisplayData[4] = ds_smgduan[TIME[4]&0x0f];
	DisplayData[5] = 0x40;
	DisplayData[6] = ds_smgduan[TIME[3]/16];				//��
	DisplayData[7] = ds_smgduan[TIME[3]&0x0f];
}


/*******************************************************************************
* ������         :DigDisplay()
* ��������		 :�������ʾ����
* ����           : ��
* ���         	 : ��
*******************************************************************************/
void DigDisplay()
{
	u8 i;
	for(i=0;i<8;i++)
	{
		switch(i)	 //λѡ��ѡ�����������ܣ�
		{
			case(0):
				LSA=0;LSB=0;LSC=0; break;//��ʾ��0λ
			case(1):
				LSA=1;LSB=0;LSC=0; break;//��ʾ��1λ
			case(2):
				LSA=0;LSB=1;LSC=0; break;//��ʾ��2λ
			case(3):
				LSA=1;LSB=1;LSC=0; break;//��ʾ��3λ
			case(4):
				LSA=0;LSB=0;LSC=1; break;//��ʾ��4λ
			case(5):
				LSA=1;LSB=0;LSC=1; break;//��ʾ��5λ
			case(6):
				LSA=0;LSB=1;LSC=1; break;//��ʾ��6λ
			case(7):
				LSA=1;LSB=1;LSC=1; break;//��ʾ��7λ
		}
		P0=DisplayData[7-i];//��������
		delay(100); //���һ��ʱ��ɨ��
		P0=0x00;//����
	}
}

/*******************************************************************************
* �� �� ��       : main
* ��������		 : ������
* ��    ��       : ��
* ��    ��    	 : ��
*******************************************************************************/
void test_ds1302_main()
{
	Ds1302Init();
	while(1)
	{
		datapros();	 //���ݴ�������
		DigDisplay();//�������ʾ����
	}
}

void test_ds1302_calendar()
{
	Ds1302Init();
	while(1)
	{
		calendar();	 //���ݴ�������
		DigDisplay();//�������ʾ����
	}
}
