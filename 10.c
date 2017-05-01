/***********************************************************
STC90C51RD+��HC-06�������ߣ�
	����  STC90C51RD+
	RXD    TXD
	TXD    RXD
�������ߣ�
	P2.0��P2.1��P2.3�ֱ��һ��ָʾ��

��������
��������ע�⣺����Ƭ��TXD��P3.1��������������������P3.1�˽��������衣���β�����Ҫ����������
��������

�ֻ�������������ͨ������
����Ѹ���Android�Ա�����ͨ�����
					By itas109
					http://blog.csdn.net/itas109
***********************************************************/
#include <reg52.h>
#include <intrins.h>
unsigned char tmp;
unsigned int c=0;

sbit led1=P2^0;		    //ָʾ��0
sbit led2=P2^1;			//ָʾ��1
sbit led3=P2^3;			//ָʾ��3

void init();   //���ڳ�ʼ��
void send(unsigned char a);	//���ֽڷ��ͺ���
void ctrl(); //���մ�����

void main()
{
		init();
          while(1)
          {         
                  if(RI==1)                     // �Ƿ������ݵ���
                  {
                   RI = 0;
									tmp=0;
                  tmp = SBUF;                   // �ݴ���յ�������
				  ctrl();
				  }       
          }
}

 void init()	//���ڳ�ʼ��
 {
 		  ES=0;								  //���ж�
		  SCON = 0x50;                        // REN=1�����н���״̬�����ڹ���ģʽ1,
											  //10λUART��1λ��ʼλ��8λ����λ��1λֹͣλ������żУ�飩�������ʿɱ�

		  TMOD = 0x20;                        // ��ʱ��1�����ڷ�ʽ2��8λ�Զ�����ģʽ, ���ڲ���������
          TH1=TL1=0xFD;                       // ������9600 �����β��Բ��þ���Ϊ11.0592��
          
          PCON &= 0x7f;                       // �����ʲ�����
          TR1 = 1;							  //��ʱ��1��ʼ����������������
											  //���ͱ�־λ��0
		  TI=0;								  //���ձ�־λ��0
		  RI=0;
		  
		  //EA=0;
	      ES=1;


          led1=0;	                           //��ʼ������3��ָʾ��ȫ��
		  led2=0;
		  led3=0;
 }
   
void send(unsigned char a)	//���ֽ����ݷ���
{							//ע�⣺����Ƭ��TXD��P3.1��������������������P3.1�˽��������衣���β�����Ҫ����������
	TI=0;	
	SBUF=a;
	while(TI==0);
	TI=0;

	if(c%2)					//����ָʾ�Ʊ�־��ÿ����һ�Σ��˵�������
	 led3=1;
	else
	 led3=0;
	c++;
} 

void ctrl()		            //���մ�����
{
  				  switch(tmp)
				  {
							case 0x01:
						led1=0;		       	    
						led2=1;
						led3=1;
						send(tmp);
						break;					
					case 0x02:					
						 led1=1;		       	   
						led2=0;
						led3=1; 
						 send(tmp);
						 break;
					case 0x03:				   
						 led1=1;		       	   
						led2=1;
						led3=0;
						 send(tmp);
						 break;
					case 0x04:					
						 led1=0;		       	    
						led2=0;
						led3=0;
						  send(tmp);
						  break;
					default:                  
						  led1=1;
						  led2=1;
						  led3=1;
						  send(tmp);
				  }
}