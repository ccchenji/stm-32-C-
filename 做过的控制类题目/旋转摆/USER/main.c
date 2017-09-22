//////////////////////////////////////////////////////////////////////////////////
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//中景园电子
//店铺地址：http://shop73023976.taobao.com/?spm=2013.1.0.0.M4PqC2
//
//  文 件 名   : main.c
//  版 本 号   : v2.0
//  作    者   : HuangKai
//  生成日期   : 2014-0101
//  最近修改   :
//  功能描述   : OLED 4接口演示例程(51系列)
//              说明:
//              ----------------------------------------------------------------
//          GND    电源地
//              VCC  接5V或3.3v电源
//              D0   接PA5（SCL）
//              D1   接PA7（SDA）
//              RES  接PB0
//              DC   接PB1
//              CS   接PA4
//              ----------------------------------------------------------------
// 修改历史   :
// 日    期   :
// 作    者   : HuangKai
// 修改内容   : 创建文件
//版权所有，盗版必究。
//Copyright(C) 中景园电子2014/3/16
//All rights reserved
//******************************************************************************/
#include "ioi2c.h"
#include "delay.h"
#include "sys.h"
#include "oled.h"
#include "bmp.h"
#include "beep.h"
#include "key.h"
#include "filter.h"
#include "MPU6050.h"
#include "math.h"
#include "stdio.h"
#include "usart.h"
#include "timer.h"
#include "led.h"


#define PI 3.14159265

s8 flag = 0, key_flag = 0, pid_flag = 0, init_flag = 0, turn_flag = 2;
s8 choose = 0;
u8 Way_Angle = 3;
u8 arry[10], arry1[10];
u8 DELAY_FLAG = 0;
double Angle_Y = 0, Angle_X = 0, SET_Angle_Y = 10, SET_Angle_X = 0;
float Accel_Y, Accel_X, Accel_Z, Gyro_X, Gyro_Y;
float SDS_OutData[4] = { 0 };
float pid_out = 0;
float pid_out1 = 0;
float pid_out4 = 0;
float pid_out3 = 0;
float pid_out_sent = 0;
float max_angle = 0;


float err = 0;
float err_last = 0 ;
float PID_I = 0;

float err1 = 0;
float err_last1 = 0 ;
float PID_I1 = 0;

float err4 = 0;
float err_last4 = 0 ;
float PID_I4 = 0;

float err3 = 0;
float err_last3 = 0 ;
float PID_I3 = 0;

float Kp1 = 0;
float Ki1 = 0;
float Kd1 = 80000;
float Kp = 200; //0.4;
float Ki = 3;
float Kd = 80000;

int motor_forward_go = 35999; //->定时器通道1
int motor_back_go = 35999; //->定时器通道2
int motor_left_go = 35999; //->定时器通道3
int motor_right_go = 35999; //->定时器通道4
float Set_num = 0, annum = 0, err_next = 0, motorarr = 1000, pid_I;
float Set_num2 = 0, annum2 = 0, err2 = 0, err_next2 = 0, err_last2 = 0, pid_out2 = 0, motorarr2 = 1000, pid_I2;
float Kps = 1000, Kis = 2, Kds = 40000;
float startsp = 0;
float tarangle, range = 25, dangle = 0;
float tarangle2 = 0, dangle2 = 0;
float Gangle = 0, Gangle2 = 0, Aangle = 0;
float Accel_Y, Accel_X, Accl_Z, Gyro_Y, Accel_Y2, Gyro_X;
float st = 0;
int maxx, maxy, flagx = 0, flagy = 0;
float powerx = 0, powery = 0;
float pid_Is = 0, pid_Is2 = 0;
void pidmain(void);
void pidmain2(void);
void calctar(void);
void run(void);
void Get_Angle(u8 way)
{
    if(way == 1)                                    //DMP没有涉及到严格的时序问题，在主函数读取
    {
    }
    else
    {
        Gyro_X = (I2C_ReadOneByte(devAddr, MPU6050_RA_GYRO_XOUT_H) << 8) + I2C_ReadOneByte(devAddr, MPU6050_RA_GYRO_XOUT_L); //读取Y轴陀螺仪
        Gyro_Y = (I2C_ReadOneByte(devAddr, MPU6050_RA_GYRO_YOUT_H) << 8) + I2C_ReadOneByte(devAddr, MPU6050_RA_GYRO_YOUT_L); //读取Y轴陀螺仪
        Accel_Y2 = (I2C_ReadOneByte(devAddr, MPU6050_RA_ACCEL_YOUT_H) << 8) + I2C_ReadOneByte(devAddr, MPU6050_RA_ACCEL_YOUT_L); //读取X轴加速度记
        Accel_Z = (I2C_ReadOneByte(devAddr, MPU6050_RA_ACCEL_ZOUT_H) << 8) + I2C_ReadOneByte(devAddr, MPU6050_RA_ACCEL_ZOUT_L); //读取Z轴陀螺仪
        Accel_X = (I2C_ReadOneByte(devAddr, MPU6050_RA_ACCEL_XOUT_H) << 8) + I2C_ReadOneByte(devAddr, MPU6050_RA_ACCEL_XOUT_L); //读取X轴加速度记
        Gyro_Y = (short)Gyro_Y;
        Gyro_X = (short)Gyro_X;				//数据类型转换  也可通过short强制类型转换
        if(Accel_Z > 32768)  Accel_Z -= 65536;
        if(Accel_Y2 > 32768)  Accel_Y2 -= 65536;						//数据类型转换
        if(Accel_X > 32768) Accel_X -= 65536; //数据类型转换
        Accel_Y = atan2(Accel_X, Accel_Z) * 180 / PI;
        Aangle = Accel_Y;
        Accel_X = atan2(Accel_Y2, Accel_Z) * 180 / PI;				//计算与地面的夹角
        Gyro_Y = Gyro_Y / 16.4;                                //陀螺仪量程转换
        Gyro_X = Gyro_X / 16.4;
        Gangle2 = Gyro_Y;
        Gangle = Gyro_X;
        if(Way_Angle == 2)		  	Kalman_Filter(Accel_Y, -Gyro_Y); //卡尔曼滤波
        else if(Way_Angle == 3)
        {
            QingHua_AngelCalculate(Accel_Y, -Gyro_Y);   //互补滤波
            QingHua_AngelCalculate2(Accel_X, Gyro_X);
        }
        Angle_X = angle2 + 1;                               //更新平衡倾角
        Angle_Y = angle + 1;
        SDS_OutData[3] = Accel_Y * 100;
    }
}


unsigned short CRC_CHECK(unsigned char *Buf, unsigned char CRC_CNT)
{
    unsigned short CRC_Temp;
    unsigned char i, j;
    CRC_Temp = 0xffff;

    for (i = 0; i < CRC_CNT; i++) {
        CRC_Temp ^= Buf[i];
        for (j = 0; j < 8; j++) {
            if (CRC_Temp & 0x01)
                CRC_Temp = (CRC_Temp >> 1 ) ^ 0xa001;
            else
                CRC_Temp = CRC_Temp >> 1;
        }
    }
    return(CRC_Temp);
}

void SDS_OutPut_Data(float S_Out[])
{
    int temp[4] = {0};
    unsigned int temp1[4] = {0};
    unsigned char databuf[10] = {0};
    unsigned char i;
    unsigned short CRC16 = 0;
    float SDS_OutData[4];
    for(i = 0; i < 4; i++) {
        SDS_OutData[i] = S_Out[i];
    }
    for(i = 0; i < 4; i++)
    {

        temp[i]  = (int)SDS_OutData[i];
        temp1[i] = (unsigned int)temp[i];

    }

    for(i = 0; i < 4; i++)
    {
        databuf[i * 2]   = (unsigned char)(temp1[i] % 256);
        databuf[i * 2 + 1] = (unsigned char)(temp1[i] / 256);
    }

    CRC16 = CRC_CHECK(databuf, 8);
    databuf[8] = CRC16 % 256;
    databuf[9] = CRC16 / 256;

    for(i = 0; i < 10; i++)
        printf("%c", databuf[i]); //LINK TO UART
}
/***************************************主函数部分*****************************************/

int main(void)
{
    LED_Init();			     //LED端口初始化
    delay_init();                 //延时初始化
    NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
    uart_init(115200);          //初始化串口1
    OLED_Init();
    OLED_Clear();
    IIC_Init();                     //模拟IIC初始化
    MPU6050_initialize();           //=====MPU6050初始化
    // DMP_Init();                     //初始化DMP
    // TIM3_Int_Init(10,7199);//10Khz的计数频率，计数到5000为500ms
    TIM2_PWM_Init(35999, 0);	 //不分频。PWM频率=72000000/36000=8Khz
    TIM3_Int_Init(50, 7199); //10Khz的计数频率，计数到5000为500ms

    TIM_SetCompare1(TIM2, 35999 );
    TIM_SetCompare2(TIM2, 35999 );
    TIM_SetCompare3(TIM2, 35999 );
    TIM_SetCompare4(TIM2, 35999 );

    while(1)
    {

        Get_Angle(3);
        /***************************************虚拟示波器部分******************************************/
//	SDS_OutData[1]=powerx;
//  SDS_OutData[0]=powery;
//	SDS_OutData[2]=Angle_X*100;
//		SDS_OutData[3]=Angle_Y*100;
//
//  SDS_OutPut_Data(SDS_OutData);
        printf("%f\n", Angle_X);

//		 int a;

//
///***************************************数字转化部分******************************************/
        //printf("互 补 滤 波 输 出 Pitch:  %f\r\n  ",Angle_Balance);

        if(Angle_X > 0) {
            arry[0] = '+';
            arry[1] = (int)Angle_X / 1000 % 10 + '0';
            arry[2] = (int)Angle_X / 100 % 10 + '0';
            arry[3] = (int)Angle_X / 10 % 10 + '0';
            arry[4] = (int)Angle_X / 1 % 10 + '0';
        }
        else
        {
            arry[0] = '-';
            arry[1] = (int) - Angle_X / 1000 % 10 + '0';
            arry[2] = (int) - Angle_X / 100 % 10 + '0';
            arry[3] = (int) - Angle_X / 10 % 10 + '0';
            arry[4] = (int) - Angle_X / 1 % 10 + '0';

        }

        if(Angle_Y > 0) {
            arry1[0] = '+';
            arry1[1] = (int)Angle_Y / 1000 % 10 + '0';
            arry1[2] = (int)Angle_Y / 100 % 10 + '0';
            arry1[3] = (int)Angle_Y / 10 % 10 + '0';
            arry1[4] = (int)Angle_Y / 1 % 10 + '0';
        }
        else
        {
            arry1[0] = '-';
            arry1[1] = (int) - Angle_Y / 1000 % 10 + '0';
            arry1[2] = (int) - Angle_Y / 100 % 10 + '0';
            arry1[3] = (int) - Angle_Y / 10 % 10 + '0';
            arry1[4] = (int) - Angle_Y / 1 % 10 + '0';

        }
        OLED_ShowString(60, 0, arry, 0);
        OLED_ShowString(2, 0, arry1, 0);

        /***************************************菜单部分******************************************/
        if(choose == 0)
        {
            //OLED_ShowCHinese(0,0,0,flag==0);//菜
            //	OLED_ShowCHinese(16,0,1,flag==0);//单

            OLED_ShowCHinese(0, 2, 12, flag == 1); //基
            OLED_ShowCHinese(16, 2, 13, flag == 1); //础
            OLED_ShowCHinese(32, 2, 14, flag == 1); //部
            OLED_ShowCHinese(48, 2, 15, flag == 1); //分
            OLED_ShowCHinese(64, 2, 4, flag == 1); //一

            OLED_ShowCHinese(0, 4, 12, flag == 2); //基
            OLED_ShowCHinese(16, 4, 13, flag == 2); //础
            OLED_ShowCHinese(32, 4, 14, flag == 2); //部
            OLED_ShowCHinese(48, 4, 15, flag == 2); //分
            OLED_ShowCHinese(64, 4, 4, flag == 2); //一
            OLED_ShowString(80, 4, ",", flag == 2);
            OLED_ShowCHinese(87, 4, 5, flag == 2); //二

            OLED_ShowCHinese(0, 6, 16, flag == 3); //发
            OLED_ShowCHinese(16, 6, 17, flag == 3); //挥
            OLED_ShowCHinese(32, 6, 14, flag == 3); //部
            OLED_ShowCHinese(48, 6, 15, flag == 3); //分

        }
        /**************************************按键部分*****************************************/
        if(KEY0 == 0)
        {
            while(!KEY0);
            if(key_flag == 0)
                flag++;
            else
                Kp += 10;

        }
        if(KEY1 == 0)
        {
            while(!KEY1);

            if(key_flag == 0)
                flag--;
            else
                Kd += 1;


        }
        if(KEY2 == 0)
        {
            OLED_Clear();

            while(!KEY2);
            choose = 1;
        }
        if(KEY3 == 0)
        {   OLED_Clear();

            while(!KEY3);
            choose = 0;
            key_flag = 0;
            TIM_SetCompare1(TIM2, motor_forward_go = 35999 );
            TIM_SetCompare2(TIM2, motor_back_go = 35999 );
            TIM_SetCompare3(TIM2, motor_left_go = 35999 );
            TIM_SetCompare4(TIM2, motor_right_go = 35999);
            pid_flag = 0;
            max_angle = 0;
        }

        if(flag > 3)   flag = 0;
        if(flag < 0)   flag = 3;


        /**************************************菜单功能部分****************************************/
        if(choose == 1)
        {

            if(flag == 1)
            {

                if(max_angle == 0)
                    pid_flag = 1;

                //SET_Angle_Y=10;

                if(Angle_Y > 10)
                {

                    pid_flag = 2;
                    max_angle = 1;

                }


                key_flag = 1;
                //TIM_SetCompare3(TIM2,motor_forward_go=15000 );

                //TIM_SetCompare2(TIM2,motor_back_go=0 );

                //	TIM_SetCompare1(TIM2,motor_left_go=15000 );
                // TIM_SetCompare2(TIM2,motor_right_go=0 );

            }



            if(flag == 2)
            {
                SET_Angle_Y = 0;
                SET_Angle_X = 0;
                pid_flag = 3;



            }
            if(flag == 3)
            {

                pid_flag = 4;
            }

            //PID部分




        }

    }
}




//定时器2中断服务程序

int moarr = 18000;
void TIM3_IRQHandler(void)   //TIM2中断
{
    if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)  //检查TIM2更新中断发生与否
    {
        TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );
        //清除TIMx更新中断标志
        if(pid_flag == 1)
        {
            err = Angle_Y - SET_Angle_Y;
            pid_out = Kp * err + Ki * PID_I + Kd * (err - err_last);
            pid_out_sent = pid_out;
            PID_I += err;
            err_last = err;

            if(pid_out > 15000)   pid_out = 15000;
            if(pid_out < -15000)  pid_out = -15000;
            if(Angle_Y < 45 && Angle_Y > -45 )
            {
                TIM_SetCompare1(TIM2, 15000 + pid_out );
                TIM_SetCompare2(TIM2, 15000 - pid_out );
            }
            else
            {
                TIM_SetCompare3(TIM2, motor_left_go = 35999 );
                TIM_SetCompare4(TIM2, motor_right_go = 35999 );
            }
        }

        if(pid_flag == 2)
        {
            TIM_SetCompare1(TIM2, 36000 );
            TIM_SetCompare2(TIM2, 36000 );
            if(Gangle > 0 && Angle_Y > -4 && Angle_Y < 4)
                TIM_SetCompare2(TIM2, 20000 );
            if(Gangle < 0 && Angle_Y > -4 && Angle_Y < 4)
                TIM_SetCompare1(TIM2, 20000 );

        }

        if(pid_flag == 3)
        {
            err = SET_Angle_Y - Angle_Y;
            pid_out = Kp1 * err + Ki1 * PID_I + Kd1 * (err - err_last);
            PID_I += err;
            err_last = err;

            err1 = Angle_Y - SET_Angle_Y;
            pid_out1 = Kp1 * err1 + Ki1 * PID_I + Kd1 * (err1 - err_last1);
            PID_I1 += err1;
            err_last1 = err1;

            if(pid_out > 36000)   pid_out = 36000;
            if(pid_out < 0)  pid_out = 0;
            if(pid_out1 > 36000)   pid_out1 = 36000;
            if(pid_out1 < 0)  pid_out1 = 0;
            TIM_SetCompare1(TIM2, 36000 - pid_out );
            TIM_SetCompare2(TIM2, 36000 - pid_out1 );

            err4 = SET_Angle_X - Angle_X;
            pid_out4 = Kp1 * err4 + Ki1 * PID_I + Kd1 * (err4 - err_last4);
            PID_I4 += err4;
            err_last4 = err4;

            err3 = Angle_X - SET_Angle_X;
            pid_out3 = Kp1 * err3 + Ki1 * PID_I + Kd1 * (err3 - err_last3);
            PID_I3 += err3;
            err_last3 = err3;

            if(pid_out3 > 36000)   pid_out3 = 36000;
            if(pid_out3 < 0)  pid_out3 = 0;
            if(pid_out4 > 36000)   pid_out4 = 36000;
            if(pid_out4 < 0)  pid_out4 = 0;
            TIM_SetCompare4(TIM2, 36000 - pid_out4 );
            TIM_SetCompare3(TIM2, 36000 - pid_out3 );
        }


        if(pid_flag == 4)
        {
            calctar();
            // pidmain();
            // pidmain2();
            run();
            //printf("%f   %f   %f\n",Angle_X,Angle_Y,pid_out);
        }


    }


}
/*
void TIM3_IRQHandler(void)   //TIM2中断
{
	if (TIM_GetITStatus(TIM3,TIM_IT_Update ) != RESET)  //检查TIM2更新中断发生与否
		{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //清除TIMx更新中断标志


	     if(num<set_num)
	     {
		   		  	CKL=!CKL;
				      num++;
	     }
  	}


}
*/
void pidmain()
{
    Set_num = tarangle;
    err = Set_num - Angle_X;
    pid_out = Kps * err + Kis * pid_I + 50000 * (err - err_last);
    err_last = err;
    pid_I += err;
    if(pid_out > moarr)pid_out = moarr;
    if(pid_out < -moarr)pid_out = -moarr;
    if(pid_out > 0)
    {
        TIM_SetCompare3(TIM2, motor_back_go = moarr + pid_out );
        TIM_SetCompare4(TIM2, motor_forward_go = moarr - pid_out );
    }
    else
    {
        TIM_SetCompare3(TIM2, motor_back_go = moarr + pid_out );
        TIM_SetCompare4(TIM2, motor_forward_go = moarr - pid_out );
    }
}
void pidmain2()
{
    Set_num2 = tarangle2;
    err2 = Set_num2 + Angle_Y;
    pid_out2 = Kps * err2 + Kis * pid_I2 + Kds * (err2 - err_last2);
    err_last2 = err2;
    pid_I2 += err2;
    if(pid_out2 > moarr)pid_out2 = moarr;
    if(pid_out2 < -moarr)pid_out2 = -moarr;
    if(pid_out2 > 0)
    {
        TIM_SetCompare1(TIM2, motor_left_go = moarr + pid_out2 );
        TIM_SetCompare2(TIM2, motor_right_go = moarr - pid_out2 );
    }
    else
    {
        TIM_SetCompare1(TIM2, motor_left_go = moarr + pid_out2 );
        TIM_SetCompare2(TIM2, motor_right_go = moarr - pid_out2 );
    }
}
void calctar()
{
    tarangle = asin(range / 80) / PI * 180 * sin(dangle2);
    tarangle2 = asin(range / 80) / PI * 180 * cos(dangle2);
    dangle2 += 0.003;
}
float k = 5;
void run()
{
    if(flagx == 0)//起摆
    {
        for(k = 0; k < 100000; k++)
        {
            TIM_SetCompare4(TIM2, motor_left_go = 0 );
        }
        for(k = 0; k < 100000; k++)
        {
            TIM_SetCompare4(TIM2, motor_left_go = 35999 );
            TIM_SetCompare1(TIM2, motor_left_go = 0 );
        }
        flagx = 1;
    }
    TIM_SetCompare4(TIM2, motor_left_go = 35999 );
    TIM_SetCompare1(TIM2, motor_left_go = 35999 );
    Set_num2 = 20;
    if(Angle_Y * Angle_Y < 16)//如果Y轴摆动角度在一个小范围内，即低端时，准备调幅以及矫正相位
    {
        if(powery > 0)
            powery = Kps * err2 + Kis * pid_Is2;//通过偏差值获取电机幅度调节的输出力度
        else
            powery = Kps * -err2 + Kis * pid_Is2;
        pid_Is2 += err2;
        if(Gyro_X > 0)//判断X角速度来确定相位偏差方向，如果相位不偏的话当Y轴到达低端时X轴速度为0，X轴有速度就说明相位有偏
            for(k = 0; k < 800; k++)TIM_SetCompare3(TIM2, motor_left_go = 0 );//吹一下电机矫正相位
        else
            for(k = 0; k < 800; k++)TIM_SetCompare4(TIM2, motor_left_go = 0 );//吹一下电机矫正相位
        TIM_SetCompare3(TIM2, motor_left_go = 36000 );//电机停转
        TIM_SetCompare4(TIM2, motor_left_go = 36000 );//电机停转
        if(powery < 0)powery = -powery;
        if(powery > 35000)powery = 35000;
		
        if(Gangle2 > 0)//通过判断Y轴角速度来确定摆动方向
        {
            TIM_SetCompare2(TIM2, motor_left_go = 36000 - powery );//幅度调节电机输出
            //	TIM_SetCompare1(TIM2,motor_left_go=36000);
        }
        else
        {
            TIM_SetCompare1(TIM2, motor_left_go = 36000 - powery );//幅度调节电机输出
            //TIM_SetCompare2(TIM2,motor_left_go=36000 );
        }
    }
    else//如果不在底部，电机不转
    {
        TIM_SetCompare1(TIM2, motor_left_go = 36000 );
        TIM_SetCompare2(TIM2, motor_left_go = 36000 );
    }
    if(Angle_X * Angle_X < 1)//如果x轴角度接近0，记录当前Y轴角度即为Y轴摆动最大值
    {
        if(Angle_Y < 0)
        {
            Angle_Y = -Angle_Y;
            maxy = Angle_Y;
            Angle_Y = -Angle_Y;
        }
        else
        {
            maxy = Angle_Y;
        }
        err2 = Set_num2 - maxy;//计算Y轴摆动幅度偏差
    }
	//x轴原理和Y轴一样，以此类推就好
///////////////////////////////////////////////////////////////////////////////////////////////////////
    if(Angle_X * Angle_X < 16)
    {
        if(powerx > 0)
            powerx = Kps * err + Kis * pid_Is;
        else
            powerx = Kps * -err + Kis * pid_Is;
        pid_Is += err;
        if(Gyro_Y > 0)for(k = 0; k < 800; k++)TIM_SetCompare1(TIM2, motor_left_go = 0 );
        else
            for(k = 0; k < 800; k++)TIM_SetCompare2(TIM2, motor_left_go = 0 );
        TIM_SetCompare1(TIM2, motor_left_go = 36000 );
        TIM_SetCompare2(TIM2, motor_left_go = 36000 );
        if(powerx < 0)powerx = -powerx;
        if(powerx > 35000)powerx = 35000;
        if(Gangle > 0)
        {
            TIM_SetCompare4(TIM2, motor_left_go = 36000 - powerx );
            //	TIM_SetCompare3(TIM2,motor_left_go=36000 );
        }
        else
        {
            TIM_SetCompare3(TIM2, motor_left_go = 36000 - powerx );
            //	TIM_SetCompare4(TIM2,motor_left_go=36000 );
        }
    }
    else
    {
        TIM_SetCompare3(TIM2, motor_left_go = 36000 );
        TIM_SetCompare4(TIM2, motor_left_go = 36000 );
    }
    if(Angle_Y * Angle_Y < 1)
    {
        if(Angle_X < 0)
        {
            Angle_X = -Angle_X;
            maxx = Angle_X;
            Angle_X = -Angle_X;
        }
        else
        {
            maxx = Angle_X;
        }
        err = Set_num2 - maxx;
    }
}

