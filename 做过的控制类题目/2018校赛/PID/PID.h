#ifndef _PID_H
#define _PID_H
#include <stdio.h>

//----------------------------PID¿ØÖÆÆ÷--------------------------------//
typedef struct _PID
{
	float Kp;
	float Kd;
	float Ki;
	float err;
	float err_last;
	float PIDI;
	float PID_Out;
}MyPID;


float PID_Control(MyPID *PID, float set_Aim, float now_Aim);
float PIDSpeed_Control(MyPID *PID, float set_Aim, float now_Aim);

#endif

