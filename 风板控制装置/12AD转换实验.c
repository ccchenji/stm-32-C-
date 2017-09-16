#include "reg51.h"
#include "AD.h"
#include "interruption.h"
#include "print.h"
#include "stdio.h"
#include "oled.h"
#include <PWM_12.h>
void keypass();
sbit key1=P2^2;//选择键 
sbit key2=P2^3;//确定键
sbit key3=P2^4;//返回键
sbit key4=P2^5;//加数值
sbit key5=P2^6;//减数值
unsigned int i=0,j=0,k=0,d=0,g=0,h=0;
unsigned int xianshi[4];
unsigned int xianshi1[4];
float err=0,err_last=0,err_pre=0;
float PID_out=0;
int temp;
float angle_set=600;
float Kp=1.14;
float Kd=9.7;
float Ki =0.006;
float PIDI=0;
unsigned char f=0;
float PWM=0;
float max=0,min=0;
sbit IN1=P3^6;
sbit IN2=P3^7;
float ad,ad_out,sum;
float PID_control(float angle)
{
   err=angle_set-angle;
   PID_out=Kp*err+Kd*(err-err_last)+Ki*PIDI;
   temp = err-err_last;
   if(err<50&&err>-50) 
   {
     PIDI+=err;
   }
   err_last=err;
   if(PID_out>255)PID_out=255;
   if(PID_out<0)PID_out=0 ;
   return PID_out;
}
void main()
{
    InitADC();
	PWM_port();
	UsartInit();
	Timer0Init();
	h=(int)((angle_set-470)/2.9*10);
	xianshi[0]=h/100;
	xianshi[1]=h%100/10;
	xianshi[2]=-2;
	xianshi[3]=h%100%10;
   OLED_Init();
   OLED_Clear();
   OLED_ShowCHinese(18,3,0);
   OLED_ShowCHinese(36,3,1);
   OLED_ShowCHinese(54,3,2);
   OLED_ShowCHinese(72,3,3);
   delay_ms(500);
   	OLED_Clear();
    OLED_ShowCHinese(0,0,4);
    OLED_ShowCHinese(18,0,5);
	OLED_ShowCHinese(36,0,6);
	OLED_ShowCHinese(54,0,7);
	OLED_ShowCHinese(72,0,8);
	OLED_ShowChar(90,0,26,16);
	OLED_ShowCHinese(36,3,9); //观察角度阴码
	OLED_ShowCHinese(54,3,10);
	OLED_ShowCHinese(72,3,11);
	OLED_ShowCHinese(90,3,12);
	OLED_ShowChar(108,3,14,16);
	OLED_ShowCHinese(36,5,13);//设定角度阴码
	OLED_ShowCHinese(54,5,14);
	OLED_ShowCHinese(72,5,15);
	OLED_ShowCHinese(90,5,16);
	OLED_ShowChar(108,5,14,16);
	while(1)
   {
      
	   IN1=1;
	   IN2=0;
       keypass();
   }
}
void timer0() interrupt 1
{

    
    TH0=(65536-2300)/256;	//给定时器赋初值，定时1ms
	TL0=(65536-2300)%256;
   if(f<5)
	   {
	   ad=AD_get() ;
	   sum+=ad;
	   f++;
	   }
	   else
	   {
	   		f=0;
			ad_out=sum/5;
			PWM=PID_control(ad_out);
			sum=0;
			PWM_change(PWM);
	   }
}
void keypass()
{
   if(key1==0)
   {
     delay_ms(10);
	  if(key1==0)
	  {
	     while(!key1);
		 if(i==0)
		 {
		        OLED_ShowCHinese(0,0,4);
                OLED_ShowCHinese(18,0,5);
	            OLED_ShowCHinese(36,0,6);
	            OLED_ShowCHinese(54,0,7);
	            OLED_ShowCHinese(72,0,8);
	            OLED_ShowChar(90,0,26,16);
		    	OLED_ShowCHinese(36,3,17); //观察角度阳码
	            OLED_ShowCHinese(54,3,18);
	            OLED_ShowCHinese(72,3,19);
	            OLED_ShowCHinese(90,3,20);
	            OLED_ShowChar(108,3,14,16);
			    OLED_ShowCHinese(36,5,13);//设定角度阴码
	            OLED_ShowCHinese(54,5,14);
	            OLED_ShowCHinese(72,5,15);
	            OLED_ShowCHinese(90,5,16);
	            OLED_ShowChar(108,5,14,16);
		 }else
		 if(i==1)
		 {
                OLED_ShowCHinese(0,0,4);
                OLED_ShowCHinese(18,0,5);
            	OLED_ShowCHinese(36,0,6);
            	OLED_ShowCHinese(54,0,7);
            	OLED_ShowCHinese(72,0,8);
	            OLED_ShowChar(90,0,26,16);
		     	OLED_ShowCHinese(36,5,21);//设定角度阳码
	            OLED_ShowCHinese(54,5,22);
            	OLED_ShowCHinese(72,5,23);
            	OLED_ShowCHinese(90,5,24);
             	OLED_ShowChar(108,5,14,16);
				OLED_ShowCHinese(36,3,9); //观察角度阴码
            	OLED_ShowCHinese(54,3,10);
             	OLED_ShowCHinese(72,3,11);
            	OLED_ShowCHinese(90,3,12);
            	OLED_ShowChar(108,3,14,16);
		 }
		  i++;
		  if(i>1)i=0;
	   }
  }
    //模式1
  if(i==1&&key2==0)
  { 
      delay_ms(10);
	  if(key2==0)
	  {
	     while(!key2);
		 j++; 
		 OLED_Clear();
         while(j==1)
		 {
		    OLED_ShowCHinese(0,1,11);
           	OLED_ShowCHinese(18,1,12);  
	        OLED_ShowChar(36,1,26,16);
			g=(int)((AD_get()-470)/2.9*10);
//		    xianshi1[0]=g/100;
//			xianshi1[1]=g%100/10;
//			xianshi1[2]=g%100%10;
           xianshi1[0]=g/100;
			xianshi1[1]=g%100/10;
			xianshi1[2]=-2;
			xianshi1[3]=g%100%10;
			for(k=0;k<4;k++)
			{
			   OLED_ShowChar(54+k*16,1,xianshi1[k]+16,16);
			}
		    if(key3==0)
			 {
			   delay_ms(10);
			   if(key3==0)
			   {							  
			     while(!key3);
			     j=0;
				 OLED_Clear();
				OLED_ShowCHinese(0,0,4);
                OLED_ShowCHinese(18,0,5);
	            OLED_ShowCHinese(36,0,6);
	            OLED_ShowCHinese(54,0,7);
   	            OLED_ShowCHinese(72,0,8);
	            OLED_ShowChar(90,0,26,16);
		    	OLED_ShowCHinese(36,3,17); //观察角度阳码
	            OLED_ShowCHinese(54,3,18);
	            OLED_ShowCHinese(72,3,19);
	            OLED_ShowCHinese(90,3,20);
	            OLED_ShowChar(108,3,14,16);
			    OLED_ShowCHinese(36,5,13);//设定角度阴码
	            OLED_ShowCHinese(54,5,14);
	            OLED_ShowCHinese(72,5,15);
	            OLED_ShowCHinese(90,5,16);
	            OLED_ShowChar(108,5,14,16);
				 break; 
			   }
			 }
		  }
	   }
	}
	//模式二
	if(key2==0&&i==0)
	{
	   delay_ms(10);
	   if(key2==0)
	   {
	      while(!key2);
		  j++;
		 OLED_Clear();
         while(j==1)
		 {
		    OLED_ShowCHinese(0,1,11);
           	OLED_ShowCHinese(18,1,12);  
	        OLED_ShowChar(36,1,26,16);
			for(k=0;k<4;k++)
			{
			   OLED_ShowChar(54+k*16,1,xianshi[k]+16,16);
			}
		   if(key4==0)
		   {
		      delay_ms(10);
			  if(key4==0)
			  {
			    while(!key4);
				angle_set=angle_set+2.8;
				h=(int)((angle_set-470)/2.9*10);
				xianshi[0]=h/100;
				xianshi[1]=h%100/10;
				xianshi[2]=-2;
				xianshi[3]=h%100%10;
//				xianshi[2]=angle_set%100%10;
				    
			  }
		   }
		   if(key5==0)
		   {
		      delay_ms(10);
			  if(key5==0)
			  {
			     while(!key5);
				 angle_set=angle_set-2.8;
				h=(int)((angle_set-470)/2.9*10);
				xianshi[0]=h/100;
				xianshi[1]=h%100/10;
				xianshi[2]=-2;
				xianshi[3]=h%100%10;
//				xianshi[2]=angle_set%100%10;
			  }
			}
		    if(key3==0)
			 {
			   delay_ms(10);
			   if(key3==0)
			   {
			     j=0;
			     while(!key3);
			  	 OLED_Clear();
				OLED_ShowCHinese(0,0,4);
                OLED_ShowCHinese(18,0,5);
	            OLED_ShowCHinese(36,0,6);
	            OLED_ShowCHinese(54,0,7);
   	            OLED_ShowCHinese(72,0,8);
	            OLED_ShowChar(90,0,26,16);
		    	OLED_ShowCHinese(36,5,21);//设定角度阳码
	            OLED_ShowCHinese(54,5,22);
            	OLED_ShowCHinese(72,5,23);
            	OLED_ShowCHinese(90,5,24);
             	OLED_ShowChar(108,5,14,16);
				OLED_ShowCHinese(36,3,9); //观察角度阴码
            	OLED_ShowCHinese(54,3,10);
             	OLED_ShowCHinese(72,3,11);
            	OLED_ShowCHinese(90,3,12);
            	OLED_ShowChar(108,3,14,16);
				 break; 
			   }
			 }

		 }
	    }
     }
}



  