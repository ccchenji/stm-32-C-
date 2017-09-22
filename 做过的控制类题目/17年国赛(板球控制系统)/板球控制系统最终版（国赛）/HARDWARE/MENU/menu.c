#include "menu.h"
#include "KEY.H"
#include "stmflash.h"
short flag_first=0;
short flag_ensure=0;
short flag_second=0;
float Kp_add=0.1;
float Kd_add=1;
float Ki_add=0.001;
extern char flag;
extern short fps;
extern short receive_date[2];
extern char flag_mode;
extern short MODEII_timer;
extern short MODEIII_flag;
extern short MODEVI_flag;
extern short MODEV_flag;
extern short MODEIV_flag;
extern short MODEVII_flag;
extern int timer;
extern short My_timer;

//位置设定
extern char  A_flag;
extern char  B_flag;
extern char  C_flag;
extern char  D_flag;

extern short Real_area;
extern short area_save;
	
//菜单调试
extern float PID_P_X;
extern float PID_I_X;
extern float PID_D_X;

extern float PID_P_Y;
extern float PID_I_Y;
extern float PID_D_Y;

//与FLASH相关的参数

extern u16  x_smoth;
extern u16  y_smoth;
extern short SET_DATE[13][2];
extern unsigned short num[28];
char cl=0;
char cy=0;
char cx=0;
char FL_flag=0;
void Menu_Init()
{
	 if(flag_ensure==0)
	 {
	   First_Page();
		 Key_choice();
		 if(KEY_Scan()==4)
		 {
			  flag_ensure=1;
			  OLED_Clear();
		 }
	 }
	 if(flag_ensure==1)
	 {
		  Second_Page();
		 	Key_choice();
		  if(KEY_Scan()==4)
			{
				flag_ensure=0;
				flag_second=0;
				flag_mode=0;
				timer=0;
				My_timer=0;
			  FL_flag=0;
			  OLED_Clear();
			}
	 }
}
//第一级的菜单
void First_Page()
{
	switch(flag_first)
	{
		case 0:
			     OLED_ShowString2(0,0,"1.PID_X");
		       OLED_ShowString(0,1,"2.PID_Y"); 
		       OLED_ShowString(0,2,"3.PID_INCREMENT");
		       OLED_ShowString(0,3,"4.X_Y");
		       OLED_ShowString(0,4,"5.MODE_CHOICE");
		       OLED_ShowString(0,5,"6.PLACE_SET");
		       OLED_ShowString(0,6,"7.FLASH");
		       break;
	  case 1:
			     OLED_ShowString(0,0,"1.PID_X");
		       OLED_ShowString2(0,1,"2.PID_Y"); 
		       OLED_ShowString(0,2,"3.PID_INCREMENT");
		       OLED_ShowString(0,3,"4.X_Y");
		       OLED_ShowString(0,4,"5.MODE_CHOICE");
		       OLED_ShowString(0,5,"6.PLACE_SET");
		       OLED_ShowString(0,6,"7.FLASH");
		       break;
		case 2:
			     OLED_ShowString(0,0,"1.PID_X");
		       OLED_ShowString(0,1,"2.PID_Y"); 
		       OLED_ShowString2(0,2,"3.PID_INCREMENT");
		       OLED_ShowString(0,3,"4.X_Y");
		       OLED_ShowString(0,4,"5.MODE_CHOICE");
		       OLED_ShowString(0,5,"6.PLACE_SET");
		       OLED_ShowString(0,6,"7.FLASH");
		       break;
		case 3:
			     OLED_ShowString(0,0,"1.PID_X");
		       OLED_ShowString(0,1,"2.PID_Y"); 
		       OLED_ShowString(0,2,"3.PID_INCREMENT");
		       OLED_ShowString2(0,3,"4.X_Y");
		       OLED_ShowString(0,4,"5.MODE_CHOICE");
		       OLED_ShowString(0,5,"6.PLACE_SET");
           OLED_ShowString(0,6,"7.FLASH");
		       break;
		case 4:
			     OLED_ShowString(0,0,"1.PID_X");
		       OLED_ShowString(0,1,"2.PID_Y"); 
		       OLED_ShowString(0,2,"3.PID_INCREMENT");
		       OLED_ShowString(0,3,"4.X_Y");
		       OLED_ShowString2(0,4,"5.MODE_CHOICE");
		       OLED_ShowString(0,5,"6.PLACE_SET");
		       OLED_ShowString(0,6,"7.FLASH");
		       break;
		case 5:
			     OLED_ShowString(0,0,"1.PID_X");
		       OLED_ShowString(0,1,"2.PID_Y"); 
		       OLED_ShowString(0,2,"3.PID_INCREMENT");
		       OLED_ShowString(0,3,"4.X_Y");
		       OLED_ShowString(0,4,"5.MODE_CHOICE");
		       OLED_ShowString2(0,5,"6.PLACE_SET");
		       OLED_ShowString(0,6,"7.FLASH");
		       break;
		case 6:
			     OLED_ShowString(0,0,"1.PID_X");
		       OLED_ShowString(0,1,"2.PID_Y"); 
		       OLED_ShowString(0,2,"3.PID_INCREMENT");
		       OLED_ShowString(0,3,"4.X_Y");
		       OLED_ShowString(0,4,"5.MODE_CHOICE");
		       OLED_ShowString(0,5,"6.PLACE_SET");
		       OLED_ShowString2(0,6,"7.FLASH");
		       break;
	  case 7:
			     OLED_ShowString(0,0,"2.PID_Y"); 
		       OLED_ShowString(0,1,"3.PID_INCREMENT");
		       OLED_ShowString(0,2,"4.X_Y");
		       OLED_ShowString(0,3,"5.MODE_CHOICE");
		       OLED_ShowString(0,4,"6.PLACE_SET");
		       OLED_ShowString(0,5,"7.FLASH");
		       OLED_ShowString2(0,6,"8.FLASH_WRITE");
		       break;
	}
}

//第二级菜单
void Second_Page()
{
	   if (flag_first==0)
			    {
						switch(flag_second)
						{
							case 0:
			 		       OLED_ShowString2(0,0,"Kp_X:");
					       OLED_ShowNum_float(18,1,PID_P_X);
				         OLED_ShowString(0,2,"Ki_X:");
				         OLED_ShowNum_float(18,3,PID_I_X);
				         OLED_ShowString(0,4,"Kd_X:");
							   OLED_ShowNum_float(18,5,PID_D_X);	
							   break;
							case 1:
			 		       OLED_ShowString(0,0,"Kp_X:");
					       OLED_ShowNum_float(18,1,PID_P_X);
				         OLED_ShowString2(0,2,"Ki_X:");
				         OLED_ShowNum_float(18,3,PID_I_X);
				         OLED_ShowString(0,4,"Kd_X:");
							   OLED_ShowNum_float(18,5,PID_D_X);	
							   break;
							case 2:
			 		       OLED_ShowString(0,0,"Kp_X:");
					       OLED_ShowNum_float(18,1,PID_P_X);
				         OLED_ShowString(0,2,"Ki_X:");
				         OLED_ShowNum_float(18,3,PID_I_X);
				         OLED_ShowString2(0,4,"Kd_X:");
							   OLED_ShowNum_float(18,5,PID_D_X);	
							   break;
							
						}							
			    }
			if(flag_first==1)
			    {
				      switch(flag_second)
							{
								case 0:
                   OLED_ShowString2(0,0,"Kp_Y:");
					         OLED_ShowNum_float(18,1,PID_P_Y);
				           OLED_ShowString(0,2,"Ki_Y:");
				           OLED_ShowNum_float(18,3,PID_I_Y);
				           OLED_ShowString(0,4,"Kd_Y:");
				           OLED_ShowNum_float(18,5,PID_D_Y);	
								   break;
                case 1:
                   OLED_ShowString(0,0,"Kp_Y:");
					         OLED_ShowNum_float(18,1,PID_P_Y);
				           OLED_ShowString2(0,2,"Ki_Y:");
				           OLED_ShowNum_float(18,3,PID_I_Y);
				           OLED_ShowString(0,4,"Kd_Y:");
				           OLED_ShowNum_float(18,5,PID_D_Y);		
                   break;	
                case 2:
                   OLED_ShowString(0,0,"Kp_Y:");
					         OLED_ShowNum_float(18,1,PID_P_Y);
				           OLED_ShowString(0,2,"Ki_Y:");
				           OLED_ShowNum_float(18,3,PID_I_Y);
				           OLED_ShowString2(0,4,"Kd_Y:");
				           OLED_ShowNum_float(18,5,PID_D_Y);		 									
							}
			    }
			if(flag_first==2)
			    {
				       switch(flag_second)
							 {
								 case 0:
								   OLED_ShowString2(0,0,"Kp_add:");
								   OLED_ShowNum_float(18,1,Kp_add);
                   OLED_ShowString(0,2,"Kd_add:");
				           OLED_ShowNum_float(18,3,Kd_add);
				           OLED_ShowString(0,4,"Ki_add:");
				           OLED_ShowNum_float(18,5,Ki_add);	
								   break;
								 case 1:
                   OLED_ShowString(0,0,"Kp_add:");
								   OLED_ShowNum_float(18,1,Kp_add);
                   OLED_ShowString2(0,2,"Kd_add:");
				           OLED_ShowNum_float(18,3,Kd_add);
				           OLED_ShowString(0,4,"Ki_add:");
				           OLED_ShowNum_float(18,5,Ki_add);	 
								   break;
								 case 2:
                   OLED_ShowString(0,0,"Kp_add:");
								   OLED_ShowNum_float(18,1,Kp_add);
                   OLED_ShowString(0,2,"Kd_add:");
				           OLED_ShowNum_float(18,3,Kd_add);
				           OLED_ShowString2(0,4,"Ki_add:");
				           OLED_ShowNum_float(18,5,Ki_add);	
                   break; 								 
							 }
			    }
				if(flag_first==3)
				{
					 OLED_ShowString(0,0,"X:");
					 OLED_ShowNum(20,0,receive_date[0],3,12);
					 OLED_ShowString(0,3,"Y:");
					 OLED_ShowNum(20,3,receive_date[1],3,12);	 
				}
				if(flag_first==4)
				{
					  if(flag_mode==0)
						{
					 	 switch(flag_second)
							 {
								 case 0:
								   OLED_ShowString2(0,0,"MODEI");
                   OLED_ShowString(0,1,"MODEII");
				           OLED_ShowString(0,2,"MODEIII");
								   OLED_ShowString(0,3,"MODEIV");
								   OLED_ShowString(0,4,"MODEV");
								   OLED_ShowString(0,5,"MODEVI");
								   OLED_ShowString(0,6,"MODEVII");
								   break;
								 case 1:
								   OLED_ShowString(0,0,"MODEI");
                   OLED_ShowString2(0,1,"MODEII");
				           OLED_ShowString(0,2,"MODEIII");
								   OLED_ShowString(0,3,"MODEIV");
								   OLED_ShowString(0,4,"MODEV");
								 	 OLED_ShowString(0,5,"MODEVI");
								   OLED_ShowString(0,6,"MODEVII");
								   break;
								 case 2:
								   OLED_ShowString(0,0,"MODEI");
                   OLED_ShowString(0,1,"MODEII");
				           OLED_ShowString2(0,2,"MODEIII");
								   OLED_ShowString(0,3,"MODEIV");
								   OLED_ShowString(0,4,"MODEV");
								 	 OLED_ShowString(0,5,"MODEVI");
								   OLED_ShowString(0,6,"MODEVII");
                   break;
 								 case 3:
									 OLED_ShowString(0,0,"MODEI");
                   OLED_ShowString(0,1,"MODEII");
				           OLED_ShowString(0,2,"MODEIII");
								   OLED_ShowString2(0,3,"MODEIV");
								   OLED_ShowString(0,4,"MODEV");
								 	 OLED_ShowString(0,5,"MODEVI");
								   OLED_ShowString(0,6,"MODEVII");
								   break;
								 case 4:
									 OLED_ShowString(0,0,"MODEI");
                   OLED_ShowString(0,1,"MODEII");
				           OLED_ShowString(0,2,"MODEIII");
								   OLED_ShowString(0,3,"MODEIV");
								   OLED_ShowString2(0,4,"MODEV");
								 	 OLED_ShowString(0,5,"MODEVI");
								   OLED_ShowString(0,6,"MODEVII");
								   break;
								 case 5:
									 OLED_ShowString(0,0,"MODEI");
                   OLED_ShowString(0,1,"MODEII");
				           OLED_ShowString(0,2,"MODEIII");
								   OLED_ShowString(0,3,"MODEIV");
								   OLED_ShowString(0,4,"MODEV");
								 	 OLED_ShowString2(0,5,"MODEVI");
								   OLED_ShowString(0,6,"MODEVII");
								   break;
								 case 6:
									 OLED_ShowString(0,0,"MODEI");
                   OLED_ShowString(0,1,"MODEII");
				           OLED_ShowString(0,2,"MODEIII");
								   OLED_ShowString(0,3,"MODEIV");
								   OLED_ShowString(0,4,"MODEV");
								 	 OLED_ShowString(0,5,"MODEVI");
								   OLED_ShowString2(0,6,"MODEVII");
								   break;
							 }
						 }
						else
						{
							 	OLED_ShowString(10,2,"TIME:");
		            OLED_ShowNum_float(50,3,((float)timer)/100);
							 switch(flag_mode)
							 {
								 case 1:
									   OLED_ShowString(0,0,"MODEI_RUNING....");
								     break;
								 case 2:
									   OLED_ShowString(0,0,"MODEII_RUNING...");
								     break;
								 case 3:
									   OLED_ShowString(0,0,"MODEIII_RUNING...");
								     break;
								 case 4:
									   OLED_ShowString(0,0,"MODEIV_RUNING...");
								     break;
								 case 5:
									   OLED_ShowString(0,0,"MODEV_RUNING...");
								     break;
								 case 6:
									   OLED_ShowString(0,0,"MODEVI_RUNING...");
								     break;
								 case 7:
									   OLED_ShowString(0,0,"MODEVII_RUNING...");
								     break;
							 }
						}
				}
				if(flag_first==5)
				{
					  switch (flag_second)
						{
							case 0:
								 OLED_ShowString2(0,0,"A:");
							   OLED_ShowNum(14,0,A_flag,2,12);
							   OLED_ShowString(0,2,"B:");
							   OLED_ShowNum(14,2,B_flag,2,12);
							   OLED_ShowString(0,4,"C:");
							   OLED_ShowNum(14,4,C_flag,2,12);
							   OLED_ShowString(0,6,"D:");
							   OLED_ShowNum(14,6,D_flag,2,12);
							   break;
							case 1:
								 OLED_ShowString(0,0,"A:");
							   OLED_ShowNum(14,0,A_flag,2,12);
							   OLED_ShowString2(0,2,"B:");
						   	 OLED_ShowNum(14,2,B_flag,2,12);
							   OLED_ShowString(0,4,"C:");
							   OLED_ShowNum(14,4,C_flag,2,12);
							   OLED_ShowString(0,6,"D:");
							   OLED_ShowNum(14,6,D_flag,2,12);
							   break;
							case  2:
								 OLED_ShowString(0,0,"A:");
							   OLED_ShowNum(14,0,A_flag,2,12);
							   OLED_ShowString(0,2,"B:");
							   OLED_ShowNum(14,2,B_flag,2,12);
							   OLED_ShowString2(0,4,"C:");
							   OLED_ShowNum(14,4,C_flag,2,12);
							   OLED_ShowString(0,6,"D:");
							   OLED_ShowNum(14,6,D_flag,2,12);
							   break;
							case 3:
								 OLED_ShowString(0,0,"A:");
							   OLED_ShowNum(14,0,A_flag,2,12);
							   OLED_ShowString(0,2,"B:");
							   OLED_ShowNum(14,2,B_flag,2,12);
							   OLED_ShowString(0,4,"C:");
							   OLED_ShowNum(14,4,C_flag,2,12);
							   OLED_ShowString2(0,6,"D:");
							   OLED_ShowNum(14,6,D_flag,2,12);
							   break;
						}
							
				}
				if(flag_first==6)
				{
					
					  switch (flag_second)
						{
							case 0:
								   OLED_ShowString2(0,0,"X_SMOTH:");
							     OLED_ShowNum(90,0,x_smoth,4,12);
							     OLED_ShowString(0,1,"Y_SMOTH:");
							     OLED_ShowNum(90,1,y_smoth,4,12);
							     OLED_ShowString(0,2,"X1:");
							     OLED_ShowNum(90,2,SET_DATE[0][0],3,12);
							     OLED_ShowString(0,3,"Y1:");
							     OLED_ShowNum(90,3,SET_DATE[0][1],3,12);
							     OLED_ShowString(0,4,"X2:");
							     OLED_ShowNum(90,4,SET_DATE[1][0],3,12);
							     OLED_ShowString(0,5,"Y2:");
							     OLED_ShowNum(90,5,SET_DATE[1][1],3,12);
							     OLED_ShowString(0,6,"X3:");
							     OLED_ShowNum(90,6,SET_DATE[2][0],3,12);
							     break;
							case 1:
								   OLED_ShowString(0,0,"X_SMOTH:");
							     OLED_ShowNum(90,0,x_smoth,4,12);
							     OLED_ShowString2(0,1,"Y_SMOTH:");
							     OLED_ShowNum(90,1,y_smoth,4,12);
							     OLED_ShowString(0,2,"X1:");
							     OLED_ShowNum(90,2,SET_DATE[0][0],3,12);
							     OLED_ShowString(0,3,"Y1:");
							     OLED_ShowNum(90,3,SET_DATE[0][1],3,12);
							     OLED_ShowString(0,4,"X2:");
							     OLED_ShowNum(90,4,SET_DATE[1][0],3,12);
							     OLED_ShowString(0,5,"Y2:");
							     OLED_ShowNum(90,5,SET_DATE[1][1],3,12);
							     OLED_ShowString(0,6,"X3:");
							     OLED_ShowNum(90,6,SET_DATE[2][0],3,12);
							     break;
							case 2:
								   OLED_ShowString(0,0,"X_SMOTH:");
							     OLED_ShowNum(90,0,x_smoth,4,12);
							     OLED_ShowString(0,1,"Y_SMOTH:");
							     OLED_ShowNum(90,1,y_smoth,4,12);
							     OLED_ShowString2(0,2,"X1:");
							     OLED_ShowNum(90,2,SET_DATE[0][0],3,12);
							     OLED_ShowString(0,3,"Y1:");
							     OLED_ShowNum(90,3,SET_DATE[0][1],3,12);
							     OLED_ShowString(0,4,"X2:");
							     OLED_ShowNum(90,4,SET_DATE[1][0],3,12);
							     OLED_ShowString(0,5,"Y2:");
							     OLED_ShowNum(90,5,SET_DATE[1][1],3,12);
							     OLED_ShowString(0,6,"X3:");
							     OLED_ShowNum(90,6,SET_DATE[2][0],3,12);
							     break;
							case 3:
                   OLED_ShowString(0,0,"X_SMOTH:");
							     OLED_ShowNum(90,0,x_smoth,4,12);
							     OLED_ShowString(0,1,"Y_SMOTH:");
							     OLED_ShowNum(90,1,y_smoth,4,12);
							     OLED_ShowString(0,2,"X1:");
							     OLED_ShowNum(90,2,SET_DATE[0][0],3,12);
							     OLED_ShowString2(0,3,"Y1:");
							     OLED_ShowNum(90,3,SET_DATE[0][1],3,12);
							     OLED_ShowString(0,4,"X2:");
							     OLED_ShowNum(90,4,SET_DATE[1][0],3,12);
							     OLED_ShowString(0,5,"Y2:");
							     OLED_ShowNum(90,5,SET_DATE[1][1],3,12);
							     OLED_ShowString(0,6,"X3:");
							     OLED_ShowNum(90,6,SET_DATE[2][0],3,12);
							     break;	
							case 4:
                   OLED_ShowString(0,0,"X_SMOTH:");
							     OLED_ShowNum(90,0,x_smoth,4,12);
							     OLED_ShowString(0,1,"Y_SMOTH:");
							     OLED_ShowNum(90,1,y_smoth,4,12);
							     OLED_ShowString(0,2,"X1:");
							     OLED_ShowNum(90,2,SET_DATE[0][0],3,12);
							     OLED_ShowString(0,3,"Y1:");
							     OLED_ShowNum(90,3,SET_DATE[0][1],3,12);
							     OLED_ShowString2(0,4,"X2:");
							     OLED_ShowNum(90,4,SET_DATE[1][0],3,12);
							     OLED_ShowString(0,5,"Y2:");
							     OLED_ShowNum(90,5,SET_DATE[1][1],3,12);
							     OLED_ShowString(0,6,"X3:");
							     OLED_ShowNum(90,6,SET_DATE[2][0],3,12);
							     break;		
							case 5:
                   OLED_ShowString(0,0,"X_SMOTH:");
							     OLED_ShowNum(90,0,x_smoth,4,12);
							     OLED_ShowString(0,1,"Y_SMOTH:");
							     OLED_ShowNum(90,1,y_smoth,4,12);
							     OLED_ShowString(0,2,"X1:");
							     OLED_ShowNum(90,2,SET_DATE[0][0],3,12);
							     OLED_ShowString(0,3,"Y1:");
							     OLED_ShowNum(90,3,SET_DATE[0][1],3,12);
							     OLED_ShowString(0,4,"X2:");
							     OLED_ShowNum(90,4,SET_DATE[1][0],3,12);
							     OLED_ShowString2(0,5,"Y2:");
							     OLED_ShowNum(90,5,SET_DATE[1][1],3,12);
							     OLED_ShowString(0,6,"X3:");
							     OLED_ShowNum(90,6,SET_DATE[2][0],3,12);
							     break;						
              case 6:
                   OLED_ShowString(0,0,"X_SMOTH:");
							     OLED_ShowNum(90,0,x_smoth,4,12);
							     OLED_ShowString(0,1,"Y_SMOTH:");
							     OLED_ShowNum(90,1,y_smoth,4,12);
							     OLED_ShowString(0,2,"X1:");
							     OLED_ShowNum(90,2,SET_DATE[0][0],3,12);
							     OLED_ShowString(0,3,"Y1:");
							     OLED_ShowNum(90,3,SET_DATE[0][1],3,12);
							     OLED_ShowString(0,4,"X2:");
							     OLED_ShowNum(90,4,SET_DATE[1][0],3,12);
							     OLED_ShowString(0,5,"Y2:");
							     OLED_ShowNum(90,5,SET_DATE[1][1],3,12);
							     OLED_ShowString2(0,6,"X3:");
							     OLED_ShowNum(90,6,SET_DATE[2][0],3,12);
							     break;
					  //分界点
							case 7:
                   OLED_ShowString2(0,0,"Y3:");
							     OLED_ShowNum(90,0,SET_DATE[2][1],3,12);	
                   OLED_ShowString(0,1,"X4:");
							     OLED_ShowNum(90,1,SET_DATE[3][0],3,12);
                   OLED_ShowString(0,2,"Y4:");
							     OLED_ShowNum(90,2,SET_DATE[3][1],3,12);
                   OLED_ShowString(0,3,"X5:");
							     OLED_ShowNum(90,3,SET_DATE[4][0],3,12);
                   OLED_ShowString(0,4,"Y5:");
							     OLED_ShowNum(90,4,SET_DATE[4][1],3,12);
                   OLED_ShowString(0,5,"X6:");
							     OLED_ShowNum(90,5,SET_DATE[5][0],3,12);
                   OLED_ShowString(0,6,"Y6:");
							     OLED_ShowNum(90,6,SET_DATE[5][1],3,12);		
                   break;		
              case 8:
                   OLED_ShowString(0,0,"Y3:");
							     OLED_ShowNum(90,0,SET_DATE[2][1],3,12);	
                   OLED_ShowString2(0,1,"X4:");
							     OLED_ShowNum(90,1,SET_DATE[3][0],3,12);
                   OLED_ShowString(0,2,"Y4:");
							     OLED_ShowNum(90,2,SET_DATE[3][1],3,12);
                   OLED_ShowString(0,3,"X5:");
							     OLED_ShowNum(90,3,SET_DATE[4][0],3,12);
                   OLED_ShowString(0,4,"Y5:");
							     OLED_ShowNum(90,4,SET_DATE[4][1],3,12);
                   OLED_ShowString(0,5,"X6:");
							     OLED_ShowNum(90,5,SET_DATE[5][0],3,12);
                   OLED_ShowString(0,6,"Y6:");
							     OLED_ShowNum(90,6,SET_DATE[5][1],3,12);		
                   break;	
							case 9:
                   OLED_ShowString(0,0,"Y3:");
							     OLED_ShowNum(90,0,SET_DATE[2][1],3,12);	
                   OLED_ShowString(0,1,"X4:");
							     OLED_ShowNum(90,1,SET_DATE[3][0],3,12);
                   OLED_ShowString2(0,2,"Y4:");
							     OLED_ShowNum(90,2,SET_DATE[3][1],3,12);
                   OLED_ShowString(0,3,"X5:");
							     OLED_ShowNum(90,3,SET_DATE[4][0],3,12);
                   OLED_ShowString(0,4,"Y5:");
							     OLED_ShowNum(90,4,SET_DATE[4][1],3,12);
                   OLED_ShowString(0,5,"X6:");
							     OLED_ShowNum(90,5,SET_DATE[5][0],3,12);
                   OLED_ShowString(0,6,"Y6:");
							     OLED_ShowNum(90,6,SET_DATE[5][1],3,12);		
                   break;	
							case 10:
                   OLED_ShowString(0,0,"Y3:");
							     OLED_ShowNum(90,0,SET_DATE[2][1],3,12);	
                   OLED_ShowString(0,1,"X4:");
							     OLED_ShowNum(90,1,SET_DATE[3][0],3,12);
                   OLED_ShowString(0,2,"Y4:");
							     OLED_ShowNum(90,2,SET_DATE[3][1],3,12);
                   OLED_ShowString2(0,3,"X5:");
							     OLED_ShowNum(90,3,SET_DATE[4][0],3,12);
                   OLED_ShowString(0,4,"Y5:");
							     OLED_ShowNum(90,4,SET_DATE[4][1],3,12);
                   OLED_ShowString(0,5,"X6:");
							     OLED_ShowNum(90,5,SET_DATE[5][0],3,12);
                   OLED_ShowString(0,6,"Y6:");
							     OLED_ShowNum(90,6,SET_DATE[5][1],3,12);		
                   break;			
             case 11:
                   OLED_ShowString(0,0,"Y3:");
							     OLED_ShowNum(90,0,SET_DATE[2][1],3,12);	
                   OLED_ShowString(0,1,"X4:");
							     OLED_ShowNum(90,1,SET_DATE[3][0],3,12);
                   OLED_ShowString(0,2,"Y4:");
							     OLED_ShowNum(90,2,SET_DATE[3][1],3,12);
                   OLED_ShowString(0,3,"X5:");
							     OLED_ShowNum(90,3,SET_DATE[4][0],3,12);
                   OLED_ShowString2(0,4,"Y5:");
							     OLED_ShowNum(90,4,SET_DATE[4][1],3,12);
                   OLED_ShowString(0,5,"X6:");
							     OLED_ShowNum(90,5,SET_DATE[5][0],3,12);
                   OLED_ShowString(0,6,"Y6:");
							     OLED_ShowNum(90,6,SET_DATE[5][1],3,12);		
                   break;	
						 case 12:
                   OLED_ShowString(0,0,"Y3:");
							     OLED_ShowNum(90,0,SET_DATE[2][1],3,12);	
                   OLED_ShowString(0,1,"X4:");
							     OLED_ShowNum(90,1,SET_DATE[3][0],3,12);
                   OLED_ShowString(0,2,"Y4:");
							     OLED_ShowNum(90,2,SET_DATE[3][1],3,12);
                   OLED_ShowString(0,3,"X5:");
							     OLED_ShowNum(90,3,SET_DATE[4][0],3,12);
                   OLED_ShowString(0,4,"Y5:");
							     OLED_ShowNum(90,4,SET_DATE[4][1],3,12);
                   OLED_ShowString2(0,5,"X6:");
							     OLED_ShowNum(90,5,SET_DATE[5][0],3,12);
                   OLED_ShowString(0,6,"Y6:");
							     OLED_ShowNum(90,6,SET_DATE[5][1],3,12);		
                   break;
						 case 13:
                   OLED_ShowString(0,0,"Y3:");
							     OLED_ShowNum(90,0,SET_DATE[2][1],3,12);	
                   OLED_ShowString(0,1,"X4:");
							     OLED_ShowNum(90,1,SET_DATE[3][0],3,12);
                   OLED_ShowString(0,2,"Y4:");
							     OLED_ShowNum(90,2,SET_DATE[3][1],3,12);
                   OLED_ShowString(0,3,"X5:");
							     OLED_ShowNum(90,3,SET_DATE[4][0],3,12);
                   OLED_ShowString(0,4,"Y5:");
							     OLED_ShowNum(90,4,SET_DATE[4][1],3,12);
                   OLED_ShowString(0,5,"X6:");
							     OLED_ShowNum(90,5,SET_DATE[5][0],3,12);
                   OLED_ShowString2(0,6,"Y6:");
							     OLED_ShowNum(90,6,SET_DATE[5][1],3,12);		
                   break;
             //分界点						 
             case 14:
                   OLED_ShowString2(0,0,"X7:");
							     OLED_ShowNum(90,0,SET_DATE[6][0],3,12);
							     OLED_ShowString(0,1,"Y7:");
							     OLED_ShowNum(90,1,SET_DATE[6][1],3,12);
							     OLED_ShowString(0,2,"X8:");
							     OLED_ShowNum(90,2,SET_DATE[7][0],3,12);
							     OLED_ShowString(0,3,"Y8:");
							     OLED_ShowNum(90,3,SET_DATE[7][1],3,12);
							     OLED_ShowString(0,4,"X9:");
							     OLED_ShowNum(90,4,SET_DATE[8][0],3,12);
							     OLED_ShowString(0,5,"Y9:");
							     OLED_ShowNum(90,5,SET_DATE[8][1],3,12);
							     OLED_ShowString(0,6,"S-X1:");
							     OLED_ShowNum(90,6,SET_DATE[9][0],3,12);
							     break;
						 case 15:
							     OLED_ShowString(0,0,"X7:");
							     OLED_ShowNum(90,0,SET_DATE[6][0],3,12);
							     OLED_ShowString2(0,1,"Y7:");
							     OLED_ShowNum(90,1,SET_DATE[6][1],3,12);
							     OLED_ShowString(0,2,"X8:");
							     OLED_ShowNum(90,2,SET_DATE[7][0],3,12);
							     OLED_ShowString(0,3,"Y8:");
							     OLED_ShowNum(90,3,SET_DATE[7][1],3,12);
							     OLED_ShowString(0,4,"X9:");
							     OLED_ShowNum(90,4,SET_DATE[8][0],3,12);
							     OLED_ShowString(0,5,"Y9:");
							     OLED_ShowNum(90,5,SET_DATE[8][1],3,12);
							     OLED_ShowString(0,6,"S-X1:");
							     OLED_ShowNum(90,6,SET_DATE[9][0],3,12);
							     break;
						 case 16:
							     OLED_ShowString(0,0,"X7:");
							     OLED_ShowNum(90,0,SET_DATE[6][0],3,12);
							     OLED_ShowString(0,1,"Y7:");
							     OLED_ShowNum(90,1,SET_DATE[6][1],3,12);
							     OLED_ShowString2(0,2,"X8:");
							     OLED_ShowNum(90,2,SET_DATE[7][0],3,12);
							     OLED_ShowString(0,3,"Y8:");
							     OLED_ShowNum(90,3,SET_DATE[7][1],3,12);
							     OLED_ShowString(0,4,"X9:");
							     OLED_ShowNum(90,4,SET_DATE[8][0],3,12);
							     OLED_ShowString(0,5,"Y9:");
							     OLED_ShowNum(90,5,SET_DATE[8][1],3,12);
							     OLED_ShowString(0,6,"S-X1:");
							     OLED_ShowNum(90,6,SET_DATE[9][0],3,12);
							     break;
						 case 17:
							     OLED_ShowString(0,0,"X7:");
							     OLED_ShowNum(90,0,SET_DATE[6][0],3,12);
							     OLED_ShowString(0,1,"Y7:");
							     OLED_ShowNum(90,1,SET_DATE[6][1],3,12);
							     OLED_ShowString(0,2,"X8:");
							     OLED_ShowNum(90,2,SET_DATE[7][0],3,12);
							     OLED_ShowString2(0,3,"Y8:");
							     OLED_ShowNum(90,3,SET_DATE[7][1],3,12);
							     OLED_ShowString(0,4,"X9:");
							     OLED_ShowNum(90,4,SET_DATE[8][0],3,12);
							     OLED_ShowString(0,5,"Y9:");
							     OLED_ShowNum(90,5,SET_DATE[8][1],3,12);
							     OLED_ShowString(0,6,"S-X1:");
							     OLED_ShowNum(90,6,SET_DATE[9][0],3,12);
							     break;
						 case 18:
							     OLED_ShowString(0,0,"X7:");
							     OLED_ShowNum(90,0,SET_DATE[6][0],3,12);
							     OLED_ShowString(0,1,"Y7:");
							     OLED_ShowNum(90,1,SET_DATE[6][1],3,12);
							     OLED_ShowString(0,2,"X8:");
							     OLED_ShowNum(90,2,SET_DATE[7][0],3,12);
							     OLED_ShowString(0,3,"Y8:");
							     OLED_ShowNum(90,3,SET_DATE[7][1],3,12);
							     OLED_ShowString2(0,4,"X9:");
							     OLED_ShowNum(90,4,SET_DATE[8][0],3,12);
							     OLED_ShowString(0,5,"Y9:");
							     OLED_ShowNum(90,5,SET_DATE[8][1],3,12);
							     OLED_ShowString(0,6,"S-X1:");
							     OLED_ShowNum(90,6,SET_DATE[9][0],3,12);
							     break;
						 case 19:
							     OLED_ShowString(0,0,"X7:");
							     OLED_ShowNum(90,0,SET_DATE[6][0],3,12);
							     OLED_ShowString(0,1,"Y7:");
							     OLED_ShowNum(90,1,SET_DATE[6][1],3,12);
							     OLED_ShowString(0,2,"X8:");
							     OLED_ShowNum(90,2,SET_DATE[7][0],3,12);
							     OLED_ShowString(0,3,"Y8:");
							     OLED_ShowNum(90,3,SET_DATE[7][1],3,12);
							     OLED_ShowString(0,4,"X9:");
							     OLED_ShowNum(90,4,SET_DATE[8][0],3,12);
							     OLED_ShowString2(0,5,"Y9:");
							     OLED_ShowNum(90,5,SET_DATE[8][1],3,12);
							     OLED_ShowString(0,6,"S-X1:");
							     OLED_ShowNum(90,6,SET_DATE[9][0],3,12);
							     break;
						 case 20:
							     OLED_ShowString(0,0,"X7:");
							     OLED_ShowNum(90,0,SET_DATE[6][0],3,12);
							     OLED_ShowString(0,1,"Y7:");
							     OLED_ShowNum(90,1,SET_DATE[6][1],3,12);
							     OLED_ShowString(0,2,"X8:");
							     OLED_ShowNum(90,2,SET_DATE[7][0],3,12);
							     OLED_ShowString(0,3,"Y8:");
							     OLED_ShowNum(90,3,SET_DATE[7][1],3,12);
							     OLED_ShowString(0,4,"X9:");
							     OLED_ShowNum(90,4,SET_DATE[8][0],3,12);
							     OLED_ShowString(0,5,"Y9:");
							     OLED_ShowNum(90,5,SET_DATE[8][1],3,12);
							     OLED_ShowString2(0,6,"S-X1:");
							     OLED_ShowNum(90,6,SET_DATE[9][0],3,12);
							     break;
						 //分界点
						 case 21:
							     OLED_ShowString2(0,0,"S-Y1:");
						       OLED_ShowNum(90,0,SET_DATE[9][1],3,12);
						       OLED_ShowString(0,1,"S-X2:");
						       OLED_ShowNum(90,1,SET_DATE[10][0],3,12);
						       OLED_ShowString(0,2,"S-Y2:");	
                   OLED_ShowNum(90,2,SET_DATE[10][1],3,12);
						       OLED_ShowString(0,3,"S-X3:");	
                   OLED_ShowNum(90,3,SET_DATE[11][0],3,12);
						       OLED_ShowString(0,4,"S-Y3:");	
                   OLED_ShowNum(90,4,SET_DATE[11][1],3,12);	
						       OLED_ShowString(0,5,"S-X4:");	
                   OLED_ShowNum(90,5,SET_DATE[12][0],3,12);		
						       OLED_ShowString(0,6,"S-Y4:");	
                   OLED_ShowNum(90,6,SET_DATE[12][1],3,12);		
                   break;
             case 22:
                   OLED_ShowString(0,0,"S-Y1:");
						       OLED_ShowNum(90,0,SET_DATE[9][1],3,12);
						       OLED_ShowString2(0,1,"S-X2:");
						       OLED_ShowNum(90,1,SET_DATE[10][0],3,12);
						       OLED_ShowString(0,2,"S-Y2:");	
                   OLED_ShowNum(90,2,SET_DATE[10][1],3,12);
						      OLED_ShowString(0,3,"S-X3:");	
                   OLED_ShowNum(90,3,SET_DATE[11][0],3,12);
						       OLED_ShowString(0,4,"S-Y3:");	
                   OLED_ShowNum(90,4,SET_DATE[11][1],3,12);	
						       OLED_ShowString(0,5,"S-X4:");	
                   OLED_ShowNum(90,5,SET_DATE[12][0],3,12);		
						       OLED_ShowString(0,6,"S-Y4:");	
                   OLED_ShowNum(90,6,SET_DATE[12][1],3,12);		
                   break;
             case 23:
                   OLED_ShowString(0,0,"S-Y1:");
						       OLED_ShowNum(90,0,SET_DATE[9][1],3,12);
						       OLED_ShowString(0,1,"S-X2:");
						       OLED_ShowNum(90,1,SET_DATE[10][0],3,12);
						       OLED_ShowString2(0,2,"S-Y2:");	
                   OLED_ShowNum(90,2,SET_DATE[10][1],3,12);
						       OLED_ShowString(0,3,"S-X3:");	
                   OLED_ShowNum(90,3,SET_DATE[11][0],3,12);
						       OLED_ShowString(0,4,"S-Y3:");	
                   OLED_ShowNum(90,4,SET_DATE[11][1],3,12);	
						       OLED_ShowString(0,5,"S-X4:");	
                   OLED_ShowNum(90,5,SET_DATE[12][0],3,12);		
						       OLED_ShowString(0,6,"S-Y4:");	
                   OLED_ShowNum(90,6,SET_DATE[12][1],3,12);		
                   break;	
						  case 24:
                   OLED_ShowString(0,0,"S-Y1:");
						       OLED_ShowNum(90,0,SET_DATE[9][1],3,12);
						       OLED_ShowString(0,1,"S-X2:");
						       OLED_ShowNum(90,1,SET_DATE[10][0],3,12);
						       OLED_ShowString(0,2,"S-Y2:");	
                   OLED_ShowNum(90,2,SET_DATE[10][1],3,12);
							     OLED_ShowString2(0,3,"S-X3:");	
                   OLED_ShowNum(90,3,SET_DATE[11][0],3,12);
							     OLED_ShowString(0,4,"S-Y3:");	
                   OLED_ShowNum(90,4,SET_DATE[11][1],3,12);	
							     OLED_ShowString(0,5,"S-X4:");	
                   OLED_ShowNum(90,5,SET_DATE[12][0],3,12);		
							     OLED_ShowString(0,6,"S-Y4:");	
                   OLED_ShowNum(90,6,SET_DATE[12][1],3,12);		
                   break;	
							case 25:
                   OLED_ShowString(0,0,"S-Y1:");
						       OLED_ShowNum(90,0,SET_DATE[9][1],3,12);
						       OLED_ShowString(0,1,"S-X2:");
						       OLED_ShowNum(90,1,SET_DATE[10][0],3,12);
						       OLED_ShowString(0,2,"S-Y2:");	
                   OLED_ShowNum(90,2,SET_DATE[10][1],3,12);
							     OLED_ShowString(0,3,"S-X3:");	
                   OLED_ShowNum(90,3,SET_DATE[11][0],3,12);
							     OLED_ShowString2(0,4,"S-Y3:");	
                   OLED_ShowNum(90,4,SET_DATE[11][1],3,12);	
							     OLED_ShowString(0,5,"S-X4:");	
                   OLED_ShowNum(90,5,SET_DATE[12][0],3,12);		
							     OLED_ShowString(0,6,"S-Y4:");	
                   OLED_ShowNum(90,6,SET_DATE[12][1],3,12);		
                   break;	
							case 26:
                   OLED_ShowString(0,0,"S-Y1:");
						       OLED_ShowNum(90,0,SET_DATE[9][1],3,12);
						       OLED_ShowString(0,1,"S-X2:");
						       OLED_ShowNum(90,1,SET_DATE[10][0],3,12);
						       OLED_ShowString(0,2,"S-Y2:");	
                   OLED_ShowNum(90,2,SET_DATE[10][1],3,12);
							     OLED_ShowString(0,3,"S-X3:");	
                   OLED_ShowNum(90,3,SET_DATE[11][0],3,12);
							    OLED_ShowString(0,4,"S-Y3:");	
                   OLED_ShowNum(90,4,SET_DATE[11][1],3,12);	
							     OLED_ShowString2(0,5,"S-X4:");	
                   OLED_ShowNum(90,5,SET_DATE[12][0],3,12);		
							     OLED_ShowString(0,6,"S-Y4:");	
                   OLED_ShowNum(90,6,SET_DATE[12][1],3,12);		
                   break;		
              case 27:
                   OLED_ShowString(0,0,"S-Y1:");
						       OLED_ShowNum(90,0,SET_DATE[9][1],3,12);
						       OLED_ShowString(0,1,"S-X2:");
						       OLED_ShowNum(90,1,SET_DATE[10][0],3,12);
						       OLED_ShowString(0,2,"S-Y2:");	
                   OLED_ShowNum(90,2,SET_DATE[10][1],3,12);
							     OLED_ShowString(0,3,"S-X3:");	
                   OLED_ShowNum(90,3,SET_DATE[11][0],3,12);
							     OLED_ShowString(0,4,"S-Y3:");	
                   OLED_ShowNum(90,4,SET_DATE[11][1],3,12);	
							     OLED_ShowString(0,5,"S-X4:");	
                   OLED_ShowNum(90,5,SET_DATE[12][0],3,12);		
							     OLED_ShowString2(0,6,"S-Y4:");	
                   OLED_ShowNum(90,6,SET_DATE[12][1],3,12);		
                   break;										
						}
				}
				
			if(flag_first==7)
			{
				if(FL_flag==0)
				{
				switch(flag_second)
				{
					case 0:
				      OLED_ShowString(0,0,"Are you sure write to flash ?");
				      OLED_ShowString2(0,4,"YES");
				      OLED_ShowString(40,4,"NO");
					    break;
				  case 1:
						  OLED_ShowString(0,0,"Are you sure write to flash ?");
				      OLED_ShowString(0,4,"YES");
				      OLED_ShowString2(40,4,"NO");
					    break;
				}
			  }
				else
				{
					   OLED_ShowString(0,2,"Flash write ok.....");
				}
			}
}

void Key_choice()
{ 
	//第一级菜单选择
	if(flag_ensure==0)
	 {
	   if(KEY_Scan()==1)
	  {
		  flag_first=flag_first+1;
		  if(flag_first>=8)
		 {
			  flag_first=0;
		 }
		 if(flag_first==0||flag_first==7)
		 {
			 OLED_Clear();
		 }
	  }
  }
	//第二级菜单选择,PID的参数调节
	  //PID_X
	 if(flag_ensure==1&&flag_first==0)
	 {
		 //选择要调节的参数
		 if(KEY_Scan()==1)
		 {
			  flag_second=flag_second+1;
			  if(flag_second>=3)
				{
					 flag_second=0;
				}
		 }
		 //Kp_X的参数调节
		  if(flag_second==0)
			{
				 if(KEY_Scan()==2)
				 {
					  PID_P_X=PID_P_X+Kp_add;
				 }
				 if(KEY_Scan()==3)
				 {
					  PID_P_X=PID_P_X-Kp_add;
				 }
				 if(PID_P_X<=0)
				 {
					  PID_P_X=0;
				 }
			}
		//Ki_X的参数调节
			if(flag_second==1)
			{
				  if(KEY_Scan()==2)
				 {
					  PID_I_X=PID_I_X+Ki_add;
				 }
				 if(KEY_Scan()==3)
				 {
					  PID_I_X=PID_I_X-Ki_add;
				 }
				 if(PID_I_X<=0)
				 {
					  PID_I_X=0;
				 } 
			}
			//Kd_X的参数调节
				if(flag_second==2)
			{
				  if(KEY_Scan()==2)
				 {
					  PID_D_X=PID_D_X+Kd_add;
				 }
				 if(KEY_Scan()==3)
				 {
					  PID_D_X=PID_D_X-Kd_add;
				 }
				 if(PID_D_X<=0)
				 {
					  PID_D_X=0;
				 }
			}
	 }
	 	  //PID_Y
	 if(flag_ensure==1&&flag_first==1)
	 {
		 //选择要调节的参数
		 if(KEY_Scan()==1)
		 {
			  flag_second=flag_second+1;
			  if(flag_second>=3)
				{
					 flag_second=0;
				}
		 }
		 //Kp_Y的参数调节
		  if(flag_second==0)
			{
				 if(KEY_Scan()==2)
				 {
					  PID_P_Y=PID_P_Y+Kp_add;
				 }
				 if(KEY_Scan()==3)
				 {
					  PID_P_Y=PID_P_Y-Kp_add;
				 }
				 if(PID_P_Y<=0)
				 {
					  PID_P_Y=0;
				 }
			}
		//Ki_Y的参数调节
			if(flag_second==1)
			{
				  if(KEY_Scan()==2)
				 {
					  PID_I_Y=PID_I_Y+Ki_add;
				 }
				 if(KEY_Scan()==3)
				 {
					  PID_I_Y=PID_I_Y-Ki_add;
				 }
				 if(PID_I_Y<=0)
				 {
					  PID_I_Y=0;
				 }
			}
			//Kd_Y的参数调节
				if(flag_second==2)
			{
				  if(KEY_Scan()==2)
				 {
					  PID_D_Y=PID_D_Y+Kd_add;
				 }
				 if(KEY_Scan()==3)
				 {
					  PID_D_Y=PID_D_Y-Kd_add;
				 }
				 if(PID_D_Y<=0)
				 {
					  PID_D_Y=0;
				 }
			}
	 }
	 //第二级菜单选择，PID参数量级改变
	if(flag_ensure==1&&flag_first==2)
	{
		 //选择要调节的参数
		 if(KEY_Scan()==1)
		 {
			  flag_second=flag_second+1;
			  if(flag_second>=3)
				{
					 flag_second=0;
				}
		 }
		 //Kp_add调节
		 if(flag_second==0)
		 {
			  if(KEY_Scan()==2)
				{
					 Kp_add=Kp_add+0.0001;
				}
				if(KEY_Scan()==3)
				{
					 Kp_add=Kp_add-0.0001;
				}
				if(Kp_add<=0)Kp_add=0;
		 }
		 //Kd_add的调节
		 if(flag_second==1)
		 {
			 if(KEY_Scan()==2)
				{
					 Kd_add=Kd_add+0.0001;
				}
				if(KEY_Scan()==3)
				{
					 Kd_add=Kd_add-0.0001;
				}
				if(Kd_add<=0)Kd_add=0;
		 }
		 //Ki_add的调节
		 if(flag_second==2)
		 {
			   if(KEY_Scan()==2)
				{
					 Ki_add=Ki_add+0.0001;
				}
				if(KEY_Scan()==3)
				{
					 Ki_add=Ki_add-0.0001;
				}
				if(Ki_add<=0)Ki_add=0;
		 }
	}
	
	//题目模式的选择
	if(flag_ensure==1&&flag_first==4)
  {
		 //选择模式
		 if(KEY_Scan()==1)
		 {
			  flag_second=flag_second+1;
			  if(flag_second>=7)
				{
					 flag_second=0;
				}
		 }
		 if(flag_mode==0)
		{
		 if(flag_second==0)
		 {
			  if(KEY_Scan()==2)
				{
					 flag_mode=1;
				 	 OLED_Clear();
				}
		 }
		 if(flag_second==1)
		 {
			  if(KEY_Scan()==2)
				{
					 flag_mode=2;
					 MODEII_timer=0;
					 OLED_Clear();
				}
		 }
		 if(flag_second==2)
		  {
			 if(KEY_Scan()==2)
				{
					 flag_mode=3;
					 MODEIII_flag=0;
					 OLED_Clear();
				}
		  }
			if(flag_second==3)
			{
				  if(KEY_Scan()==2)
				{
					 flag_mode=4;
					 MODEVI_flag=0;
					 OLED_Clear();
				}
			}
		 if(flag_second==4)
		 {
			    if(KEY_Scan()==2)
				{
					 flag_mode=5;
					 MODEV_flag=0;
					 OLED_Clear();
				}
		 }
		 if(flag_second==5)
		 {
			    if(KEY_Scan()==2)
				{
					 flag_mode=6;
					 MODEIV_flag=1;
					 Real_area=0;
					 area_save=0;
					 OLED_Clear();
				}
		 }
		 if(flag_second==6)
		 {
			   if(KEY_Scan()==2)
				{
					 flag_mode=7;
					 MODEVII_flag=0;
					 OLED_Clear();
			  }
		 }
	  }
		 else
		 {
			 if(KEY_Scan()==3)
				{
					 flag_mode=0;
					 OLED_Clear();
					 timer=0;
				   My_timer=0;
				}
		 }
	}
  //发挥部分第2题位置设定
	if(flag_ensure==1&&flag_first==5)
	{
		   if(KEY_Scan()==1)
		 {
			  flag_second=flag_second+1;
			  if(flag_second>=4)
				{
					 flag_second=0;
				}
		 }
	  //A区设置
		 if(flag_second==0)
		 {
			   if(KEY_Scan()==2)
				 {
					  A_flag=A_flag+1;
				 }
				 if(KEY_Scan()==3)
				 {
					  A_flag=A_flag-1;
				 }
				 if(A_flag<=1)
				 {
					  A_flag=1;
				 }
				 if(A_flag>=10)
				 {
					  A_flag=10;
				 }
		 }
		 //B区设置
		 if(flag_second==1)
		 {
			   if(KEY_Scan()==2)
				 {
					  B_flag=B_flag+1;
				 }
				 if(KEY_Scan()==3)
				 {
					  B_flag=B_flag-1;
				 }
				 if(B_flag<=1)
				 {
					  B_flag=1;
				 }
				 if(B_flag>=10)
				 {
					  B_flag=10;
				 }			 
		 }
		//C区设置
		 	 if(flag_second==2)
		 {
			   if(KEY_Scan()==2)
				 {
					  C_flag=C_flag+1;
				 }
				 if(KEY_Scan()==3)
				 {
					  C_flag=C_flag-1;
				 }
				 if(C_flag<=1)
				 {
					  C_flag=1;
				 }
				 if(C_flag>=10)
				 {
					  C_flag=10;
				 }			 
		 }
		//D区设置
		   	 if(flag_second==3)
		   {
			   if(KEY_Scan()==2)
				 {
					  D_flag=D_flag+1;
				 }
				 if(KEY_Scan()==3)
				 {
					  D_flag=D_flag-1;
				 }
				 if(D_flag<=1)
				 {
					  D_flag=1;
				 }
				 if(D_flag>=10)
				 {
					  D_flag=10;
				 }			 
		  }
	}
//FLASH写入,参数
		if(flag_ensure==1&&flag_first==6)
		{
			
			
			  if(KEY_Scan()==1)
		  {
			  flag_second=flag_second+1;
			  if(flag_second>=28)
				{
					 flag_second=0;
				}
				  if(flag_second==0||flag_second==7||flag_second==14||flag_second==21)
				{
					 	OLED_Clear();
				}
		  }
			
		
			if(flag_second==0)
			{
				 if(KEY_Scan()==2)
				{
					 x_smoth=x_smoth+1;
				}
				if(KEY_Scan()==3)
				{
					 x_smoth=x_smoth-1;
				}
				if(x_smoth<=0)x_smoth=0;
			}
			
			
			if(flag_second==1)
			{
				  if(KEY_Scan()==2)
				{
					 y_smoth=y_smoth+1;
				}
				if(KEY_Scan()==3)
				{
					 y_smoth=y_smoth-1;
				}
				if(y_smoth<=0)y_smoth=0;
			}
			
			
			if(flag_second==2)
			{
				 	if(KEY_Scan()==2)
				{
					 SET_DATE[0][0]=SET_DATE[0][0]+1;
				}
				if(KEY_Scan()==3)
				{
					SET_DATE[0][0]=SET_DATE[0][0]-1;
				}
				if(SET_DATE[0][0]<=0)SET_DATE[0][0]=0;
			}
			
			
			if(flag_second==3)
			{
				 if(KEY_Scan()==2)
				{
					 SET_DATE[0][1]=SET_DATE[0][1]+1;
				}
				if(KEY_Scan()==3)
				{
					SET_DATE[0][1]=SET_DATE[0][1]-1;
				}
				if(SET_DATE[0][1]<=0)SET_DATE[0][1]=0;
			}
			
			
			if(flag_second==4)
			{
				  if(KEY_Scan()==2)
				{
					 SET_DATE[1][0]= SET_DATE[1][0]+1;
				}
				if(KEY_Scan()==3)
				{
					 SET_DATE[1][0]= SET_DATE[1][0]-1;
				}
				if( SET_DATE[1][0]<=0) SET_DATE[1][0]=0;
			}
			
			if(flag_second==5)
			{
				  if(KEY_Scan()==2)
				{
					 SET_DATE[1][1]= SET_DATE[1][1]+1;
				}
				if(KEY_Scan()==3)
				{
					 SET_DATE[1][1]= SET_DATE[1][1]-1;
				}
				if( SET_DATE[1][1]<=0) SET_DATE[1][1]=0;
			}
			
			if(flag_second==6)
			{
				 if(KEY_Scan()==2)
				{
					 SET_DATE[2][0]= SET_DATE[2][0]+1;
				}
				if(KEY_Scan()==3)
				{
					 SET_DATE[2][0]= SET_DATE[2][0]-1;
				}
				if( SET_DATE[2][0]<=0) SET_DATE[2][0]=0;
			}
			
			if(flag_second==7)
			{
				  if(KEY_Scan()==2)
				{
					 SET_DATE[2][1]= SET_DATE[2][1]+1;
				}
				if(KEY_Scan()==3)
				{
					 SET_DATE[2][1]= SET_DATE[2][1]-1;
				}
				if( SET_DATE[2][1]<=0) SET_DATE[2][1]=0;
			}
			
			if(flag_second==8)
			{
				 	if(KEY_Scan()==2)
				{
					 SET_DATE[3][0]= SET_DATE[3][0]+1;
				}
				if(KEY_Scan()==3)
				{
					 SET_DATE[3][0]= SET_DATE[3][0]-1;
				}
				if( SET_DATE[3][0]<=0) SET_DATE[3][0]=0;
			}
			
			if(flag_second==9)
			{
				 	if(KEY_Scan()==2)
				{
					 SET_DATE[3][1]= SET_DATE[3][1]+1;
				}
				if(KEY_Scan()==3)
				{
					 SET_DATE[3][1]= SET_DATE[3][1]-1;
				}
				if( SET_DATE[3][1]<=0) SET_DATE[3][1]=0;
			}
			
			if(flag_second==10)
			{
				 if(KEY_Scan()==2)
				{
					 SET_DATE[4][0]= SET_DATE[4][0]+1;
				}
				if(KEY_Scan()==3)
				{
					  SET_DATE[4][0]=  SET_DATE[4][0]-1;
				}
				if(  SET_DATE[4][0]<=0)  SET_DATE[4][0]=0;
			}
			
			if(flag_second==11)
			{
				  if(KEY_Scan()==2)
				{
					 SET_DATE[4][1]= SET_DATE[4][1]+1;
				}
				if(KEY_Scan()==3)
				{
					  SET_DATE[4][1]=  SET_DATE[4][1]-1;
				}
				if(  SET_DATE[4][1]<=0)  SET_DATE[4][1]=0;
			}
			
			if(flag_second==12)
			{
				 if(KEY_Scan()==2)
				{
					 SET_DATE[5][0]= SET_DATE[5][0]+1;
				}
				if(KEY_Scan()==3)
				{
					  SET_DATE[5][0]=  SET_DATE[5][0]-1;
				}
				if(  SET_DATE[5][0]<=0) SET_DATE[5][0]=0;
			}
			
			if(flag_second==13)
			{
				  if(KEY_Scan()==2)
				{
					 SET_DATE[5][1]= SET_DATE[5][1]+1;
				}
				if(KEY_Scan()==3)
				{
					  SET_DATE[5][1]=  SET_DATE[5][1]-1;
				}
				if(  SET_DATE[5][1]<=0) SET_DATE[5][1]=0;
			}
			
			if(flag_second==14)
			{
				 	if(KEY_Scan()==2)
				{
					 SET_DATE[6][0]=  SET_DATE[6][0]+1;
				}
				if(KEY_Scan()==3)
				{
					   SET_DATE[6][0]=   SET_DATE[6][0]-1;
				}
				if(   SET_DATE[6][0]<=0)  SET_DATE[6][0]=0;
			}
			
			if(flag_second==15)
			{
				  if(KEY_Scan()==2)
				{
					 SET_DATE[6][1]=  SET_DATE[6][1]+1;
				}
				if(KEY_Scan()==3)
				{
					   SET_DATE[6][1]=   SET_DATE[6][1]-1;
				}
				if(   SET_DATE[6][1]<=0)  SET_DATE[6][1]=0;
			}
		if(flag_second==16)
		{
			 	if(KEY_Scan()==2)
				{
					 SET_DATE[7][0]= SET_DATE[7][0]+1;
				}
				if(KEY_Scan()==3)
				{
					   SET_DATE[7][0]=  SET_DATE[7][0]-1;
				}
				if(   SET_DATE[7][0]<=0) SET_DATE[7][0]=0;
		}
		
		if(flag_second==17)
		{
			 	if(KEY_Scan()==2)
				{
					 SET_DATE[7][1]= SET_DATE[7][1]+1;
				}
				if(KEY_Scan()==3)
				{
					   SET_DATE[7][1]=  SET_DATE[7][1]-1;
				}
				if(   SET_DATE[7][1]<=0) SET_DATE[7][1]=0;
		}
		
		if(flag_second==18)
		{
			  	if(KEY_Scan()==2)
				{
					 SET_DATE[8][0]=  SET_DATE[8][0]+1;
				}
				if(KEY_Scan()==3)
				{
					   SET_DATE[8][0]=   SET_DATE[8][0]-1;
				}
				if( SET_DATE[8][0]<=0)  SET_DATE[8][0]=0;
		}
		
		if(flag_second==19)
		{
			  	if(KEY_Scan()==2)
				{
					 SET_DATE[8][1]=  SET_DATE[8][1]+1;
				}
				if(KEY_Scan()==3)
				{
					   SET_DATE[8][1]=   SET_DATE[8][1]-1;
				}
				if( SET_DATE[8][1]<=0)  SET_DATE[8][1]=0;
		}
		
		if(flag_second==20)
		{
			   	if(KEY_Scan()==2)
				{
					 SET_DATE[9][0]=  SET_DATE[9][0]+1;
				}
				if(KEY_Scan()==3)
				{
					   SET_DATE[9][0]=   SET_DATE[9][0]-1;
				}
				if( SET_DATE[9][0]<=0) SET_DATE[9][0]=0;
		}
		
		if(flag_second==21)
		{
			 	  if(KEY_Scan()==2)
				{
					 SET_DATE[9][1]=  SET_DATE[9][1]+1;
				}
				if(KEY_Scan()==3)
				{
					   SET_DATE[9][1]=   SET_DATE[9][1]-1;
				}
				if( SET_DATE[9][1]<=0) SET_DATE[9][1]=0;
		}
		
		if(flag_second==22)
		{
			  if(KEY_Scan()==2)
				{
					 SET_DATE[10][0]= SET_DATE[10][0]+1;
				}
				if(KEY_Scan()==3)
				{
					  SET_DATE[10][0]=  SET_DATE[10][0]-1;
				}
				if( SET_DATE[10][0]<=0)SET_DATE[10][0]=0;
		}
		
		if(flag_second==23)
		{
			   if(KEY_Scan()==2)
				{
					 SET_DATE[10][1]= SET_DATE[10][1]+1;
				}
				if(KEY_Scan()==3)
				{
					  SET_DATE[10][1]=  SET_DATE[10][1]-1;
				}
				if( SET_DATE[10][1]<=0)SET_DATE[10][1]=0;
		}
		
		if(flag_second==24)
		{
			    if(KEY_Scan()==2)
				{
					 SET_DATE[11][0]=  SET_DATE[11][0]+1;
				}
				if(KEY_Scan()==3)
				{
					   SET_DATE[11][0]=   SET_DATE[11][0]-1;
				}
				if(  SET_DATE[11][0]<=0) SET_DATE[11][0]=0;
		}
		
		if(flag_second==25)
		{
			   if(KEY_Scan()==2)
				{
					 SET_DATE[11][1]=  SET_DATE[11][1]+1;
				}
				if(KEY_Scan()==3)
				{
					   SET_DATE[11][1]=   SET_DATE[11][1]-1;
				}
				if(  SET_DATE[11][1]<=0) SET_DATE[11][1]=0;
		}
		
		if(flag_second==26)
		{
				if(KEY_Scan()==2)
				{
					 SET_DATE[12][0]=   SET_DATE[12][0]+1;
				}
				if(KEY_Scan()==3)
				{
					    SET_DATE[12][0]=   SET_DATE[12][0]-1;
				}
				if(   SET_DATE[12][0]<=0)  SET_DATE[12][0]=0;
		}
		
		if(flag_second==27)
		{
			 		if(KEY_Scan()==2)
				{
					 SET_DATE[12][1]=   SET_DATE[12][1]+1;
				}
				if(KEY_Scan()==3)
				{
					    SET_DATE[12][1]=   SET_DATE[12][1]-1;
				}
				if(   SET_DATE[12][1]<=0)  SET_DATE[12][1]=0;
		}
		
		}
		
	 if(flag_ensure==1&&flag_first==7)
		{
			 		if(KEY_Scan()==2)
				 {
					  flag_second=0;
				 }
				 if(KEY_Scan()==3)
				 {
					  flag_second=1;
				 }
				if(flag_second==0&&FL_flag==0)
				{
					 if(KEY_Scan()==1)
		      {  
						 cx=0;
						 for(cl=0;cl<13;cl++)
						 {
							  for(cy=0;cy<2;cy++)
								{
									 num[cx]=SET_DATE[cl][cy];
									 cx++;
								}
						 }
						     num[26]=x_smoth;
						     num[27]=y_smoth;
			        STMFLASH_Write(0X0801FC00,(u16 *)num,sizeof(num));
						  FL_flag=1;
						  OLED_Clear();
		      }
			  }
				
				if(flag_second==1&&FL_flag==0)
				{
					 	if(KEY_Scan()==1)
		      {
			        flag_ensure=0;
				      flag_second=0;
				      flag_mode=0;
				      timer=0;
				      My_timer=0;
			        OLED_Clear();
		      }
				}
		}
}



