#ifndef __FILTER_H
#define __FILTER_H
  /**************************************************************************
���ߣ�ƽ��С��֮��
�ҵ��Ա�С�꣺http://shop114407458.taobao.com/
**************************************************************************/
extern float angle, angle_dot,angle2;
void Kalman_Filter(float Accel,float Gyro);		
void Yijielvbo(float angle_m, float gyro_m);
void QingHua_AngelCalculate(float G_angle,float Gyro);
void QingHua_AngelCalculate2(float G_angle,float Gyro);
void Yijielvbo2(float angle_m, float gyro_m);
#endif
