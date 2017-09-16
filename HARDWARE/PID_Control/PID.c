#include "PID.h"
float err_X=0;
float err_last_X=0;
float PID_P_X=15;//10 //10
float PID_I_X=0.01;//0  //0.01
float PID_D_X=130;//70  //90
float PID_Out_X=0;
float PIDI_X=0;

float err_Y=0;
float err_last_Y=0;
float PID_P_Y=15;//20.06 //20.06
float PID_I_Y=0.01;//0  //0.01
float PID_D_Y=130;//75  //100
float PID_Out_Y=0;
float PIDI_Y=0;
int num_up_x = 0;
int num_up_y = 0;
float pid_x_lasterror_save[10] = {0};
float pid_y_lasterror_save[10] = {0};
extern short receive_date[2];


//X方向的PID
float PID_control_X(float Set_Aim)
{
	 err_X=Set_Aim-receive_date[0];
	 PID_Out_X=PID_P_X*err_X+PID_D_X*(err_X-pid_x_lasterror_save[0])+PIDI_X*PID_I_X;
	 if(num_up_x>10)num_up_x = 0;
	
	  pid_x_lasterror_save[num_up_x]=err_X;
	
	 num_up_x++;
	 if(err_X<35&&err_X>-35)
	 {
		  PIDI_X+=err_X;
	 }
	 else
	 {
		 PIDI_X=0; 
	 }
	 if(err_X<=4&&err_X>=-4)
	 {
		  PID_Out_X=0;
	 }
	 if(PID_Out_X<=-200)PID_Out_X=-200;
	 if(PID_Out_X>=200)PID_Out_X=200;
	 return PID_Out_X;
}



//Y方向的PID
float PID_control_Y(float Set_Aim)
{
	 err_Y=Set_Aim-receive_date[1];
	 PID_Out_Y=PID_P_Y*err_Y+PID_D_Y*(err_Y-pid_y_lasterror_save[num_up_y])+PIDI_Y*PID_I_Y;
	
	if(num_up_y>10)
	{
		 num_up_y=0;
	}
	
	 pid_y_lasterror_save[num_up_y]=err_Y;
   num_up_y++;
	
	
	 if(err_Y<35&&err_Y>-35)
	 {
		  PIDI_Y+=err_Y;
	 }
	 else
	 {
		 PIDI_Y=0; 
	 }
	 if(err_Y<=4&&err_Y>=-4)
	 {
		  PID_Out_Y=0;
	 }
	 if(PID_Out_Y<=-200)PID_Out_Y=-200;
	 if(PID_Out_Y>=200)PID_Out_Y=200;
	 return PID_Out_Y;
}




