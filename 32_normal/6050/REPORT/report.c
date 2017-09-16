#include <report.h>
#include "delay.h"
#include "sys.h"
#include "usart.h"

//����1����1���ַ� 
//c:Ҫ���͵��ַ�
void usart1_send_char(u8 c)
{   	
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET); //ѭ������,ֱ���������   
	USART_SendData(USART1,c);  
} 
//�������ݸ�����������λ�����(V2.6�汾)
//fun:������. 0XA0~0XAF
//data:���ݻ�����,���28�ֽ�!!
//len:data����Ч���ݸ���
void usart1_niming_report(u8 fun,u8*data,u8 len)
{
	u8 send_buf[32];
	u8 i;
	if(len>28)return;	//���28�ֽ����� 
	send_buf[len+3]=0;	//У��������
	send_buf[0]=0X88;	//֡ͷ
	send_buf[1]=fun;	//������
	send_buf[2]=len;	//���ݳ���
	for(i=0;i<len;i++)send_buf[3+i]=data[i];			//��������
	for(i=0;i<len+3;i++)send_buf[len+3]+=send_buf[i];	//����У���	
	for(i=0;i<len+4;i++)usart1_send_char(send_buf[i]);	//�������ݵ�����1 
}
//���ͼ��ٶȴ��������ݺ�����������
//aacx,aacy,aacz:x,y,z������������ļ��ٶ�ֵ
//gyrox,gyroy,gyroz:x,y,z�������������������ֵ



//      ��Ҫ�Ķ�����������
void I_send_data(short lvboqian,short lvbohou,short My_Angle)
{
	u8 tbuf[6]; 
	tbuf[0]=(lvboqian>>8)&0XFF;
	tbuf[1]=lvboqian&0XFF;
	tbuf[2]=(lvbohou>>8)&0XFF;
	tbuf[3]=lvbohou&0XFF;
	tbuf[4]=(My_Angle>>8)&0XFF;
	tbuf[5]=My_Angle&0XFF;
	usart1_niming_report(0XA1,tbuf,6);//�Զ���֡,0XA1
}	
