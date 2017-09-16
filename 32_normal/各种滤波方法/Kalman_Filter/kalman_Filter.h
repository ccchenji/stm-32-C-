/************************************************************************************
*   Copyright    ���ϴ�ѧ1209ʵ����
*   All   right   reserved.  
*   
*   �ļ����� :  Kalman_Filter.h
*   �ļ���ʶ :  �����ù���ƻ��� 
*   ժ       Ҫ :  �������˲������ⲿ����
*   ��ǰ�汾 :   V1.00               
*   ��       �� :  �                          
*   �������  :  2013/1/27
*    
*   ��֧�ֵ�оƬ : MC9S12DG128                            
*   ��֧�ֵı����� : CodeWarrior 5.X
     
*************************************************************************************/

#ifndef _KALMAN_FILTER_H
#define _KALMAN_FILTER_H

/////////////////////////////////////////
extern float Angle, Angle_dot; 		//�ⲿ��Ҫ���õı���

//////////////////////////////////////////
extern void Kalman_Filter(float angle_m,float gyro_m);
extern void complement_filter(float angle_m_cf,float gyro_m_cf);
#endif /*PORT_H END */
