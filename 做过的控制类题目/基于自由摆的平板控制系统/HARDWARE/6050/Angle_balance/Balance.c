#include "Balance.h"
#include "filter.h"
#include "math.h"
#include "mpu6050.h"
float Angle_Balance_X;
float Angle_Balance_Y;
extern float N_Accel_Y;
extern float N_Accel_X;
extern float N_Gyro_Y;
float Accel_Y,Accel_X,Accel_Z,Gyro_X,Gyro_Y,Gyro_Z;
//对X轴的平滑滤波的参数
short laoma1=0;
short laoma2=1;
short laoma3=0;
double laomashuzu[10]={0};
double laomashuzu2[10]={0};
float laoma_sum=0;
float laoma_temp=0;
float averge_laoma=0;
void Get_Angle()
{ 
	    float Angle_X,Angle_Y;
	    Gyro_X=(MPU_Read_Byte(MPU_GYRO_XOUTH_REG)<<8)+MPU_Read_Byte(MPU_GYRO_XOUTL_REG);
			Gyro_Y=(MPU_Read_Byte(MPU_GYRO_YOUTH_REG)<<8)+MPU_Read_Byte(MPU_GYRO_YOUTL_REG);    //读取Y轴陀螺仪
	    Gyro_Z=(MPU_Read_Byte(MPU_GYRO_ZOUTH_REG)<<8)+MPU_Read_Byte(MPU_GYRO_ZOUTL_REG); 
		  Accel_X=(MPU_Read_Byte(MPU_ACCEL_XOUTH_REG)<<8)+MPU_Read_Byte(MPU_ACCEL_XOUTL_REG); //读取X轴加速度记
	    Accel_Y=(MPU_Read_Byte(MPU_ACCEL_YOUTH_REG)<<8)+MPU_Read_Byte(MPU_ACCEL_YOUTL_REG);
		  Accel_Z=(MPU_Read_Byte(MPU_ACCEL_ZOUTH_REG)<<8)+MPU_Read_Byte(MPU_ACCEL_ZOUTL_REG);    //读取Z加速度
	    if(Gyro_X>32768)  Gyro_X-= 65536;
	 		if(Gyro_Y>32768)  Gyro_Y-= 65536;     //数据类型转换  也可通过short强制类型转换
	    if(Gyro_Z>32768)  Gyro_Z-= 65536;
	  	if(Accel_X>32768) Accel_X-=65536;    //数据类型转换
	    if(Accel_Y>32768) Accel_Y-=65536;
	    if(Accel_Z>32768) Accel_Z-=65536;     //数据类型转换
 //对X轴的平滑滤波
	    if(laoma1<10)
			{
        laomashuzu[laoma1]= Accel_X;
	      laoma1++;
			}
			else
			{
				  for(laoma2=1;laoma2<10;laoma2++)
				{
				  laomashuzu[laoma2-1]=laomashuzu[laoma2];				
				}
				  laomashuzu[9]=Accel_X;
				for(laoma2=0;laoma2<10;laoma2++)
				{
					 laomashuzu2[laoma2]=laomashuzu[laoma2];
				}
				 for(laoma2=0;laoma2<9;laoma2++)
	      {
		       for(laoma3=0;laoma3<10-laoma2-1;laoma3++)
		      {
			     if(laomashuzu2[laoma3]>laomashuzu2[laoma3+1])
				   {
					  laoma_temp=laomashuzu2[laoma3];
					  laomashuzu2[laoma3]=laomashuzu2[laoma3+1];
					  laomashuzu2[laoma3+1]=laoma_temp;
			   	 }
		      }
    	  }
				for(laoma2=1;laoma2<9;laoma2++)
      	{
		     laoma_sum+=laomashuzu2[laoma2];
	      }
				averge_laoma=laoma_sum/8;
				laoma_sum = 0;
			}
	    
//X轴的角度
	    Angle_X=atan2(Accel_Y,Accel_Z)*180/PI;
	    Gyro_X=Gyro_X/16.4;
	   // Kalman_Filter(Angle_X,-Gyro_X);
	    Angle_Balance_X=angle;
//Y轴的角度
	   	Angle_Y=atan2(Accel_X,Accel_Z)*180/PI;                 //计算与地面的夹角	
		  Gyro_Y=Gyro_Y/16.4;                                    //陀螺仪量程转换	
			N_Gyro_Y=Gyro_Y;
 	  	Kalman_Filter(Angle_Y,-Gyro_Y);//卡尔曼滤波	
	    Angle_Balance_Y=angle;                                   //更新平衡倾角
}



