#include "PID.H"
#include "IN.H"
//-----结构体内部：Kp,Kd,Ki,err,err_last,PIDI,PID_Out
MyPID nowPID = { 8,90,0.1,0,0,0,0 };//初始化PID结构体//90
MyPID Speed_PID = { 0.7,0,0,0,0,0,0 };//初始化速度PID结构体

float PID_Control(MyPID *PID, float set_Aim, float now_Aim)
{
	PID->err = set_Aim - now_Aim;//得到误差值
	if (PID->err > 3 || PID->err < -3)PID->PID_Out = PID->Kp*PID->err + PID->Kd*(PID->err - PID->err_last) + PID->Ki*PID->PIDI;//计算PID的输出
	else PID->PID_Out = 0;
	PID->err_last = PID->err;
	if (PID->err<30 && PID->err>-30)//在一定范围内才进行积分
	{
		PID->PIDI += PID->err;
	}
	else
	{
		PID->PIDI = 0;
	}
	if (PID->PID_Out < 0)//将PID的输出归正
	{
		PID->PID_Out = 0 - PID->PID_Out;
		IN1 = 1;
		IN2 = 0;
	}
	else
	{
		IN1 = 0;
		IN2 = 1;
	}
	if (PID->PID_Out >= 900) PID->PID_Out = 900;//对PID的输出限幅
	if (PID->PID_Out <= 450)PID->PID_Out = 450;
	return PID->PID_Out;
}

float PIDSpeed_Control(MyPID *PID, float set_Aim, float now_Aim)
{
	PID->err = set_Aim - now_Aim;//得到误差值
  if(PID->err>10||PID->err<-10)PID->PID_Out = PID->Kp*PID->err+PID->Kd*(PID->err-PID->err_last)+PID->Ki*PID->PIDI;//计算PID的输出,增量式PID计算
	else PID->PID_Out=0;
	if (PID->err<60 && PID->err>-60)//在一定范围内才进行积分
	{
		PID->PIDI += PID->err;
	}
	else
	{
		PID->PIDI = 0;
	}
	PID->err_last = PID->err;
	if (PID->PID_Out < 0)//将PID的输出归正
	{
		PID->PID_Out = 0 - PID->PID_Out;
	}
	if (PID->PID_Out >= 900) PID->PID_Out = 900;//对PID的输出限幅
	if (PID->PID_Out <= 470)PID->PID_Out = 450;
	return PID->PID_Out;
}

