#include "control.h"
#include "sys.h"
struct  My_PID
{
	float err;
  float err_last;
  float Kp;
  float Kd;
  float Ki;
  float PID_O;
  float PIDI;	
};
struct My_PID PID1;//前
struct My_PID PID2;//后
struct My_PID PID3;//左
struct My_PID PID4;//右
extern float pitch;
extern float roll;
extern float long_roll;
extern float long_pitch;
/***************前面的风机*****************/
float PID_change1(float p,float d,float i)
{
	  PID1.Kp=p;
    PID1.Kd=d;
    PID1.Ki=i;	
	  return PID1.Kp;
}
double PID_Control(double set_angle)
{ 
	  PID1.err=set_angle-long_roll;
	  PID1.PID_O = PID1.Kp*PID1.err + PID1.Ki*PID1.PIDI+ PID1.Kd*(PID1.err-PID1.err_last);
	  PID1.err_last = PID1.err;
		if(PID1.err>=-5&&PID1.err<=5)
		{
	  PID1.PIDI = PID1.PIDI+PID1.err;
		}
		else
		{
			 PID1.PIDI=0;
		}	
		PID1.PID_O=0-PID1.PID_O;
		if(PID1.PID_O>=3599)PID1.PID_O=3599;
		if(PID1.PID_O<=1010)PID1.PID_O=1010;
		return PID1.PID_O;
}
/*****************后面的风机*******************/
float PID_change2(float p,float d,float i)
{
	  PID2.Kp=p;
    PID2.Kd=d;
    PID2.Ki=i;	
	  return 0;
}
double PID_Contro2(double set_angle)
{ 
	  PID2.err=set_angle-long_roll;
	  PID2.PID_O = PID2.Kp*PID2.err + PID2.Ki*PID2.PIDI+ PID2.Kd*(PID2.err-PID2.err_last);
	  PID2.err_last = PID2.err;
	  if(PID2.err<=5&&PID2.err>=-5)
	  {
		PID2.PIDI = PID2.PIDI+PID2.err;
	  }
		else
		{
			 PID2.PIDI=0;
		}
		if(PID2.PID_O>=3599)PID2.PID_O=3599;
		if(PID2.PID_O<=1010)PID2.PID_O=1010;
		return PID2.PID_O;
}
/*****************左面的风机*******************/
float PID_change3(float p,float d,float i)
{
	  PID3.Kp=p;
    PID3.Kd=d;
    PID3.Ki=i;	
	  return 0;
}
double PID_Contro3(double set_angle)
{ 
	  PID3.err=set_angle-long_pitch;
	  PID3.PID_O = PID3.Kp*PID3.err + PID3.Ki*PID3.PIDI+ PID3.Kd*(PID3.err-PID3.err_last);
	  PID3.err_last = PID3.err;
	  if(PID3.err<=3&&PID3.err>=-3)
		{
			PID3.PIDI=PID3.PIDI+PID3.err;
		}
		else
		{
			 PID3.PIDI=0;
		}
		if(PID3.PID_O>=3599)PID3.PID_O=3599;
		if(PID3.PID_O<=1010)PID3.PID_O=1010;
		return PID3.PID_O;
}
/*********************右面的风机*******************/
float PID_change4(float p,float d,float i)
{
	 PID4.Kp=p;
	 PID4.Kd=d;
	 PID4.Ki=i;
	 return 0;
}
double PID_Contro4(double set_angle)
{ 
	  PID4.err=set_angle-long_pitch;
	  PID4.PID_O = PID4.Kp*PID4.err + PID4.Ki*PID4.PIDI+ PID4.Kd*(PID4.err-PID4.err_last);
	  PID4.err_last = PID4.err;
	  if(PID4.err<=3&&PID4.err>=-3)
		{
	   	PID4.PIDI = PID4.PIDI+PID4.err;
	  }
		else
		{
			 PID4.PIDI=0;
		}
		PID4.PID_O=0-PID4.PID_O;
		if(PID4.PID_O>=3599)PID4.PID_O=3599;
		if(PID4.PID_O<=1010)PID4.PID_O=1010;
		return PID4.PID_O;
}

