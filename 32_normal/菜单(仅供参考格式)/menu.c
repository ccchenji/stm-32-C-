#include "menu.h"
#include "KEY.H"
short flag_first=0;
short flag_ensure=0;
short flag_second=0;
float Kp_add=0.0001;
float Kd_add=0.0001;
float Ki_add=0.0001;
extern unsigned char Disp_save[10];


//�˵�����
float Kp=1.12;
float Ki=1.1;
float Kd=1.567;



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
			  OLED_Clear();
			}
	 }
}
//��һ���Ĳ˵�
void First_Page()
{
	switch(flag_first)
	{
		case 0:
			     OLED_ShowString2(0,0,"1.PID_VIEW");
		       OLED_ShowString(0,1,"2.PID_CHANGE"); 
		       OLED_ShowString(0,2,"3.PID_INCREMENT");
		       OLED_ShowString(0,3,"4.MF_VIEW");
		       OLED_ShowString(0,4,"5.MF_CHANGE");
		       OLED_ShowString(0,5,"6.MF_INCREMENT");
		       break;
	  case 1:
			     OLED_ShowString(0,0,"1.PID_VIEW");
		       OLED_ShowString2(0,1,"2.PID_CHANGE"); 
		       OLED_ShowString(0,2,"3.PID_INCREMENT");
		       OLED_ShowString(0,3,"4.MF_VIEW");
		       OLED_ShowString(0,4,"5.MF_CHANGE");
		       OLED_ShowString(0,5,"6.MF_INCREMENT");
		       break;
		case 2:
			     OLED_ShowString(0,0,"1.PID_VIEW");
		       OLED_ShowString(0,1,"2.PID_CHANGE"); 
		       OLED_ShowString2(0,2,"3.PID_INCREMENT");
		       OLED_ShowString(0,3,"4.MF_VIEW");
		       OLED_ShowString(0,4,"5.MF_CHANGE");
		       OLED_ShowString(0,5,"6.MF_INCREMENT");
		       break;
		case 3:
			     OLED_ShowString(0,0,"1.PID_VIEW");
		       OLED_ShowString(0,1,"2.PID_CHANGE"); 
		       OLED_ShowString(0,2,"3.PID_INCREMENT");
		       OLED_ShowString2(0,3,"4.MF_VIEW");
		       OLED_ShowString(0,4,"5.MF_CHANGE");
		       OLED_ShowString(0,5,"6.MF_INCREMENT");
		       break;
		case 4:
			     OLED_ShowString(0,0,"1.PID_VIEW");
		       OLED_ShowString(0,1,"2.PID_CHANGE"); 
		       OLED_ShowString(0,2,"3.PID_INCREMENT");
		       OLED_ShowString(0,3,"4.MF_VIEW");
		       OLED_ShowString2(0,4,"5.MF_CHANGE");
		       OLED_ShowString(0,5,"6.MF_INCREMENT");
		       break;
		case 5:
			     OLED_ShowString(0,0,"1.PID_VIEW");
		       OLED_ShowString(0,1,"2.PID_CHANGE"); 
		       OLED_ShowString(0,2,"3.PID_INCREMENT");
		       OLED_ShowString(0,3,"4.MF_VIEW");
		       OLED_ShowString(0,4,"5.MF_CHANGE");
		       OLED_ShowString2(0,5,"6.MF_INCREMENT");
		       break;
	}
}
void Second_Page()
{
	   if (flag_first==0)
			    {
			 		     OLED_ShowString(0,0,"Kp:");
					     OLED_ShowNum_float(18,1,Kp);
				       OLED_ShowString(0,2,"Kd:");
				       OLED_ShowNum_float(18,3,Kd);
				       OLED_ShowString(0,4,"Ki:");
				       OLED_ShowNum_float(18,5,Ki);			   		     
			     }
			if(flag_first==1)
			    {
				      switch(flag_second)
							{
								case 0:
                   OLED_ShowString2(0,0,"Kp:");
					         OLED_ShowNum_float(18,1,Kp);
				           OLED_ShowString(0,2,"Kd:");
				           OLED_ShowNum_float(18,3,Kd);
				           OLED_ShowString(0,4,"Ki:");
				           OLED_ShowNum_float(18,5,Ki);	
								   break;
                case 1:
                   OLED_ShowString(0,0,"Kp:");
					         OLED_ShowNum_float(18,1,Kp);
				           OLED_ShowString2(0,2,"Kd:");
				           OLED_ShowNum_float(18,3,Kd);
				           OLED_ShowString(0,4,"Ki:");
				           OLED_ShowNum_float(18,5,Ki);		
                   break;	
                case 2:
                   OLED_ShowString(0,0,"Kp:");
					         OLED_ShowNum_float(18,1,Kp);
				           OLED_ShowString(0,2,"Kd:");
				           OLED_ShowNum_float(18,3,Kd);
				           OLED_ShowString2(0,4,"Ki:");
				           OLED_ShowNum_float(18,5,Ki);		 									
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
}

void Key_choice()
{ 
	//��һ���˵�ѡ��
	if(flag_ensure==0)
	 {
	   if(KEY_Scan()==1)
	  {
		  flag_first=flag_first+1;
		  if(flag_first>=6)
		 {
			  flag_first=0;
		 }
	  }
   }
	//�ڶ����˵�ѡ��,PID�Ĳ�������
	 if(flag_ensure==1&&flag_first==1)
	 {
		 //ѡ��Ҫ���ڵĲ���
		 if(KEY_Scan()==1)
		 {
			  flag_second=flag_second+1;
			  if(flag_second>=3)
				{
					 flag_second=0;
				}
		 }
		 //Kp�Ĳ�������
		  if(flag_second==0)
			{
				 if(KEY_Scan()==2)
				 {
					  Kp=Kp+Kp_add;
				 }
				 if(KEY_Scan()==3)
				 {
					  Kp=Kp-Kp_add;
				 }
				 if(Kp<=0)
				 {
					  Kp=0;
				 }
			}
		//Kd�Ĳ�������
			if(flag_second==1)
			{
				  if(KEY_Scan()==2)
				 {
					  Kd=Kd+Kd_add;
				 }
				 if(KEY_Scan()==3)
				 {
					  Kd=Kd-Kd_add;
				 }
				 if(Kd<=0)
				 {
					  Kd=0;
				 }
			}
			//Ki�Ĳ�������
				if(flag_second==2)
			{
				  if(KEY_Scan()==2)
				 {
					  Ki=Ki+Ki_add;
				 }
				 if(KEY_Scan()==3)
				 {
					  Ki=Ki-Ki_add;
				 }
				 if(Ki<=0)
				 {
					  Ki=0;
				 }
			}
	 }
	 //�ڶ����˵�ѡ��PID���������ı�
	if(flag_ensure==1&&flag_first==2)
	{
		 //ѡ��Ҫ���ڵĲ���
		 if(KEY_Scan()==1)
		 {
			  flag_second=flag_second+1;
			  if(flag_second>=3)
				{
					 flag_second=0;
				}
		 }
		 //Kp_add����
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
		 //Kd_add�ĵ���
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
		 //Ki_add�ĵ���
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
}



