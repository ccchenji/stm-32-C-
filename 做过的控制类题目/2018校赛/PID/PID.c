#include "PID.H"
#include "IN.H"
//-----�ṹ���ڲ���Kp,Kd,Ki,err,err_last,PIDI,PID_Out
MyPID nowPID = { 8,90,0.1,0,0,0,0 };//��ʼ��PID�ṹ��//90
MyPID Speed_PID = { 0.7,0,0,0,0,0,0 };//��ʼ���ٶ�PID�ṹ��

float PID_Control(MyPID *PID, float set_Aim, float now_Aim)
{
	PID->err = set_Aim - now_Aim;//�õ����ֵ
	if (PID->err > 3 || PID->err < -3)PID->PID_Out = PID->Kp*PID->err + PID->Kd*(PID->err - PID->err_last) + PID->Ki*PID->PIDI;//����PID�����
	else PID->PID_Out = 0;
	PID->err_last = PID->err;
	if (PID->err<30 && PID->err>-30)//��һ����Χ�ڲŽ��л���
	{
		PID->PIDI += PID->err;
	}
	else
	{
		PID->PIDI = 0;
	}
	if (PID->PID_Out < 0)//��PID���������
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
	if (PID->PID_Out >= 900) PID->PID_Out = 900;//��PID������޷�
	if (PID->PID_Out <= 450)PID->PID_Out = 450;
	return PID->PID_Out;
}

float PIDSpeed_Control(MyPID *PID, float set_Aim, float now_Aim)
{
	PID->err = set_Aim - now_Aim;//�õ����ֵ
  if(PID->err>10||PID->err<-10)PID->PID_Out = PID->Kp*PID->err+PID->Kd*(PID->err-PID->err_last)+PID->Ki*PID->PIDI;//����PID�����,����ʽPID����
	else PID->PID_Out=0;
	if (PID->err<60 && PID->err>-60)//��һ����Χ�ڲŽ��л���
	{
		PID->PIDI += PID->err;
	}
	else
	{
		PID->PIDI = 0;
	}
	PID->err_last = PID->err;
	if (PID->PID_Out < 0)//��PID���������
	{
		PID->PID_Out = 0 - PID->PID_Out;
	}
	if (PID->PID_Out >= 900) PID->PID_Out = 900;//��PID������޷�
	if (PID->PID_Out <= 470)PID->PID_Out = 450;
	return PID->PID_Out;
}

