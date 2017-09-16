#include "Balance.h"
#include "filter.h"
#include "math.h"
#include "mpu6050.h"
float Angle_Balance;
extern float N_angle;
//放到定时器，定时5MS左右（因为角加速度需要积分才能得到角度）
void Get_Angle()
{ 
	    float Accel_Y,Accel_X,Accel_Z,Gyro_Y;
			Gyro_Y=(MPU_Read_Byte(MPU_GYRO_YOUTH_REG)<<8)+MPU_Read_Byte(MPU_GYRO_YOUTL_REG);    //读取Y轴陀螺仪
			Accel_Z=(MPU_Read_Byte(MPU_ACCEL_ZOUTH_REG)<<8)+MPU_Read_Byte(MPU_ACCEL_ZOUTL_REG);    //读取Z加速度
		  Accel_X=(MPU_Read_Byte(MPU_ACCEL_XOUTH_REG)<<8)+MPU_Read_Byte(MPU_ACCEL_XOUTL_REG); //读取X轴加速度记
	 		if(Gyro_Y>32768)  Gyro_Y-=65536;     //数据类型转换  也可通过short强制类型转换
			if(Accel_Z>32768)  Accel_Z-=65536;     //数据类型转换
	  	if(Accel_X>32768) Accel_X-=65536;    //数据类型转换
	   	Accel_Y=atan2(Accel_X,Accel_Z)*180/PI;                 //计算与地面的夹角	
		  Gyro_Y=Gyro_Y/16.4;                                    //陀螺仪量程转换	
 	  	Kalman_Filter(Accel_Y,-Gyro_Y);//卡尔曼滤波	
	    Angle_Balance=angle;                                   //更新平衡倾角
}



