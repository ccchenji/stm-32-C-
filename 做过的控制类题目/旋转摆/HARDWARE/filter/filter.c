#include "filter.h"
  /**************************************************************************
���ߣ�ƽ��С��֮��
�ҵ��Ա�С�꣺http://shop114407458.taobao.com/
**************************************************************************/
float K1 =0.15; 
float angle,angle2, angle_dot; 	
float Q_angle=0.001;// ����������Э����
float Q_gyro=0.003;//0.03 ����������Э���� ����������Э����Ϊһ��һ�����о���
float R_angle=0.5;// ����������Э���� �Ȳ���ƫ��
float dt=0.005;//                 
char  C_0 = 1;
float Q_bias, Angle_err;
float PCt_0, PCt_1, E;
float K_0, K_1, t_0, t_1;
float Pdot[4] ={0,0,0,0};
float PP[2][2] = { { 1, 0 },{ 0, 1 } };
float g_fCarAngle;
float g_fGyroscopeAngleIntegral;
float g_fGRAVITY_ADJUST_TIME_CONSTANT=1.5;
float DT=0.01;
float g_fCarAngle2;
float g_fGyroscopeAngleIntegral2;
float g_fGRAVITY_ADJUST_TIME_CONSTANT2=1.5;
float DT2=0.01;
/*------------------------------------------------
                 �廪�ں��˲�
��ڲ������Ƕȡ����ٶ�
���ڲ�������
˵����ȫ�ֱ�������Ƕ�
@Jassy 2016.5.12
------------------------------------------------*/
void QingHua_AngelCalculate(float G_angle,float Gyro)
{
  float fDeltaValue;
  g_fCarAngle = g_fGyroscopeAngleIntegral;
  fDeltaValue = (G_angle - g_fCarAngle) / g_fGRAVITY_ADJUST_TIME_CONSTANT ;
  g_fGyroscopeAngleIntegral += (Gyro*1.2 + fDeltaValue) * DT ;
  angle=g_fCarAngle;
}
void QingHua_AngelCalculate2(float G_angle,float Gyro)
{
  float fDeltaValue;
  g_fCarAngle2 = g_fGyroscopeAngleIntegral2;
  fDeltaValue = (G_angle - g_fCarAngle2) / g_fGRAVITY_ADJUST_TIME_CONSTANT2 ;
  g_fGyroscopeAngleIntegral2 += (Gyro*1.2 + fDeltaValue) * DT2 ;
  angle2=g_fCarAngle2;
}
/**************************************************************************
�������ܣ����׿������˲�
��ڲ��������ٶȡ����ٶ�
����  ֵ����
**************************************************************************/
void Kalman_Filter(float Accel,float Gyro)		
{
	angle+=(Gyro - Q_bias) * dt; //�������
	Pdot[0]=Q_angle - PP[0][1] - PP[1][0]; // Pk-����������Э�����΢��

	Pdot[1]=-PP[1][1];
	Pdot[2]=-PP[1][1];
	Pdot[3]=Q_gyro;
	PP[0][0] += Pdot[0] * dt;   // Pk-����������Э����΢�ֵĻ���
	PP[0][1] += Pdot[1] * dt;   // =����������Э����
	PP[1][0] += Pdot[2] * dt;
	PP[1][1] += Pdot[3] * dt;
		
	Angle_err = Accel - angle;	//zk-�������
	
	PCt_0 = C_0 * PP[0][0];
	PCt_1 = C_0 * PP[1][0];
	
	E = R_angle + C_0 * PCt_0;
	
	K_0 = PCt_0 / E;
	K_1 = PCt_1 / E;
	
	t_0 = PCt_0;
	t_1 = C_0 * PP[0][1];

	PP[0][0] -= K_0 * t_0;		 //����������Э����
	PP[0][1] -= K_0 * t_1;
	PP[1][0] -= K_1 * t_0;
	PP[1][1] -= K_1 * t_1;
		
	angle	+= K_0 * Angle_err;	 //�������
	Q_bias	+= K_1 * Angle_err;	 //�������
	angle_dot   = Gyro - Q_bias;	 //���ֵ(�������)��΢��=���ٶ�
}

/**************************************************************************
�������ܣ�һ�׻����˲�
��ڲ��������ٶȡ����ٶ�
����  ֵ����
**************************************************************************/
void Yijielvbo(float angle_m, float gyro_m)
{
   angle = K1 * angle_m+ (1-K1) * (angle + gyro_m * 0.005);
}
void Yijielvbo2(float angle_m, float gyro_m)
{
   angle2 = K1 * angle_m+ (1-K1) * (angle + gyro_m * 0.005);
}

