#include <report.h>
#include "delay.h"
#include "sys.h"
#include "usart.h"

//串口1发送1个字符 
//c:要发送的字符
void usart1_send_char(u8 c)
{   	
	while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET); //循环发送,直到发送完毕   
	USART_SendData(USART1,c);  
} 
//传送数据给匿名四轴上位机软件(V2.6版本)
//fun:功能字. 0XA0~0XAF
//data:数据缓存区,最多28字节!!
//len:data区有效数据个数
void usart1_niming_report(u8 fun,u8*data,u8 len)
{
	u8 send_buf[32];
	u8 i;
	if(len>28)return;	//最多28字节数据 
	send_buf[len+3]=0;	//校验数置零
	send_buf[0]=0X88;	//帧头
	send_buf[1]=fun;	//功能字
	send_buf[2]=len;	//数据长度
	for(i=0;i<len;i++)send_buf[3+i]=data[i];			//复制数据
	for(i=0;i<len+3;i++)send_buf[len+3]+=send_buf[i];	//计算校验和	
	for(i=0;i<len+4;i++)usart1_send_char(send_buf[i]);	//发送数据到串口1 
}
//发送加速度传感器数据和陀螺仪数据
//aacx,aacy,aacz:x,y,z三个方向上面的加速度值
//gyrox,gyroy,gyroz:x,y,z三个方向上面的陀螺仪值



//      需要改动数据在这里
void I_send_data(short lvboqian,short lvbohou,short My_Angle)
{
	u8 tbuf[6]; 
	tbuf[0]=(lvboqian>>8)&0XFF;
	tbuf[1]=lvboqian&0XFF;
	tbuf[2]=(lvbohou>>8)&0XFF;
	tbuf[3]=lvbohou&0XFF;
	tbuf[4]=(My_Angle>>8)&0XFF;
	tbuf[5]=My_Angle&0XFF;
	usart1_niming_report(0XA1,tbuf,6);//自定义帧,0XA1
}	
