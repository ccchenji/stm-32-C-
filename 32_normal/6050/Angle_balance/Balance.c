#include "Balance.h"
#include "filter.h"
#include "math.h"
#include "mpu6050.h"
float Angle_Balance;
extern float N_angle;
//�ŵ���ʱ������ʱ5MS���ң���Ϊ�Ǽ��ٶ���Ҫ���ֲ��ܵõ��Ƕȣ�
void Get_Angle()
{ 
	    float Accel_Y,Accel_X,Accel_Z,Gyro_Y;
			Gyro_Y=(MPU_Read_Byte(MPU_GYRO_YOUTH_REG)<<8)+MPU_Read_Byte(MPU_GYRO_YOUTL_REG);    //��ȡY��������
			Accel_Z=(MPU_Read_Byte(MPU_ACCEL_ZOUTH_REG)<<8)+MPU_Read_Byte(MPU_ACCEL_ZOUTL_REG);    //��ȡZ���ٶ�
		  Accel_X=(MPU_Read_Byte(MPU_ACCEL_XOUTH_REG)<<8)+MPU_Read_Byte(MPU_ACCEL_XOUTL_REG); //��ȡX����ٶȼ�
	 		if(Gyro_Y>32768)  Gyro_Y-=65536;     //��������ת��  Ҳ��ͨ��shortǿ������ת��
			if(Accel_Z>32768)  Accel_Z-=65536;     //��������ת��
	  	if(Accel_X>32768) Accel_X-=65536;    //��������ת��
	   	Accel_Y=atan2(Accel_X,Accel_Z)*180/PI;                 //���������ļн�	
		  Gyro_Y=Gyro_Y/16.4;                                    //����������ת��	
 	  	Kalman_Filter(Accel_Y,-Gyro_Y);//�������˲�	
	    Angle_Balance=angle;                                   //����ƽ�����
}



