/************************************************************************************
*   Copyright    济南大学1209实验室
*   All   right   reserved.  
*   
*   文件名称 :  Kalman_Filter.h
*   文件标识 :  见配置管理计划书 
*   摘       要 :  卡尔曼滤波程序外部声明
*   当前版本 :   V1.00               
*   作       者 :  李超                          
*   完成日期  :  2013/1/27
*    
*   所支持的芯片 : MC9S12DG128                            
*   所支持的编译器 : CodeWarrior 5.X
     
*************************************************************************************/

#ifndef _KALMAN_FILTER_H
#define _KALMAN_FILTER_H

/////////////////////////////////////////
extern float Angle, Angle_dot; 		//外部需要引用的变量

//////////////////////////////////////////
extern void Kalman_Filter(float angle_m,float gyro_m);
extern void complement_filter(float angle_m_cf,float gyro_m_cf);
#endif /*PORT_H END */
